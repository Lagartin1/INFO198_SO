#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <locale>
#include <map>
#include <cstring>
#include <fstream>

using namespace std;


void leerMAP(map<string,string> &map, string mpPath);
void desempaquetar(string resultdado,map<string,string> &mp);
void search(map<string,string> &mp);
bool isExtit(string search);
string sendMessageToCache(string texto);

int main() {
    locale::global(locale("es_ES.UTF-8"));
    string mpPath = getenv("MAPA_ARCHIVOS");
    map<string,string> mp;
    leerMAP(mp,mpPath);
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
            search(mp);
        }
    }
}

bool isExtit(string search){
    search.erase(remove_if(search.begin(), search.end(), ::isspace), search.end());
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    return search == "salirahora";
}


string sendMessageToCache(string texto){
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
        cout << "Resultado: " << endl;
        close(socket_fd);
        return contenido;
    }
    close(socket_fd);
    return "";
}
void search(map<string,string> &mp){
    cout << "Buscar -> ";
    string search,respuesta;
    getline(cin,search);
    if (isExtit(search)){
        // llamar a cache para que termine mensaje será (exit)
        // terminar
        sendMessageToCache("!!");
        cout << "Saliendo..." << endl;
        exit(EXIT_SUCCESS);
    }else{
        //llamar a cache y mostrar contenido
        respuesta = sendMessageToCache(search);
        desempaquetar(respuesta,mp);
    }
    cout << endl;
}


void desempaquetar(string resultado,map<string,string> &mp){
    if (resultado != "-1"){
        istringstream iss(resultado);
        string palabra;
        int ln = 1;
        while (getline(iss,palabra,';')){
            palabra.erase(0,1);
            size_t pos = palabra.find(',');
            string id = palabra.substr(0,pos);
            string cant = palabra.substr(pos+1);
            cant.pop_back();
            cout <<"("<< ln++ <<") Puntaje: " << cant << " -  " << mp[id] << endl;
        }
    }else{
        cout << "No se encontraron resultados" << endl;
    }
}


void leerMAP(map<string,string> &map, string mpPath){
    ifstream file(mpPath);
    string line;
    while (getline(file,line)){
        size_t pos = line.find_last_of(',');
        if (pos != string::npos) {
            // El nombre del archivo es desde el inicio hasta la última coma
            string nombre = line.substr(0, pos);
            // El ID es desde la posición después de la última coma hasta el final de la línea
            string id = line.substr(pos + 1);
            map[id] = nombre;
        }
    }
    file.close();
}