#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include "encryptions.h"
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;

string Vigener::lower(const string& str) {
    string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string Vigener::vigenere(string text, string key, double* t, bool decryption) {
    auto start = steady_clock::now();
    // Так как шифр Виженера НЕ МОЖЕТ криптовать/декриптовать через ключ с цифрами, проверяем их на вхождение в него:
    string alphabetstr = "abcdefghijklmnopqrstuvwxyz";
    bool kick_error = false;
    for (int i = 0; i < 10; i++) {
        string symbol = to_string(i);
        if ((key.find(symbol) != std::string::npos)) {
            kick_error = true;
        }
    }
    // И если цифры действительно есть, принудительно завершаем программу и говорим пользователю, что так НЕЛЬЗЯ ДЕЛАТЬ
    // после чего бьем по рукам, крича: "РУКИ УБЕРИ!!!!"
    if (kick_error) {
        cout << "Text cannot be crypted/decrypted with Vigener Cypher if there is digits in key" << endl;
        return "";
        exit(2);
    }


    int key_length = key.length();
    // Обычный словарь: номер -> буква
    map<int, string> number_to_letter = {
        {0, "a"}, {1, "b"}, {2, "c"}, {3, "d"}, {4, "e"},
        {5, "f"}, {6, "g"}, {7, "h"}, {8, "i"}, {9, "j"},
        {10, "k"}, {11, "l"}, {12, "m"}, {13, "n"}, {14, "o"},
        {15, "p"}, {16, "q"}, {17, "r"}, {18, "s"}, {19, "t"},
        {20, "u"}, {21, "v"}, {22, "w"}, {23, "x"}, {24, "y"},
        {25, "z"}
    };

    // Обратный словарь: буква -> номер
    unordered_map<string, int> letter_to_number;
    for (const auto& [number, letter] : number_to_letter) {
        letter_to_number[letter] = number;
    }

    // подготавливаем нужные переменные
    vector<string> words;
    stringstream ss(text);
    string word;
    string result;
    int keystringlength = 0;
    string keystring;
    // режем строку на слова и пихаем в вектор
    while (getline(ss, word, ' ')) {
        words.push_back(word);
    }

    // узнаем длину ключа
    for (string w : words) {
        keystringlength += w.size();
    }

    // начинаем сборку строки-ключа
    for (int i = 1; i <= (keystringlength / key.length()); i++) {
        keystring += key;
    }
    keystring += key.substr(0, (keystringlength % key_length));
    // приступаем к шифровке
    int keystatus = 0;
    for (string w : words) {
        // тут мы подгоняем ключ под каждое слово, содержащееся в векторе words
        w = lower(w);
        if (decryption) {
            // здесь начинается расшифровка, при условии, что аргумент decryption == true
            for (int i = 0; i < w.length(); i++) {
                string l1, l2;
                l1 = w[i];
                // если есть циферка или что еще, но не буква - просто добавляем в текст
                if (alphabetstr.find(l1) == std::string::npos) {
                    result += l1;
                }
                else {
                    l2 = keystring[keystatus];
                    int index = letter_to_number[l1] - letter_to_number[l2];
                    if (index < 0) {
                        index += letter_to_number.size();
                    }
                    result += number_to_letter[index];
                    keystatus += 1;
                }
            }
            result += " ";
        }
        else {
            // здесь начинается шифровка
            for (int i = 0; i < w.length(); i++) {
                string l1, l2;
                l1 = w[i];
                // если есть циферка или что еще, но не буква - просто добавляем в текст
                if (alphabetstr.find(l1) == std::string::npos) {
                    result += l1;
                }
                else {
                    l2 = keystring[keystatus];
                    int index = letter_to_number[l1] + letter_to_number[l2];
                    if (index >= letter_to_number.size()) {
                        index = index % letter_to_number.size();
                    }
                    result += number_to_letter[index];
                    keystatus += 1;
                }

            }
            result += " ";
        }
    }
    if (t != nullptr) {
        auto end = steady_clock::now();
        *t = chrono::duration_cast<chrono::microseconds>(end - start).count();
    }
    return result;
}

