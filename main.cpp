#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

void insertionSort(int A[], int arraySize) {
    for (int j = 1; j < arraySize; j++) {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] >= key) {
            A[i+1] = A[i];
            i--;
        }
        A[i+1] = key;
    }
}



int main() {
    int A[] = {7,3,6,1,8,9,2,10,4,5};

    insertionSort(A, 10);

    cout << "Test" << endl;
    return 0;
}