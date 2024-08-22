
Comp = g++
# Opciones del compilador
CFLAGS = -Wall -Wextra -std=c++17 -Iinclude
BIN_DIR = bin/
SRC_DIR = src/


all: clean app

app:
	$(Comp) $(CFLAGS) -o $(BIN_DIR)app $(SRC_DIR)Mainapp.cpp

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)