#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int findInTextNaive(const string pattern, const string text, int* operationCounter = nullptr) {
    int patternLen = pattern.length();
    int textLen = text.length();

    if (operationCounter) *operationCounter = 0;

    for (int i = 0; i <= textLen - patternLen; i++) {
        int matchCount = 0;
        int tempTextIdx = i;
        for (int j = 0; j < patternLen; j++) {

            if (operationCounter) (*operationCounter)++;
            if (text[tempTextIdx++] == pattern[j]) {
                matchCount++;
            } else {
                break;
            }
        }

        if (matchCount == patternLen) {
            return i;
        }
    }

    return -1;
}

int findInTextBoyerMoore(const string text, const string pattern, int* operationCounter = nullptr) {
    int shiftTable[0x100];
    int patternLen = pattern.length();
    int textLen = text.length();

    for (int i = 0; i < 0x100; i++) {
        shiftTable[i] = patternLen;
    }

    for (int i = 0; i < patternLen - 1; i++) {
        shiftTable[pattern[i]] = patternLen - 1 - i;
    }

    if (operationCounter) *operationCounter = 0;

    for (int textIdx = patternLen - 1; textIdx < textLen; textIdx += shiftTable[text[textIdx]]) {
        int patternIdx = patternLen - 1;

        if (operationCounter) (*operationCounter)++;
        if (text[textIdx] == pattern[patternIdx]) {
            int tempTextIdx = textIdx;
            while (--patternIdx >= 0 && text[--tempTextIdx] == pattern[patternIdx]) {}
            if (patternIdx < 0) {
                return tempTextIdx;
            }
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <fileName> pattern" << endl;
        return -1;
    }

    string textTemplate, text;

    ifstream inputFile(argv[1]);

    while (getline(inputFile, textTemplate))
        text.append(textTemplate);

    string pattern = argv[2];

    cout << "Searching for " << pattern << " in file " << argv[1] << endl;

    int operationCounter;

    auto startTime = chrono::high_resolution_clock::now();
    int indexNaive = findInTextNaive(pattern, text, &operationCounter);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> naiveDuration = endTime - startTime;

    cout << "Naive Search:" << endl;
    cout << "Index: " << indexNaive << endl;
    cout << "Operations: " << operationCounter << endl;
    cout << "Time: " << naiveDuration.count() << " seconds" << endl;

    startTime = chrono::high_resolution_clock::now();
    int indexBoyerMoore = findInTextBoyerMoore(text, pattern, &operationCounter);
    endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> bmDuration = endTime - startTime;

    cout << "\nBoyer-Moore Search:" << endl;
    cout << "Index: " << indexBoyerMoore << endl;
    cout << "Operations: " << operationCounter << endl;
    cout << "Time: " << bmDuration.count() << " seconds" << endl;

    return 0;
}
