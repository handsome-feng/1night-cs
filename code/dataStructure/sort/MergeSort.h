#ifndef SORT_MERGESORT_H
#define SORT_MERGESORT_H

template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
    T aux[r-l+1];

    for (int i = l; i <= r; i++)
        aux[i-l] = arr[i];

    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {
        if (i > mid) {
            arr[k] = aux[j-l]; j++;
        } else if (j > r) {
            arr[k] = aux[i-l]; i++;
        } else if (aux[i-l] < aux[j-l]) {
            arr[k] = aux[i-l]; i++; 
        } else {
            arr[k] = aux[j-l]; j++;
        }
    }
}

// 递归使用，对arr[l...r]的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r) {
    if (l >= r)
        return;

    // 优化：当数组小于15时，插入排序更快
    // if (r - l < 15) {
    //     insertionSort(arr, l, r);
    //     return;
    // }
    
    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    // 优化：已经有序的情况下，无需merge
    if (arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);

}

// 自顶向下，递归
template <typename T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n - 1);
}

// 自低向上，迭代, 没有通过索引来定位元素，所以对于链表结构的排序，更有效率
template <typename T>
void mergeSortBU(T arr[], int n) {
    for (int sz = 1; sz < n; sz += sz) {
        for (int i = 0; i + sz < n; i += 2 * sz) {
            if (arr[i+sz-1] > arr[i+sz])
                __merge (arr, i, i + sz - 1,  min(i + 2 * sz - 1, n - 1 ));
        }
    }
}
#endif // SORT_MERGESORT_H