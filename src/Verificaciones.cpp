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
        cout << "Error: El texto ingresado esta vacio" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (!isalpha(text[i]) && text[i] != ' ') {
            cout << "Error: El texto ingresado no es un texto valido, solo puede contener letras y espacios" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

void verificarVector(string vect){
    int n = vect.length();
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
        cout << "Precaución: No ingresó un texto,algunas opciones no estarán disponibles" << endl;
        c++;
    }else{
        verificarTexto(text);
    }
    if (vect.empty()){
        cout << "Precaución: No ingresó un vector,algunas opciones no estarán disponibles" << endl;
        c++;
    }else{
        verificarVector(vect);
    }
    if(num.empty()){
        cout << "Precaución: No ingresó un numero,algunas opciones no estarán disponibles" << endl;
        c++;
    }else{
        verificarNumero(num);
    }
    if (c >=3 ){
        cout << "\nError: No se ingresaron los parámetros necesarios. El programa no puede continuar." << endl;
        exit(EXIT_FAILURE);
    }
}