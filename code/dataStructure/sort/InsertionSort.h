#ifndef SORT_INSERTIONSORT_H
#define SORT_INSERTIONSORT_H

template<typename T>
void insertionSort (T arr[], int n) {
    for (int i = 1; i < n; i++) {
        // 寻找arr[i]合适的插入位置
        for (int j = i; j > 0 && arr[j] < arr[j-1]; j--) {
            swap (arr[j], arr[j-1]);
        }
    }
}

template<typename T>
void insertionSort2 (T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T e = arr[i];
        int j; //保存元素e应该插入的位置
        for (j = i; j > 0 && arr[j-1] > e; j--) {
            arr[j] = arr[j-1]; //向后移动
        }
        arr[j] = e;
    }
}

#endif // SORT_INSERTIONSORT_H