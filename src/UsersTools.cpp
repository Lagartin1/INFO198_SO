#include "../include/UsersTools.h"

void extractUsers(map <string,string> &users) {
    const char* csvFilePath = getenv("CSV_FILE_PATH");

    if (csvFilePath == nullptr) {
        cout << "Error: la variable de entorno CSV_FILE_PATH no está configurada." << endl;
        cout << "Configure la variable de entorno CSV_FILE_PATH con la ruta del archivo csv, de la forma especificada en el archvio README.md" << endl;
        exit(EXIT_FAILURE);
    }
    ifstream file(csvFilePath);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << std::endl;
        cout << "Verifique que existe el archvio Users.csv y que la variable de entorno CSV_FILE_PATH este correctamente configurada" << endl;
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

bool verificarUsuario(string user, string pass, map<string,string> &users){
    // Usuario con menos de 3 letras
    if (user.length() < 3) {
        cout << "Error: El usuario debe tener al menos 3 letras" << endl;
        exit(EXIT_FAILURE); 
    }
    // pass con menos de 6 caracteres
    if (pass.length() < 6) {
        cout << "Error: Usuario o contraseña incorrectos" << endl;
        exit(EXIT_FAILURE); 
    }
    // usuario contiene numeros
    for (char c : user) {
        if (isdigit(c)) {
            cout << "Error: El usuario no puede contener números" << endl;
            exit(EXIT_FAILURE);
        }
    }
    // pass contiene caracteres que no son letras ni números
    for (char c : pass) {
        if (!isalnum(c)) {
            cout << "Error: Usuario o contraseña incorrectos" << endl;
            exit(EXIT_FAILURE); 
        }
    }
    // verificacion si usuario y contraseña es correcto 
    if (users.find(user) != users.end() && users[user] == pass){
        return true;
    }
    return false;
}



