#include "UsersTools.cpp"
#include "TextTools.cpp"
#include "NumTools.cpp"
#include <map>

void menu(string& text, string v, string& num, Usuario user,map<string, Usuario> &users) {
    string MapaFilePath = getenv("MAPA_ARCHIVOS");
    bool isAdmin ; 
    if (user.getTipo() == "Admin"){
        isAdmin = true;
    }else{
        isAdmin = false;
    }
    while (true) {
        string option; 
        cout << "=========================================="<<endl;
        cout << "           Menu de opciones" << endl;
        cout << "==========================================" << endl;
        cout << "0. Salir" << endl;
        cout << "1. Verificar si un string es palindromo" << endl;
        cout << "2. Contar vocales de un String" << endl;
        cout << "3. Contar letras de un string " << endl;
        cout << "4. Calcular promedio y sumatoria de un vector" << endl;
        cout << "5. Calcular una f(x)=5x*x + 1/x" << endl;
        cout << "6. Contar palabras" << endl;
        cout << "7. Conteo paralelo con threads"  << endl;
        cout << "8. Crear indice invertido" << endl;
        cout << "9. Analisis de performance"<<endl;
        cout << "10. Planificador"<<endl;
        if (isAdmin){
            cout << "11. Listar usuarios" << endl;
            cout << "12. Agregar usuario" << endl;
            cout << "13. Eliminar usuario" << endl;
        }
        cout << "Ingrese una opcion: ";
        getline(cin, option);
        if (option == "0") {
            cout << "Adios " << user.getUser() << endl;
            exit(EXIT_SUCCESS);
        }else if (option == "1") {
            cout<< "\n" <<endl;
            isPalindrome(text);   
        }else if (option == "2") {
            countVocals(text);                
        }
        else if (option == "3") {
            cout<< "\n" <<endl;
            countLetters(text);
        }
        else if (option == "4") {
            cout<< "\n" <<endl;
            operarVector(v);
        }
        else if (option == "5") {
            cout<< "\n" <<endl;
            if (num.find(",") != string::npos){
                calculateFunc(static_cast<float> (stof(num)));
            }else{
                calculateFunc(static_cast<int> (stoi(num)));
            }
        }else if (option == "6") {
            cout<< "\n" <<endl;
            string wordcount = getenv("COUNTWORDS_OUT");
            int res = system(wordcount.c_str());
            if (res != 0){
                cout << "Error al ejecutar el programa" << endl;
            }
        }else if (option == "7") {
            cout<< "\n" <<endl;
            string wordthreads = getenv("COUNTWORD_THREADS_OUT");
            int res = system(wordthreads.c_str());
            if (res != 0){
                cout << "Error al ejecutar el programa" << endl;
            }
        }else if (option == "8") {
            cout<< "\n" <<endl;
            ifstream file(MapaFilePath);
            if (file) {
                file.close();
                string pathIndex = getenv("INVERTED_INDEX");
                string invertedIndexApp = getenv("INVERTED_OUT");
                string orden = invertedIndexApp +" " +pathIndex;
                int res = system(orden.c_str());
                if (res != 0){
                    cout << "Error al ejecutar el programa" << endl;
                }
            }else{
                cout << "Error: No se ha ejecutado la opcion (7) Contar palabras con hilo" << endl;
            }
            
        }else if(option == "9"){
            cout<< "\n" <<endl;
            string performance = getenv("PERFORMANCE_OUT");
            int res = system(performance.c_str());
            if (res != 0){
                cout << "Error al ejecutar el programa" << endl;
            }
        }else if(option == "10"){
            cout<< "\n" <<endl;
            string planificador = getenv("PLANIFICADOR_OUT");
            system(planificador.c_str());

        }else if(option == "10" && isAdmin){
            cout<< "\n" <<endl;
            listUsers(users);
        }else if (option == "11" && isAdmin){
            cout<< "\n" <<endl;
            addUser(users);
        }else if (option == "12" && isAdmin){
            cout<< "\n" <<endl;
            deleteUser(users);
        }else{
            borrarConsola();
            cout << "\nOpcion no valida \nIngrese nuevamente" << endl;
        }
        cout << "\nPresione enter para continuar" << endl;
        cin.ignore();
        borrarConsola();
    }
}