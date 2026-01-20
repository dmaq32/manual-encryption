#include <iostream>
#include <string>
#include <chrono>

#include "encryptions.h"

using namespace std;
using namespace chrono;

std::string Atbash::EncryptDecrypt(const std::string& text, double* t) {
    auto start = steady_clock::now();

    const int n = 256;

    std::string result;
    for (char c : text) {
        result += (char)(n - 1 - (int)c);
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return result;
}




