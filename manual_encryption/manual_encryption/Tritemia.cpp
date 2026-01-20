#include "encryptions.h"
#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace chrono;

string Tritemia::get_alphabet() {
    return "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&'()*+,-./:;<=>?@^_{|}~`";
}


string Tritemia::encrypt(const std::string& text) {

    std::string alphabet = get_alphabet();
    std::string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        size_t pos = alphabet.find(text[i]);

        if (pos != std::string::npos) {
            size_t new_pos = (pos + i) % alphabet.length();
            result += alphabet[new_pos];
        }
        else {
            result += text[i];
        }
    }
    return result;
}

string Tritemia::decrypt(const std::string& text) {

    std::string alphabet = get_alphabet();
    std::string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        size_t pos = alphabet.find(text[i]);

        if (pos != std::string::npos) {
            size_t original_pos = (pos - i + alphabet.length()) % alphabet.length();
            result += alphabet[original_pos];
        }
        else {
            result += text[i];
        }
    }

    return result;
}