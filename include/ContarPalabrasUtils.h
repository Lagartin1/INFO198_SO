#ifndef CONTARPALABRASUTILS_H
#define CONTARPALABRASUTILS_H

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
bool archivosConExtensionExisten(const string& extension, const string& carpeta);
bool carpetaExiste(const string& path);
void generarArchivoConIDs(const std::string& carpetaEntrada, const std::string& carpetaSalida, const std::string& extension);
#endif // CONTARPALABRASUTILS_H