#include <iostream>
#include <string>
#include <chrono>

#include "encryptions.h"

using namespace std;
using namespace chrono;

std::string Atbash::EncryptDecrypt(const std::string& text) {

    const int n = 256;

    std::string result;
    for (char c : text) {
        result += (char)(n - 1 - (int)c);
    }
    return result;
}




