/*
Given the head of a singly linked list, reverse the list, and return the reversed list.
Input: head = [1,2,3,4,5]
Output: [5,4,3,2,1]
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution_1 {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 无虚拟头节点的头插法
        ListNode* new_head = head;
        ListNode* p = head->next;
        new_head->next = nullptr;
        while (p) {
            ListNode* q = p->next;
            p->next = new_head;
            new_head = p;
            if (q == nullptr) {
                break;
            }
            p = q;
        }
        return p;
    }
};

class Solution_2 {
public:
    ListNode* reverseList(ListNode* head) {
        // 利用虚拟头节点的头插法
        ListNode virtual_head;
        ListNode* p = head;
        ListNode* q = nullptr;
        while (p) {
            q = p->next;
            p->next = virtual_head.next;
            virtual_head.next = p;
            p = q;
        }
        return virtual_head.next;
    }
};

class Solution_3 {
public:
    ListNode* reverseList(ListNode* head) {
        // 边界条件
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 下一节点为头的链表已经反转完成，当前节点应插入到末尾
        ListNode* tail = head->next;
        ListNode* new_head = reverseList(head->next); // 递归语义
        head->next = tail->next;
        tail->next  = head;
        return new_head;
    }
};