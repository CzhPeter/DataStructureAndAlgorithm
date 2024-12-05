#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a, b) { \
    __typeof(a) __c = (a); \
    (a) = (b); \
    (b) = __c; \
}

typedef struct Node {
    char ch; // 字符
    int freq; // 频次
    struct Node *lchild, *rchild;
} Node; // 哈夫曼树节点

typedef struct Heap {
    Node **__data, **data;
    int n, size;
} Heap;

Heap *getNewHeap(int size) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->__data = (Node **)malloc(sizeof(Node *) * size);
    h->data = h->__data - 1;
    h->size = size;
    h->n = 0;
    return h;
}

void clearHeap(Heap *h) {
    if (h == NULL) return;
    free(h->__data);
    free(h);
    return;
}

int fullHeap(Heap *h) {
    return h->n == h->size;
}

int emptyHeap(Heap *h) {
    return h->n == 0;
}

Node *top(Heap *h) {
    if (emptyHeap(h)) return NULL;
    return h->data[1];
}

void up_maintain(Heap *h, int i) {
    while (i > 1 && h->data[i]->freq < h->data[i / 2]->freq) {
        swap(h->data[i], h->data[i / 2]);
        i = i / 2;
    }
    return;
}

int cmpHeap(Heap *h, int i, int j) {
    return h->data[i]->freq < h->data[j]->freq;
}

void down_maintain(Heap *h, int i) {
    while (i * 2 <= h->n) {
        int index = i, l = i * 2, r = i * 2 + 1;
        if (cmpHeap(h, l, index)) {
            index = l;
        }
        if (r <= h->n && cmpHeap(h, r, index)) {
            index = r;
        }
        if (i == index) {
            return;
        }
        swap(h->data[i], h->data[index]);
        i = index;
    }
    return;
}

int pushHeap(Heap *h, Node *n) {
    if (fullHeap(h)) return 0;
    h->n += 1;
    h->data[h->n] = n;
    up_maintain(h, h->n);
    return 1;
}

int popHeap(Heap *h) {
    if (emptyHeap(h)) return 0;
    h->data[1] = h->data[h->n];
    h->n -= 1;
    down_maintain(h, 1);
    return 1;
}

Node *getNewNode(char ch, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->ch = ch;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

void swap_node(Node **node_arr, int index, int pos) {
    Node *temp = node_arr[index];
    node_arr[index] = node_arr[pos];
    node_arr[pos] = temp;
    return;
}

int find_min_node(Node **node_arr, int n) {
    int index = 0;
    for (int j = 1; j <= n; ++j) {
        if (node_arr[index]->freq > node_arr[j]->freq) {
            index = j;
        }
    }
    return index;
}

Node *buildHaffmanTree(Node **node_arr, int n) {
    Heap *h = getNewHeap(n);
    // 用小顶堆优化查找过程
    for (int i = 0; i < n; ++i) {
        pushHeap(h, node_arr[i]);
    }
    for (int i = 1; i < n; ++i) {
        Node *node1 = top(h);
        popHeap(h);
        Node *node2 = top(h);
        popHeap(h);
        Node *node3 = getNewNode(0, node1->freq + node2->freq);
        node3->lchild = node1;
        node3->rchild = node2;
        pushHeap(h, node3);
    }
    Node *ret = top(h);
    clearHeap(h);
    return ret;
}

#define MAX_CHAR_NUM 128
char *char_code[MAX_CHAR_NUM] = {0};

void extractHaffmanCode(Node *root, char buff[], int k) {
    buff[k] = 0;
    // 对叶子结点打印编码
    if (root->lchild == NULL && root->rchild == NULL) {
        char_code[root->ch] = strdup(buff);
        return;
    }
    // 递归赋编码值
    buff[k] = '0';
    extractHaffmanCode(root->lchild, buff, k + 1);
    buff[k] = '1';
    extractHaffmanCode(root->rchild, buff, k + 1);
    return;
}

int main() {
    char s[10];
    int n, freq;
    scanf("%d", &n);
    Node **node_arr = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; ++i) {
        scanf("%s%d", s, &freq);
        node_arr[i] = getNewNode(s[0], freq);
    }
    Node *root = buildHaffmanTree(node_arr, n);
    char buff[1000];
    extractHaffmanCode(root, buff, 0);
    for (int i = 0; i < MAX_CHAR_NUM; ++i) {
        if (char_code[i] == NULL) continue;
        printf("%c : %s\n", i, char_code[i]);
    }
    clear(root);
    return 0;
}