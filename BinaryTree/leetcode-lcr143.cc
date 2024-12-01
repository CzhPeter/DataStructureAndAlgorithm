/*
给定两棵二叉树 tree1 和 tree2，
判断 tree2 是否以 tree1 的某个节点为根的子树具有相同的结构和节点值。
注意，空树 不会是以 tree1 的某个节点为根的子树具有相同的结构和节点值。
输入：tree1 = [3,6,7,1,8], tree2 = [6,1]
输出：true
解释：tree2 与 tree1 的一个子树拥有相同的结构和节点值。即 6 - > 1。
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
    bool match_one(TreeNode* A, TreeNode* B) {
        if (B == nullptr) return true;
        if (A == nullptr || A->val != B->val) return false;
        // 左右子树进行匹配
        return match_one(A->left, B->left) && match_one(A->right, B->right);
    }

    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (A == nullptr || B == nullptr) return false;
        // 当前结点可以匹配上，就继续匹配子树
        if (A->val == B->val && match_one(A, B)) return true;
        // 当前结点不行，继续向下匹配
        if (isSubStructure(A->left, B)) return true;
        if (isSubStructure(A->right, B)) return true;
        return false;
    }
};