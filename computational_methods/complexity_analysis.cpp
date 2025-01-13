#include <iostream>
#include <algorithm>
#include <fstream>
#include <clocale>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

ifstream inputFile;

struct MeasurementData {
    char algorithmName[10];
    int initialDataSize;
    float dataGrowthRate;
    int repetitions;
    int trialsPerRun;
    char outputFilename[20];
    void (*algorithmFunction)(int, int, int*);
};

void bubbleSort(int start, int end, int array[]);
void quickSort(int start, int end, int array[]);

const MeasurementData measurements[2] = {
    {"Bubble", 2000, 1.3, 10, 4, "bubbleSortData.csv", bubbleSort},
    {"Quick", 10000, 1.5, 30, 4, "quickSortData.csv", quickSort}
};

void bubbleSort(int start, int end, int array[]) {
    bool swapped;
    for (int j = start + 1; j < end; j++) {
        swapped = false;
        for (int i = start; i <= end - j; i++) {
            if (array[i] > array[i + 1]) {
                swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void quickSort(int start, int end, int array[]) {
    swap(array[(start + end) / 2], array[end - 1]);
    int pivot = array[end - 1];
    int left = start;
    int right = end - 2;

    while (left < right) {
        while (left < end && array[left] <= pivot) left++;
        while (right > start && array[right] > pivot) right--;
        if (left < right) swap(array[left], array[right]);
    }

    left = (left + right + 1) / 2;
    if (array[left] > pivot) swap(array[left], array[end - 1]);
    right = left + 1;

    while (left > start && array[left - 1] == pivot) left--;
    while (right < end && array[right] == pivot) right++;

    if (left - start >= 2) quickSort(start, left, array);
    if (end - right >= 2) quickSort(right, end, array);
}

float testAlgorithm(int numTrials, int dataSize, void (*algorithm)(int, int, int*)) {
    printf("Processing for %i...", dataSize);

    float executionTimes[numTrials];
    int dataArray[dataSize];

    for (int trial = 0; trial < numTrials; trial++) {
        for (int i = 0; i < dataSize; i++)
            dataArray[i] = rand() * rand();

        int start = 0;
        int end = dataSize - 1;

        auto startTime = high_resolution_clock::now();
        algorithm(start, end, dataArray);
        auto endTime = high_resolution_clock::now();

        for (int i = 0; i < dataSize - 2; i++) {
            if (dataArray[i] > dataArray[i + 1]) {
                printf("Sorting error at indices %i and %i: %i > %i.\n", i, i + 1, dataArray[i], dataArray[i + 1]);
                system("pause");
                return 1;
            }
        }

        auto duration = duration_cast<microseconds>(endTime - startTime);
        executionTimes[trial] = (float)duration.count() / 1.0E6;
    }

    sort(executionTimes, executionTimes + numTrials);
    float averageTime = 0;
    for (int i = 1; i < numTrials - 1; i++) averageTime += executionTimes[i];
    averageTime /= (numTrials - 2);

    printf("done\n");
    return averageTime;
}

int main() {
    setlocale(LC_NUMERIC, "English_United States.1250");
    printf("Measuring algorithm complexity\n");
    printf("Bubble Sort and Quick Sort\n");

    for (int measurementIndex = 0; measurementIndex < 2; measurementIndex++) {
        #define config measurements[measurementIndex]
        #define arraySize (int)(config.initialDataSize * pow(config.dataGrowthRate, i))

        const char *filename = config.outputFilename;
        printf("Testing algorithm %s\n", filename);

        FILE *file = fopen(filename, "w");
        fclose(file);

        float initialTime;

        for (int i = 0; i < config.repetitions; i++) {
            printf("%i/%i ", i + 1, config.repetitions);
            float timeTaken = testAlgorithm(config.trialsPerRun, arraySize, config.algorithmFunction);
            if (i == 0) initialTime = timeTaken;

            printf("%i;%f;%f\n", arraySize, timeTaken, initialTime * arraySize / config.initialDataSize);

            file = fopen(filename, "a");
            fprintf(file, "%i;%f;%f\n", arraySize, timeTaken, initialTime * arraySize / config.initialDataSize);
            fclose(file);
        }

        string content = "";
        inputFile.open(filename);
        if (inputFile.good()) {
            printf("\nSaved to file: %s\n", filename);
            while (!inputFile.eof()) {
                getline(inputFile, content);
                cout << content << endl;
            }
            inputFile.close();
        } else {
            printf("Error reading file\n");
        }
    }

    system("pause");
    return 0;
}
