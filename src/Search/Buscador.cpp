#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <locale>


using namespace std;


void search();
bool isExtit(string search);


int main() {
    locale::global(locale("es_ES.UTF-8"));
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Error al crear el proceso hijo" << endl;
        exit(EXIT_FAILURE);
    }else if(pid == 0 ){
        execl("./cache","cache",nullptr);
        perror("Error al ejecutar cache");
    }else {
        sleep(2); //espera para que se inicie el cache y motor
        cout << "================================="<< endl;
        cout << "   Bienvenido al Buscador" << endl;
        cout << "================================="<< endl;;
        cout << "Escribe 'salir ahora' para salir" << endl;
        while (true){
            search();
        }
    }
}

bool isExtit(string search){
    search.erase(remove_if(search.begin(), search.end(), ::isspace), search.end());
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    return search == "salirahora";
}


void sendMessageToCache(string texto){
    //enviar mensaje a cache
    int socket_fd;
    struct  sockaddr_in server_addr;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2020);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al conectar con el cache");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    send(socket_fd, texto.c_str(), texto.size(), 0);
    char buffer[1024];
    int bytes_received = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        perror("Error al recibir la palabra");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_received] = '\0';
    string contenido = buffer;
    if (contenido != "success"){
        cout << "Resultado: " << contenido << endl;
    }
    close(socket_fd);

    
}
void search(){
    cout << "Buscar -> ";
    string search;
    getline(cin,search);
    if (isExtit(search)){
        // llamar a cache para que termine mensaje será (exit)
        // terminar
        sendMessageToCache("!!");
        cout << "Saliendo..." << endl;
        exit(EXIT_SUCCESS);
    }else{
        //llamar a cache y mostrar contenido
        sendMessageToCache(search);
    }
    cout << endl;
}