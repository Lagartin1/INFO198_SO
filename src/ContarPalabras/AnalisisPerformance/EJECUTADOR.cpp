#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>  // Para getenv
#include <chrono>   // Para medir el tiempo
#include <string>   // Para std::string
#include <thread>   // Para this_thread::sleep_for (opcional si quieres hacer pausas entre ejecuciones)
#include <iomanip>  // Para formatear la salida del tiempo
#include <fstream>  // Para manejar archivos

using namespace std;
using namespace std::chrono;

// Función para convertir la cadena de ARRAY_THREADS en un vector de enteros
vector<int> convertirArrayThreads(const string& str) {
    vector<int> resultado;
    stringstream ss(str);
    string token;

    // Separar la cadena por comas
    while (getline(ss, token, ',')) {
        resultado.push_back(stoi(token));  // Convertir cada token en entero y agregar al vector
    }

    return resultado;
}

int main() {
    // Obtener la variable de entorno ARRAY_THREADS
    char* arrayThreadsCStr = getenv("ARRAY_THREADS");
    if (arrayThreadsCStr == nullptr) {
        cerr << "Error: La variable de entorno ARRAY_THREADS no está definida." << endl;
        return 1;
    }
    string arrayThreadsStr = string(arrayThreadsCStr);

    // Convertir la cadena en un vector de enteros
    vector<int> arrayThreads = convertirArrayThreads(arrayThreadsStr);

    // Obtener la variable de entorno COUNT_WITH_THREADS
    char* countThreadCStr = getenv("COUNT_WITH_THREADS");
    if (countThreadCStr == nullptr) {
        cerr << "Error: La variable de entorno COUNT_WITH_THREADS no está definida." << endl;
        return 1;
    }
    string countThread = string(countThreadCStr);

     char* graphPyCStr = getenv("GRAPH_PYTHON_PATH");
    if (countThreadCStr == nullptr) {
        cerr << "Error: La variable de entorno COUNT_WITH_THREADS no está definida." << endl;
        return 1;
    }
    string graphCommand = "python3 " + string(graphPyCStr);

    // Definir el número de repeticiones
    int repeticiones = stoi(getenv("REPETICIONES"));
    if (repeticiones < 2){
        cout << "Error: cantidad de repeticiones inferior a 2" << endl;
        return 0;
    }
    string pathDatos = getenv("GRAPH_DATA");
    
    // Abrir el archivo para escribir los datos
    ofstream archivo("/home/vicntea/INFO198_SO/src/ContarPalabras/AnalisisPerformance/variablesEntorno/DATOS.txt", ios::trunc);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo DATOS.txt para escritura." << endl;
        return 1;
    }

    // Para cada valor en ARRAY_THREADS, ejecutar el comando y medir el tiempo
    for (int j = 0; j < repeticiones; j++) {
        for (int numHilos : arrayThreads) {
            // Concatenar el número de hilos al comando
            string comando = countThread + " " + to_string(numHilos);

            // Medir el tiempo de ejecución
            auto inicio = high_resolution_clock::now();

            int res = system(comando.c_str());
            
            auto fin = high_resolution_clock::now();
            auto duracion_ns = duration_cast<nanoseconds>(fin - inicio).count();

            // Verificar si el comando se ejecutó correctamente
            if (res != 0) {
                cerr << "Error al ejecutar el programa con " << numHilos << " hilos." << endl;
                continue;
            }

            // Convertir a segundos
            double duracion_seg = duracion_ns / 1e9;  // Convertir a segundos
            archivo << numHilos << "," << fixed << setprecision(6) << duracion_seg << "; ";
        }
        archivo << endl;  // Nueva línea después de cada repetición
    }

    archivo.close();  // Cerrar el archivo

    cout << "Análisis de rendimiento completado. Resultados guardados en DATOS.txt." << endl;

    int res = system(graphCommand.c_str());
    if (res == 0) {
        std::cout << "El script se ejecutó correctamente." << std::endl;
    } else {
        std::cerr << "Error al ejecutar el script." << std::endl;
    }
    return 0;
}

