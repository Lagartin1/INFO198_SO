
Comp = g++
# Opciones del compilador
CFLAGS = -Wall -Wextra -std=c++17 -Iinclude
BIN_DIR = bin/
SRC_DIR = src/


all: clean mkdir app app2

app:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app $(SRC_DIR)MainApp.cpp
app2:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app2 $(SRC_DIR)ContarPalabras.cpp

mkdir:
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)*