#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "sort_test.h"

using namespace std;

void output(int *arr, int n) {
    cout << "arr[" << n << "] = "; 
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return;
}

void output(vector<int>& arr) {
    cout << "arr[" << arr.size() << "] = "; 
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return;
}

void test1() {
    cout << "test array: " << endl;
    // sort array
    int *arr = getRandData(10);
    output(arr, 10);
    sort(arr, arr + 10);
    output(arr, 10);
    sort(arr, arr + 10, greater<int>());
    output(arr, 10);
}

void test2() {
    cout << "test vector: " << endl;
    // sort vector
    vector<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.push_back(rand() % 10000);
    }
    output(arr);
    sort(arr.begin(), arr.end());
    output(arr);
    sort(arr.begin(), arr.end(), greater<int>());
    output(arr);
    return;
}

struct Data {
    int x, y;
};

void output(vector<Data>& arr) {
    cout << "arr[" << arr.size() << "] = "; 
    for (int i = 0; i < arr.size(); ++i) {
        cout << "(" << arr[i].x << ", " << arr[i].y << ") ";
    }
    cout << endl;
    return;
}

bool cmp(const Data &a, const Data &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y > b.y;
}

void test3() {
    cout << "test other data structures: " << endl;
    vector<Data> arr;
    for (int i = 0; i < 10; ++i) {
        Data d;
        d.x = rand() % 10, d.y = rand() % 10;
        arr.push_back(d);
    }
    output(arr);
    sort(arr.begin(), arr.end(), cmp);
    output(arr);
    return;
}

void test4() {
    cout << "test sord ind: " << endl;
    int *arr = getRandData(10);
    // 创建一个下标数组
    int *ind = getRandData(10);
    for (int i = 0; i < 10; ++i) {
        ind[i] = i;
    }
    output(arr, 10);
    sort(ind, ind + 10, [&](int i, int j) -> bool {
        return arr[i] < arr[j];
    });
    output(arr, 10);
    output(ind, 10);
    return;
}

int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}