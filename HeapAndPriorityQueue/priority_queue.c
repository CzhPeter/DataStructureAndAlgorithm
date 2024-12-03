#include <stdio.h>
#include <stdlib.h>

#define ROOT 1
#define FATHER(i) ((i) / 2)
#define LEFT(i) ((i) * 2)
#define RIGHT(i) ((i) * 2 + 1)
#define cmp > // > : 大顶堆; < : 小顶堆
#define swap(a, b) { \
    printf("swap(%d, %d)\n", a, b); \
    __typeof(a) __c = (a); \
    (a) = (b); \
    (b) = __c; \
}

typedef struct PriorityQueue {
    int *__data, *data;
    int size, n;
} PriorityQueue;

PriorityQueue *initPQ(int size) {
    PriorityQueue *p = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    p->__data = (int *)malloc(sizeof(int) * size);
    p->data = p->__data - 1;
    p->size = size;
    p->n = 0;
    return p;
}

int empty(PriorityQueue *p) {
    return p->n == 0;
}

int full(PriorityQueue *p) {
    return p->n == p->size;
}

int top(PriorityQueue *p) {
    return p->data[1];
}

void up_update(int *data, int i) {
    printf("\nUP update : %d\n", data[i]);
    while (i > ROOT && data[i] cmp data[FATHER(i)]) {
        swap(data[i], data[FATHER(i)]);
        i = FATHER(i);
    }
    printf("\n");
    return;
}

void down_update(int *data, int i, int n) {
    printf("\nDOWN update : %d\n", data[i]);
    while (LEFT(i) <= n) {
        int index = i, l = LEFT(i), r = RIGHT(i); // index指向三元组中的最大/小值
        if (data[l] cmp data[index]) index = l;
        if (r <= n && data[r] cmp data[index]) index = r;
        if (index == i) break; // i位置元素本身就最大/小
        swap(data[i], data[index]);
        i = index;
    }
    printf("\n");
    return;
}

int push(PriorityQueue *p, int x) {
    if (full(p)) return 0;
    p->n += 1;
    p->data[p->n] = x;
    up_update(p->data, p->n);
    return 1;
}

int pop(PriorityQueue *p) {
    if (empty(p)) return 0;
    p->data[ROOT] = p->data[p->n];
    p->n -= 1;
    down_update(p->data, ROOT, p->n);
    return 1;
}

void clearPQ(PriorityQueue *p) {
    if (p == NULL) return;
    free(p->data);
    free(p);
    return;
}

void output(PriorityQueue *p) {
    printf("PQ(%d)", p->n);
    for (int i = 1; i <= p->n; ++i) {
        printf("%d ", p->data[i]);
    }
    printf("\n");
    return;
}

int main() {
    int op, x;
    #define MAX_OP 100
    PriorityQueue *p = initPQ(MAX_OP);
    while (~scanf("%d", &op)) {
        if (op == 1) {
            scanf("%d", &x);
            if (push(p, x)) {
                printf("insert %d to priority queue : \n", x);
                output(p);
            }
        } else {
            printf("top: %d\n", top(p));
            if (pop(p)) {
                output(p);
            }  
        }
    }
    clearPQ(p);
    return 0;
}