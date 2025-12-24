#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <random>
#include <functional>
#include <chrono>
#include <iomanip>
#include "encryptions.h"

using namespace std;
using namespace chrono;

void Pleifer::createMatrix() {
    matrix.resize(16, vector<unsigned char>(16));
    vector<unsigned char> keyWithoutDuplicates;

    for (unsigned char c : key) {
        if (find(keyWithoutDuplicates.begin(), keyWithoutDuplicates.end(), c)
            == keyWithoutDuplicates.end()) {
            keyWithoutDuplicates.push_back(c);
        }
    }

    int index = 0;

    for (unsigned char c : keyWithoutDuplicates) {
        if (index < 256) {
            int row = index / 16;
            int col = index % 16;
            matrix[row][col] = c;
            index++;
        }
    }

    for (int asciiCode = 0; asciiCode < 256; asciiCode++) {
        unsigned char c = static_cast<unsigned char>(asciiCode);

        if (find(keyWithoutDuplicates.begin(), keyWithoutDuplicates.end(), c)
            != keyWithoutDuplicates.end()) {
            continue;
        }

        if (index < 256) {
            int row = index / 16;
            int col = index % 16;
            matrix[row][col] = c;
            index++;
        }
    }

    initAvailablePaddingChars();
}

void Pleifer::initAvailablePaddingChars() {
    vector<unsigned char> usedChars(key.begin(), key.end());

    for (int i = 0; i < 256; i++) {
        unsigned char c = static_cast<unsigned char>(i);
        if (find(usedChars.begin(), usedChars.end(), c) == usedChars.end()) {
            availablePaddingChars.push_back(c);
        }
    }

    if (availablePaddingChars.empty()) {
        availablePaddingChars = {0xFF, 0xFE, 0xFD};
    }
}

unsigned char Pleifer::getRandomPaddingChar(const string& text) {
    vector<unsigned char> usedChars(key.begin(), key.end());
    usedChars.insert(usedChars.end(), text.begin(), text.end());

    for (int i = 0; i < 256; i++) {
        unsigned char c = static_cast<unsigned char>(i);
        if (find(usedChars.begin(), usedChars.end(), c) == usedChars.end()) {
            return c;
        }
    }

    if (!availablePaddingChars.empty()) {
        return availablePaddingChars[0];
    }

    return 0xFF;
}

string Pleifer::prepareText(const string& text) {
    string result = text;

    string finalResult;
    for (size_t i = 0; i < result.length(); i++) {
        finalResult += result[i];
        if (i + 1 < result.length() && result[i] == result[i + 1]) {
            unsigned char paddingChar = getRandomPaddingChar(text);
            finalResult += static_cast<char>(paddingChar);
        }
    }

    if (finalResult.length() % 2 != 0) {
        unsigned char paddingChar = getRandomPaddingChar(text);
        finalResult += static_cast<char>(paddingChar);
    }

    return finalResult;
}

pair<int, int> Pleifer::findPosition(unsigned char c) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

string Pleifer::encrypt(const string& plaintext, double* t) {
    auto start = steady_clock::now();

    string preparedText = prepareText(plaintext);
    string ciphertext;

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        unsigned char first = preparedText[i];
        unsigned char second = preparedText[i + 1];

        auto pos1 = findPosition(first);
        auto pos2 = findPosition(second);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        unsigned char enc1, enc2;

        if (row1 == row2) {
            enc1 = matrix[row1][(col1 + 1) % 16];
            enc2 = matrix[row2][(col2 + 1) % 16];
        }
        else if (col1 == col2) {
            enc1 = matrix[(row1 + 1) % 16][col1];
            enc2 = matrix[(row2 + 1) % 16][col2];
        }
        else {
            enc1 = matrix[row1][col2];
            enc2 = matrix[row2][col1];
        }

        ciphertext += enc1;
        ciphertext += enc2;
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = duration_cast<microseconds>(end - start).count();
    }

    return ciphertext;
}

string Pleifer::decrypt(const string& ciphertext, double* t) {
    auto start = steady_clock::now();

    string preparedText = prepareText(ciphertext);
    string plaintext;

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        unsigned char first = preparedText[i];
        unsigned char second = preparedText[i + 1];

        auto pos1 = findPosition(first);
        auto pos2 = findPosition(second);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        unsigned char dec1, dec2;

        if (row1 == row2) {
            dec1 = matrix[row1][(col1 + 15) % 16];
            dec2 = matrix[row2][(col2 + 15) % 16];
        }
        else if (col1 == col2) {
            dec1 = matrix[(row1 + 15) % 16][col1];
            dec2 = matrix[(row2 + 15) % 16][col2];
        }
        else {
            dec1 = matrix[row1][col2];
            dec2 = matrix[row2][col1];
        }

        plaintext += dec1;
        plaintext += dec2;
    }

    string cleanedResult;
    for (size_t i = 0; i < plaintext.length(); i++) {
        if (i + 1 < plaintext.length() && plaintext[i] == plaintext[i + 1]) {
            i++;
        }
        cleanedResult += plaintext[i];
    }

    if (!cleanedResult.empty() && cleanedResult.length() > plaintext.length() / 2) {
        cleanedResult.pop_back();
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = duration_cast<microseconds>(end - start).count();
    }

    return cleanedResult;
}

string Pleifer::toHexString(const string& data) {
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : data) {
        ss << "\\x" << setw(2) << static_cast<int>(c);
    }
    return ss.str();
}

using namespace std;
