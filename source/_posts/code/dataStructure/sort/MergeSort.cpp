#include <iostream>
#include "SortTestHelper.h"

template <typename T>
void __mergeSort(T arr[], int l, int r)
{
    __mergeSort(arr, l, r/2);
    __mergeSort(arr, r/2 + 1, r);
}

template <typename T>
void MergeSort(T arr[], int n)
{
    __mergeSort(arr, 0, n - 1);
}

int main
{
    return 0;
}
