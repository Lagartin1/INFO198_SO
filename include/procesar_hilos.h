#include "ContarPalabrasUtils.h"
#include <thread>
#include <vector>
#include <limits>
#include <stdexcept>

void procesarArchivosConHilos(const string& extension, const string& carpetaEntrada, const string& carpetaSalida, int numHilos);