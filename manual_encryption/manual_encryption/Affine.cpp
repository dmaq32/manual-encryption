#include <iostream>
#include <string>
#include "encryptions.h"
#include <chrono>
#include <unordered_map>
#include <numeric>

using namespace std;
using namespace chrono;


string Affine::buildAlphabet() {
    string ru_cp1251 =
        "\xA8"
        "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
        "\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
        "\xB8"
        "\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
        "\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

    string en =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    string digits = "0123456789";

    string punct =
        " .,!?;:-—()[]{}\"'«»/\\@#¹$%^&*_+=<>~`|"
        "\n\t";
    return en + ru_cp1251 + digits + punct;
}
Affine a;
const string kAlphabet = a.buildAlphabet();

unordered_map<unsigned char, int> Affine::buildPosMap() {
    unordered_map<unsigned char, int> pos;
    pos.reserve(kAlphabet.size());
    for (int i = 0; i < (int)kAlphabet.size(); ++i) {
        pos[(unsigned char)kAlphabet[i]] = i;
    }
    return pos;
}

const unordered_map<unsigned char, int> kPos = a.buildPosMap();

int Affine::modInv(int a, int m) {
    a %= m;
    if (a < 0) a += m;
    for (int i = 1; i < m; i++) {
        if ((a * i) % m == 1) return i;
    }
    return -1;
}

bool Affine::checkA(int a) {
    int m = (int)kAlphabet.size();
    a %= m;
    if (a < 0) a += m;
    return gcd(a, m) == 1;
}

string Affine::encrypt(string text, int a, int b, double* t) {
    auto start = steady_clock::now();

    const int m = (int)kAlphabet.size();
    if (!checkA(a)) return "ERROR";
    b %= m;
    if (b < 0) b += m;

    string result;
    result.reserve(text.size());

    for (unsigned char c : text) {
        auto it = kPos.find(c);
        if (it == kPos.end()) {

            result += (char)c;
            continue;
        }
        int x = it->second;
        int y = (a * x + b) % m;
        result += kAlphabet[y];
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}

string Affine::decrypt(string text, int a, int b, double* t) {
    auto start = steady_clock::now();

    const int m = (int)kAlphabet.size();
    if (!checkA(a)) return "ERROR";
    b %= m;
    if (b < 0) b += m;

    int a_inv = modInv(a, m);
    if (a_inv == -1) return "ERROR";

    string result;
    result.reserve(text.size());

    for (unsigned char c : text) {
        auto it = kPos.find(c);
        if (it == kPos.end()) {
            result += (char)c;
            continue;
        }
        int y = it->second;
        int x = (a_inv * (y - b)) % m;
        if (x < 0) x += m;
        result += kAlphabet[x];
    }

    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}