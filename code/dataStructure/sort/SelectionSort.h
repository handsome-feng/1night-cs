#ifndef SORT_SELECIIONSORT_H
#define SORT_SELECTIONSORT_H

template<typename T>
void selectionSort (T arr[], int n) {
    for (int i = 0; i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        swap (arr[i], arr[minIndex]);
    }
}

#endif // SORT_SELECTIONSORT_H