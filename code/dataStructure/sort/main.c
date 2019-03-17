#include <iostream>

#include "SortTestHelper.h"
#include "MergeSort.h"
#include "SelectionSort.h"
#include "InsertionSort.h"

using namespace std;

int main() {
    int n = 50000;

    cout << "Test for random array, size = " << n << ", random range [0, " << n << "]" << endl;
    int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);

    delete[] arr1;

    cout << endl;

    // 对于近乎有序的数组，越有序，InsertionSort的时间性能越趋近O(n)
    int swapTimes = 10;
    assert (swapTimes >= 0);

    cout << "Test for nearly ordered array, size = "<< n << ", swap time = " << swapTimes << endl;
    arr1 = SortTestHelper::generateNearlyOrderArray(n, swapTimes);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("MergeSort", mergeSort, arr1, n);
    SortTestHelper::testSort("MergeSortBU", mergeSortBU, arr2, n);

    delete[] arr1;

    return 0;
}