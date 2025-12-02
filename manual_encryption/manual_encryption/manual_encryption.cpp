#include <iostream>
#include <string>
#include "encryptions.h"
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    DoublePolybius cipher;

    string text_50 = "London is a capital of Great Britain";
    string text_500 = "vigenere cipher is a method of encrypting alphabetic text by using a series of interwoven caesar ciphers based on the letters of a keyword it is simple enough to be implemented by hand but also provides much stronger security than a basic substitution cipher for your tests you can use this long block of text to measure performance of your implementation and to ensure that spaces and non alphabet characters are handled correctly by your encryption and decryption functions";
    string text_1500 = "vigenere cipher long performance test text for encryption and decryption experiments using only lowercase letters and spaces in order to avoid issues with unsupported characters in a simple alphabet based implementation this text is intentionally verbose and repetitive so that the length reaches more than one thousand five hundred characters without relying on punctuation or digits or special symbols the purpose of such a long sequence of words is to let you measure the speed of your function with realistic but still controlled input data while keeping the structure easy to understand and to compare after encryption and decryption you can check that the original message is restored exactly character by character space by space if your algorithm is implemented correctly the vigenere cipher should transform this long stream of letters into something that looks random while still allowing perfect recovery when the same key is used for decryption a longer text is also useful to reveal logic errors such as incorrect key repetition off by one mistakes or problems with handling spaces and non alphabetic characters in this simplified scenario we choose to leave only letters and spaces so the algorithm can ignore nothing and simply process letters while copying spaces directly to the output the content of this block does not matter from a semantic point of view what matters is variety of letter combinations word lengths and general size of the input string feel free to modify this paragraph by inserting your own sentences random words or even generated content as long as you keep the limitations related to the alphabet you can also duplicate this entire block multiple times if you need even larger input for stress testing purposes or benchmarking on different systems or compilers some developers like to compare execution time between various optimization levels and different data structures using the same fixed input because that makes results comparable and reproducible across test runs and environments in addition a long text increases the chance that subtle bugs will appear early during debugging rather than much later in production environments where problems are harder to trace and to fix quickly";
    cout << "ШИФР ПОЛИБИУСА" << endl;

    //cipher.demonstrateProcess("London is a capital of Great Britain");
    double t_enc1, t_dec1, t_enc11, t_dec11, t_enc111, t_dec111;
    string encrypted_cipher = cipher.encrypt(text_50, &t_enc1);
    cout << "Исходный текст:" << "London is a capital of Great Britain" << endl;
    cout << "Зашифрованный текст:" << encrypted_cipher << endl;
    cout << "Время шифрования: " << t_enc1 << " мкс " << endl;
    string decrypted_cipher = cipher.decrypt(encrypted_cipher, &t_dec1);
    cout << "Расшифрованный текст:" << encrypted_cipher << endl;
    cout << "Время дешифрования: " << t_dec1 << " мкс " << endl;


    cout << endl << "ШИФР СЦИТАЛЫ";

    double t_enc2, t_dec2, t_enc22, t_dec22, t_enc222, t_dec222;
    Scytale c(5);
    cout << endl << "Исходное слово/предложение: " << text_50 << endl;
    string enc = c.encrypt(text_50, &t_enc2);
    cout << "Шифр: " << enc << endl;
    cout << "Время шифрования: " << t_enc2 << " мкс " << endl;
    string dec = c.decrypt(enc, &t_dec2);
    cout << "Расшифровано: " << dec << endl;
    cout << "Время дешифрования: " << t_dec2 << " мкс " << endl;


    Tritemia t;
    double t_enc3, t_dec3, t_enc33, t_dec33, t_enc333, t_dec333;
    string key;

    cout << endl << "TRITHEMIUS CIPHER";
    cout << endl << "Original text: " << text_50 << std::endl;

    string encrypted = t.encrypt(text_50, &t_enc3);
    cout << "Encrypted text: " << encrypted << std::endl;
    cout << "Encryption time: " << t_enc3 << " мкс " << endl;

    string decrypted = t.decrypt(encrypted, &t_dec3);
    cout << "Decrypted text: " << decrypted << std::endl;
    cout << "Decryption time: " << t_dec3 << " мкс " << endl;


    cout << endl << "ШИФР ПЛЕЙФЕРА" << endl;

    key = "secret";
    cout << "Исходный текст: " << text_50 << endl;
    double t_enc4, t_dec4, t_enc44, t_dec44, t_enc444, t_dec444;


    Pleifer cipher_pleifer(key);
    double encryptTime, decryptTime;

    string encrypted_pleifer = cipher_pleifer.encrypt(text_50, &t_enc4);
    cout << "Зашифрованный текст: " << encrypted_pleifer << endl;
    cout << "Время шифрования: " << t_enc4 << " мкс " << endl;

    string decrypted_pleifer = cipher_pleifer.decrypt(encrypted_pleifer, &t_dec4);
    cout << "Расшифрованный текст: " << decrypted_pleifer << endl;
    cout << "Время дешифрования: " << t_dec4 << " мкс " << endl;

    cout << endl << "ШИФР ВИЖЕНЕРА" << endl;

    double t_enc5, t_dec5, t_enc55, t_dec55, t_enc555, t_dec555;
    Vigener v;
    string crypted = v.vigenere(text_50, "secret", &t_enc5);
    string decrypted_vigener = v.vigenere(crypted, "secret", &t_dec5, true);
    cout << "Исходный текст:" << text_50 << endl;
    cout << "Зашифрованный текст: " << crypted << endl;
    cout << "Время шифрования: " << t_enc5 << " мкс" << endl;
    cout << decrypted_vigener << endl;
    cout << "Время дешифрования: " << t_dec5 << " мкс" << endl;


    //cout << endl << "ВЕЛИКИЙ ШИФР" << endl;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*legrand l;
    l.build_mappings();
    string plain;
    plain = "London is a capital of Great Britain";

    double t_enc6, t_dec6;
    string r1 = l.encrypt_text(plain, &t_enc6);
    cout << "\nЗашифрованный текст:\n" << r1 << "\nВремя: " << t_enc6 << " мкс\n";
    string r2 = l.decrypt_codes(r1, &t_dec6);
    cout << "Расшифровка:\n" << r2 << "\nВремя: " << t_dec6 << " мкс\n";
    */

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
    string enc7 = af.encrypt(text_50, a, b, &t_enc7);
    string dec7 = af.decrypt(enc7, a, b, &t_dec7);

    string enc11 = cipher.encrypt(text_500, &t_enc11);
    string dec11 = cipher.decrypt(enc11, &t_dec11);
    string enc111 = cipher.encrypt(text_1500, &t_enc111);
    string dec111 = cipher.decrypt(enc111, &t_dec111);

    string enc22 = c.encrypt(text_500, &t_enc22);
    string dec22 = c.decrypt(enc22, &t_dec22);
    string enc222 = c.encrypt(text_1500, &t_enc222);
    string dec222 = c.decrypt(enc222, &t_dec222);

    string enc33 = t.encrypt(text_500, &t_enc33);
    string dec33 = t.decrypt(enc33, &t_dec33);
    string enc333 = t.encrypt(text_1500, &t_enc333);
    string dec333 = t.decrypt(enc333, &t_dec333);

    string enc44 = cipher_pleifer.encrypt(text_500, &t_enc44);
    string dec44 = cipher_pleifer.decrypt(enc44, &t_dec44);
    string enc444 = cipher_pleifer.encrypt(text_1500, &t_enc444);
    string dec444 = cipher_pleifer.decrypt(enc444, &t_dec444);

    string enc55 = v.vigenere(text_1500, "secret", &t_enc55);
    string dec55 = v.vigenere(enc55, "secret", &t_dec55, true);
    string enc555 = v.vigenere(text_1500, "secret", &t_enc555);
    string dec555 = v.vigenere(enc555, "secret", &t_dec555, true);

    string enc77 = af.encrypt(text_500,a, b, &t_enc77);
    string dec77 = af.decrypt(enc77, a, b, &t_dec77);
    string enc777 = af.encrypt(text_1500, a, b, &t_enc777);
    string dec777 = af.decrypt(enc777, a, b, &t_dec777);

    cout << "Encrypted: " << enc7 << endl;
    cout << "Encryption time:" << t_enc7 << endl;
    cout << "Decrypted: " << dec7 << endl;
    cout << "Decryption time:" << t_dec7 << endl;

    cout << endl << "Сравнение скорости шифрования/дешифрования:" << endl << endl;

    cout << endl << "Текст ~ 50 символов "  << endl << endl;
    cout << "Шифрование" << endl;
    cout << "Шифр Полибиуса: " << t_enc1 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_enc2 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_enc3 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_enc4 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_enc5 << " мкс" << endl;
    //cout << "Великий шифр: " << t_enc6 << " мкс" << endl;
    cout << "Аффинный шифр:" << t_enc7 << " мкс" << endl;

    cout << endl << "Дешифрование" << endl;
    cout << "Шифр Полибиуса: " << t_dec1 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_dec2 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_dec3 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_dec4 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_dec5 << " мкс" << endl;
    //cout << "Великий шифр: " << t_dec6 << " мкс" << endl;
    cout << "Аффинный шифр: " << t_dec7 << " мкс" << endl;

    cout << endl << endl << "Текст ~ 500 символов " << endl << endl;
    cout << "Шифрование" << endl;
    cout << "Шифр Полибиуса: " << t_enc11 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_enc22 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_enc33 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_enc44 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_enc55 << " мкс" << endl;
    //cout << "Великий шифр: " << t_enc6 << " мкс" << endl;
    cout << "Аффинный шифр:" << t_enc77 << " мкс" << endl;

    cout << endl << "Дешифрование" << endl;
    cout <<  "Шифр Полибиуса: " << t_dec11 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_dec22 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_dec33 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_dec44 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_dec55 << " мкс" << endl;
    //cout << "Великий шифр: " << t_dec6 << " мкс" << endl;
    cout << "Аффинный шифр: " << t_dec77 << " мкс" << endl;

    cout << endl << endl <<  "Текст ~ 1500 символов " << endl << endl;
    cout << "Шифрование" << endl;
    cout << "Шифр Полибиуса: " << t_enc111 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_enc222 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_enc333 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_enc444 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_enc555 << " мкс" << endl;
    //cout << "Великий шифр: " << t_enc6 << " мкс" << endl;
    cout << "Аффинный шифр:" << t_enc77 << " мкс" << endl;
    cout << endl << "Дешифрование" << endl;
    cout << "Шифр Полибиуса: " << t_dec111 << " мкс" << endl;
    cout << "Шифр Сциталы: " << t_dec222 << " мкс" << endl;
    cout << "Шифр Тритемия: " << t_dec333 << " мкс" << endl;
    cout << "Шифр Плейфера: " << t_dec444 << " мкс" << endl;
    cout << "Шифр Виженера: " << t_dec555 << " мкс" << endl;
    //cout << "Великий шифр: " << t_dec6 << " мкс" << endl;
    cout << "Аффинный шифр: " << t_dec777 << " мкс" << endl;



    
}

