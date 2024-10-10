#include "../../include/ContarPalabrasUtils.h"


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


void generarArchivoConIDs(const std::string& carpetaEntrada, const std::string& carpetaSalida, const std::string& extension) {
    // Construir la ruta completa del archivo de salida en la carpeta de salida
    std::string archivoSalida = carpetaSalida + "/map.txt";
    
    // Eliminar el archivo existente si existe
    std::remove(archivoSalida.c_str());

    std::ofstream archivo(archivoSalida);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida en " << archivoSalida << std::endl;
        return;
    }

    int id = 0; // Iniciar ID
    for (const auto& entry : fs::directory_iterator(carpetaEntrada)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
           
            archivo << entry.path().filename().string() << "," << id << std::endl;
            ++id; // Incrementar el ID para el siguiente archivo
        }
    }

    archivo.close();
    std::cout << "El archivo " << archivoSalida << " ha sido generado exitosamente." << std::endl;
}

