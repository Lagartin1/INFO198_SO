#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>
#include "Usuario.h"
#include "../src/Usuario.cpp"
using namespace std;

void extractUsers(map <string,Usuario> &users,string txtFilePath);
void verificarUsuario(string user, string pass);
void extractUsers(map<string, Usuario> &users);
void listUsers(map <string,Usuario> &users);
void addUserData(string user, string pass, string tipo);
void addUser(map <string,Usuario> &users);
bool verificarUsuarioNuevo(string user);
bool verficarPassUsuarioNuevo(string pass);
bool deleteUserData(string user);
void deleteUser(map <string,Usuario> &users);