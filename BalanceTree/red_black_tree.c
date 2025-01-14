#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1
#define DBLACK 2

#define K(n) (n->key)
#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define C(n) (n->color)

typedef struct Node {
    int key, color; // 0 red; 1 black; 2 double black
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = -1;
    NIL->color = BLACK;
    NIL->lchild = NIL->rchild = NIL;
    return;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->color = RED;
    p->lchild = p->rchild = NIL;
    return p;
}

int has_red_node(Node *root) {
    return C(L(root)) == RED || C(R(root)) == RED;
}

Node *left_rotate(Node *root) {
    Node *new_root = root->rchild;
    root->rchild = new_root->lchild;
    new_root->lchild = root;
    return new_root;
}

Node *right_rotate(Node *root) {
    Node *new_root = root->lchild;
    root->lchild = new_root->rchild;
    new_root->rchild = root;
    return new_root;
}

Node *insert_maintain(Node *root) {
    // 判断是否失衡：左右子树中是否出现相邻两个红色节点
    int flag = 0;
    if (C(L(root)) == RED && has_red_node(L(root))) flag = 1;
    if (C(R(root)) == RED && has_red_node(R(root))) flag = 2;
    if (flag == 0) return root;
    // 情况一：左右子树根节点均为红色
    if (C(L(root)) == RED && C(R(root)) == RED) goto red_up_maintain;
    // 情况二：左右子树的子树根节点也为红色，分为LL, LR, RR, RL
    if (flag == 1) {
        if (C(R(L(root))) == RED) {
            L(root) = left_rotate(L(root));
        }
        root = right_rotate(root);
    } else {
        if (C(L(R(root))) == RED) {
            R(root) = right_rotate(R(root));
        }
        root = left_rotate(root);
    }
red_up_maintain:
    // 红色上浮调整
    C(root) = RED;
    C(L(root)) = C(R(root)) = BLACK;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = __insert(root->lchild, key);
    else root->rchild = __insert(root->rchild, key);
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    C(root) = BLACK;
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase_maintain(Node *root) {
    // 判断左右孩子是否有双重黑
    if (C(L(root)) != DBLACK && C(R(root)) != DBLACK) {
        return root;
    }
    // 双重黑的兄弟节点为红色
    if (has_red_node(root)) {
        // 原根节点变红色，左旋/右旋后把新根节点变成黑色，
        // 此时双重黑的兄弟节点变为黑色，递归处理
        root->color = RED;
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
        } else {
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        }
        root->color = BLACK;
        return root;
    }
    // 双重黑的兄弟节点为黑色
    // 情况1：兄弟节点的孩子没有红色节点
    if (root->lchild->color == DBLACK && !has_red_node(root->rchild) || 
        root->rchild->color == DBLACK && !has_red_node(root->lchild) ) {
        root->color += 1;
        root->lchild->color -= 1;
        root->rchild->color -= 1;
        return root;
    }
    // 情况2：孩子有红色节点，需要区分是否同侧，构成LL, LR, RR, RL四种类型
    if (root->rchild->color == DBLACK) {
        // 双重黑节点的兄弟节点在左侧
        root->rchild->color = BLACK;
        if (root->lchild->lchild->color != RED) { // 兄弟节点的右孩子为红色，LR先对兄弟节点进行小左旋
            root->lchild = left_rotate(root->lchild);
        }
        // LL & LR 再对根节点大右旋
        root->lchild->color = root->color; // 新根节点的颜色改为原根节点的颜色
        root = right_rotate(root);
    } else {
        // 双重黑节点的兄弟节点在右侧
        root->lchild->color = BLACK;
        if (root->rchild->rchild->color != RED) { // 兄弟节点的左孩子为红色，RL先对兄弟节点进行小右旋
            root->rchild = right_rotate(root->rchild);
        }
        // LL & LR 再对根节点大左旋
        root->rchild->color = root->color; // 新根节点的颜色改为原根节点的颜色
        root = left_rotate(root);
    }
    // 新根节点的两个子节点颜色都改黑
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key < root->key) {
        root->lchild = __erase(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        // 删除节点度为0或1
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->lchild : root->rchild;
            // 孩子节点上色（删除红色节点：孩子颜色不变；删除黑色节点：度为1：孩子红变黑；度为0：NIL变双重黑）
            temp->color += root->color;
            free(root);
            return temp;
        }
        // 删除节点度为2：找前驱，转换为度为1或0的问题
        Node *temp = predecessor(root);
        root->key = temp->key;
        root->lchild = __erase(root->lchild, temp->key);
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

void output(Node *root) {
    if (root == NIL) return;
    printf("(%d | %d; %d, %d)\n",
        C(root),
        K(root),
        K(L(root)),
        K(R(root))
    );
    output(root->lchild);
    output(root->rchild);
    return;
}

int main() {
    srand(time(0));
    #define MAX_N 10
    Node *root = NIL;
    for (int i = 0; i < MAX_N; ++i) {
        int x = rand() % 100;
        printf("\ninsert %d to red black tree: \n", x);
        root = insert(root, x);
        output(root);
    }
    int x;
    while (~scanf("%d", &x)) {
        printf("\nerase %d from red black tree\n", x);
        root = erase(root, x);
        output(root);
    }
    return 0;
}