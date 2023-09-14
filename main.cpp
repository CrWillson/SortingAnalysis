#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <random>
#include <string>
#include <functional>
#include <chrono>

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
 * Generate a randomized array of size n using a given seed
 * Used for generating the same random array multiple times instead of cloning it
 * @return an int array of size n
*/
int* generateRandomArray(int n, int seed) {
    srand(seed);

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
 * The one pointer method is used.
 * @return the index of the lower pointer
*/
int partitionMedianThree(int A[], int first, int last) {
    int pivot;
    int middle = (int)floor((last - first) / 2);
    int a = A[first];
    int b = A[middle];
    int c = A[last];

    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        pivot = b;
        swap(A, middle, last);
    }
    else if ((b <= a && a <= c) || (c <= a && a <= b)) {
        pivot = a;
        swap(A, first, last);
    }
    else if ((a <= c && c <= b) || (b <= c && c <= a)) {
        pivot = c;
    }

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
 * Quick sort partition method that uses the middle index as the pivot.
 * 
 * The one pointer method is used.
 * @return the index of the lower pointer
*/
int partitionMiddleIndex(int A[], int first, int last) {
    int middle = (int)floor((last - first) / 2);
    int pivot = A[middle];
    swap(A, middle, last);

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
void forwardQuickTest(int start, int size, int step, function<int(int[], int, int)> partitionMethod, string name) {
    ofstream outFile("./output/ForwardQuickSort" + name + ".csv");

    for (int n = start; n <= size; n += step) {
        cout << "Forward Quick " + name + " sort size: " << n << endl;
        double time = 0;
        int* A = generateForwardSortedArray(n);

        time = quickTest(A, n, partitionMethod);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
    outFile.close();
}

/**
 * Perform a test of the quick sort on reverse sorted arrays from size 1 to 'size'
 * using the given partitionMethod.
*/
void reverseQuickTest(int start, int size, int step, function<int(int[], int, int)> partitionMethod, string name) {
    ofstream outFile("./output/ReverseQuickSort" + name + ".csv");

    for (int n = start; n <= size; n += step) {
        cout << "Reverse Quick " + name + " sort size: " << n << endl;
        double time = 0;
        int* A = generateReverseSortedArray(n);

        time = quickTest(A, n, partitionMethod);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
    outFile.close();
}

/**
 * Perform a test of the quick sort on randomized array using the given partition method
 * Outputs to a file titled "RandomQuickSort[name].csv"
 * The seed is used to generate the same sets of random arrays
*/
void randomQuickTest(int start, int size, int step, int seed, function<int(int[], int, int)> partitionMethod, string name) {
    int* seedArray = generateRandomArray(size, seed); 

    ofstream outFile("./output/RandomQuickSort" + name + ".csv");

    for (int n = start; n <= size; n += step) {
        int* A = generateRandomArray(n, seedArray[n]);

        cout << "Random Quick " + name + " sort size " << n << endl;
        double time = quickTest(A, n, partitionMethod);
        outFile << n << "," << time << "\n";

        delete[] A;
    }
    
    delete[] seedArray;
    outFile.close();
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
double insertionTest(int A[], int n) {
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
void forwardInsertionTest(int start, int size, int step) {
    ofstream outFile("./output/ForwardInsertionSort.csv");

    for (int n = start; n <= size; n += step) {
        cout << "Forward Insertion sort size: " << n << endl;
        double time = 0;
        int* A = generateForwardSortedArray(n);

        time = insertionTest(A, n);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
    outFile.close();
}

/**
 * Perform a test of the insertion sort on reverse sorted arrays from size 1 to 'size'
*/
void reverseInsertionTest(int start, int size, int step) {
    ofstream outFile("./output/ReverseInsertionSort.csv");

    for (int n = start; n <= size; n += step) {
        cout << "Reverse Insertion sort size: " << n << endl;
        double time = 0;
        int* A = generateReverseSortedArray(n);

        time = insertionTest(A, n);
        outFile << n << "," << time << "\n";
        delete[] A;
    }
    outFile.close();
}

/**
 * Perform a test of the insertion sort on randomized array
 * The seed is used to generate the same sets of random arrays
*/
void randomInsertionTest(int start, int size, int step, int seed) {
    int* seedArray = generateRandomArray(size, seed); 

    ofstream outFile("./output/RandomInsertionSort.csv");

    for (int n = start; n <= size; n += step) {
        int* A = generateRandomArray(n, seedArray[n]);

        cout << "Random Insertion sort size " << n << endl;
        double time = insertionTest(A, n);
        outFile << n << "," << time << "\n";

        delete[] A;
    }
    delete[] seedArray;
    outFile.close();
}

int main(int argc, char** argv) {
    //srand(argv[0]);
    auto start = chrono::high_resolution_clock::now();
    
    //int randSeed = (rand() % 1000000) + 1;
    int randSeed = 420;
    
    //thread insFor(forwardInsertionTest, 2, 10000, 2);
    //thread insRev(reverseInsertionTest, 2, 10000, 2);
    thread insRand(randomInsertionTest, 1, 500, 1, randSeed);

    //thread quickForLast(forwardQuickTest, 2, 10000, 2, partitionTwoPointer, "Last");
    //thread quickForMedian(forwardQuickTest, 2, 10000, 2, partitionMedianThree, "Median");
    //thread quickForMiddle(forwardQuickTest, 2, 10000, 2, partitionMiddleIndex, "Middle");

    //thread quickRevLast(reverseQuickTest, 2, 10000, 2, partitionTwoPointer, "Last");
    //thread quickRevMedian(reverseQuickTest, 2, 10000, 2, partitionMedianThree, "Median");
    //thread quickRevMiddle(reverseQuickTest, 2, 10000, 2, partitionMiddleIndex, "Middle");

    thread quickRandTwoPSm(randomQuickTest, 1, 500, 1, randSeed, partitionTwoPointer, "TwoPointerSm");
    //thread quickRandTwoPXl(randomQuickTest, 250, 1000000, 250, randSeed, partitionTwoPointer, "TwoPointerXl");
    //thread quickRandOneP(randomQuickTest, 250, 1000000, 250, randSeed, partitionOnePointer, "OnePointer");
    //thread quickRandMedian(randomQuickTest, 250, 1000000, 250, randSeed, partitionMedianThree, "Median");
    //thread quickRandMiddle(randomQuickTest, 250, 1000000, 250, randSeed, partitionMiddleIndex, "Middle");

    //insFor.join();
    //insRev.join();
    insRand.join();

    //quickForLast.join();
    //quickForMedian.join();
    //quickForMiddle.join();

    //quickRevLast.join();
    //quickRevMedian.join();
    //quickRevMiddle.join();

    quickRandTwoPSm.join();
    //quickRandTwoPXl.join();
    //quickRandOneP.join();
    //quickRandMedian.join();
    //quickRandMiddle.join();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop-start);

    cout << "***************************************************************" << endl;
    cout << "Completed all tests" << endl;
    cout << "\t Time elapsed: " << duration.count() << "\n";

    return 0;
}