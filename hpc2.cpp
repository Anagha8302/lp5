#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr_seq = new int[n];
    int *arr_par = new int[n];

    srand(time(0));

    for (int i = 0; i < n; ++i)
    {
        int rand_num = rand() % 100;
        arr_seq[i] = rand_num;
        arr_par[i] = rand_num;
    }

    // Sequential Bubble Sort
    clock_t start_seq = clock();
    bubbleSort(arr_seq, n);
    clock_t end_seq = clock();
    double sequentialBubbleTime = double(end_seq - start_seq) / CLOCKS_PER_SEC;

    cout << "Sequential Bubble Sort Time: " << sequentialBubbleTime << " seconds" << endl;

    // Parallel Bubble Sort
    clock_t start_par = clock();
#pragma omp parallel
    {
        bubbleSort(arr_par, n);
    }
    clock_t end_par = clock();
    double parallelBubbleTime = double(end_par - start_par) / CLOCKS_PER_SEC;

    cout << "Parallel Bubble Sort Time: " << parallelBubbleTime << " seconds" << endl;

    delete[] arr_seq;
    delete[] arr_par;

    return 0;
}
/*----------------------------------------------------------------------------------mergeSOrt----------------------------*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

using namespace std;

void merge(int arr[], int l, int m, int r) {
    // Merge function for Merge Sort
}

void mergeSort(int arr[], int l, int r) {
    // Merge sort algorithm implementation
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

double measureTime(void (*sortFunction)(int[], int, int), int arr[], int n) {
    // Function to measure execution time of sorting algorithms
    clock_t start = clock();
    sortFunction(arr, 0, n - 1);
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];
    int *arr_copy = new int[n];

    srand(time(0));

    for (int i = 0; i < n; ++i) {
        int rand_num = rand() % 100;
        arr[i] = rand_num;
        arr_copy[i] = rand_num;
    }

    double sequentialMergeTime, parallelMergeTime;

    // Sequential Merge Sort
    sequentialMergeTime = measureTime(mergeSort, arr, n);
    cout << "Sequential Merge Sort Time: " << sequentialMergeTime << " seconds" << endl;

    // Parallel Merge Sort
    parallelMergeTime = measureTime(mergeSort, arr_copy, n);
    cout << "Parallel Merge Sort Time: " << parallelMergeTime << " seconds" << endl;

    delete[] arr;
    delete[] arr_copy;

    return 0;
}
