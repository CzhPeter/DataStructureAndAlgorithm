/*
You are given an array of k linked-lists lists,
each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
*/

#include <iostream>
#include <vector>
#include <set>

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
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        typedef pair<int, int> PII;
        int n = lists.size();
        set<PII> s;
        // 先存放每个链表的第一个元素
        for (int i = 0; i < n; ++i) {
            if (lists[i] == nullptr) continue;
            s.insert(PII(lists[i]->val, i));
        }
        ListNode new_head, *p = &new_head, *q; // new_head为虚拟头节点
        new_head.next = nullptr;
        // 将堆顶添加到结果链表中，并往堆内加入剩余元素
        while (s.size()) {
            PII a = *s.begin();
            s.erase(s.begin());
            q = lists[a.second];
            lists[a.second] = lists[a.second]->next;
            p->next = q;
            q->next = nullptr;
            p = q;
            if (lists[a.second]) {
                s.insert(PII(lists[a.second]->val, a.second));
            }
        }
        return new_head.next;
    }
};