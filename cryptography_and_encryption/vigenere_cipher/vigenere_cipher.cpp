
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr int ALPHABET_SIZE = 26;

void generateVigenereTable(char table[ALPHABET_SIZE][ALPHABET_SIZE]) {
    for (int row = 0; row < ALPHABET_SIZE; ++row) {
        for (int col = 0; col < ALPHABET_SIZE; ++col) {
            table[row][col] = 'A' + (col + row) % ALPHABET_SIZE;
        }
    }
}

string readFromFile(const string& filename) {
    ifstream inFile(filename);
    string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    content.erase(remove_if(content.begin(), content.end(), [](char c) { return isspace(c); }), content.end());
    transform(content.begin(), content.end(), content.begin(), ::toupper);
    return content;
}

void writeToFile(const string& filename, const string& content) {
    ofstream outFile(filename);
    outFile << content;
    outFile.close();
}

string encryptText(const string& plaintext, const string& key, const char table[ALPHABET_SIZE][ALPHABET_SIZE]) {
    string encrypted;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char plainChar = plaintext[i];
        char keyChar = key[i % key.length()];
        encrypted.push_back(table[plainChar - 'A'][keyChar - 'A']);
    }
    return encrypted;
}

string decryptText(const string& encryptedText, const string& key, const char table[ALPHABET_SIZE][ALPHABET_SIZE]) {
    string decrypted;
    for (size_t i = 0; i < encryptedText.length(); ++i) {
        char encryptedChar = encryptedText[i];
        char keyChar = key[i % key.length()];
        for (int row = 0; row < ALPHABET_SIZE; ++row) {
            if (table[row][keyChar - 'A'] == encryptedChar) {
                decrypted.push_back('A' + row);
                break;
            }
        }
    }
    return decrypted;
}

int main() {
    char vigenereTable[ALPHABET_SIZE][ALPHABET_SIZE];
    generateVigenereTable(vigenereTable);

    string text = readFromFile("text.txt");
    string key = "EXAMPLEKEY";

    string encryptedText = encryptText(text, key, vigenereTable);
    writeToFile("encrypted.txt", encryptedText);

    string decryptedText = decryptText(encryptedText, key, vigenereTable);
    writeToFile("decrypted.txt", decryptedText);

    cout << "Original text: " << text << endl;
    cout << "Encrypted text: " << encryptedText << endl;
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}