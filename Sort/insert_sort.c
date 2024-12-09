#include <stdio.h>
#include <stdlib.h>
#include "sort_test.h"

// 时间复杂度：O(n^2) （最好情况为O(n)）
void insert_sort(int *arr, int l, int r) {
    for (int i = l + 1; i < r; ++i) {
        // 将待排序区中的每一个元素向已排序区中插入并调整位置
        int j = i;
        while (j > l && arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j -= 1;
        }
    }
    return;
}

void unguarded_insert_sort(int *arr, int l, int r) {
    // 找到全局最小值的下标
    int index = l;
    for (int i = l + 1; i < r; ++i) {
        if (arr[i] < arr[index]) {
            index = i;
        }
    }
    // 将最小值移到第一位（维持稳定排序）
    while (index > l) {
        swap(arr[index], arr[index - 1]);
        index -= 1;
    }
    // 将待排序区中的每一个元素向已排序区中插入并调整位置
    for (int i = l + 1; i < r; ++i) {
        int j = i;
        // 去掉对j越界的判断
        while (arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j -= 1;
        }
    }
    return;
}

int main() {
    int *arr = getRandData(SMALL_DATA_N);
    TEST(insert_sort, arr, SMALL_DATA_N);
    TEST(unguarded_insert_sort, arr, SMALL_DATA_N);
    free(arr);
    return 0;
}