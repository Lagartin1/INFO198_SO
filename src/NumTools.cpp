#include "../include/NumTools.h"



void operarVector(string vect){
    vector<int> v;
    rellenarVector(v, vect);
    averageAndSumVector(v);
}

void rellenarVector(vector<int> &v, string vect){
    string cache = "";
    int l = vect.length();
    for (int i = 0; i < l; i++){
        if (vect[i] == ';'){
            int number = stoi(cache);
            v.push_back(number);
            cache = "";
        }else{
            cache += vect[i];
        }
    }    
}


void averageAndSumVector(vector <int> &v){
    int n = v.size();
    int sum = 0;
    for(int i = 0; i<n;i++){
        sum += v[i];
    }
    cout << "El vector es: ";
    imprimirVector(v);
    cout << "La sumatoria de los elementos del vector es: " << sum << endl;
    cout << "El promedio de los elementos del vector es: " << sum/(n-1) << endl;
}

void calculateFunc(int n){
    if (n != 0){
        cout << "El resultado de la funcion es: " << 5*n*n + 1/n << endl;
    } else {
        cout << "Error Divivion por 0 "<< endl;
        exit(EXIT_FAILURE);
    }
}

void calculateFunc(float n){
    if (n != 0){
        cout << "El resultado de la funcion es: " << 5*n*n + 1/n << endl;
    } else {
        cout << "Error Divivion por 0 "<< endl;
        exit(EXIT_FAILURE);
    }
}
void imprimirVector(vector<int> &v){
    int size_v = v.size();
    cout << "{";
    for (int i = 0; i < size_v; i++){
        cout << v[i] << " ";
    }
    cout << "}";
    cout << endl;
}