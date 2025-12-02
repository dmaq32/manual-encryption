#pragma once
#include <string>
#include <vector>
using namespace std;


// Манукьянц В. А.
class Vigener {
public:
    string lower(const string& str);
    string vigenere(string text, string key, double* t = nullptr, bool decryption = false);

};

// Плеханов И.Г.
class Pleifer {
private:
    string key;
    vector<vector<char>> matrix;

    void createMatrix();
    string prepareText(const string& text);
public:
    Pleifer(const string& key) : key(key) {
        createMatrix();
    }
    pair<int, int> findPosition(char c);
    string encrypt(const string& plaintext, double *t = nullptr);
    string decrypt(const string& ciphertext, double *t = nullptr);

    void printMatrix();
};

// Ястребцов И.Г.
class Tritemia {
public:
    string get_alphabet();
    string encrypt(const std::string& text, double* t = nullptr);
    string decrypt(const std::string& text, double* t = nullptr);
};

// Конкин Д.О.
class DoublePolybius {
    vector<vector<char>> square;

public:
    DoublePolybius() : square{
        {'A','B','C','D','E','F'},
        {'G','H','I','J','K','L'},
        {'M','N','O','P','Q','R'},
        {'S','T','U','V','W','X'},
        {'Y','Z',' ',' ',' ',' '}
    } {
    }
    pair<int, int> findCoordinates(char letter);
    char findLetter(int row, int col);
    void demonstrateProcess(string text);
    string encrypt(string text, double* t = nullptr);
    string decrypt(string text, double* t = nullptr);

};

// Астапова К.А.
class Scytale {
    int d;
public:
    Scytale(int diam) : d(diam) {}
    string encrypt(string t, double* t2 = nullptr);
    string decrypt(string ct, double* t = nullptr);
};