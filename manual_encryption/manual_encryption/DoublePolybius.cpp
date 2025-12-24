#include <iostream>
#include "encryptions.h"
#include <chrono>
using namespace std;
using namespace chrono;


pair<int, int> DoublePolybius::findCoordinates(char letter) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (square[i][j] == letter) {
                return { i + 1, j + 1 };
            }
        }
    }
    return { 0, 0 };
}

char DoublePolybius::findLetter(int row, int col) {
    if (row >= 1 && row <= 9 && col >= 1 && col <= 9) {
        return square[row - 1][col - 1];
    }
    return ' ';
}

string DoublePolybius::encrypt(string text, double* t) {
    auto start = steady_clock::now();

    vector<int> verticalCoords, horizontalCoords;

    for (char character : text) {
        auto coords = findCoordinates(character);
        verticalCoords.push_back(coords.first);
        horizontalCoords.push_back(coords.second);
    }

    vector<int> allCoords;
    for (int v : verticalCoords) {
        allCoords.push_back(v);
    }
    for (int h : horizontalCoords) {
        allCoords.push_back(h);
    }

    string result;
    for (size_t i = 0; i < allCoords.size(); i += 2) {
        if (i + 1 < allCoords.size()) {
            char newLetter = findLetter(allCoords[i], allCoords[i + 1]);
            result += newLetter;
        }
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}

string DoublePolybius::decrypt(string cipher,double *t) {
    auto start = steady_clock::now();

    vector<int> allCoords;
    for (char character : cipher) {
        auto coords = findCoordinates(character);
        allCoords.push_back(coords.first);
        allCoords.push_back(coords.second);
    }

    int half = allCoords.size() / 2;
    vector<int> verticalCoords, horizontalCoords;

    for (int i = 0; i < half; i++) {
        verticalCoords.push_back(allCoords[i]);
    }
    for (size_t i = half; i < allCoords.size(); i++) {
        horizontalCoords.push_back(allCoords[i]);
    }

    string result;
    for (size_t i = 0; i < verticalCoords.size() && i < horizontalCoords.size(); i++) {
        char originalLetter = findLetter(verticalCoords[i], horizontalCoords[i]);
        result += originalLetter;
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}

void DoublePolybius::demonstrateProcess(string text) {
    cout << "Исходный текст: " << text << endl;
    vector<int> verticalCoords, horizontalCoords;
    cout << "Буквы: ";
    for (char c : text) cout << c << " ";
    cout << endl;

    cout << "Вертикальные координаты:   ";
    for (char c : text) {
        auto coords = findCoordinates(c);
        verticalCoords.push_back(coords.first);
        cout << coords.first << " ";
    }
    cout << endl;

    cout << "Горизонтальные координаты: ";
    for (char c : text) {
        auto coords = findCoordinates(c);
        horizontalCoords.push_back(coords.second);
        cout << coords.second << " ";
    }
    cout << endl;

    vector<int> allCoords;
    for (int v : verticalCoords) allCoords.push_back(v);
    for (int h : horizontalCoords) allCoords.push_back(h);

    cout << "Все координаты подряд: ";
    for (int coord : allCoords) cout << coord << " ";
    cout << endl;

    cout << "Координаты - буквы: ";
    string result;
    for (size_t i = 0; i < allCoords.size(); i += 2) {
        if (i + 1 < allCoords.size()) {
            char letter = findLetter(allCoords[i], allCoords[i + 1]);
            cout << allCoords[i] << allCoords[i + 1] << "-" << letter << " ";
            result += letter;
        }
    }
    cout << endl;

    cout << "Зашифрованный текст: " << result << endl;
}