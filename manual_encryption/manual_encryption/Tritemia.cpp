#include "encryptions.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

string Tritemia::get_alphabet() {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
}


string Tritemia::encrypt(const std::string& text, double* t) {
    auto start = high_resolution_clock::now();

    std::string alphabet = get_alphabet();
    std::string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        size_t pos = alphabet.find(std::toupper(text[i]));

        if (pos != std::string::npos) {
            size_t new_pos = (pos + i) % alphabet.length();
            result += alphabet[new_pos];
        }
        else {
            result += text[i];
        }
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return result;
}

string Tritemia::decrypt(const std::string& text, double* t) {
    auto start = steady_clock::now();

    std::string alphabet = get_alphabet();
    std::string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        size_t pos = alphabet.find(std::toupper(text[i]));

        if (pos != std::string::npos) {
            size_t original_pos = (pos - i + alphabet.length()) % alphabet.length();
            result += alphabet[original_pos];
        }
        else {
            result += text[i];
        }
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}