#include "../include/MainApp.h"

int main(int argc, char *argv[]){
    int opt;
    string user, pass, text, vect, num;
    map<string, string> users;

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
   
    extractUsers(users);
    int c = 0;
    cout << "\n";
    if (text.empty()){
        cout << "Error: No ingresó un texto,no podra utilizar algunas de las opciones" << endl;
        c++;
    }else{
        verificarTexto(text);
    }
    if (vect.empty()){
        cout << "Error: No ingresó un vector,no podra utilizar algunas de las opciones" << endl;
        c++;
    }else{
        verificarVector(vect);
    }
    if(num.empty()){
        cout << "Error: No ingresó un numero,no podra utilizar algunas de las opciones" << endl;
        c++;
    }else{
        verificarNumero(num);
    }
    if (c >=3 ){
        cout << "\nError: No ingresó los parametros requeridos (<texto>  <lista de numeros enteros> <numero entero> ) para la ejecucion" << endl;
        exit(EXIT_FAILURE);
    }
    cout << "\n";
    cout << "=========================================="<<endl;
    if (verificarUsuario(user, pass, users)){
        cout << " Bienvenido " << user << endl;
        menu(text, vect, num, user);
    }
    else{
        cout << "Error: Usuario o contraseña incorrectos" << endl;
        exit(EXIT_FAILURE);
    }
}
