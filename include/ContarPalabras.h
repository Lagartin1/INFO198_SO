#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>
#include <unistd.h>
using namespace std;
namespace fs = std::filesystem;

void procesarArchivo(string pathIN,string name, string pathOut);
void procesar(const string& extension, const string& carpetaEntrada, const string& carpetaSalida);
void contarPalabrasTotalesEnCarpeta(const string& carpetaEntrada, const fs::path& archivoSalida);
bool archivosConExtensionExisten(const string& extension, const string& carpeta);
bool carpetaExiste(const string& path);
