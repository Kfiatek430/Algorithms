#include<iostream>
#include<ctime>
using namespace std;

void merge(int start, int middle, int end, int array[], int temp[]) {
    int left = start, right = middle + 1, k = start;

    for (int p = start; p <= end; p++) {
        temp[p] = array[p];
    }

    while (left <= middle && right <= end) {
        if (temp[left] < temp[right]) {
            array[k] = temp[left];
            left++;
        } else {
            array[k] = temp[right];
            right++;
        }
        k++;
    }

    while (left <= middle) {
        array[k] = temp[left];
        left++;
        k++;
    }
}

void mergeSort(int start, int end, int array[], int temp[]) {
    if (start < end) {
        int middle = (start + end) / 2;
        mergeSort(start, middle, array, temp);
        mergeSort(middle + 1, end, array, temp);
        merge(start, middle, end, array, temp);
    }
}

int main() {
    srand(time(NULL));
    int size;

    cout << "Enter the number of elements:\n";
    cin >> size;

    int numbers[size];
    int temp[size];

    cout << "Generating numbers: ";
    for (int i = 0; i < size; i++) {
        numbers[i] = rand() % (size * 2) + 1;
        cout << numbers[i] << ((i < size - 1) ? "," : "\n");
    }

    mergeSort(0, size - 1, numbers, temp);

    for (int i = 0; i < size; i++) {
        cout << numbers[i] << ((i < size - 1) ? "," : "\n");
    }
}
