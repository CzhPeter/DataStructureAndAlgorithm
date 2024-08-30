/*
Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer. 
Internally, pos is used to denote the index of the node that tail's next pointer is connected to (0-indexed). 
It is -1 if there is no cycle. Note that pos is not passed as a parameter.

Do not modify the linked list.
*/

#include <unordered_set>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        // 设头节点到环起始点的距离为a，环的长度为x
        // 当慢指针走到起始点时，快指针在环内走了 a 距离，此时双指针都在环内
        // 慢指针在走了 x - a 的距离后，与快指针相遇
        // 此时只要让快指针再走 a 距离，快指针就会回到起始点
        ListNode *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        if (fast == nullptr || fast->next == nullptr) return nullptr;
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

class Solution_2 {
public:
    ListNode *detectCycle(ListNode *head) {
        // 利用哈希表记录遇到的节点，一旦遇到已经访问过的节点，说明存在环，直接返回
        std::unordered_set<ListNode*> visited;
        while (head) {
            if (visited.count(head)) return head;
            visited.insert(head);
            head = head->next;
        }
        return nullptr;
    }
};
