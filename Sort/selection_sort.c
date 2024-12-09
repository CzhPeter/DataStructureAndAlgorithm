#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort_test.h"

// 时间复杂度：O(n^2)
void selection_sort(int *arr, int l, int r) {
    for (int i = l; i < r - 1; ++i) {
        int index = i; // 维护待排序区的最小值下标
        for (int j = i + 1; j < r; ++j) {
            if (arr[j] < arr[index]) index = j;
        }
        swap(arr[i], arr[index]);
    }
    return;
}

int main() {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(selection_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}