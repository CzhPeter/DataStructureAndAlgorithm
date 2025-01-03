#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "sort_test.h"

using namespace std;

// 时间复杂度：O(nlogn) ~ O(n^2)
void quick_sort(int *arr, int l, int r) {
    // code = 0
    if ((r - l) <= 2) {
        if ((r - l) <= 1) return;
        if (arr[l] > arr[l + 1]) {
            swap(arr[l], arr[l + 1]);
        }
        return;
    }

    // code = 1
    // partition
    int x = l, y = r - 1, z = arr[l];
    while (x < y) {
        while (x < y && arr[y] >= z) {
            y--;
        }
        if (x < y) {
            arr[x++] = arr[y];
        }
        while (x < y && arr[x] <= z) {
            x++;
        }
        if (x < y) {
            arr[y--] = arr[x];
        }
    }
    arr[x] = z;

    // code = 2
    quick_sort(arr, l, x);
    // code = 3
    quick_sort(arr, x + 1, r);
    return; // code = 4
}

struct Data {
    Data(int *arr, int l, int r) 
    : arr(arr), l(l), r(r), code(0) {}
    int *arr, l, r;
    int x;
    int code;
};

void non_quick_sort(int *arr, int l, int r) {
    stack<Data> s;
    Data d(arr, l, r);
    s.push(d);
    while (!s.empty()) {
        Data &cur = s.top();
        int x = cur.l, y = cur.r - 1, z = cur.arr[cur.l];
        switch (cur.code) {
        case 0:
            if ((cur.r - cur.l) <= 2) {
                if ((cur.r - cur.l) <= 1) {
                    s.pop();
                } else {
                    if (cur.arr[cur.l] > cur.arr[cur.l + 1]) {
                        swap(cur.arr[cur.l], cur.arr[cur.l + 1]);
                    }
                    s.pop();
                }
            } else {
                cur.code = 1;
            }
            break;
        case 1: 
            while (x < y) {
                while (x < y && cur.arr[y] >= z) {
                    y--;
                }
                if (x < y) {
                    cur.arr[x++] = cur.arr[y];
                }
                while (x < y && cur.arr[x] <= z) {
                    x++;
                }
                if (x < y) {
                    cur.arr[y--] = cur.arr[x];
                }
            }
            cur.arr[x] = z;
            cur.x = x;
            cur.code = 2;
            break;
        case 2:
            cur.code = 3;
            s.push(Data(cur.arr, cur.l, cur.x));
            break;
        case 3:
            cur.code = 4;
            s.push(Data(cur.arr, cur.x + 1, cur.r));
            break;
        case 4:
            s.pop();
            break;
        }
    }
    return;
}

void quick_sort_improve_v1(int *arr, int l, int r) {
    if ((r - l) <= 2) {
        if ((r - l) <= 1) return;
        if (arr[l] > arr[l + 1]) {
            swap(arr[l], arr[l + 1]);
        }
        return;
    }
    // partition
    int x = l, y = r - 1, z = arr[l];
    // 减少x和y的大小判断次数
    do {
        while (arr[x] < z) {
            x++;
        }
        while (arr[y] > z) {
            y--;
        }
        if (x <= y) {
            swap(arr[x], arr[y]);
            x++;
            y--;
        }
    } while (x <= y);
    quick_sort_improve_v1(arr, l, x);
    quick_sort_improve_v1(arr, x, r);
    return;
}

int three_point_select(int a, int b, int c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    return b;
}

void quick_sort_improve_v2(int *arr, int l, int r) {
    if ((r - l) <= 2) {
        if ((r - l) <= 1) return;
        if (arr[l] > arr[l + 1]) {
            swap(arr[l], arr[l + 1]);
        }
        return;
    }
    // partition
    int x = l, y = r - 1;
    // 三点取中法取基准值
    int z = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
    do {
        while (arr[x] < z) {
            x++;
        }
        while (arr[y] > z) {
            y--;
        }
        if (x <= y) {
            swap(arr[x], arr[y]);
            x++;
            y--;
        }
    } while (x <= y);
    quick_sort_improve_v2(arr, l, x);
    quick_sort_improve_v2(arr, x, r);
    return;
}

void quick_sort_improve_v3(int *arr, int l, int r) {
    if ((r - l) <= 2) {
        if ((r - l) <= 1) return;
        if (arr[l] > arr[l + 1]) {
            swap(arr[l], arr[l + 1]);
        }
        return;
    }
    while (l < r) {
        // partition
        int x = l, y = r - 1;
        // 三点取中法取基准值
        int z = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
        do {
            while (arr[x] < z) {
                x++;
            }
            while (arr[y] > z) {
                y--;
            }
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++;
                y--;
            }
        } while (x <= y);
        // 单边递归法
        quick_sort_improve_v3(arr, l, x); // left
        // 将右边分区在本层循环继续划分
        l = x;
    }
    return;
}

#define threshold 16

void __quick_sort_improve_v4(int *arr, int l, int r) {
    // 指定分区内元素的数量， 使分区间有序，分区内无序
    while (r - l > threshold) {
        // partition
        int x = l, y = r - 1;
        // 三点取中法取基准值
        int z = three_point_select(arr[l], arr[r - 1], arr[(l + r) / 2]);
        do {
            while (arr[x] < z) {
                x++;
            }
            while (arr[y] > z) {
                y--;
            }
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++;
                y--;
            }
        } while (x <= y);
        // 单边递归法
        __quick_sort_improve_v4(arr, l, x); // left
        // 将右边分区在本层循环继续划分
        l = x;
    }
    return;
}

void unguarded_insert_sort(int *arr, int l, int r) {
    int index = l;
    for (int i = l + 1; i < r; ++i) {
        if (arr[i] < arr[index]) {
            index = i;
        }
    }
    while (index > l) {
        swap(arr[index], arr[index - 1]);
        index -= 1;
    }
    for (int i = l + 1; i < r; ++i) {
        int j = i;
        while (arr[j] < arr[j - 1]) {
            swap(arr[j], arr[j - 1]);
            j -= 1;
        }
    }
    return;
}

void quick_sort_improve_v4(int *arr, int l, int r) {
    __quick_sort_improve_v4(arr, l, r);
    // 对分区内无序的整体进行插入排序
    unguarded_insert_sort(arr, l, r);
    return;
}

int main() {
    int *arr_s = getRandData(SMALL_DATA_N);
    int *arr_b = getRandData(BIG_DATA_N);
    TEST(quick_sort, arr_s, SMALL_DATA_N);
    TEST(quick_sort, arr_b, BIG_DATA_N);
    TEST(non_quick_sort, arr_b, BIG_DATA_N);
    TEST(quick_sort_improve_v1, arr_b, BIG_DATA_N);
    TEST(quick_sort_improve_v2, arr_b, BIG_DATA_N);
    TEST(quick_sort_improve_v3, arr_b, BIG_DATA_N);
    TEST(quick_sort_improve_v4, arr_b, BIG_DATA_N);
    free(arr_s);
    free(arr_b);
    return 0;
}