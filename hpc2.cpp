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
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for (i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}

void mergeSortSequential(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortParallel(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergeSortParallel(arr, l, m);
            }
#pragma omp section
            {
                mergeSortParallel(arr, m + 1, r);
            }
        }
        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    int *arr_seq = new int[n];
    int *arr_par = new int[n];

    srand(time(0));
    for (int i = 0; i < n; i++) {
        int rand_num = rand() % 100;
        arr_seq[i] = rand_num;
        arr_par[i] = rand_num;
    }

    clock_t start_seq = clock();
    mergeSortSequential(arr_seq, 0, n - 1);
    clock_t end_seq = clock();
    double sequentialMS = double(end_seq - start_seq) / CLOCKS_PER_SEC;
    cout << "Sequential time: " << sequentialMS << " seconds" << endl;

    clock_t start_par = clock();
    mergeSortParallel(arr_par, 0, n - 1);
    clock_t end_par = clock();
    double parallelMergeTime = double(end_par - start_par) / CLOCKS_PER_SEC;
    cout << "Parallel Merge Sort Time: " << parallelMergeTime << " seconds" << endl;

    delete[] arr_seq;
    delete[] arr_par;

    return 0;
}
