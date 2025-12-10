#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


// Манукьянц В. А.
class Vigener {
public:
    string lower(const string& str);
    string vigenere(string text, string key, double* t = nullptr, bool decryption = false);

};

// Плеханов И.Г.
class Pleifer {
private:
    string key;
    vector<vector<char>> matrix;

    void createMatrix();
    string prepareText(const string& text);
public:
    Pleifer(const string& key) : key(key) {
        createMatrix();
    }
    pair<int, int> findPosition(char c);
    string encrypt(const string& plaintext, double *t = nullptr);
    string decrypt(const string& ciphertext, double *t = nullptr);

    void printMatrix();
};

// Ястребцов И.Г.
class Tritemia {
public:
    string get_alphabet();
    string encrypt(const std::string& text, double* t = nullptr);
    string decrypt(const std::string& text, double* t = nullptr);
};

// Конкин Д.О.
class DoublePolybius {
    vector<vector<char>> square;

public:
    DoublePolybius() : square{
        {'A','B','C','D','E'},
        {'F','G','H','I','K'},
        {'L','M','N','O','P'},
        {'Q','R','S','T','U'},
        {'V','W','X','Y','Z'}
    } {
    }
    pair<int, int> findCoordinates(char letter);
    char findLetter(int row, int col);
    void demonstrateProcess(string text);
    string encrypt(string text, double* t = nullptr);
    string decrypt(string text, double* t = nullptr);

};

// Астапова К.А.
class Scytale {
    int d;
public:
    Scytale(int diam) : d(diam) {}
    string encrypt(string t, double* t2 = nullptr);
    string decrypt(string ct, double* t = nullptr);
};

// Жаданос М.Ю.
class Affine {
public:
    int modInv(int a, int m);
    bool checkA(int a);
    string encrypt(string text, int a, int b, double* t);
    string decrypt(string text, int a, int b, double* t);

};

//Цэрнэ Д.В.
class legrand {
public:
    static vector<uint32_t> utf8_to_codepoints(const string& s) {
        vector<uint32_t> out;
        size_t i = 0;
        while (i < s.size()) {
            unsigned char c = s[i];
            uint32_t cp = 0;
            size_t len = 0;
            if ((c & 0x80) == 0) { cp = c; len = 1; }
            else if ((c & 0xE0) == 0xC0) {
                if (i + 1 >= s.size()) break;
                cp = ((c & 0x1F) << 6) | (s[i + 1] & 0x3F);
                len = 2;
            }
            else if ((c & 0xF0) == 0xE0) {
                if (i + 2 >= s.size()) break;
                cp = ((c & 0x0F) << 12) | ((s[i + 1] & 0x3F) << 6) | (s[i + 2] & 0x3F);
                len = 3;
            }
            else if ((c & 0xF8) == 0xF0) {
                if (i + 3 >= s.size()) break;
                cp = ((c & 0x07) << 18) | ((s[i + 1] & 0x3F) << 12)
                    | ((s[i + 2] & 0x3F) << 6) | (s[i + 3] & 0x3F);
                len = 4;
            }
            else break;
            out.push_back(cp);
            i += len;
        }
        return out;
    }

    static string codepoint_to_utf8(uint32_t cp) {
        string s;
        if (cp <= 0x7F) s.push_back((char)cp);
        else if (cp <= 0x7FF) {
            s.push_back((char)(0xC0 | ((cp >> 6) & 0x1F)));
            s.push_back((char)(0x80 | (cp & 0x3F)));
        }
        else if (cp <= 0xFFFF) {
            s.push_back((char)(0xE0 | ((cp >> 12) & 0x0F)));
            s.push_back((char)(0x80 | ((cp >> 6) & 0x3F)));
            s.push_back((char)(0x80 | (cp & 0x3F)));
        }
        else {
            s.push_back((char)(0xF0 | ((cp >> 18) & 0x07)));
            s.push_back((char)(0x80 | ((cp >> 12) & 0x3F)));
            s.push_back((char)(0x80 | ((cp >> 6) & 0x3F)));
            s.push_back((char)(0x80 | (cp & 0x3F)));
        }
        return s;
    }

    static uint32_t to_lower_cp(uint32_t cp) {
        if (cp >= 'A' && cp <= 'Z') return cp + 32;
        return cp;
    }

    static bool is_letter_or_space(uint32_t cp) {
        return (cp >= 'A' && cp <= 'Z') || (cp >= 'a' && cp <= 'z') || cp == 0x20;
    }

    unordered_map<string, int> syllable_to_code;
    unordered_map<int, string> code_to_syllable;

    void build_mappings();
    string encrypt_text(const string& plain, double* t = nullptr);
    string decrypt_codes(const string& codes, double* t = nullptr);

};