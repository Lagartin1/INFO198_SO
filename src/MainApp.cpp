#include "../include/MainApp.h"
#include "MenuControls.cpp"

int main(int argc, char *argv[]){
    int opt;
    string user, pass, text, vect, num;
    map<string, Usuario> users;
    string USERSPATH = getenv("TXT_FILE_PATH");

    while ((opt = getopt(argc, argv, "u:p:t:v:n:")) != -1){
        switch (opt)
        {
        case 'u':
            user = optarg;
            break;
        case 'p':
            pass = optarg;
            break;
        case 't':
            text = string(optarg);
            break;
        case 'v':
            vect = string(optarg);
            break;
        case 'n':
            num = optarg;
            break;
        }
    }
    if (user.empty() && pass.empty()){
        cout << "Error: Debe ingresar un usuario y contraseña" << endl;
        exit(EXIT_FAILURE);
    }
   
    extractUsers(users, USERSPATH);
    verificarEntradadas(text, vect, num);
    cout << "\n";
    cout << "=========================================="<<endl;
    // verificacion si usuario y contraseña es correcto 
    verificarUsuario(user, pass);
    if (users.find(user) != users.end() && users[user].getPass() == pass){
        cout << "Bienvenido \n" << "Usuario: "<<user <<" Rol: " << users[user].getTipo() <<endl;
        printf("PID: %d\n", getpid());
        Usuario u = users[user];
        menu(text, vect, num,u,users);
    }
    else{
        cout << "Error: Usuario o contraseña incorrectos" << endl;
        exit(EXIT_FAILURE);
    }
}
