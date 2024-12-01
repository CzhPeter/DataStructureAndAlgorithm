/*
Given the root of a binary tree, 
return the level order traversal of its nodes' values.
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) return vector<vector<int>>();
        // bfs
        TreeNode* node;
        queue<TreeNode*> q;
        q.push(root);
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
            ans.push_back(temp);
        }
        return ans;
    }
};

class Solution_1 {
public:
    void dfs(TreeNode* root, int k, vector<vector<int>>& ans) {
        if (root == nullptr) return;
        if (k == ans.size()) ans.push_back(vector<int>());
        ans[k].push_back(root->val);
        dfs(root->left, k + 1, ans);
        dfs(root->right, k + 1, ans);
        return;
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        // dfs
        vector<vector<int>> ans;
        dfs(root, 0, ans);
        return ans;
    }
};