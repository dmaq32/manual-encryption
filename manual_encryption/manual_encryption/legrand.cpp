#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>
#include <limits>
#include "encryptions.h"

using namespace std;
using steady_clock = chrono::steady_clock;


static uint32_t to_lower_cp(uint32_t cp) {
    if (cp >= 'A' && cp <= 'Z') return cp + 32;
    return cp;
}

static bool is_letter_or_space(uint32_t cp) {
    return (cp >= 'A' && cp <= 'Z') || (cp >= 'a' && cp <= 'z') || cp == 0x20;
}

unordered_map<string, int> syllable_to_code;
unordered_map<int, string> code_to_syllable;

void legrand::build_mappings() {
    syllable_to_code.clear();
    code_to_syllable.clear();

    vector<string> common_syllables = {
        "the", "and", "ing", "ion", "ent", "her", "for", "tha", "nth", "int",
        "ere", "tio", "ter", "est", "ers", "ati", "hat", "ate", "all", "eth",
        "hes", "ver", "his", "oft", "ith", "men"
    };

    vector<string> letters;
    for (char c = 'a'; c <= 'z'; ++c) letters.push_back(string(1, c));
    letters.push_back(" ");

    vector<string> all_syllables;
    all_syllables.insert(all_syllables.end(), common_syllables.begin(), common_syllables.end());
    all_syllables.insert(all_syllables.end(), letters.begin(), letters.end());

    int code = 100;
    for (const auto& syl : all_syllables) {
        syllable_to_code[syl] = code;
        code_to_syllable[code] = syl;
        ++code;
    }

    syllable_to_code["???"] = 999;
    code_to_syllable[999] = "???";
}

string legrand::encrypt_text(const string& plain, double* t) {
    vector<uint32_t> cps = utf8_to_codepoints(plain);
    vector<uint32_t> norm;
    for (auto cp : cps)
        if (is_letter_or_space(cp))
            norm.push_back(to_lower_cp(cp));

    auto start = steady_clock::now();
    string out;
    size_t i = 0;

    while (i < norm.size()) {
        int max_len = 0;
        int code = 999;

        for (auto& p : syllable_to_code) {
            const string& syl = p.first;
            if (syl.size() <= norm.size() - i) {
                bool match = true;
                for (size_t k = 0; k < syl.size(); ++k) {
                    if (norm[i + k] != syl[k]) { match = false; break; }
                }
                if (match && (int)syl.size() > max_len) {
                    max_len = syl.size();
                    code = p.second;
                }
            }
        }

        if (max_len > 0) {
            char buf[4];
            snprintf(buf, sizeof(buf), "%03d", code);
            out += buf;
            i += max_len;
        }
        else {
            if (norm[i] == 0x20) out += "000";
            else out += "999";
            ++i;
        }
    }

    if (t) *t = chrono::duration_cast<chrono::microseconds>(
        steady_clock::now() - start).count();
    return out;
}

string legrand::decrypt_codes(const string& codes, double* t) {
    auto start = steady_clock::now();
    string s;
    for (char c : codes)
        if (isdigit(c) || isspace(c))
            s.push_back(c);

    if (t) *t = 0;

    bool hasSpace = false;
    for (char c : s) if (isspace((unsigned char)c)) hasSpace = true;

    if (!hasSpace && s.size() % 3 != 0) {
        return "[ERROR: неверный формат кода]\n";
    }

    vector<string> tok;
    string cur;
    if (hasSpace) {
        for (char c : s) {
            if (isspace((unsigned char)c)) {
                if (!cur.empty()) { tok.push_back(cur); cur.clear(); }
            }
            else cur.push_back(c);
        }
        if (!cur.empty()) tok.push_back(cur);
    }
    else {
        for (size_t i = 0; i < s.size(); i += 3)
            tok.push_back(s.substr(i, 3));
    }

    string out;
    for (auto& t2 : tok) {
        if (t2.size() != 3) { out += '?'; continue; }
        int code = stoi(t2);
        auto it = code_to_syllable.find(code);
        if (it != code_to_syllable.end())
            out += it->second;
        else
            out += '?';
    }

    if (t) *t = chrono::duration_cast<chrono::microseconds>(
        steady_clock::now() - start).count();
    return out;
}
