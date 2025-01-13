#include<iostream>
#include<ctime>
using namespace std;

void insertionSortMethod1(int array[], int size) {
    int currentIndex = 1;
    for (int i = 0; i < size;) {
        int currentElement = array[i];
        while (i > 0) {
            if (array[i - 1] <= currentElement) {
                break;
            } else {
                array[i] = array[i - 1];
                i--;
            }
        }
        array[i] = currentElement;
        i = currentIndex++;
    }

    for (int i = 0; i < size; i++) {
        cout << array[i] << ((i < size - 1) ? "," : "\n");
    }
}

void insertionSortMethod2(int array[], int size) {
    for (int currentIndex = 1; currentIndex < size; currentIndex++) {
        int currentElement = array[currentIndex];
        int i = currentIndex;

        while (i > 0) {
            if (currentElement < array[i - 1]) {
                array[i] = array[i - 1];
                array[i - 1] = currentElement;
            }
            i--;
        }
    }

    for (int i = 0; i < size; i++) {
        cout << array[i] << ((i < size - 1) ? "," : "\n");
    }
}

int main() {
    srand(time(NULL));
    int size;

    cout << "Enter the number of elements:\n";
    cin >> size;
    int numbers[size];

    cout << "Generating numbers: ";
    for (int i = 0; i < size; i++) {
        numbers[i] = rand() % (size * 2) + 1;
        cout << numbers[i] << ((i < size - 1) ? "," : "\n");
    }

    // Call the first sorting method
    // insertionSortMethod1(numbers, size);

    // Call the second sorting method
    insertionSortMethod2(numbers, size);
}
