//
// Created by Development Environment on 4/29/19.
// Typical sorting algorithms used
//

#ifndef LAB3_1_SORTING_H
#define LAB3_1_SORTING_H

/**
 *
 * @tparam T
 * @param p_val1
 * @param p_val2
 */
template <typename T>
void swap(T *p_val1, T *p_val2)
{

    if (p_val1 == nullptr) {
        return;
    } else {
        if (p_val2 == nullptr) {
            return;
        }
    }
    T p_temp = *p_val1;
    *p_val1 = *p_val2;
    *p_val2 = p_temp;
}

template <typename T>
void bubbleSort(T* arr, const int leftSize, const int rightSide)
{
    int i;
    for (i = leftSize; rightSide - 1 > i; i++)
    {
        for (int j = leftSize; j < rightSide - i - 1; j++)
        {
            if (!(arr[j] > arr[j + 1]))
                continue;
            swap(&arr[j], &arr[j + 1]);

        }
    }
}

template <typename T>
void quicksort(T* arr, const int leftSide, const int rightSide)
{
    if (arr[leftSide] <= arr[(rightSide + leftSide) / 2]) {}
    else {
        swap(arr[leftSide], arr[(rightSide + leftSide) / 2]);
    }

    if (arr[(rightSide + leftSide) / 2] <= arr[rightSide]) {}
    else {
        swap(arr[rightSide], arr[(rightSide + leftSide) / 2]);
    }

    if (arr[leftSide] <= arr[(rightSide + leftSide) / 2]) {}
    else {
        swap(arr[leftSide], arr[(rightSide + leftSide) / 2]);
    }


    // Variables
    int i = leftSide,
            j = rightSide;

    T	p_pivot = arr[(leftSide + rightSide) / 2];

    while (i <= j)
    {
        while (arr[i] < p_pivot)
        {
            i++;
        }

        while (arr[j] > p_pivot)
        {
            j--;
        }

        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (leftSide < j)
    {
        quicksort(arr, leftSide, j);
    }
    if (i < rightSide)
    {
        quicksort(arr, i, rightSide);
    }

}

template <typename T>
void insertionSort(T* array, const int leftSide, const int rightSide)
{
    T key;
    int j;
    int i;
    for (i = leftSide; i < rightSide; i++)
    {
        key = array[i];
        j = i - 1;

        if (j >= leftSide) {
            while (array[j] > key) {
                array[j + 1] = array[j];
                j = j - 1;
            }
        } // end while

        array[j + 1] = key;

    }
}

#endif //LAB3_1_SORTING_H
