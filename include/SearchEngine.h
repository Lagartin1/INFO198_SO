#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

string response(string resultado,int n); 
void sendMessageToCache(string texto);
string resultado(string palabra, string &pathIndex);
string palabraCompuesta(string palabra,string &pathIndex,int topk);

