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
