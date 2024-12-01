/*
Given the root of an n-ary tree, return the preorder traversal of its nodes' values.
Nary-Tree input serialization is represented in their level order traversal. 
Each group of children is separated by the null value.
Input: root = [1,null,3,2,4,null,5,6]
Output: [1,3,5,6,2,4]
*/

#include <iostream>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    void __preorder(Node* root, vector<int>& ans) {
        if (root == nullptr) return;
        ans.push_back(root->val);
        for (auto x : root->children) {
            __preorder(x, ans);
        }
        return;
    }

    vector<int> preorder(Node* root) {
        vector<int> ans;
        __preorder(root, ans);
        return ans;
    }
};