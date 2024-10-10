//ContarPalabrasThreads.h

#include <vector> //para hilos
#include <thread> //para hilos




void procesarConHilos(const string& extension, const string& carpetaEntrada, const string& carpetaSalida, int numThreads);

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

void procesarArchivo(string pathIN,string name, string pathOut);
void procesar(const string& extension, const string& carpetaEntrada, const string& carpetaSalida);
bool archivosConExtensionExisten(const string& extension, const string& carpeta);
bool carpetaExiste(const string& path);

