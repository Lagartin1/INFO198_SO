#include "../include/TextTools.h"


void isPalindrome(string text) {
    int n = text.length();
    bool isPalindrome = true;
    for (int i = 0; i < n / 2; i++) {
        if (text[i] != text[n - i - 1]) {
            isPalindrome = false;
            break;
        }
    }
    if (isPalindrome) {
        cout << "El string" << text <<" es un palindoromo" << endl;
    } else {
        cout <<"El string "<< text <<"palindoromo" << endl;
    }
}

void countVocals(string text){
    int n = text.length();
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u') {
            c++;
        }
    }
    cout << "El texo "<<text << "contiene " << c << "vocales" << endl;
}


void countLetters(string text){
    int n = text.length();
    string abcdario = "abcdefghijklmnopqrstuvwxyz";
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (abcdario.find(tolower(text[i])) != string::npos) {
            c++;
        }
    }
    cout << "El texto "<<text << "contiene " << c << "letras" << endl;    
}