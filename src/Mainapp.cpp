#include "../include/UserTools.h"
#include "../include/NumTools.h"
#include "../include/Texttools.h"
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
    int opt;
    string user,pass,text,vet,num;
    map <string,string> users;
    
    while ((opt = getopt(argc, argv, "u:p:t:v:n:")) != -1) {
        switch (opt) {
            case 'u':
                user = optarg;
                break;
            case 'p':
                pass = optarg;
                break;
            case 't':
                text = optarg;
                break;
            case 'v':
                vet = optarg;
                break;
            case 'n':
                num = optarg;
                break;
        }
    }
    if (user.empty() && pass.empty()){
        cout << "Error: Debe ingresar un usuario y contraseña" << endl;
        exit(EXIT_FAILURE);
    }
    extractUsers(users);
    if(users.find(user)!= users.end() && users[user] == pass ){
        //lanzar menu
        cout << "Bienvenido " << user << endl;
    }else{
        cout << "Error: Usuario o contraseña incorrectos" << endl;
        exit(EXIT_FAILURE);
    }
}