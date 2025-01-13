#include<iostream>
#include<cmath>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

ifstream inputFile;
ofstream outputFile;

int main() {
    string originalText, fileContent, encryptedText = "", decryptedText;
    int alphabetSize = 26, shiftKey = 3;

    fileContent = "";
    inputFile.open("text.txt");
    if (inputFile.good()) {
        while (!inputFile.eof()) {
            string word;
            inputFile >> word;
            fileContent.append(word);
        }
        inputFile.close();
    }

    // Encrypt the text
    for (int i = 0; i < fileContent.size(); i++) {
        char currentChar = fileContent[i];
        if (currentChar > 'Z') currentChar -= 0x20;
        if (currentChar >= 'A' && currentChar <= 'Z') {
            encryptedText.push_back((currentChar + shiftKey - 'A') % alphabetSize + 'A');
        }
    }

    outputFile.open("encryptedText.txt");
    if (outputFile.good()) {
        outputFile << encryptedText;
        outputFile.close();
    }

    // Decrypt the text
    for (int i = 0; i < encryptedText.length(); i++) {
        char currentChar = encryptedText[i];
        currentChar -= shiftKey;
        if (currentChar < 'A') currentChar += alphabetSize;
        decryptedText.push_back(currentChar);
    }

    cout << decryptedText;

    outputFile.open("decryptedText.txt");
    if (outputFile.good()) {
        outputFile << decryptedText;
        outputFile.close();
    }

    return 0;
}
