#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DL 3
#define STR(n) #n
#define DIGIT_LEN_STR(n) "%" STR(n) "d"

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* get_new_node(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = val;
    new_node->next = NULL;
    return new_node;
}

// 无头链表的返回值为链表的首地址
Node* insert(Node* head, int pos, int val) {
    if (pos == 0) {
        Node* new_node = get_new_node(val);
        new_node->next = head;
        head = new_node;
        return head;
    }
    int len = 0;
    for (Node* p = head; p != NULL; p = p->next) {
        len += 1;
    }
    if (pos > len) return head;
    // 找到待插入位置的前一个结点
    Node *p = head;
    for (int i = 0; i < pos - 1; ++i) {
        p = p->next;
    }
    Node* new_node = get_new_node(val);
    new_node->next = p->next;
    p->next = new_node;
    return head;
}

// 有头链表插入操作，可以不对插入链表头做特殊操作
Node* insert_with_virtual_head(Node* head, int pos, int val) {
    int len = 0;
    for (Node* p = head; p != NULL; p = p->next) {
        len += 1;
    }
    if (pos > len) return head;
    Node new_head;
    Node* p = &new_head;
    new_head.next = head;
    for (int i = 0; i < pos; ++i) {
        p = p->next;
    }
    Node* new_node = get_new_node(val);
    new_node->next = p->next;
    p->next = new_node;
    return new_head.next;
}

Node* erase(Node* head, int pos) {
    if (pos == 0) {
        Node* new_head = head->next;
        free(head);
        return new_head;
    }
    int len = 0;
    for (Node* p = head; p != NULL; p = p->next) {
        len += 1;
    }
    if (pos > len) return head;
    Node *p = head;
    for (int i = 0; i < pos - 1; ++i) {
        p = p->next;
    }
    Node* erase_node = p->next;
    if (erase_node->next == NULL) {
        p->next = NULL;
        free(erase_node);
        return head;
    }
    p->next = p->next->next;
    free(erase_node);
    return head;
}

void clear(Node *head) {
    if (head == NULL) return;
    for (Node* p = head, *q; p != NULL; p = q) {
        q = p->next;
        free(p);
    }
    return;
}

void output_linklist(Node* head, int flag) {
    int n = 0;
    for (Node* p = head; p != NULL; p = p->next) {
        n += 1;
    }
    for (int i = 0; i < n; ++i) {
        printf(DIGIT_LEN_STR(DL), i);
        printf("  ");
    }
    printf("\n");
    for (Node* p = head; p != NULL; p = p->next) {
        printf(DIGIT_LEN_STR(DL), p->data);
        printf("->");
    }
    printf("\n");
    if (flag == 0) printf("\n\n");
    return;
}

int find(Node* head, int val) {
    Node *p = head;
    int n = 0;
    while (p) {
        if (p->data == val) {
            output_linklist(head, 1);
            int len = n * (DL + 2) + 2;
            for (int i = 0; i < len; ++i) printf(" ");
            printf("^\n");
            for (int i = 0; i < len; ++i) printf(" ");
            printf("|\n");
            return 1;
        }
        n += 1;
        p = p->next;
    }
    return 0;
}

int main() {
    srand(time(0));
    Node* head = NULL;
    for (int i = 0; i < 20; ++i) {
        int op = rand() % 3;
        int pos, val;
        switch (op) {
            case 0:
                pos = rand() % (i + 1);
                val = rand() % 100;
                printf("insert %d at %d to linklist with virtual head\n", val, pos);
                head = insert_with_virtual_head(head, pos, val);
                break;
            case 1:
                pos = rand() % (i + 1);
                val = rand() % 100;
                printf("insert %d at %d to linklist\n", val, pos);
                head = insert(head, pos, val);
                break;
            case 2:
                pos = rand() % (i + 1);
                printf("erase at %d to linklist\n", pos);
                head = erase(head, pos);
                break;
        }
        output_linklist(head, 0);
    }
    int val;
    while (~scanf("%d", &val)) {
        if (!find(head, val)) {
            printf("not found\n");
        }
    }
    clear(head);
    return 0;
}