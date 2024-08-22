#include "../include/NumTools.h"


void averageAndSumVector(vector <int> v){
    int n = v.size();
    int sum = 0;
    for(int i = 0; i<n;i++){
        sum += v[i];
    }
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


