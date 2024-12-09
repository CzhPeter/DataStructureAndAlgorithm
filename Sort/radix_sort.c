#include <stdio.h>
#include <stdlib.h>
#include "sort_test.h"

// 时间复杂度：O(n)
void radix_sort(int *arr, int l, int r) {
    #define K 65536 // int为32位整形，两轮基数排序，基准值为2^16
    int *count = (int *)malloc(sizeof(int) * K);
    int *temp = (int *)malloc(sizeof(int) * (r - l));
    // round 1: 按个位来排序
    memset(count, 0, sizeof(int) * K);
    // 存放个位值出现的次数
    for (int i = l; i < r; ++i) {
        count[arr[i] % K] += 1;
    }
    // 求前缀和
    for (int i = 1; i < K; ++i) {
        count[i] += count[i - 1];
    }
    // 存放个位排序的结果
    for (int i = r - 1; i >= l; --i) {
        temp[--count[arr[i] % K]] = arr[i];
    }
    memcpy(arr + l, temp, sizeof(int) * (r - l));
    // round 2: 按十位来排序
    memset(count, 0, sizeof(int) * K);
    for (int i = l; i < r; ++i) {
        count[arr[i] / K] += 1;
    }
    for (int i = 1; i < K; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = r - 1; i >= l; --i) {
        temp[--count[arr[i] / K]] = arr[i];
    }
    memcpy(arr + l, temp, sizeof(int) * (r - l));
    free(count);
    free(temp);
    return;
}

int main() {
    int *arr_s = getRandData(SMALL_DATA_N);
    int *arr_b = getRandData(BIG_DATA_N);
    TEST(radix_sort, arr_s, SMALL_DATA_N);
    TEST(radix_sort, arr_b, BIG_DATA_N);
    free(arr_s);
    free(arr_b);
    return 0;
}