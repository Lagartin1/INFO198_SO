#include <string>

using namespace std;

#ifndef USUARIO_H
#define USUARIO_H

class Usuario {
    private:
        string user;
        string pass;
        string tipo;
    public :
        Usuario(){ pass = ""; user = ""; tipo = ""; };
        Usuario(string u, string p,string t){ user = u; pass = p; tipo = t; };
        string getUser();
        string getPass();
        string getTipo();
};

#endif
