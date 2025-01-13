#include<iostream>
#include<ctime>
using namespace std;

void bubbleSort(int array[], int size) {
    bool swapped;
    for (int i = 1; i < size; i++) {
        swapped = false;
        for (int j = 0; j < size - i; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    for (int i = 0; i < size; i++) {
        cout << array[i] << ((i < size - 1) ? ", " : "\n");
    }
}

int main() {
    srand(time(NULL));
    int arraySize;

    cout << "Enter the number of elements:\n";
    cin >> arraySize;

    int array[arraySize];

    cout << "Generated array: ";
    for (int i = 0; i < arraySize; i++) {
        array[i] = rand() % (arraySize * 2) + 1;
        cout << array[i] << ((i < arraySize - 1) ? ", " : "\n");
    }

    bubbleSort(array, arraySize);
}