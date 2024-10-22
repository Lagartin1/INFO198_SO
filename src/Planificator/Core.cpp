#include <iostream>
#include <string>
#include <fstream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sstream>
using namespace std;

string operar(int num1,int num2,string operation);
string operar(float num1,float num2,string operation);

int main() {
    int server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error al crear el socket");
        return 1;
    }

    // Estructura de la dirección del socket
    struct sockaddr_un server_addr;
    server_addr.sun_family = AF_UNIX;
    string socket_dir = getenv("SOCKET_DIR");
    socket_dir += "/sCore";
    strcpy(server_addr.sun_path, socket_dir.c_str());

    // Eliminar un socket previo si existe
    unlink(socket_dir.c_str());

    // Asignar la dirección al socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error en bind core");
        close(server_socket);
        return 1;
    }
    if (listen(server_socket, 1) == -1) {
            perror("Error en listen");
            close(server_socket);
            return 1;
    }
     while (true) {
        // Aceptar conexión
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket == -1) {
            perror("Error en accept core");
            continue;
        }

        // Recibir la operación
        char buffer[256];
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0 ) {
            perror("Error al recibir la operación");
            close(client_socket);
            continue;
        }
        buffer[bytes_received] = '\0';

        // (formato operacion;num1,num2)
        stringstream ss(buffer);
        string operacion, num1_str, num2_str;
        getline(ss, operacion, ';');
        getline(ss, num1_str, ',');
        getline(ss, num2_str, ';');
        // Convertir los números a enteros o flotantes
        string resultado_str;
        // Verificar si los números son flotantes
        if (num1_str.find(".") != string::npos || num2_str.find(".") != string::npos){
            resultado_str = operar(stof(num1_str),stof(num2_str),operacion);
        }else{
            resultado_str = operar(stoi(num1_str),stoi(num2_str),operacion);
        // Enviar el resultado al distribuidor;
        }
        send(client_socket, resultado_str.c_str(), resultado_str.size(), 0);
        // Cerrar el socket del cliente
        close(client_socket);
    }

}

string operar(int num1,int num2,string operation){
    int resultado;
    if (operation == "suma"){
        resultado = num1 + num2;
    }else if (operation == "resta"){
        resultado = num1 - num2;
    }else if (operation == "multiplicacion"){
        resultado = num1 * num2;
    }else if (operation == "division"){
        resultado = num1 / num2;
    }
    return to_string(resultado);
}

string operar(float num1,float num2,string operation){
    float resultado;
    if (operation == "suma"){
        resultado = num1 + num2;
    }else if (operation == "resta"){
        resultado = num1 - num2;
    }else if (operation == "multiplicacion"){
        resultado = num1 * num2;
    }else if (operation == "division"){
        resultado = num1 / num2;
    }
    return to_string(resultado);
}