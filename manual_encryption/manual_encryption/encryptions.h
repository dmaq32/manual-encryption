#pragma once
#include <string>
using namespace std;

// Манукьянц В. А.
class Vigener {
public:
    string lower(const string& str);
    string vigenere(string text, string key, double* t = nullptr, bool decryption = false);

};
