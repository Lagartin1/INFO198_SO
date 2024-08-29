#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <map>

using namespace std;

void extractUsers(map <string,string> &users);
bool verificarUsuario(string user, string pass,map<string,string> &users);

