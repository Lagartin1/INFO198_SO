# Compilador
Comp = g++

# Opciones del compilador
CFLAGS = -Wall -Wextra -std=c++17 -pthread -Iinclude

# Directorios
BIN_DIR = bin/
SRC_DIR = src/
APP2_DIR = src/ContarPalabras/
APP3_DIR = src/ContarPalabras/
APP4_DIR = src/IndiceInvertido/
PLANIFICADOR_DIR = src/Planificator/
SOCK_DIR = sockets/

# Archivos fuente
MAIN_SRC = $(SRC_DIR)MainApp.cpp
APP2_SRC = $(APP2_DIR)ContarPalabras.cpp $(APP2_DIR)ContarPalabrasUtils.cpp
APP3_SRC = $(APP3_DIR)procesar_hilos.cpp $(APP3_DIR)ContarPalabrasUtils.cpp
APP4_SRC = $(APP4_DIR)InvertedIndex.cpp

# Objetivos
all: clean mkdir app app2 app3 app4 planificador distribuidor core

# Compilación de la aplicación principal
app:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app $(MAIN_SRC)

# Compilación de la aplicación app2
app2:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app2 $(APP2_SRC)

# compila el 3
app3:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app3 $(APP3_SRC)

app4:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app4 $(APP4_SRC)

# Compilación del planificador
planificador:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)planificador $(PLANIFICADOR_DIR)Planificator.cpp

# Compilación del distribuidor
distribuidor:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)distribuidor $(PLANIFICADOR_DIR)Distributor.cpp

# Compilación del core
core:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)core $(PLANIFICADOR_DIR)Core.cpp

# Crear el directorio bin si no existe
mkdir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(SOCK_DIR)

# Limpieza de archivos generados
clean:
	rm -rf $(BIN_DIR)*
