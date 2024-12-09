#include <stdio.h>
#include <stdlib.h>
#include "sort_test.h"

// 时间复杂度：O(n^2)
void bubble_sort(int *arr, int l, int r) {
    for (int i = r - 1; i >= l + 1; --i) {
        for (int j = l; j < i; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    return;
}

void bubble_sort_improve(int *arr, int l, int r) {
    for (int i = r - 1, count; i >= l + 1; --i) {
        count = 0;
        for (int j = l; j < i; ++j) {
            if (arr[j] <= arr[j + 1]) continue;
            swap(arr[j], arr[j + 1]);
            count += 1;
        }
        // 未发生任何交换，说明待排序区已经有序，直接完成排序过程
        if (count == 0) {
            break;
        }
    }
    return;
}

int main() {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(bubble_sort, arr ,SMALL_DATA_N);
    TEST(bubble_sort_improve, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}