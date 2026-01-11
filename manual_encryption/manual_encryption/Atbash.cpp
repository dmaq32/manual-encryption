#include <iostream>
#include <string>
#include <chrono>

#include "encryptions.h"

using namespace std;
using namespace chrono;

std::string Atbash::EncryptDecrypt(const std::string& text, double* t) {
    auto start = steady_clock::now();

    const std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&'()*+,-./:;<=>?@^_{|}~`";
    const int n = alphabet.length();

    std::string result;

    for (char c : text) {
        size_t pos = alphabet.find(c);
        if (pos != std::string::npos) {
            result += alphabet[n - 1 - pos];
        }
        else {
            result += c;
        }
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return result;
}




