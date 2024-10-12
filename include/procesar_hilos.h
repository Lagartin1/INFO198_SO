#include "ContarPalabrasUtils.h"
#include <thread>
#include <vector>
#include <limits>
#include <stdexcept>
#include <mutex>
#include <sstream>
#include <algorithm>
void procesarArchivosConHilos(const string& extension, const string& carpetaEntrada, const string& carpetaSalida, size_t numHilos,vector<string> &stopwords);
void procesarArchivoConMutex(const string& pathIN, const string& name, const string& pathOut,vector<string> &stopwords);