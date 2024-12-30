#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_M 3
#define MAX_OP 12
#define LCHILD(root, pos) (root->next[pos])
#define RCHILD(root, pos) (root->next[pos + 1])
#define LAST_KEY(root) (root->key[root->n - 1])
#define LAST_CHILD(root) (root->next[root->n])
typedef struct Node {
    int n;
    int key[MAX_M + 1];
    struct Node *next[MAX_M + 1];
} Node;

Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->n = 0;
    memset(p->next, 0, sizeof(Node *) * (MAX_M + 1));
    return p;
}

Node *insert_key(Node *root, int key) {
    if (root == NULL) {
        root = getNewNode();
        root->key[(root->n)++] = key;
        return root;
    }
    // 找到终端节点内的插入位置，元素后移再插入
    int pos = 0;
    while (pos < root->n && root->key[pos] < key) {
        pos += 1;
    }
    if (root->key[pos] == key) return root;
    for (int i = root->n - 1; i >= pos; --i) {
        root->key[i + 1] = root->key[i];
    }
    root->key[pos] = key;
    root->n += 1;
    return root;
}

// 参数：父节点，可能发生失衡的子节点，子节点在父节点的子树位置
Node *insert_maintain(Node *root, Node *child, int pos) {
    if (child->n < MAX_M) return root;
    // 进行节点分裂
    int split_pos = MAX_M / 2;
    Node *node1 = getNewNode();
    Node *node2 = getNewNode();
    node1->n = split_pos;
    node2->n = MAX_M - 1 - split_pos;
    for (int i = 0; i < split_pos; ++i) {
        node1->key[i] = child->key[i];
        node1->next[i] = child->next[i];
    }
    node1->next[split_pos] = child->next[split_pos];
    for (int i = 0; i < node2->n; ++i) {
        node2->key[i] = child->key[i + split_pos + 1];
        node2->next[i] = child->next[i + split_pos + 1];
    }
    node2->next[node2->n] = child->next[child->n];
    // 中间节点上移到父节点中
    for (int i = root->n; i >= pos; --i) {
        root->key[i + 1] = root->key[i];
        root->next[i + 1] = root->next[i];
    }
    root->key[pos] = child->key[split_pos];
    root->next[pos] = node1;
    root->next[pos + 1] = node2;
    root->n += 1;
    free(child);
    return root;
}

Node *__insert(Node *root, int key) {
    // root为终端节点
    if (root == NULL || root->next[0] == NULL) {
        return insert_key(root, key);
    }
    // root不是终端节点，找到要插入的那棵子树
    int pos = 0;
    while (pos < root->n && root->key[pos] < key) {
        pos += 1;
    }
    if (pos < root->n && root->key[pos] == key) return root;
    __insert(root->next[pos], key);
    return insert_maintain(root, root->next[pos], pos);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    // 应对根节点可能关键字太多的情况
    if (root->n == MAX_M) {
        Node *p = getNewNode();
        p->next[0] = root;
        root = insert_maintain(p, root, 0);
    }
    return root;
}

void erase_pos(Node *root, int pos) {
    for (int i = pos + 1; i < root->n; ++i) {
        root->key[i - 1] = root->key[i];
    }
    root->n -= 1;
    return;
}

void right_rotate(Node *root, int pos) {
    // 右孩子所有的key向后移动一位再填上父节点pos处的key
    for (int i = RCHILD(root, pos)->n + 1; i >= 0; --i) {
        RCHILD(root, pos)->key[i] = RCHILD(root, pos)->key[i - 1];
        RCHILD(root, pos)->next[i] = RCHILD(root, pos)->next[i - 1];
    }
    RCHILD(root, pos)->key[0] = root->key[pos];
    // 把左孩子的最后一个关键字赋值给父节点pos处
    root->key[pos] = LAST_KEY(LCHILD(root, pos));
    // 把左孩子的最后一个分支移动到右孩子的第一个分支
    RCHILD(root, pos)->next[0] = LAST_CHILD(LCHILD(root, pos));
    LAST_CHILD(LCHILD(root, pos)) = NULL;
    RCHILD(root, pos)->n += 1;
    LCHILD(root, pos)->n -= 1;
    return;
}

void left_rotate(Node *root, int pos) {
    // 将父节点pos处的关键字放到左孩子关键字的最后一位
    LCHILD(root, pos)->key[LCHILD(root, pos)->n] = root->key[pos];
    LCHILD(root, pos)->n += 1;
    // 将右孩子的第一个关键字放到父节点的pos处
    root->key[pos] = RCHILD(root, pos)->key[0];
    // 把右孩子的第一个分支移动到左孩子的最后一个分支
    LAST_CHILD(LCHILD(root, pos)) = RCHILD(root, pos)->next[0];
    // 右孩子所有关键字和分支向前移动一位
    for (int i = 0; i < RCHILD(root, pos)->n; ++i) {
        RCHILD(root, pos)->key[i] = RCHILD(root, pos)->key[i + 1];
        RCHILD(root, pos)->next[i] = RCHILD(root, pos)->next[i + 1];
    }
    // 右孩子最后一个分支置空
    LAST_CHILD(RCHILD(root, pos)) = NULL;
    RCHILD(root, pos)->n -= 1;
    return;
}

// 合并pos和pos + 1处的节点
void merge_node(Node *root, int pos) {
    Node *node = getNewNode();
    for (int i = 0; i <= LCHILD(root, pos)->n; ++i) {
        node->key[i] = LCHILD(root, pos)->key[i];
        node->next[i] = LCHILD(root, pos)->next[i];
    }
    node->n = LCHILD(root, pos)->n + 1;
    node->key[node->n - 1] = root->key[pos];
    for (int i = 0; i <= RCHILD(root, pos)->n; ++i) {
        node->key[i + node->n] = RCHILD(root, pos)->key[i];
        node->next[i + node->n] = RCHILD(root, pos)->next[i];
    }
    node->n += RCHILD(root, pos)->n;
    free(LCHILD(root, pos));
    free(RCHILD(root, pos));
    for (int i = pos + 1; i <= root->n; ++i) {
        root->key[i - 1] = root->key[i];
        root->next[i - 1] = root->next[i];
    }
    root->next[pos] = node;
    root->n -= 1;
    return;
}

Node *erase_maintain(Node *root, int pos) {
    int lower_bound = (MAX_M + 1) / 2 - 1;
    if (root->next[pos]->n >= lower_bound) return root;
    // 情况1：左右兄弟有关键字可以借
    if (pos > 0 && root->next[pos - 1]->n > lower_bound) {
        right_rotate(root, pos - 1);
    } else if (pos < root->n && root->next[pos + 1]->n > lower_bound) {
        left_rotate(root, pos);
    } else {
        // 情况2：左右兄弟没有关键字可以借
        if (pos > 0) merge_node(root, pos - 1); // merge(i, j) -> pos = j 与 pos = j + 1 合并
        else merge_node(root, pos);
    }
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NULL) return root;
    int pos = 0;
    while (pos < root->n && root->key[pos] < key) {
        pos += 1;
    }
    if (root->next[0] == NULL) {
        // key在终端节点处，直接删除对应的pos
        if (root->key[pos] == key) {
            erase_pos(root, pos);
        }
        return root;
    } else {
        // key不在终端节点处
        if (pos < root->n && root->key[pos] == key) {
            // key在当前节点的关键字中
            // 找前驱
            Node *temp = root->next[pos];
            while (temp->next[temp->n]) {
                temp = temp->next[temp->n];
            }
            // 与前驱进行替换
            int val = temp->key[temp->n - 1];
            root->key[pos] = val;
            // 递归删除前驱
            root->next[pos] = __erase(root->next[pos], val);
        } else {
            // key不在当前节点的关键字中
            root->next[pos] = __erase(root->next[pos], key);
        }
    }
    return erase_maintain(root, pos);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    if (root->n == 0) {
        // 把唯一子树提升为根节点
        Node *temp = root->next[0];
        free(root);
        root = temp;
    }
    return root;
}

void clear(Node *root) {
    if (root == NULL) return;
    for (int i = 0; i <= root->n; ++i) {
        clear(root->next[i]);
    }
    free(root);
    return;
}

void print_node(Node *root) {
    printf("%d : ", root->n);
    for (int i = 0; i < root->n; ++i) {
        printf("%4d", root->key[i]);
    }
    printf(" | ");
    if (root->next[0] == NULL) goto output_end;
    for (int i = 0; i <= root->n; ++i) {
        printf("%4d", root->next[i]->key[0]);
    }
output_end:
    printf("\n");
    return;
}

void output(Node *root) {
    if (root == NULL) return;
    print_node(root);
    for (int i = 0; i <= root->n; ++i) {
        output(root->next[i]);
    }
    return;
}

int main() {
    srand(time(0));
    Node *root = NULL;
    for (int i = 0; i < MAX_OP; ++i) {
        int x = rand() % 100;
        root = insert(root, x);
        printf("\ninsert %d to BTree: \n", x);
        output(root);
    }
    int x;
    while (~scanf("%d", &x)) {
        printf("erase %d from BTree: \n", x);
        root = erase(root, x);
        output(root);
    }
    return 0;
}