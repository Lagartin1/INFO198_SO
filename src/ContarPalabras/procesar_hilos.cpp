#include "../../include/procesar_hilos.h"
#include <unordered_set> // Para unordered_set
#include <queue>         // Para queue
#include <condition_variable> // Para condition_variable
#include <atomic>       // Para atomic
using namespace std;

mutex mtx;
condition_variable cv;
queue<pair<string, int>> tareas; // Cola de tareas
atomic<bool> tareasFinalizadas{false}; // Indica si todas las tareas han sido asignadas

// Reemplazar vector<string> por unordered_set para stopwords
void extraerStopwords(unordered_set<string>& stopwords, string filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo de stopwords." << endl;
        return;
    }
    string word;
    while (file >> word) {
        stopwords.insert(word); // Usar insert para unordered_set
    }
    file.close();
}

// Procesar archivos con mutex para control de acceso
void procesarArchivoConMutex(const string& pathIN, const string& name, const string& pathOut, int id, const string& extension, unordered_set<string>& stopwords) {
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
            if (!cleanWord.empty() && stopwords.find(cleanWord) == stopwords.end()) {
                palabras[cleanWord]++;
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

// Función que cada hilo ejecutará
void hiloProcesador(const string& pathIN, const string& pathOut, const string& extension, unordered_set<string>& stopwords) {
    while (true) {
        pair<string, int> tarea;

        {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [] { return !tareas.empty() || tareasFinalizadas.load(); }); // Espera a que haya tareas o que se hayan finalizado
            if (tareasFinalizadas.load() && tareas.empty()) break; // Termina si no hay más tareas
            tarea = tareas.front();
            tareas.pop();
        }

        procesarArchivoConMutex(pathIN, tarea.first, pathOut, tarea.second, extension, stopwords);
    }
}

void procesarArchivosConHilos(const string& extension, const string& carpetaEntrada, const string& carpetaSalida, size_t numHilos, unordered_set<string>& stopwords) {
    vector<thread> hilos;

    // Recolectar archivos con la extensión dada
    for (const auto& entry : fs::directory_iterator(carpetaEntrada)) {
        if (entry.path().extension() == extension) {
            tareas.push({entry.path().filename().string(), static_cast<int>(tareas.size())}); // Agregar tarea a la cola
        }
    }

    // Crear hilos para procesar archivos
    for (size_t i = 0; i < numHilos; ++i) {
        hilos.emplace_back(hiloProcesador, carpetaEntrada, carpetaSalida, extension, ref(stopwords));
    }

    // Indicar que se han asignado todas las tareas
    {
        lock_guard<mutex> lock(mtx);
        tareasFinalizadas.store(true);
    }
    cv.notify_all(); // Notificar a todos los hilos

    // Unir los hilos
    for (auto& hilo : hilos) {
        hilo.join();
    }
}


int main(int argc, char* argv[]) {
    unsigned int hilosDisponibles = std::thread::hardware_concurrency();


    // Estos datos hay que traerlos de variables de entorno
    string extension = ".txt";  
    string carpetaEntrada = getenv("CARPETA_ENTRADA");
    string carpetaSalida = getenv("CARPETA_SALIDA");
    int numHilos = stoi(getenv("CANTIDAD_THREAD")); 
    string carpetaMap = getenv("MAPA_ARCHIVOS");
    string stopWordPath = getenv("STOP_WORDS");
    int opcion;
    unordered_set<string> stopwords;
    extraerStopwords(stopwords,stopWordPath);

    if (numHilos > static_cast<int>(hilosDisponibles)){
        cout << "Error: Superaste la cantidad de hilos disponibles" << endl << endl;
        cout << "Programa finalizado" << endl;
        return 0;
    }
    
    // Si ejecutamos como ./app3 -h 3  entonces, ejecutará el procesador con las stopwords con esa cantidad de hilos
    if (argc > 2 && string(argv[1]) == "-h") {
        numHilos = atoi(argv[2]); // Convertir el argumento a entero
        cout << "Procesando archivos con " << numHilos << " hilos...\n" << endl;
        procesarArchivosConHilos(extension, carpetaEntrada, carpetaSalida, numHilos, stopwords);
        cout << "El proceso de conteo de palabras ha finalizado.\n" << endl;
        return 0;
        // Aquí NO se genera el archivo con IDs

    } else if (argc > 1 && string(argv[1]) == "default") {
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
