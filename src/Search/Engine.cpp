#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string response(string resultado,int n); 
void sendMessageToCache(string texto);
string resultado(string palabra, string &pathIndex);
string palabraCompuesta(string palabra,string &pathIndex,int topk);



int main() {
    string pathIndex = getenv("INVERTED_INDEX");
    int topk = stoi(getenv("TOPK"));
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("Error al configurar SO_REUSEADDR y SO_REUSEPORT");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2021);  // Usando el puerto 2021
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error en bind motor");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd, 1) == -1) {
        perror("Error en listen motor");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    while (true) {
        // Aceptar conexión del cliente (buscador)
        int client_fd = accept(socket_fd, nullptr, nullptr);
        if (client_fd == -1) {
            perror("Error en accept motor");
            continue;
        }
        // Recibir la operación del planificador
        char buffer[1024];
        int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == -1) {
            perror("Error al recibir la palabra, motor");
            close(socket_fd);
            continue;
        }
        buffer[bytes_received] = '\0';
        string palabra = buffer;
        if (palabra == "!!") {
            send(client_fd, "success", 7, 0);
            close(socket_fd);
            exit(EXIT_SUCCESS);
        }else{
            string respuesta;

            // palabra_
            // palabra1_palabra2 
            if ((palabra.find(' ')!= string::npos) && palabra.size()){
                respuesta = palabraCompuesta(palabra,pathIndex,topk);
            }else{ 
                respuesta = response(resultado(palabra, pathIndex),topk);
            }
            send(client_fd, respuesta.c_str(), respuesta.size(), 0);
            close(client_fd);
        }

    }
    close(socket_fd);
}



string resultado(string palabra, string &pathIndex) {
    // Leer el archivo de índices invertidos
    ifstream file(pathIndex);
    string line,content;
    bool found = false;
    while (getline(file, line) && (!found) )  {
        stringstream ss(line);
        string word;
        getline(ss, word, ';');
        if (word == palabra) {
            getline(ss, content);
            found = true;
        }
    }
    file.close();
    if (found) {
        return content;
    }
    return "-1";
}

string response(string resultado, int n) {
    if (resultado == "-1") {
        return resultado;
    }
    int i = 0;
    string response="",t;
    istringstream iss(resultado);
    while(i<n && getline(iss,t,';')){
        i++;
        response+=t + ";";
    }
    return response;
}


string palabraCompuesta(string palabra, string &pathIndex,int topk){
    vector<string> respuestas; 
    istringstream iss(palabra);
    for(string p; iss >> p;){
        string resp = response(resultado(p,pathIndex),topk);
        if (resp != "-1"){
            respuestas.push_back(resp);
        }
    }
    if (respuestas.size() == 0){
        return "-1";
    }
    map<string,int> resp;
    for(int i = 0;i< static_cast<int>(respuestas.size()) ;i++){
        string t,id,cant;
        istringstream iss2(respuestas[i]);
        while( getline(iss2,t,';')){
            t.erase(0,1);
            size_t pos = t.find(',');
            id = t.substr(0,pos);
            cant = t.substr(pos+1);
            cant.pop_back();
            resp[id]+=stoi(cant);
        }
    }

    // Convertimos el map en un vector de pares
    vector<pair<string, int>> elementos(resp.begin(), resp.end());

    // Ordenamos el vector en función de los valores en orden descendente
    sort(elementos.begin(), elementos.end(), [](const auto& a, const auto& b) {
        return a.second > b.second; // Orden descendente
    });
    
    string respond = "";
    for(const auto& par : elementos){
            respond+= '(' + par.first + ',' + to_string(par.second) + ");";
    }
    return respond;
}
