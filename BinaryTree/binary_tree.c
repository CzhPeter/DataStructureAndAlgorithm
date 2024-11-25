#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node* getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node* insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (rand() % 2) {
        root->lchild = insert(root->lchild, key);
    }
    else {
        root->rchild = insert(root->rchild, key);
    }
    return root;
}

void clear(Node *root) {
    if (root == NULL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

void bfs(Node *root) {
    Node* queue[15];
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        Node *node = queue[head];
        printf("\nnode: %d ", node->key);
        if (node->lchild) {
            queue[tail++] = node->lchild;
            printf("\t%d->%d (left)\n", node->key, node->lchild->key);
        }
        if (node->rchild) {
            queue[tail++] = node->rchild;
            printf("\t%d->%d (right)\n", node->key, node->rchild->key);
        }
        head++;
    }
    return;
}

int tot = 0;
void dfs(Node *root) {
    if (root == NULL) return;
    int start, end;
    tot += 1;
    start = tot;
    if (root->lchild) dfs(root->lchild);
    if (root->rchild) dfs(root->rchild);
    tot += 1;
    end = tot;
    printf("%d : [%d, %d]\n", root->key, start, end);
    return;
}

int main() {
    srand(time(0));
    Node *root = NULL;
    for (int i = 0; i < 10; ++i) {
        root = insert(root, rand() % 100);
    }
    bfs(root);
    dfs(root);
    clear(root);    
    return 0;
}