#include "NumTools.cpp"
#include "TextTools.cpp"
#include "UsersTools.cpp"
void continueprog(string user){
    cout << "\nDesea Continuar ?[C:continuar / S:Salir ] ";
    string option2;
    cin >> option2;
    while ((option2 != "C" && option2 != "c") && (option2 != "S" && option2 != "s"))
    {
        cout << "\nOpcion no valida, Ingrese [C:continuar / S:Salir ] ";
        cin >> option2;
    }
    if (option2 == "S" || option2 == "s")
    {
        cout << "Adios " << user << endl;
        exit(EXIT_SUCCESS);
    }
    cout << "\n";
}

void menu(string& text, string v, string& num, string user) {
    while (true) {
        string option;
         cout << "=========================================="<<endl;
        cout << "1. Verificar si un string es palindromo" << endl;
        cout << "2. Contar vocales de un String" << endl;
        cout << "3. Contar letras de un string " << endl;
        cout << "4. Calcular promedio y sumatoria de un vector" << endl;
        cout << "5. Calcular una f(x)=5x*x + 1/x" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> option;
        if (option == "1") {
            if (!text.empty()) {
                cout<< "\n" <<endl;
                isPalindrome(text);   
            }else{
                cout << "\nOpcion no valida,no se ha ingresado un texto" << endl;
            }
            continueprog(user);
        }
        else if (option == "2") {
            if (!text.empty()) {
                cout<< "\n" <<endl;
                countVocals(text);
            }else {
                cout << "\nOpcion no valida,no se ha ingresado un texto" << endl;
            }
            continueprog(user);
                
        }
        else if (option == "3") {
            if (!text.empty()) {
                cout<< "\n" <<endl;
                countLetters(text);
                
            }else{
                cout << "\nOpcion no valida,no se ha ingresado un texto" << endl;
            }
            continueprog(user);
        }
        else if (option == "4") {
            if (!v.empty()){
                cout<< "\n" <<endl;
                vector<int> vector_v;
                rellenarVector(vector_v,v);
                averageAndSumVector(vector_v);
            }else{
                cout << "\nOpcion no valida,no ha ingresado un vecotor" << endl;
            }
            continueprog(user);
        }
        else if (option == "5") {
            if(!num.empty()){
                cout<< "\n" <<endl;
                if (num.find(".") != string::npos || num.find(",") != string::npos){
                    calculateFunc(static_cast<float> (stof(num)));
                }else{
                    calculateFunc(static_cast<int> (stoi(num)));
                }
            }
            else{
                cout << "\nOpcion no valida,no ha ingresado un numero" << endl;
            }
            continueprog(user);
        }
        else if (option == "6") {
            cout << "Adios " << user << endl;
            exit(EXIT_SUCCESS);
        }else{
            borrarConsola();
            cout << "\nOpcion no valida \nIngrese nuevamente" << endl;
        }
    }
}
