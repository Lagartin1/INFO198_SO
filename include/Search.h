#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <sstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <locale>
#include <map>
#include <cstring>
#include <fstream>

using namespace std;


void leerMAP(map<string,string> &map, string mpPath);
void desempaquetar(string resultdado,map<string,string> &mp);
void search(map<string,string> &mp);
bool isExtit(string search);
string sendMessageToCache(string texto);