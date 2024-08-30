/*
Given the head of a linked list, 
remove the nth node from the end of the list and return its head.
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
*/
#include <iostream>
#include <stdlib.h>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 利用虚拟头节点简化操作
        // 等距离双指针找倒数第n个节点的前一个节点
        ListNode virtual_head, *p = &virtual_head, *q = p;
        virtual_head.next = head;
        for (int i = 0; i < n + 1; ++i) {
            q = q->next;
        }
        while (q) {
            p = p->next;
            q = q->next;
        }
        q = p->next;
        p->next = p->next->next;
        free(q);
        return virtual_head.next;
    }
};