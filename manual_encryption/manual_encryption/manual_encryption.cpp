#include <iostream>
#include <string>
#include <fstream>
#include "encryptions.h"
using namespace std;
string read_file(const string& filename) {
    ifstream in(filename);
    string text, line;
    while (getline(in, line)) {
        text += line;
    }
    return text;
}
template<typename Func, typename... Args>
auto Time(Func&& func, Args&&... args) {
    auto start = chrono::high_resolution_clock::now();

    std::invoke(forward<Func>(func), forward<Args>(args)...);

    auto end = high_resolution_clock::now();
    return chrono::duration_cast<microseconds>(end - start);
}

int main()
{

    
    setlocale(LC_ALL, "Russian");
    DoublePolybius cipher;

    string text_50 = read_file("file_50.txt");
    string text_1500 = read_file("file_1500.txt");
    string text_5000 = read_file("file_5000.txt");
    cout << "ШИФР ПОЛИБИУСА" << endl;

    double t_enc1, t_dec1, t_enc11, t_dec11, t_enc111, t_dec111;
    string encrypted_cipher = cipher.encrypt(text_50);
    t_enc1 = Time(cipher.encrypt(text_50)).count();
    cout << "Исходный текст:" << "London is the capital of Great Britain" << endl;
    cout << "Зашифрованный текст:" << encrypted_cipher << endl;
    cout << "Время шифрования: " << t_enc1 << " мкс " << endl;
    string decrypted_cipher = cipher.decrypt(encrypted_cipher);
    t_dec1 = Time(cipher.decrypt(encrypted_cipher)).count();
    cout << "Расшифрованный текст:" << decrypted_cipher << endl;
    cout << "Время дешифрования: " << t_dec1 << " мкс " << endl;


    cout << endl << "ШИФР СЦИТАЛЫ" << endl;

    double t_enc2, t_dec2, t_enc22, t_dec22, t_enc222, t_dec222;
    Scytale c(5);
    cout << "Исходное слово/предложение: " << text_50 << endl;
    string enc = c.encrypt(text_50);;
    t_enc2 = Time(c.encrypt(text_50)).count();
    cout << "Зашифрованное слово: " << enc << endl;
    cout << "Время шифрования: " << t_enc2 << " мкс " << endl;
    t_dec2 = Time(c.decrypt(enc)).count();
    string dec = c.decrypt(enc);
    cout << "Расшифрованный текст: " << dec << endl;
    cout << "Время дешифрования: " << t_dec2 << " мкс " << endl;


    Tritemia t;
    double t_enc3, t_dec3, t_enc33, t_dec33, t_enc333, t_dec333;
    string key;

    cout << endl << "ШИФР ТРИТЕМИЯ";
    cout << endl << "Исходный текст: " << text_50 << std::endl;

    string encrypted = t.encrypt(text_50);
    t_enc3 = Time(t.encrypt(text_50)).count();
    cout << "Зашифрованный текст: " << encrypted << std::endl;
    cout << "Время дешифрования: " << t_enc3 << " мкс " << endl;

    string decrypted = t.decrypt(encrypted);
    t_dec3 = Time(c.decrypt(encrypted)).count();
    cout << "Расшифрованный текст: " << decrypted << std::endl;
    cout << "Время дешифрования: " << t_dec3 << " мкс " << endl;


    cout << endl << "ШИФР ПЛЕЙФЕРА" << endl;

    key = "secret";
    cout << "Исходный текст: " << text_50 << endl;
    double t_enc4, t_dec4, t_enc44, t_dec44, t_enc444, t_dec444;


    Pleifer cipher_pleifer(key);
    double encryptTime, decryptTime;


    string encrypted_pleifer = cipher_pleifer.encrypt(text_50);
    t_enc4 = Time(cipher_pleifer.decrypt(text_50)).count();
    cout << "Зашифрованный текст: " << encrypted_pleifer << endl;
    cout << "Время шифрования: " << t_enc4 << " мкс " << endl;

    string decrypted_pleifer = cipher_pleifer.decrypt(encrypted_pleifer);
    t_dec4 = Time(cipher_pleifer.decrypt(encrypted_pleifer)).count();
    cout << "Расшифрованный текст: " << decrypted_pleifer << endl;
    cout << "Время дешифрования: " << t_dec4 << " мкс " << endl;

    cout << endl << "ШИФР ВИЖЕНЕРА" << endl;

    double t_enc5, t_dec5, t_enc55, t_dec55, t_enc555, t_dec555;
    Vigener v;
    string crypted = v.vigenere(text_50, "secret");
    t_enc5 = Time(v.vigenere(text_50,"secret")).count();
    string decrypted_vigener = v.vigenere(crypted, "secret", true);
    cout << "Исходный текст:" << text_50 << endl;
    cout << "Зашифрованный текст: " << crypted << endl;
    cout << "Время шифрования: " << t_enc5 << " мкс" << endl;
    t_dec5 = Time(v.vigenere(crypted, "secret",true)).count();
    cout << decrypted_vigener << endl;
    cout << "Время дешифрования: " << t_dec5 << " мкс" << endl;


    cout << endl << "ВЕЛИКИЙ ШИФР" << endl;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    legrand l;
    l.build_mappings();
    string plain;

    double t_enc6, t_dec6, t_enc66, t_dec66, t_enc666, t_dec666;
    cout << "Исходный текст:" << text_50 << endl;
    string r1 = l.encrypt_text(text_50);
    t_enc6 = Time(l.encrypt_text(text_50)).count();
    cout << "Зашифрованный текст:\n" << r1 << "\nВремя: " << t_enc6 << " мкс\n";
    string r2 = l.decrypt_codes(r1);
    t_dec6 = Time(l.decrypt_codes(r1)).count();
    cout << "Расшифровка:\n" << r2 << "\nВремя: " << t_dec6 << " мкс\n";
    

    cout << endl << "АФИННЫЙ ШИФР:" << endl;
    Affine af;
    int a, b;
    double t_enc7, t_dec7, t_enc77, t_dec77, t_enc777, t_dec777;


    cout << "Enter a (1,3,5,7,9,11,15,17,19,21,23,25): ";
    cin >> a;

    if (!af.checkA(a)) {
        cout << "Bad 'a' value\n";
        return 1;
    }

    cout << "Enter b (0-25): ";
    cin >> b;
    b = b % 26;
    if (b < 0) b += 26;

    cin.ignore();


    t_enc7 = Time(af.encrypt(text_50,a,b)).count();
    t_dec7 = Time(af.encrypt(enc, a, b)).count();


    string enc7 = af.encrypt(text_50, a, b);
    string dec7 = af.decrypt(enc7, a, b);

    string enc11 = cipher.encrypt(text_1500);
    t_enc11 = Time(cipher.encrypt(text_1500)).count();
    string dec11 = cipher.decrypt(enc11);
    t_dec11 = Time(cipher.encrypt(enc11)).count();
    string enc111 = cipher.encrypt(text_5000);
    t_enc111 = Time(cipher.encrypt(text_5000)).count();
    string dec111 = cipher.decrypt(enc111);
    t_dec111 = Time(cipher.encrypt(enc111)).count();

    string enc22 = c.encrypt(text_1500);
    t_enc22 = Time(c.encrypt(text_1500)).count();
    string dec22 = c.decrypt(enc22);
    t_dec22 = Time(c.encrypt(enc22)).count();
    string enc222 = c.encrypt(text_5000);
    t_enc222 = Time(c.encrypt(text_5000)).count();
    string dec222 = c.decrypt(enc222);
    t_dec222 = Time(c.encrypt(enc222)).count();

    string enc33 = t.encrypt(text_1500);
    t_enc33 = Time(t.encrypt(text_1500)).count();
    string dec33 = t.decrypt(enc33);
    t_dec33 = Time(t.encrypt(enc33)).count();
    string enc333 = t.encrypt(text_5000);
    t_enc333 = Time(t.encrypt(text_5000)).count();
    string dec333 = t.decrypt(enc333);
    t_dec33 = Time(t.encrypt(enc333)).count();

    string enc44 = cipher_pleifer.encrypt(text_1500);
    t_enc44 = Time(cipher_pleifer.encrypt(text_1500)).count();
    string dec44 = cipher_pleifer.decrypt(enc44);
    t_dec44 = Time(cipher_pleifer.encrypt(enc44)).count();
    string enc444 = cipher_pleifer.encrypt(text_5000);
    t_enc444 = Time(cipher_pleifer.encrypt(text_5000)).count();
    string dec444 = cipher_pleifer.decrypt(enc444);
    t_dec444 = Time(cipher_pleifer.encrypt(enc444)).count();

    string enc55 = v.vigenere(text_1500, "secret");
    t_enc55 = Time(v.vigenere(text_1500,"secret")).count();
    string dec55 = v.vigenere(enc55, "secret", true);
    t_dec55 = Time(v.vigenere(enc55, "secret",true)).count();
    string enc555 = v.vigenere(text_5000, "secret");
    t_enc555 = Time(v.vigenere(text_5000, "secret")).count();
    string dec555 = v.vigenere(enc555, "secret", true);
    t_dec555 = Time(v.vigenere(enc555, "secret",true)).count();


    string enc66 = l.encrypt_text(text_1500);
    t_enc66 = Time(l.encrypt_text(text_1500)).count();
    string dec66 = l.encrypt_text(enc66);
    t_dec66 = Time(l.encrypt_text(enc66)).count();
    string enc666 = l.encrypt_text(text_5000);
    t_enc666 = Time(l.encrypt_text(text_5000)).count();
    string dec666 = l.encrypt_text(enc666);
    t_dec666 = Time(l.encrypt_text(enc666)).count();


    string enc77 = af.encrypt(text_1500,a, b);
    t_enc77 = Time(af.encrypt(text_1500,a,b)).count();
    string dec77 = af.decrypt(enc77, a, b);
    t_enc77 = Time(af.encrypt(enc77, a, b)).count();
    string enc777 = af.encrypt(text_5000, a, b);
    t_enc777 = Time(af.encrypt(text_5000, a, b)).count();
    string dec777 = af.decrypt(enc777, a, b);
    t_enc77 = Time(af.encrypt(enc777, a, b)).count();


    cout << "Encrypted: " << enc7 << endl;
    cout << "Encryption time:" << t_enc7 << endl;
    cout << "Decrypted: " << dec7 << endl;
    cout << "Decryption time:" << t_dec7 << endl;




    Atbash atbash;
    cout << endl << "ШИФР АТБАШ" << endl;

    double t_enc8, t_dec8, t_enc88, t_dec88, t_enc888, t_dec888;
    string encrypted_atbash = atbash.EncryptDecrypt(text_50);
    cout << "Исходный текст:" << "London is the capital of Great Britain" << endl;
    cout << "Зашифрованный текст:" << encrypted_atbash << endl;
    cout << "Время шифрования: " << t_enc8 << " мкс " << endl;

    string decrypted_atbash = atbash.EncryptDecrypt(encrypted_atbash);
    cout << "Расшифрованный текст:" << decrypted_atbash << endl;
    cout << "Время дешифрования: " << t_dec8 << " мкс " << endl;

    string enc88 = atbash.EncryptDecrypt(text_1500);
    t_enc88 = Time(atbash.EncryptDecrypt(text_1500)).count();
    string dec88 = atbash.EncryptDecrypt(enc88);
    t_dec88 = Time(atbash.EncryptDecrypt(enc88)).count();
    string enc888 = atbash.EncryptDecrypt(text_5000);
    t_enc888 = Time(atbash.EncryptDecrypt(text_5000)).count();
    string dec888 = atbash.EncryptDecrypt(enc888);
    t_dec888 = Time(atbash.EncryptDecrypt(enc888)).count();







    cout << endl << "Сравнение скорости шифрования/дешифрования:" << endl << endl;

    cout << endl << "Текст ~ 500 символов "  << endl << endl;
    cout << "Шифрование" << endl;
    cout << "Шифр Полибиуса: " << t_enc1 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_enc2 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_enc3 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_enc4 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_enc5 << " мкс" << endl;
    cout << "Великий шифр: " << t_enc6 << " мкс" << endl;
    cout << "Аффинный шифр:" << t_enc7 << " мкс" << endl;
    cout << "Шифр Атбаш:" << t_enc8 << " мкс" << endl;

    cout << endl << "Дешифрование" << endl;
    cout << "Шифр Полибиуса: " << t_dec1 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_dec2 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_dec3 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_dec4 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_dec5 << " мкс" << endl;
    cout << "Великий шифр: " << t_dec6 << " мкс" << endl;
    cout << "Аффинный шифр: " << t_dec7 << " мкс" << endl;
    cout << "Шифр Атбаш:" << t_dec8 << " мкс" << endl;

    cout << endl << endl << "Текст ~ 1500 символов " << endl << endl;
    cout << "Шифрование" << endl;
    cout << "Шифр Полибиуса: " << t_enc11 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_enc22 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_enc33 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_enc44 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_enc55 << " мкс" << endl;
    cout << "Великий шифр: " << t_enc66 << " мкс" << endl;
    cout << "Аффинный шифр:" << t_enc77 << " мкс" << endl;
    cout << "Шифр Атбаш:" << t_enc88 << " мкс" << endl;

    cout << endl << "Дешифрование" << endl;
    cout <<  "Шифр Полибиуса: " << t_dec11 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_dec22 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_dec33 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_dec44 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_dec55 << " мкс" << endl;
    cout << "Великий шифр: " << t_dec66 << " мкс" << endl;
    cout << "Аффинный шифр: " << t_dec77 << " мкс" << endl;
    cout << "Шифр Атбаш:" << t_dec88 << " мкс" << endl;

    cout << endl << endl <<  "Текст ~ 5000 символов " << endl << endl;
    cout << "Шифрование" << endl;
    cout << "Шифр Полибиуса: " << t_enc111 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_enc222 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_enc333 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_enc444 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_enc555 << " мкс" << endl;
    cout << "Великий шифр: " << t_enc666 << " мкс" << endl;
    cout << "Аффинный шифр:" << t_enc777 << " мкс" << endl;
    cout << "Шифр Атбаш:" << t_enc888 << " мкс" << endl;

    cout << endl << "Дешифрование" << endl;
    cout << "Шифр Полибиуса: " << t_dec111 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_dec222 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_dec333 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_dec444 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_dec555 << " мкс" << endl;
    cout << "Великий шифр: " << t_dec666 << " мкс" << endl;
    cout << "Аффинный шифр: " << t_dec777 << " мкс" << endl;
    cout << "Шифр Атбаш:" << t_dec888 << " мкс" << endl;

    
}

