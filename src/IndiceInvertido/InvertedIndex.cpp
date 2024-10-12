#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <fstream>
#include <filesystem>
#include <unistd.h>
using namespace std;
namespace fs = std::filesystem;



void mappingWords(string pathFile,map<string , vector< tuple<string,string> > > &index,string fileName){
    ifstream file(pathFile);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo" << endl;
    }else{
        string lines;
        while (getline(file, lines)) {
            stringstream line(lines);
            string word;string amount ;
            getline(line, word, ';');
            getline(line, amount, ';');
            index[word].push_back(make_tuple(fileName,amount));
        }
    }
}
void saveIndex(string pathFile, map<string , vector< tuple<string,string> > > & index){
    ofstream outFile(pathFile);
    if (!outFile.is_open()) {
        cout << "Error: No se pudo abrir el archivo de salida " << pathFile << endl;
    }else{
        for (const auto& [key, value] : index) {
            outFile << key;  // Escribir la palabra clave
            for (const auto& tuple : value) {
                outFile << ";(" << get<0>(tuple) << "," << get<1>(tuple) << ")";
            }
            outFile << ";"<<endl;
        }
    }
    outFile.close();
}


int main(int argc, char* argv[]) {
    if (argc < 1){
        cout << "Error: Falta el path del el archivo de indexacion invertida" << endl;
       return EXIT_FAILURE; 
    }
    cout << "=================================" << endl;
    cout << " Creador de indice invertido" << endl;
    cout << "PID del proceso: " << getpid() << endl;
    cout << "=================================\n" << endl;

    string invertedIndexPATH = argv[1]; 
    string extension = ".txt";
    //variables de entorno 
    string mapaFilePath = getenv("mapa_archivos")+string("/mapa.txt");
    string outFilesPAth = "/home/francisco/GitProyects/INFO198_SO/out";    

    //crear indice invertido
    map<string, vector< tuple<string, string> > > invertedIndex;
    
    //leer todos los archivos del directorio
    cout << "Creando indice invertido..." << endl;
    for (const auto& entry : fs::directory_iterator(outFilesPAth)) {
        if (entry.path().extension() == extension) {
            mappingWords(entry.path().string(), invertedIndex, entry.path().stem().string());
        }
    }
    //escribir el indice invertido en un archivo
    saveIndex(invertedIndexPATH, invertedIndex);
    cout << "Indice invertido creado exitosamente, ruta: " << invertedIndexPATH << endl;
    exit(EXIT_SUCCESS);    

}