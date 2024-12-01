/*
Given the root of a binary tree, 
return the zigzag level order traversal of its nodes' values.
Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
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
    void dfs(TreeNode* root, int k, vector<vector<int>>& ans) {
        if (root == nullptr) return;
        if (k == ans.size()) {
            ans.push_back(vector<int>());
        }
        ans[k].push_back(root->val);
        dfs(root->left, k + 1, ans);
        dfs(root->right, k + 1, ans);
        return;
    }

    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        dfs(root, 0, ans);
        for (int k = 1; k < ans.size(); k += 2) {
            for (int i = 0, j = ans[k].size() - 1; i < j; i++, j--) {
                swap(ans[k][i], ans[k][j]);
            }
        }
        return ans;
    }
};