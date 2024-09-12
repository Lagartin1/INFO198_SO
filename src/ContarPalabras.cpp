#include "../include/ContarPalabras.h"


bool carpetaExiste(const string& path) {
    return fs::exists(path) && fs::is_directory(path);
}

bool archivosConExtensionExisten(const string& extension, const string& carpeta) {
    for (const auto& entry : fs::directory_iterator(carpeta)) {
        if (entry.path().extension() == extension) {
            return true;
        }
    }
    return false;
}

void procesar(const string& extension, const string& carpetaEntrada, const string& carpetaSalida) {
    for (const auto& entry : fs::directory_iterator(carpetaEntrada)) {
        if (entry.path().extension() == extension) {
            procesarArchivo(carpetaEntrada,entry.path().filename(), carpetaSalida);
        }
    }
}

void procesarArchivo(string pathIN,string name, string pathOut){
    ifstream file(pathIN+"/"+name);
    map<string, int> palabras;
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << endl;
    }else{
        //procesar cada linea del archivo y cada palabra
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string palabra;
            while (ss >> palabra) {
                if (palabras.find(palabra) != palabras.end()){
                    palabras[palabra] += 1;
                }else{
                    palabras[palabra] = 1;
                }
            }
        }
        file.close();
        //escribir en el archivo de salida
        ofstream outFile(pathOut+"/"+name);
        if (!outFile.is_open()) {
            cout << "Error: No se pudo abrir el archivo de salida" << endl;
        }else{
            for (auto const& item : palabras){
                outFile << item.first << ";" << item.second << endl;
            }
            outFile.close();

        }
        cout << "Archivo " << pathIN <<"/" << name<< " ," << palabras.size()<< " palabras distintas" << endl;
    }
}

int main() {
    cout << "=============================================" <<endl;
    cout << "Bienvenido al programa de conteo de palabras." << endl;
    cout << "pid: " << getpid() << endl;
    cout << "=============================================" <<endl;

    string extension, carpetaEntrada, carpetaSalida;
    int opcion;

    do {
        while (true) {
            try {
                cout << "                Menu        " <<endl;
                cout << "=============================================" <<endl;
                cout << "Seleccione una opcion:" << endl;
                cout << "(0) Salir" << endl;
                cout << "(1) Ingrese la extension de archivos a procesar (ej: .txt)" << endl;
                cout << "(2) Ingrese el path de la carpeta de entrada (ej: /home)" << endl;
                cout << "(3) Ingrese el path de la carpeta de salida (ej: /home)" << endl;
                cout << "(4) Procesar" << endl;
                cout << "Opción: ";
                cin >> opcion;

                if (cin.fail()) {

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    throw runtime_error("Entrada no válida. Por favor, ingrese un número entero.");
                }
                cin.ignore();
                break;
            } catch (const runtime_error& e) {
            
                cout << e.what() << endl;
            }
        }
        switch (opcion) {
            case 1:
                cout << "Ingrese la extension de archivos a procesar (ej: .txt): ";
                cin >> extension;
                while (!extension.empty() && extension[0] != '.'){
                    cin.clear();
                    cout << "Error: La extensión ingresada debe ser de la forma '.<extencion> '(ej: .txt , .csv)" << endl;
                    cout << "Ingrese la extension de archivos a procesar (ej: .txt): ";
                    cin >> extension;
                }
                break;

            case 2:
                cout << "Ingrese el path de la carpeta de entrada: ";
                getline(cin, carpetaEntrada);
                while (!carpetaExiste(carpetaEntrada) ) {
                    cout << endl << "Error: La carpeta de entrada no existe." << endl << endl;
                    carpetaEntrada.clear(); 
                    cin.clear();   
                    cout << "Ingrese el path de la carpeta de entrada: ";
                    getline(cin, carpetaEntrada);
                }
                break;

            case 3:
                cout << "Ingrese el path de la carpeta de salida: ";
                getline(cin, carpetaSalida);
                while(!carpetaExiste(carpetaSalida)) {
                    cout << "Error: La carpeta de salida no existe." << endl;
                    carpetaSalida.clear(); 
                    cin.clear();
                    cout << "Ingrese el path de la carpeta de salida: ";
                    getline(cin, carpetaSalida);
                }
                break;

            case 4:
              
                if (extension.empty() || carpetaEntrada.empty() || carpetaSalida.empty()) {
                    cout << "Error: Debe ingresar todos los datos antes de procesar." << endl;
                } else if (!archivosConExtensionExisten(extension, carpetaEntrada)) {
                    cout << "Error: No hay archivos con la extensión indicada en la carpeta de entrada." << endl;
                } else {
                    cout << "Procesando archivos...\n" << endl;
                    procesar(extension, carpetaEntrada, carpetaSalida);
                    cout << "El proceso de conteo de palabras ha finalizado.\n" << endl;
                }
                break;

            case 0:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
            
        }
        cout << "=============================================" <<endl;

    } while (opcion != 0 ) ;

    return 0;
}
