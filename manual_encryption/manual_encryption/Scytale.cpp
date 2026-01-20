#include <iostream>
#include "encryptions.h"
#include <chrono>
using namespace chrono;
using namespace std;

string Scytale::encrypt(string t) {

    string s = t;
    int len = s.length();
    int r = (len + d - 1) / d;

    string res;
    for (int col = 0; col < d; col++) {
        for (int row = 0; row < r; row++) {
            int pos = row * d + col;
            if (pos < len)
                res += s[pos];
            else
                res += ' ';
        }
    }
    return res;
}

string Scytale::decrypt(string ct) {

    int len = ct.length();
    int r = len / d; 
    string res;

    for (int row = 0; row < r; row++) {
        for (int col = 0; col < d; col++) {
            int pos = col * r + row;
            if (pos < len)
                res += ct[pos];
        }
    }

    size_t last = res.find_last_not_of(' ');
    if (last != string::npos)
        res = res.substr(0, last + 1);
    else
        res = "";

    return res;
}