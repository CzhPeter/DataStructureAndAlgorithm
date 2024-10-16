#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node *getNewNode(int val) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = val;
    node->next = NULL;
    return node;
}

typedef struct LinkList {
    Node head, *tail;
} LinkList;

LinkList* initLinkList() {
    LinkList *l = (LinkList*)malloc(sizeof(LinkList));
    l->head.next = NULL;
    l->tail = &(l->head);
    return l;
}

void clearLinkList(LinkList *l) {
    Node *p = l->head.next, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    free(l);
    return;
}

int emptyList(LinkList *l) {
    return l->head.next == NULL;
}

int frontList(LinkList *l) {
    if (l->head.next == NULL) return -1;
    return l->head.next->data;
}

int insertTail(LinkList *l, int val) {
    Node *node = getNewNode(val);
    l->tail->next = node;
    l->tail = node;
    return 1;
}

int eraseHead(LinkList *l) {
    if (emptyList(l)) return 0;
    Node *p = l->head.next;
    l->head.next = l->head.next->next;
    if (p == l->tail) l->tail = &(l->head);
    free(p);
    return 1;
}

typedef struct Queue {
    LinkList *l;
    int count;
} Queue;

Queue *initQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->l = initLinkList();
    q->count = 0;
    return q;
}

int emptyQueue(Queue *q) {
    return q->count == 0;
}

int front(Queue *q) {
    if (emptyQueue(q)) return -1;
    return frontList(q->l);
}

int push(Queue *q, int val) {
    if (!insertTail(q->l, val)) return 0;
    q->count += 1;
    return 1;
}

int pop(Queue *q) {
    if (!eraseHead(q->l)) return 0;
    q->count -= 1;
    return 1;
}

void clearQueue(Queue *q) {
    if (q == NULL) return;
    clearLinkList(q->l);
    free(q);
    return;
}

void outputQueue(Queue *q) {
    printf("Queue: ");
    Node *p = q->l->head.next;
    while (p != NULL) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("\n\n");
}

int main() {
    srand(time(0));
    Queue *q = initQueue();
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
