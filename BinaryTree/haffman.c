#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch; // 字符
    int freq; // 频次
    struct Node *lchild, *rchild;
} Node; // 哈夫曼树节点

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
    for (int i = 1; i < n; ++i) {
        // 找到频次最小的两个节点 TODO: 用堆和优先队列优化查找过程
        int index_1 = find_min_node(node_arr, n - i);
        swap_node(node_arr, index_1, n - i);
        int index_2 = find_min_node(node_arr, n - i - 1);
        swap_node(node_arr, index_2, n - i - 1);
        // 记录合并后频次
        int freq = node_arr[n - i]->freq + node_arr[n - i - 1]->freq;
        // 建树
        Node *node = getNewNode(0, freq);
        node->lchild = node_arr[n - i];
        node->rchild = node_arr[n - i - 1];
        // 合并后的节点加入节点数组末尾
        node_arr[n - i - 1] = node;
    }
    return node_arr[0];
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