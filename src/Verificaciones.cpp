#include "../include/Verificaciones.h"

void verificarNumero(string num){
    int n = num.length();
    if (n == 0) {
        cout << "Error: El numero ingresado esta vacio" << endl;
        exit(EXIT_FAILURE);
    }
    int commaCount = 0;    
    for (int i = 0; i < n; i++) {
        if (!isdigit(num[i]) && num[i] != ',') {
            cout << "Error: El numero ingresado no es un numero,el separador decimal debe ser coma (,) o no contener en caso de ser entero " << endl;
            exit(EXIT_FAILURE);
        }
        if (num[i] == ',') {
            commaCount++;
            if (commaCount > 1) {
                cout << "Error: El numero ingresado contiene mas de una coma" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void verificarTexto(string text){
    int n = text.length();
    if (n == 0) {
        cout << "Error: La frase ingresada esta vacia" << endl;
        exit(EXIT_FAILURE);
    }
}

void verificarVector(string vect){
    int n = vect.length();
    if ( n == 0) {
        cout << "Error: El vector ingresado esta vacio" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (!isdigit(vect[i]) && vect[i] != ';') {
            cout << "Error: El vector ingresado no es valido, solo puede contener numeros enteros separados por punto y coma (;)" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

void verificarEntradadas(string text, string vect, string num){
    int c = 0;
    cout << "\n";
    if (text.empty()){
        cout << "Error: No se ingreso una frase" << endl;
        c++;
    }
    if(vect.empty()){
        cout << "Error: No se ingreso un vector" << endl;
        c++;
    }
    if(num.empty()){
        cout << "Error: No se ingreso un numero" << endl;
        c++;
    }
    if (c>0){
        exit(EXIT_FAILURE);
    }
    return;
    
}