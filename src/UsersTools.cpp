#include "../include/UsersTools.h"

void extractUsers(map <string,string> &users) {
    ifstream file("../Data/Users.csv");
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << std::endl;
        exit(EXIT_FAILURE);
    }
    string lines;
    while (getline(file, lines)) {
        // lineas de la forma user;pass
        stringstream line(lines);
        string user, pass;
        getline(line, user, ';');
        getline(line, pass, ';');
        users[user] = pass;
    }
    file.close();
}

void borrarConsola(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
