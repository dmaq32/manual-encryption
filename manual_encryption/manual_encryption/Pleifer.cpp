#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <random>
#include <functional>
#include <chrono>
#include "encryptions.h"
using namespace std;
using namespace chrono;

void Pleifer::createMatrix() {
    matrix.resize(5, vector<char>(5));
    string keyWithoutDuplicates;
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    for (char c : key) {
        char upperC = toupper(c);
        if (upperC == 'J') upperC = 'I';
        if (keyWithoutDuplicates.find(upperC) == string::npos && isalpha(upperC)) {
            keyWithoutDuplicates += upperC;
        }
    }

    for (char c : alphabet) {
        if (keyWithoutDuplicates.find(c) == string::npos) {
            keyWithoutDuplicates += c;
        }
    }

    int index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = keyWithoutDuplicates[index++];
        }
    }
}

string Pleifer::prepareText(const string& text) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            result += toupper(c);
        }
    }

    for (char& c : result) {
        if (c == 'J') c = 'I';
    }

    string finalResult;
    for (size_t i = 0; i < result.length(); i++) {
        finalResult += result[i];
        if (i + 1 < result.length() && result[i] == result[i + 1]) {
            finalResult += 'X';
        }
    }

    if (finalResult.length() % 2 != 0) {
        finalResult += 'X';
    }

    return finalResult;
}

pair<int, int> Pleifer::findPosition(char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                return { i, j };
            }
        }
    }
    return { -1, -1 };
}
string Pleifer::encrypt(const string& plaintext,double *t) {
    auto start = steady_clock::now();

    string preparedText = prepareText(plaintext);
    string ciphertext;

    cout << "»ÒıÓ‰Ì˚È ÚÂÍÒÚ: " << plaintext << endl;

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        char first = preparedText[i];
        char second = preparedText[i + 1];

        auto pos1 = findPosition(first);
        auto pos2 = findPosition(second);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        char enc1, enc2;

        if (row1 == row2) {
            enc1 = matrix[row1][(col1 + 1) % 5];
            enc2 = matrix[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2) {
            enc1 = matrix[(row1 + 1) % 5][col1];
            enc2 = matrix[(row2 + 1) % 5][col2];
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
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return ciphertext;
}

string Pleifer::decrypt(const string& ciphertext, double *t) {
    auto start = steady_clock::now();

    string preparedText = prepareText(ciphertext);
    string plaintext;

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        char first = preparedText[i];
        char second = preparedText[i + 1];

        auto pos1 = findPosition(first);
        auto pos2 = findPosition(second);

        int row1 = pos1.first, col1 = pos1.second;
        int row2 = pos2.first, col2 = pos2.second;

        char dec1, dec2;

        if (row1 == row2) {
            dec1 = matrix[row1][(col1 + 4) % 5];
            dec2 = matrix[row2][(col2 + 4) % 5];
        }
        else if (col1 == col2) {
            dec1 = matrix[(row1 + 4) % 5][col1];
            dec2 = matrix[(row2 + 4) % 5][col2];
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
        if (i + 1 < plaintext.length() && plaintext[i] == plaintext[i + 1] && plaintext[i + 1] == 'X') {
            i++;
        }
        cleanedResult += plaintext[i];
    }

    if (!cleanedResult.empty() && cleanedResult.back() == 'X') {
        cleanedResult.pop_back();
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return cleanedResult;
}

void Pleifer::printMatrix() {
    cout << "Ã‡ÚËˆ‡ œÎÂÈÙÂ‡:" << endl;
    cout << "  0 1 2 3 4" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
        for (int j = 0; j < 5; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}   
