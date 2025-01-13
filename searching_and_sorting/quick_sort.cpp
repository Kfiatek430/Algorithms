#include<ctime>
#include<algorithm>
#include<iostream>

using namespace std;

void quickSort(int left, int right, int array[]) {
    int i = left, j = right;
    int pivot = array[(left + right) / 2];
    do {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;
        if (i <= j) {
            swap(array[i], array[j]);
            i++, j--;
        }
    } while (i <= j);

    if (left < j)
        quickSort(left, j, array);
    if (i < right)
        quickSort(i, right, array);
}

int main() {
    srand(time(NULL));
    int numElements;

    cout << "Enter the number of elements:\n";
    cin >> numElements;

    int numbers[numElements];

    cout << "Generating: ";
    for (int i = 0; i < numElements; i++) {
        numbers[i] = rand();
        cout << numbers[i] << ((i < numElements - 1) ? "," : "\n");
    }

    int left = 0;
    int right = numElements - 1;

    quickSort(left, right, numbers);

    for (int i = 0; i < numElements; i++)
        cout << numbers[i] << ((i < numElements - 1) ? "," : "\n");
}
