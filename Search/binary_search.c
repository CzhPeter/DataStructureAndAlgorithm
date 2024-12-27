#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void output(int *arr, int n, int index) {
    int len = 0;
    for (int i = 0; i < n; ++i) {
        len += printf("%4d", i);
    }
    printf("\n");
    for (int i = 0; i < len; ++i) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (i == index) printf("\033[1;32m");
        printf("%4d", arr[i]);
        if (i == index) printf("\033[0m");
    }
    printf("\n");
    return;
}

int binary_search(int *arr, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) / 2;
        printf("[%d, %d], mid = %d, arr[%d] = %d\n", 
            head, tail, mid, mid, arr[mid]);
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) {
            head = mid + 1;
        } else {
            tail = mid - 1;
        }
    }
    return -1;
}

void test_binary_search(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    arr[0] = rand() % 10;
    for (int i = 1; i < n; ++i) {
        arr[i] = arr[i - 1] + rand() % 10;
    }
    output(arr, n, -1);
    int x;
    while (scanf("%d", &x)) {
        if (x == -1) break;
        int index = binary_search(arr, n, x);
        output(arr, n, index);
    }
    return;
}

#define EXP 1e-4
#define min(a, b) ((a) < (b) ? (a) : (b))

// 单调问题都可以使用二分算法进行求解
double f(double x) {
    if (x >= 0)    x -=  min(x, 3000) * 0.03;
    if (x > 3000)  x -= (min(x, 12000) - 3000)  * 0.1;
    if (x > 12000) x -= (min(x, 25000) - 12000) * 0.2;
    if (x > 25000) x -= (min(x, 35000) - 25000) * 0.25;
    if (x > 35000) x -= (min(x, 55000) - 35000) * 0.3;
    if (x > 55000) x -= (min(x, 80000) - 55000) * 0.35;
    if (x > 80000) x -= (x - 80000) * 0.45;
    return x;
}

double binary_algorithm(double y) {
    double head = 0, tail = 1000000, mid;
    while (tail - head >= EXP) {
        mid = (head + tail) / 2.0;
        printf("[%lf, %lf], mid = %lf, f(%lf) = %lf\n", 
            head, tail, mid, mid, f(mid));
        if (f(mid) < y) {
            head = mid;
        } else {
            tail = mid;
        }
    }
    return head;
}

void test_binary_algorithm() {
    printf("\ntest binary algorithm\n");
    double y;
    while (~scanf("%lf", &y)) {
        if (y < 0) break;
        double x = binary_algorithm(y);
        printf("f(%.2lf) = %.2lf\n", x, y);
    }
    return;
}

int main() {
    #define MAX_N 10
    srand(time(0));
    test_binary_search(MAX_N);
    test_binary_algorithm();
    return 0;
}