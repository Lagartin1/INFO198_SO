#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

#ifndef PBUSQUEDA_H
#define PBUSQUEDA_H
class Pbusqueda{
    private:
        string palabra;
        string contenido;
        system_clock::time_point ingreso;
    public:
        //Constructor
        Pbusqueda(string palabra, string contenido, system_clock::time_point ingreso){
            this->palabra = palabra;
            this->contenido = contenido;
            this->ingreso = ingreso;
        }
        string getPalabra(){return palabra;} 
        string getContenido(){return contenido;}
        system_clock::time_point getIngreso(){return ingreso;}
        void setPalabra(string palabra){ this->palabra = palabra;}
        void setContenido(string contenido){ this->contenido = contenido;}
        void setIngreso(system_clock::time_point ingreso){ this->ingreso = ingreso;}
};
#endif

void reemplazarMasAntiguo(vector<Pbusqueda>& cache, string& nuevaPalabra, string& nuevoContenido);
void agregarCache(vector<Pbusqueda>& cache, string& palabra, string& contenido);
string searchCache(vector<Pbusqueda>& cache, string palabra, int size);
string sendMessageToEngine(string palabra);



