#include<ctime>
#include<algorithm>
#include<iostream>

using namespace std;

int main() {
    srand(time(NULL));
    int num_elements, search_value;

    cout << "Enter number of elements:\n";
    cin >> num_elements;
    int numbers[num_elements];

    cout << "Random numbers: ";
    for (int i = 0; i < num_elements; i++) {
        numbers[i] = rand() % (num_elements * 2) + 1;
        cout << numbers[i] << ((i < num_elements - 1) ? "," : "\n");
    }

    sort(numbers, numbers + num_elements);
    cout << "Sorted numbers: ";
    for (int i = 0; i < num_elements; i++)
        cout << "[" << i << "]:" << numbers[i] << ((i < num_elements - 1) ? "," : "\n");

    cout << "Enter the number to search:\n";
    cin >> search_value;

    int low = 0, high = num_elements - 1, mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (numbers[mid] == search_value) {
            cout << "Index of the searched number: " << mid;
            return 0;
        }
        else {
            if (numbers[mid] < search_value)
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    cout << search_value << " is not in the array";
}