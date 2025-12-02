#include <iostream>
#include <string>
#include "encryptions.h"
#include <chrono>
#include <vector>
#include <map>


using namespace std;
using namespace chrono;

int Affine::modInv(int a, int m) {
    a = a % m;
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) return i;
    }
    return -1;
}

bool Affine::checkA(int a) {
    return (a % 2 != 0) && (a % 13 != 0);
}

string Affine::encrypt(string text, int a, int b, double* t) {
    auto start = steady_clock::now();
    string result = "";
    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            int x = c - 'A';
            int y = (a * x + b) % 26;
            result += char(y + 'A');
        }
        else if (c >= 'a' && c <= 'z') {
            int x = c - 'a';
            int y = (a * x + b) % 26;
            result += char(y + 'a');
        }
        else result += c;
    }
    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}

string Affine::decrypt(string text, int a, int b, double* t) {
    auto start = steady_clock::now();
    string result = "";
    int a_inv = modInv(a, 26);
    if (a_inv == -1) return "ERROR";

    for (char c : text) {
        if (c >= 'A' && c <= 'Z') {
            int y = c - 'A';
            int x = (a_inv * (y - b)) % 26;
            if (x < 0) x += 26;
            result += char(x + 'A');
        }
        else if (c >= 'a' && c <= 'z') {
            int y = c - 'a';
            int x = (a_inv * (y - b)) % 26;
            if (x < 0) x += 26;
            result += char(x + 'a');
        }
        else result += c;
    }
    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}