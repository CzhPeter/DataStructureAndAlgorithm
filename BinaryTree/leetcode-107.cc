/*
Given the root of a binary tree, 
return the bottom-up level order traversal of its nodes' values. 
Input: root = [3,9,20,null,null,15,7]
Output: [[15,7],[9,20],[3]]
*/

#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (root == nullptr) return vector<vector<int>>();
        // bfs
        TreeNode* node;
        queue<TreeNode*> q;
        q.push(root);
        stack<vector<int>> s;
        vector<vector<int>> ans;
        while (!q.empty()) {
            int cnt = q.size();
            vector<int> temp;
            for (int i = 0; i < cnt; ++i) {
                node = q.front();
                temp.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
                q.pop();
            }
            s.push(temp);
        }
        while (!s.empty()) {
            ans.push_back(s.top());
            s.pop();
        }
        return ans;
    }
};