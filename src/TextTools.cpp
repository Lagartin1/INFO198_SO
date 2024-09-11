#include "../include/TextTools.h"


void isPalindrome(string text) {
    string cleanText;
    for (char c : text)  if(!isspace(c)) cleanText += tolower(c);
    bool isPalim = true;
    int r = cleanText.length();
    int l = 0;
    while (l<r){
        if (cleanText[l] != cleanText[r-1]){
            isPalim = false;
            break;
        }
        l++;r--;
    }
    if (isPalim) {
        cout << "El string \"" << text << "\" es un palíndromo" << endl;
    } else {
        cout << "El string \"" << text << "\" no es un palíndromo" << endl;
    }
}

void countVocals(string text){
    int n = text.length();
    int c = 0;
    for (int i = 0; i < n; i++) {
        char cI = tolower(text[i]);
        if (cI == 'a' || cI == 'e' || cI == 'i' || cI == 'o' || cI == 'u') {
            c++;
        }
    }
    cout << "El texo "<< '"' <<text << '"' << " contiene " << c << " vocales" << endl;
}


void countLetters(string text){
    int n = text.length();
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (isalpha(text[i])) {
            c++;
        }
    }
    cout << "El texto " << '"'<<text << '"' << " contiene " << c << " letras" << endl;    
}
void borrarConsola(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}