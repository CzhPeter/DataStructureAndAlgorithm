#include <iostream>

using namespace std;

#define MAX_N 10000
int fa[MAX_N + 5]; // fa[i]代表第i个节点的父节点的编号

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        fa[i] = i; // 编号为自己的即为根节点
    }
    return;
}

int find(int x) {
    if (fa[x] == x) return x;
    return find(fa[x]);
}

int merge(int a, int b) {
    int aa = find(a), bb = find(b);
    if (aa == bb) return 0;
    fa[aa] = bb;
    return 1;
}

void output(int n) {
    int ret = 0;
    for (int i = 0; i <= n; ++i) {
        ret += printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < ret; ++i) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i <= n; ++i) {
        ret += printf("%3d", fa[i]);
    }
    printf("\n");
    return;
}

int main() {
    int n, a, b;
    cin >> n;
    init(n);
    while (cin >> a >> b) {
        printf("merge %d with %d : %d\n", a, b, merge(a, b));
        output(n);
    }
    return 0;
}