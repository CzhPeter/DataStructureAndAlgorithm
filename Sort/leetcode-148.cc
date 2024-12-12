/*
Given the head of a linked list, return the list after sorting it in ascending order.
Input: head = [4,2,1,3]
Output: [1,2,3,4]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

 // Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // 快速排序法
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        int l = head->val, r = head->val;
        ListNode *p = head, *h1 = nullptr, *h2 = nullptr, *q = nullptr;
        // 设立基准值
        while (p) {
            l = min(p->val, l);
            r = max(p->val, r);
            p = p->next;
        }
        if (l == r) return head;
        int mid = (l + r) >> 1;
        // 根据基准值进行左右分区，头插到h1和h2中
        p = head;
        while (p) {
            q = p->next;
            if (p->val <= mid) {
                p->next = h1;
                h1 = p;
            } else {
                p->next = h2;
                h2 = p;
            }
            p = q;
        }
        // 对2个分区递归地快速排序
        h1 = sortList(h1);
        h2 = sortList(h2);
        // 合并分区
        p = h1;
        while (p->next) p = p->next;
        p->next = h2;
        return h1;
    }
};

class Solution_1 {
public:
    int getLength(ListNode* head) {
        int n = 0;
        while (head) {
            n += 1;
            head = head->next;
        }
        return n;
    }

    ListNode* merge_sort(ListNode* head, int n) {
        if (n <= 1) return head;
        // 将链表分成2部分
        int l = n / 2, r = n - l;
        ListNode *p = head, *p1 = head, *p2 = nullptr;
        for (int i = 1; i < l; ++i) {
            p = p->next;
        }
        p2 = p->next;
        p->next = nullptr;
        p1 = merge_sort(p1, l);
        p2 = merge_sort(p2, r);
        // 合并链表成有序
        ListNode ret; // 虚拟头节点
        p = &ret;
        ret.next = nullptr;
        while (p1 || p2) {
            if (p2 == nullptr || (p1 && p1->val < p2->val)) {
                p->next = p1;
                p = p1;
                p1 = p1->next;
            } else {
                p->next = p2;
                p = p2;
                p2 = p2->next;
            }
        }
        return ret.next;
    }

    // 归并排序法 
    ListNode* sortList(ListNode* head) {
        int n = getLength(head);
        return merge_sort(head, n);
    }
};