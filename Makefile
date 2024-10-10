# Compilador
Comp = g++

# Opciones del compilador
CFLAGS = -Wall -Wextra -std=c++17 -Iinclude

# Directorios
BIN_DIR = bin/
SRC_DIR = src/
APP2_DIR = src/ContarPalabras/
APP3_DIR = src/ContarPalabras/

# Archivos fuente
MAIN_SRC = $(SRC_DIR)MainApp.cpp
APP2_SRC = $(APP2_DIR)ContarPalabras.cpp $(APP2_DIR)ContarPalabrasUtils.cpp #Agregué ContarPalabrasUtils.cpp a la variable APP2_SRC, asegurando que todas las definiciones de funciones necesarias para ContarPalabras.cpp se incluyan en la compilación.
APP3_SRC = $(APP3_DIR)procesar_hilos.cpp $(APP3_DIR)ContarPalabrasUtils.cpp
# Objetivos
all: clean mkdir app app2 app3

# Compilación de la aplicación principal
app:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app $(MAIN_SRC)

# Compilación de la aplicación app2
app2:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app2 $(APP2_SRC)

# compila el 3
app3:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app3 $(APP3_SRC)
# Crear el directorio bin si no existe
mkdir:
	mkdir -p $(BIN_DIR)

# Limpieza de archivos generados
clean:
	rm -rf $(BIN_DIR)*
