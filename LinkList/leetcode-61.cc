/*
Given the head of a linked list, rotate the list to the right by k places.
Input: head = [1,2,3,4,5], k = 2
Output: [4,5,1,2,3]
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
    int getLength(ListNode* head) {
        int len = 0;
        while (head) {
            len += 1;
            head = head->next;
        }
        return len;
    }

    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return head;
        // 找到倒数第k个节点，把链表分成2部分，后半部分接到前半部分之前即可
        int n = getLength(head);
        k %= n; // 当k大于链表长度时，需要通过取余进行预处理
        if (k == 0) return head;
        
        // 使用等距离双指针法快速定位到倒数第k个节点的前一个节点位置
        ListNode *p = head, *q = head;
        for (int i = 0; i < k + 1; ++i) {
            q = q->next;
        }
        while (q) {
            p = p->next;
            q = q->next;
        }

        // 拆分链表，q为后半部分链表头，p为前半部分链表尾
        q = p->next;
        p->next = nullptr;
        
        // 遍历后半部分找到链表尾，将其接到前半部分链表头之前
        p = q;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = head;
        return q;
    }
};
