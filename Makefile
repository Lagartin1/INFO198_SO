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
APP5_DIR = src/ContarPalabras/AnalisisPerformance/
PLANIFICADOR_DIR = src/Planificator/
SOCK_DIR = sockets/
BUSCADOR_DIR = src/Search/

# Archivos fuente
MAIN_SRC = $(SRC_DIR)MainApp.cpp
APP2_SRC = $(APP2_DIR)ContarPalabras.cpp $(APP2_DIR)ContarPalabrasUtils.cpp
APP3_SRC = $(APP3_DIR)procesar_hilos.cpp $(APP3_DIR)ContarPalabrasUtils.cpp
APP4_SRC = $(APP4_DIR)InvertedIndex.cpp
APP5_SRC = $(APP5_DIR)EJECUTADOR.cpp # Agregado para app5 src\ContarPalabras\AnalisisPerformance\EJECUTADOR.cpp

# Objetivos
all: clean mkdir app app2 app3 app4 app5 planificador distribuidor core buscador cache engine

# Compilación de la aplicación principal
app:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app $(MAIN_SRC)

# Compilación de la aplicación app2
app2:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app2 $(APP2_SRC)

# Compilación de la aplicación app3
app3:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app3 $(APP3_SRC)

# Compilación de la aplicación app4
app4:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app4 $(APP4_SRC)

# Compilación de la aplicación app5
app5:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app5 $(APP5_SRC)

# Compilación del planificador
planificador:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)planificador $(PLANIFICADOR_DIR)Planificator.cpp

# Compilación del distribuidor
distribuidor:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)distribuidor $(PLANIFICADOR_DIR)Distributor.cpp

# Compilación del core
core:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)core $(PLANIFICADOR_DIR)Core.cpp

# Crear el directorio bin y sockets si no existen
buscador:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)buscador $(BUSCADOR_DIR)Buscador.cpp
cache:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)cache $(BUSCADOR_DIR)Cache.cpp
engine:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)engine $(BUSCADOR_DIR)Engine.cpp

mkdir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(SOCK_DIR)

# Limpieza de archivos generados
clean:
	rm -rf $(BIN_DIR)*
