/*
Given two integer arrays preorder and inorder 
where preorder is the preorder traversal of a binary tree 
and inorder is the inorder traversal of the same tree, 
construct and return the binary tree.
Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) return nullptr;
        int pos = 0, n = preorder.size(); 
        // root pos in inorder
        while (inorder[pos] != preorder[0]) {
            pos += 1;
        }
        TreeNode *root = new TreeNode(preorder[0]);
        vector<int> preArr, inArr;
        // left child
        // preorder
        for (int i = 1; i <= pos; ++i) {
            preArr.push_back(preorder[i]);
        }
        // inorder
        for (int i = 0; i < pos; ++i) {
            inArr.push_back(inorder[i]);
        }
        root->left = buildTree(preArr, inArr);
        // right child
        preArr.clear();
        inArr.clear();
        // preorder
        for (int i = pos + 1; i < n; ++i) {
            preArr.push_back(preorder[i]);
        }
        // inorder
        for (int i = pos + 1; i < n; ++i) {
            inArr.push_back(inorder[i]);
        }
        root->right = buildTree(preArr, inArr);
        return root;
    }
};