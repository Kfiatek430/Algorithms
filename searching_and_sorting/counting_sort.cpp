#include<iostream>
#include<ctime>
using namespace std;

void countingSort(int array[], int size) {
    int maxElement = array[0];
    int minElement = array[0];

    for (int i = 1; i < size; i++) {
        if(array[i] > maxElement) {
            maxElement = array[i];
        }
        if(array[i] < minElement) {
            minElement = array[i];
        }
    }

    int range = maxElement - minElement + 1;
    int countArray[range] = {0};

    for (int i = 0; i < size; i++) {
        countArray[array[i] - minElement]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        for (int j = 0; j < countArray[i]; j++) {
            array[index] = i + minElement;
            index++;
        }
    }
}

int main() {
    srand(time(NULL));
    int size;

    cout << "Enter the number of elements:\n";
    cin >> size;
    int array[size];

    cout << "Generated array: ";
    for (int i = 0; i < size; i++) {
        array[i] = rand() % size + 1;
        cout << array[i] << ((i < size - 1) ? "," : "\n");
    }

    countingSort(array, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << ((i < size - 1) ? "," : "\n");
    }

    return 0;
}
