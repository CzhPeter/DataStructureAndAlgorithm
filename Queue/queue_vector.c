#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct vector {
    int size;
    int *data;
} vector;

vector* initVector(int n) {
    vector* p = (vector*)malloc(sizeof(vector));
    p->size = n;
    p->data = (int*)malloc(sizeof(int) * n);
    return p;
}

int seekVector(vector* v, int pos) {
    if (pos < 0 || pos >= v->size) return -1;
    return v->data[pos];
}

int insertVector(vector* v, int pos, int val) {
    if (pos < 0 || pos >= v->size) return 0;
    v->data[pos] = val;
    return 1;
}

void clearVector(vector* v) {
    if (v == NULL) return;
    free(v->data);
    free(v);
    return;
}

typedef struct Queue {
    vector *data;
    int size, head, tail, count;
} Queue;

Queue *initQueue(int n) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = initVector(n);
    q->size = n;
    q->head = q->tail = q->count = 0;
    return q;
}

int empty(Queue *q) {
    return q->count == 0;
}

int push(Queue *q, int val) {
    if (q->count == q->size) return 0;
    insertVector(q->data, q->tail, val);
    q->tail += 1;
    if (q->tail == q->size) q->tail = 0; // 循环队列
    q->count += 1;
    return 1;
}

int front(Queue *q) {
    return seekVector(q->data, q->head);
}

int pop(Queue *q) {
    if (empty(q)) return 0;
    q->head += 1;
    q->count -= 1;
    return 1;
}

void clearQueue(Queue *q) {
    if (q == NULL) return;
    clearVector(q->data);
    free(q);
    return;
}

void outputQueue(Queue *q) {
    printf("Queue: ");
    for (int i = 0; i < q->count; ++i) {
        printf("%4d", seekVector(q->data, (q->head + i) % q->size));
    }
    printf("\n");
}

int main() {
    srand(time(0));
    Queue *q = initQueue(5);
    for (int i = 0; i < 10; ++i) {
        int op = rand() % 5; // 0: pop | 1, 2, 3, 4: push
        int val = rand() % 100;
        switch (op) {
        case 0:
        case 1:
            printf("front of queue: %d, pop it\n", front(q));
            pop(q);
            break;
        case 2:
        case 3:
        case 4:
            printf("push %d to queue\n", val);
            push(q, val);
            break;
        }
        outputQueue(q);
    }
    clearQueue(q);
    return 0;
}
