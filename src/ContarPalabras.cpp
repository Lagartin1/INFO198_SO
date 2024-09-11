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

void contarPalabrasTotalesEnCarpeta(const string& carpetaEntrada, const fs::path& archivoSalida) {
    ofstream outFile(archivoSalida, ios::app); 
    if (!outFile) {
        cerr << "Error al abrir el archivo de salida: " << archivoSalida << endl;
        return;
    }

    map<string, int> contadorPalabras;
    string palabra;


    for (const auto& entry : fs::directory_iterator(carpetaEntrada)) {
        if (entry.path().extension() == ".txt") {  
            ifstream inFile(entry.path());
            if (!inFile) {
                cerr << "Error al abrir el archivo de entrada: " << entry.path() << endl;
                continue;
            }
            // Contar las palabras del archivo actual
            while (inFile >> palabra) {
                ++contadorPalabras[palabra];
            }
        }
    }


    for (const auto& entry : contadorPalabras) {
        outFile << entry.first << ";" << entry.second << endl;
    }

    cout << "Archivo de salida: " << archivoSalida << " procesado. Conteo total de palabras guardado." << endl;
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
        cin.clear();
        cout << "Seleccione una opcion:" << endl;
        cout << "(0) Salir" << endl;
        cout << "(1) Ingrese la extension de archivos a procesar (ej: .txt)" << endl;
        cout << "(2) Ingrese el path de la carpeta de entrada (ej: /home)" << endl;
        cout << "(3) Ingrese el path de la carpeta de salida (ej: /home)" << endl;
        cout << "(4) Procesar" << endl;
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1:
                cout << "Ingrese la extension de archivos a procesar (ej: .txt): ";
                cin >> extension;
                cin.ignore(); 
                break;

            case 2:
                cout << "Ingrese el path de la carpeta de entrada: ";
                getline(cin, carpetaEntrada);
                if (!carpetaExiste(carpetaEntrada)) {
                    cout << endl << "Error: La carpeta de entrada no existe." << endl << endl;
                    carpetaEntrada.clear(); 
                }
                cout << carpetaEntrada << endl;
                break;

            case 3:
                cout << "Ingrese el path de la carpeta de salida: ";
                getline(cin, carpetaSalida);
                if (!carpetaExiste(carpetaSalida)) {
                    cout << "Error: La carpeta de salida no existe." << endl;
                    carpetaSalida.clear(); 
                }
                break;

            case 4:
              
                if (extension.empty() || carpetaEntrada.empty() || carpetaSalida.empty()) {
                    cout << "Error: Debe ingresar todos los datos antes de procesar." << endl;
                } else if (!archivosConExtensionExisten(extension, carpetaEntrada)) {
                    cout << "Error: No hay archivos con la extensión indicada en la carpeta de entrada." << endl;
                } else {
                    procesar(extension, carpetaEntrada, carpetaSalida);
                    cout << "El proceso de conteo de palabras ha finalizado." << endl;
                }
                break;

            case 0:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
            
        }

    } while (opcion != 0);

    return 0;
}
