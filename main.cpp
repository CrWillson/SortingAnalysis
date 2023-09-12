#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>
#include <functional>

using namespace std;

/**
 * Swap elements at index a and index b in array A
*/
void swap(int A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

/**
 * Generate a randomized array of size n
 * @return an int array of size n
*/
int* generateRandomArray(int n) {
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
            A[i] = (rand() % n) + 1;
    }
    return A;
}

/**
 * Generate a forward sorted array of size n
 * @return an int array of size n
*/
int* generateForwardSortedArray(int n) {
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        A[i] = i + 1;
    }
    /*for (int i = 0; i < n; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;*/
    return A;
}

/**
 * Generate a reverse sorted array of size n
 * @return an int array of size n
*/
int* generateReverseSortedArray(int n) {
    int* A = new int[n];
    int j = 0;
    for (int i = n; i > 0; i--) {
        A[j] = i;
        j++;
    }
    /*for (int i = 0; i < n; i++) {
        cout << A[i] << ", ";
    }
    cout << endl;*/
    return A;
}

/**
 * Check if array A with size n is sorted
 * @return true if the array is sorted
*/
bool isSorted(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        if (j > i) {
            return false;
        }
    }
    return true;
}

/**
 * Quick sort partition method that uses the last element as the pivot and two pointers
 * @return the index of the lower pointer
*/
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

/**
 * Quick sort partition method that uses the last element as the pivot and one pointer
 * @return the index of the lower pointer
*/
int partitionOnePointer(int A[], int first, int last) {
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

/**
 * Quick sort partition method that uses the median of the first, middle, and last
 * element as the pivot.
 * 
 * The two pointer method is used.
 * @return the index of the lower pointer
*/
int partitionMedianThree(int A[], int first, int last) {
    int pivot;
    int a = A[first];
    int b = A[(int)floor((last - first) / 2)];
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

/**
 * Quick sort partition method that uses the middle index as the pivot.
 * 
 * The two pointer method is used.
 * @return the index of the lower pointer
*/
int partitionMiddleIndex(int A[], int first, int last) {
    int pivot = A[(int)floor((last - first) / 2)];
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

/**
 * Quick sort array A from indices first to last using the partitionMethod given
*/
void quickSort(int A[], int first, int last, function<int(int[], int, int)> partitionMethod) {
    if (first < last) {
        int mid = partitionMethod(A, first, last);
        quickSort(A, first, mid - 1, partitionMethod);
        quickSort(A, mid + 1, last, partitionMethod);

    }
}

/**
 * Perform a test of the quick sort of n elements
 * @return the execution time of the sort in nanoseconds
*/
double quickTest(int A[], int n, function<int(int[], int, int)> partitionMethod) {
    auto start = chrono::high_resolution_clock::now();
    quickSort(A, 0, n - 1, partitionMethod);
    auto stop = chrono::high_resolution_clock::now();

    if (!isSorted(A, n)) {
            cout << "Invalid sort!" << endl;
            return -1;
    }

    chrono::duration<double, std::nano> ms_double = stop - start;

    cout << "\t Time elapsed: " << ms_double.count() << "\n";

    return ms_double.count();
}

/**
 * Perform a test of the quick sort on forward sorted arrays from size 1 to 'size'
 * using the given partitionMethod.
*/
void forwardQuickTest(int size, function<int(int[], int, int)> partitionMethod) {
    ofstream outFile("./output/ForwardQuickSort.csv");

    for (int n = 1; n <= size; n++) {
        cout << "Forward Quick sort size: " << n << endl;
        double time = 0;
        int* A = generateForwardSortedArray(n);

        time = quickTest(A, n, partitionMethod);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
}

/**
 * Perform a test of the quick sort on reverse sorted arrays from size 1 to 'size'
 * using the given partitionMethod.
*/
void reverseQuickTest(int size, function<int(int[], int, int)> partitionMethod) {
    ofstream outFile("./output/ReverseQuickSort.csv");

    for (int n = 1; n <= size; n++) {
        cout << "Reverse Quick sort size: " << n << endl;
        double time = 0;
        int* A = generateReverseSortedArray(n);

        time = quickTest(A, n, partitionMethod);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
}

void randomQuickTest(int A[], int size, function<int(int[], int, int)> partitionMethod) {

}

/**
 * Insertion sort array A with size arraySize
*/
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

/**
 * Perform a test of the insertion sort of n elements
 * @return the execution time of the sort in nanoseconds
*/
double InsertionTest(int A[], int n) {
    auto start = chrono::high_resolution_clock::now();
    insertionSort(A, n);
    auto stop = chrono::high_resolution_clock::now();

    if (!isSorted(A, n)) {
            cout << "Invalid sort!" << endl;
            return -1;
    }

    chrono::duration<double, std::nano> ms_double = stop - start;

    cout << "\t Time elapsed: " << ms_double.count() << "\n";

    return ms_double.count();
}

/**
 * Perform a test of the insertion sort on forward sorted arrays from size 1 to 'size'
*/
void forwardInsertionTest(int size) {
    ofstream outFile("./output/ForwardInsertionSort.csv");

    for (int n = 1; n <= size; n++) {
        cout << "Forward Insertion sort size: " << n << endl;
        double time = 0;
        int* A = generateForwardSortedArray(n);

        time = InsertionTest(A, n);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
}

/**
 * Perform a test of the insertion sort on reverse sorted arrays from size 1 to 'size'
*/
void reverseInsertionTest(int size) {
    ofstream outFile("./output/ReverseInsertionSort.csv");

    for (int n = 1; n <= size; n++) {
        cout << "Reverse Insertion sort size: " << n << endl;
        double time = 0;
        int* A = generateReverseSortedArray(n);

        time = InsertionTest(A, n);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
}

void randomInsertionTest(int A[], int size) {
    ofstream outFile("./output/RandomInsertionSort.csv");

    for (int n = 1; n <= size; n++) {
        
    }

}

void allRandomTests(int inSize, int quSize) {
    for (int n = 1; n < quSize; n++) {
        int* A = generateRandomArray(n);

        
        thread quickTwoPointer(randomQuickTest, A, n, partitionTwoPointer);
    }
}

int main() {
    srand(time(0));

    thread FInsertionTest(forwardQuickTest, 10000, partitionTwoPointer);
    //thread RInsertionTest(reverseInsertionTest, 10000);

    FInsertionTest.join();
    //RInsertionTest.join();
    cout << "Completed all tests" << endl;
/*
    int A[] = {5,6,8,3,4,7,9,2,10,1};

    quickSort(A, 0, 9, partitionTwoPointer);*/

    return 0;
}