#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;

void swap(int A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

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

int partitionTwoPointer(int A[], int first, int last) {
    int pivot = A[last];
    int lower = first;
    int upper = last - 1;

    while (lower <= upper) {
        while (lower <= upper && A[upper] >= pivot) {
            upper--;
        }
        while (lower <= upper && A[lower] <= pivot) {
            lower++;
        }
        if (lower < upper) {
            swap(A, lower, upper);
        }
    }

    swap(A, lower, last);
    return lower;
}

void quickSortTwoPointer(int A[], int first, int last) {
    if (first < last) {
        int mid = partitionTwoPointer(A, first, last);
        quickSortTwoPointer(A, first, mid - 1);
        quickSortTwoPointer(A, mid + 1, last);

    }
}

int partitionOnePointer(int A[], int first, int last) {
    int pivot;
    int a = A[first];
    int b = A[(int)floor(first / last)];
    int c = A[last];

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        pivot = b;
    }
    else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        pivot = a;
    }
    else if ((a <= c && c <= b) || (b <= c && c <= a)) {
        pivot = c;
    }
    
    int lowPointer = first - 1;
    for (int ptr = first; ptr <= last - 1; ptr++) {
        if (A[ptr] <= pivot) {
            lowPointer++;
            swap(A, lowPointer, ptr);
        }
    }
    lowPointer++;
    swap(A, lowPointer, last);
    return lowPointer;
}

void quickSortOnePointer(int A[], int first, int last) {
    if (first < last) {
        int mid = partitionOnePointer(A, first, last);
        quickSortOnePointer(A, first, mid - 1);
        quickSortOnePointer(A, mid + 1, last);

    }
}

int partitionMedianThree(int A[], int first, int last) {
    int pivot = A[last];
    int lowPointer = first - 1;
    for (int ptr = first; ptr <= last - 1; ptr++) {
        if (A[ptr] <= pivot) {
            lowPointer++;
            swap(A, lowPointer, ptr);
        }
    }
    lowPointer++;
    swap(A, lowPointer, last);
    return lowPointer;
}

void quickSortMedianThree(int A[], int first, int last) {
    if (first < last) {
        int mid = partitionMedianThree(A, first, last);
        quickSortMedianThree(A, first, mid - 1);
        quickSortMedianThree(A, mid + 1, last);

    }
}

int checkSort(int A[], int size) {
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        if (j > i) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int A[] = {7,3,6,1,8,9,2,10,4,5};

    quickSortMedianThree(A, 0, 9);

    int check = checkSort(A, 10);
    cout << check << endl;
    return 0;
}