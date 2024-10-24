#include <iostream>
#include <string>
#include <fstream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sstream>



using namespace std;


string sendMessageCore(string operacion,string num1,string num2);


int main() {
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error al crear el proceso hijo" << endl;
        exit(EXIT_FAILURE);
    }else if(pid == 0 ){
        execl("./core","core",nullptr);
        perror("Error al ejecutar el core");

    }else {
        sleep(3); //espera para que se inicie el distribuidor
        // Crear un socket Unix
        int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
        if (server_socket == -1) {
            perror("Error al crear el socket");
            return 1;
        }

        // Estructura de la dirección del socket
        string socketdir = getenv("SOCKET_DIR");
        socketdir+="/sDistrib";
        struct sockaddr_un server_addr;
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path,socketdir.c_str());

        // Eliminar un socket previo si existe
        unlink(socketdir.c_str());

        // Asignar la dirección al socket
        if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            perror("Error en bind distribuidor");
            close(server_socket);
            return 1;
        }

        // Escuchar conexiones
        if (listen(server_socket, 1) == -1) {
            perror("Error en listen");
            close(server_socket);
            return 1;
        }
        while (true) {
            // Aceptar conexión del cliente (planificador)
            int client_socket = accept(server_socket, nullptr, nullptr);
            if (client_socket == -1) {
                perror("Error en accept distribuidor");
                continue;
            }

            // Recibir la operación del planificador
            char buffer[1024];
            int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received == -1) {
                perror("Error al recibir la operación");
                close(client_socket);
                continue;
            }
            buffer[bytes_received] = '\0';

            // Parsear la operación recibida
            stringstream ss(buffer);
            string core_id, operation, num1, num2;
            getline(ss, core_id, ';');
            getline(ss, operation, ';');
            getline(ss, num1, ',');
            getline(ss, num2, ';');
            // llamar a core con socket
            string resultado = sendMessageCore(operation, num1, num2);
            // Escribir el resultado en el archivo de resultados
            ofstream resultados(getenv("RESULTADOS"),ios::app);
            if (resultados.is_open()) {
                string escribir = "(" + core_id + ";" + operation + ";" + num1 + "," + num2 + ";" + ")=>" + resultado;
                resultados << escribir<<endl;
                resultados.close();
            }else{
                cerr << "Error: No se pudo abrir el archivo de resultados" << endl;

            }
            // Cerrar el socket del cliente
            close(client_socket);
        }

        // Cerrar el socket del servidor
        close(server_socket);
        return 0;
    }
}



string sendMessageCore(string operacion,string num1,string num2){
    int socket_fd;
    struct sockaddr_un server_addr;

    // Crear un socket Unix
    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del socket
    server_addr.sun_family = AF_UNIX;
    string socket_dir = getenv("SOCKET_DIR");
    socket_dir += "/sCore";
    strcpy(server_addr.sun_path, socket_dir.c_str());

    // Conectar al socket del programa operación
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al conectar al programa core");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    // Enviar la operación al programa operación
    stringstream ss;
    ss << operacion << ";" << num1 << "," << num2;
    string operacion_str = ss.str();
    send(socket_fd, operacion_str.c_str(), operacion_str.size(), 0);

    // Recibir el resultado del programa operación
    char buffer[128];
    int bytes_received = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
    }
    // Cerrar el socket
    close(socket_fd);
    return string(buffer);
}
