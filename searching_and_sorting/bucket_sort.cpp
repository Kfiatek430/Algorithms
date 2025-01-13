#include<iostream>
#include<ctime>
#include<vector>
#include<string>

using namespace std;

void insertionSort(vector<float>& data, int size) {
    for (int i = 1; i < size; i++) {
        float currentElement = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > currentElement) {
            data[j + 1] = data[j];
            j--;
        }
    data[j + 1] = currentElement;
    }
}

void bucketSort(float array[], int size) {
    float maxElement = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > maxElement) {
            maxElement = array[i];
        }
    }

    vector<float> buckets[10];

    for (int i = 0; i < size; i++) {
        int bucketIndex = (int)(array[i] / (maxElement + 1) * 10);
        buckets[bucketIndex].push_back(array[i]);
    }

    for (int i = 0; i < 10; i++) {
        insertionSort(buckets[i], buckets[i].size());
    }

    int index = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            array[index++] = buckets[i][j];
        }
    }
}

int main() {
    srand(time(NULL));
    int arraySize;

    cout << "Enter the number of elements:\n";
    cin >> arraySize;

    float array[arraySize];

    cout << "Generated array: ";
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand() % (arraySize * 2) + 1;
        cout << array[i] << ((i < arraySize - 1) ? ", " : "\n");
    }

    bucketSort(array, arraySize);

    cout << "Sorted array: ";
    for (int i = 0; i < arraySize; i++) {
        cout << array[i] << ((i < arraySize - 1) ? ", " : "\n");
    }

    return 0;
}
