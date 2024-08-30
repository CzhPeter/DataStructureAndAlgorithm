/*
Given the head of a singly linked list and two integers left and right where left <= right, 
reverse the nodes of the list from position left to position right, and return the reversed list.
Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (head == nullptr || head->next == nullptr || left == right) return head;
        ListNode* start = head;
        ListNode* end = head;
        ListNode virtual_head, *prev = &virtual_head;
        virtual_head.next = head;
        for (int i = 1; i < left; ++i) {
            prev = prev->next;
            start = start->next;
        }
        for (int i = 1; i < right; ++i) {
            end = end->next;
        }
        ListNode* new_head = end->next;
        end->next = nullptr;
        ListNode* p = start;
        while(p != nullptr) {
            ListNode* next = p->next;
            p->next = new_head;
            new_head = p;
            if (next == nullptr) break;
            p = next;
        }
        prev->next = new_head;
        return virtual_head.next;
    }
};

class Solution_2 {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == 1 && right == 1) return head;
        if (left != 1) {
            // 把当前头节点之后的子链表的翻转结果，接在当前头节点后面
            head->next = reverseBetween(head->next, left - 1, right - 1);
        } else { 
            // 左区间为1，右区间不为1，说明当前头节点也在翻转区域内，记录翻转后子链表的尾节点
            ListNode* tail = head->next, *new_head;
            // 递归得到翻转剩下部分的链表，把当前头节点挂到末尾
            new_head = reverseBetween(head->next, left, right - 1);
            head->next = tail->next;
            tail->next = head;
            head = new_head;
        }
        return head;
    }
};