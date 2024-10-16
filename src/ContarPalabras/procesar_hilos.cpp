#include "../../include/procesar_hilos.h"
using namespace std;

// Mutex declaration outside of functions for shared access control
mutex mtx;

void extraerStopwords(vector<string>& stopwords,string filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo de stopwords." << endl;
        return;
    }
    string word;
    while (file >> word) {  // Leer cada palabra del archivo suponiendo que hay una palabra por linea
        stopwords.push_back(word);
    }
    file.close();
}


// Función que cada hilo ejecutará, con mutex para control de acceso
void procesarArchivoConMutex(const string& pathIN, const string& name, const string& pathOut,int id, string extension,vector<string> &stopwords) {
    // Bloquear el acceso a los archivos mientras se abre y procesa el archivo de entrada
    {
        lock_guard<std::mutex> lock(mtx);  // Protege solo esta sección
        ifstream file(pathIN + "/" + name);
        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << pathIN + "/" + name << endl;
            return;
        }
        
        // Procesamiento del archivo
        map<string, int> palabras;
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string palabra;
            while (ss >> palabra) {
                string cleanWord = "";
                for (char c : palabra) {
                    if (isalpha(c) || isLetterWithAccent(c)) {
                        cleanWord += tolower(c);
                    }
                }
                if (!cleanWord.empty()){
                    if ( find(stopwords.begin(), stopwords.end(), cleanWord) == stopwords.end()){
                        palabras[cleanWord]++;
                    }

                }
            }
        }
        file.close();
        
        // Escribir los resultados en el archivo de salida
        ofstream outFile(pathOut + "/" + to_string(id) + extension);
        if (!outFile.is_open()) {
            cout << "Error: No se pudo abrir el archivo de salida " << pathOut + "/" + name << endl;
            return;
        }

        for (const auto& item : palabras) {
            outFile << item.first << ";" << item.second << endl;
        }
        outFile.close();

        cout << "Archivo " << pathIN + "/" + name << ", " << palabras.size() << " palabras distintas" << endl;
    }
}

void procesarArchivosConHilos(const string& extension, const string& carpetaEntrada, const string& carpetaSalida, size_t numHilos,vector<string> &stopwords) {
    vector<thread> hilos;
    vector<string> archivos;

    // Recolectar archivos con la extensión dada
    for (const auto& entry : fs::directory_iterator(carpetaEntrada)) {
        if (entry.path().extension() == extension) {
            archivos.push_back(entry.path().filename().string());
        }
    }

    // Crear hilos para procesar archivos
    for (size_t i = 0; i < archivos.size(); ++i) {
        if (hilos.size() >= numHilos) {
            for (auto& hilo : hilos) {
                hilo.join();  // Espera a que los hilos terminen
            }
            hilos.clear();  // Reiniciar el vector de hilos
        }

        // Llamar a la función procesarArchivoConMutex en un hilo
        hilos.emplace_back([&, i]() { 
            procesarArchivoConMutex(carpetaEntrada, archivos[i], carpetaSalida,i,extension,stopwords); 
        });
    }

    // Unir los hilos restantes
    for (auto& hilo : hilos) {
        hilo.join();
    }
}




int main(int argc, char* argv[]) {
    unsigned int hilosDisponibles = std::thread::hardware_concurrency();


    // Estos datos hay que traerlos de variables de entorno
    string extension = ".txt";  
    string carpetaEntrada = "../in/libros";
    string carpetaSalida = "../out"; 
    int numHilos = stoi(getenv("CANTIDAD_THREAD")); 
    string carpetaMap = getenv("MAPA_ARCHIVOS");
    string stopWordPath = getenv("STOP_WORDS");
    int opcion;
    vector<string> stopwords;
    extraerStopwords(stopwords,stopWordPath);

    if (numHilos > static_cast<int>(hilosDisponibles)){
        cout << "Error: Superaste la cantidad de hilos disponibles" << endl << endl;
        cout << "Programa finalizado" << endl;
        return 0;
    }
    // Si PONES  ./app default se lanza este de inmediato
    if (argc > 1 && string(argv[1]) == "default") {
        cout << "Ejecutando con valores por defecto." << endl;
        cout << "Procesando archivos con " << numHilos << " hilos...\n" << endl;
        procesarArchivosConHilos(extension, carpetaEntrada, carpetaSalida, numHilos,stopwords);
        cout << "El proceso de conteo de palabras ha finalizado.\n" << endl;
        generarArchivoConIDs(carpetaEntrada,carpetaMap,extension);
        return 0; 
    }

    // Sino este con ./app
    cout << "=============================================" << endl;
    cout << "Bienvenido al programa de conteo de palabras CON HILOS." << endl;

    do {
        cout << "                Menu        " << endl;
        cout << "=============================================" << endl;
        cout << "Seleccione una opcion:" << endl;
        cout << "(0) Salir" << endl;
        cout << "(1) Ingrese la extension de archivos a procesar (ej: .txt)" << endl;
        cout << "(2) Ingrese el path de la carpeta de entrada (ej: /home)" << endl;
        cout << "(3) Ingrese el path de la carpeta de salida (ej: /home)" << endl;
        cout << "(4) Ingrese la cantidad de hilos a utilizar: ";
        cin >> opcion;

        // Limpiar el buffer
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                cout << "Ingrese la extension de archivos a procesar (ej: .txt): ";
                cin >> extension;
                while (!extension.empty() && extension[0] != '.') {
                    cout << "Error: La extensión ingresada debe ser de la forma '.<extencion>' (ej: .txt, .csv)" << endl;
                    cout << "Ingrese la extension de archivos a procesar (ej: .txt): ";
                    cin >> extension;
                }
                break;

            case 2:
                cout << "Ingrese el path de la carpeta de entrada: ";
                getline(cin, carpetaEntrada);
                while ((!carpetaExiste(carpetaEntrada)) || (carpetaEntrada ==carpetaSalida)) {
                    if ((carpetaEntrada ==carpetaSalida)){
                        cout << endl << "Error: La carpeta de entrada es la misma que la de salida" << endl << endl;
                    }
                    else{cout << endl << "Error: La carpeta de entrada no existe." << endl << endl;
                    }
                    
                    carpetaEntrada.clear(); 
                    cin.clear();   
                    cout << "Ingrese el path de la carpeta de entrada: ";
                    getline(cin, carpetaEntrada);
                    
                };
                break;

            case 3:
                cout << "Ingrese el path de la carpeta de salida: ";
                getline(cin, carpetaSalida);
                while((!carpetaExiste(carpetaSalida)) || (carpetaEntrada == carpetaSalida) ) {
                    if ((carpetaEntrada ==carpetaSalida)){
                        cout << endl << "Error: La carpeta de salida es la misma que la de entrada" << endl << endl;
                    }
                    else{cout << "Error: La carpeta de salida no existe." << endl;}
                    carpetaSalida.clear(); 
                    cin.clear();
                    cout << "Ingrese el path de la carpeta de salida: ";
                    getline(cin, carpetaSalida);
                }
                break;

            case 4:
                // Obtener la cantidad de hilos disponibles
                cout << endl << endl;
                cout << "Este sistema puede utilizar hasta " << hilosDisponibles << " hilos." << endl << endl;

                cout << "Ingrese la cantidad de hilos a utilizar: ";
                cin >> numHilos;

                if (cin.fail() || numHilos <= 0 || numHilos > static_cast<int>(hilosDisponibles)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (numHilos > static_cast<int>(hilosDisponibles)) {
                        cout << "Error: Ha ingresado un número mayor al máximo de hilos disponibles (" << hilosDisponibles << ")." << endl;
                    } else {
                        cout << "Error: Debe ingresar un número entero positivo." << endl;
                    }
                    continue; // Volver al inicio del do-while
                }

                if (extension.empty() || carpetaEntrada.empty() || carpetaSalida.empty()) {
                    cout << "Error: Debe ingresar todos los datos antes de procesar." << endl;
                } else if (!archivosConExtensionExisten(extension, carpetaEntrada)) {
                    cout << "Error: No hay archivos con la extensión indicada en la carpeta de entrada." << endl;
                } else {
                    cout << "Procesando archivos con " << numHilos << " hilos...\n" << endl;
                    procesarArchivosConHilos(extension, carpetaEntrada, carpetaSalida, numHilos,stopwords);
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
        cout << "=============================================" << endl;

    } while (opcion != 0);

    return 0;
}
