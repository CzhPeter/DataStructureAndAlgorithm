#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_NODE 10
#define KEY(n) n ? n->key : -1

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
    if (rand() % 2) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

Node* getRandomBinaryTree(int n) {
    Node *root = NULL;
    for (int i = 0; i < n; ++i) {
        root = insert(root, rand() % 100);
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

char buff[1000];
int len = 0;

// 二叉树转广义表（基于前序遍历）
void __serialize(Node* root) {
    if (root == NULL) return;
    len += sprintf(buff + len, "%d", root->key);
    if (root->lchild == NULL && root->rchild == NULL) return;
    len += sprintf(buff + len, "(");
    __serialize(root->lchild);
    if (root->rchild) {
        len += sprintf(buff + len, ",");
        __serialize(root->rchild);
    }
    len += sprintf(buff + len, ")");
    return;
}

void serialize(Node *root) {
    memset(buff, 0, sizeof(buff));
    len = 0;
    __serialize(root);
    return;
}

void print(Node *node) {
    printf("%d(%d, %d)\n", KEY(node), 
                           KEY(node->lchild),
                           KEY(node->rchild));
    return;
}

void output(Node *root) {
    if (root == NULL) return;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return;
}

/*
广义表转二叉树
1. 遇到关键字 --> 生成新节点
2. 遇到( --> 将刚刚的新节点压栈，标记重置
3. 遇到, --> 标记当前处理右子树
4. 遇到) --> 将栈顶元素出栈
5. 每生成新节点 --> 根据标记设置左右子树
*/
Node *deserialize(char *buff, int n) {
    Node **s = (Node **)malloc(sizeof(Node *) * MAX_NODE);
    int top = -1, flag = 0, scode = 0, key = 0; // scode: 状态码
    Node *p = NULL, *root = NULL;
    for (int i = 0; buff[i]; ++i) {
        // scode: 0: 分发任务; 1~4对应上述2～5的操作
        switch (scode) {
            case 0: // 任务分发
                if (buff[i] >= '0' && buff[i] <= '9') {
                    scode = 1;
                } else if (buff[i] == '(') {
                    scode = 2;
                } else if (buff[i] == ',') {
                    scode = 3;
                } else {
                    scode = 4;
                }
                i -= 1;
                break;
            case 1:
                key = 0;
                while (buff[i] <= '9' && buff[i] >= '0') {
                    key = key * 10 + (buff[i] - '0');
                    i += 1;
                }
                p = getNewNode(key);
                if (top >= 0 && flag == 0) {
                    s[top]->lchild = p;
                } else if (top >= 0 && flag == 1) {
                    s[top]->rchild = p;
                }
                i -= 1;
                scode = 0;
                break;
            case 2:
                top += 1;
                s[top] = p;
                flag = 0;
                scode = 0;
                break;
            case 3:
                flag = 1;
                scode = 0;
                break;
            case 4:
                root = s[top];
                top -= 1;
                scode = 0;
                break;
        }
    }
    return root;
}

int main() {
    srand(time(0));
    Node *root = getRandomBinaryTree(10);
    serialize(root);
    output(root);
    printf("Buff[]: %s\n", buff);
    Node *new_root = deserialize(buff, len);
    output(new_root);
    return 0;
}
