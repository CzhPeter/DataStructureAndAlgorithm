/*
Given two integer arrays pushed and popped each with distinct values, 
return true if this could have been the result of a sequence of push and pop operations on an initially empty stack, 
or false otherwise.
*/

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int x = 0; // 入栈序列的下标
        int n = pushed.size();
        stack<int> s;
        for (int i = 0; i < n; ++i) {
            // 当前出栈序列的元素不等于栈顶元素或栈为空时
            if (s.empty() || popped[i] != s.top()) {
                // 入栈序列的元素依次入栈，直到所有元素都入栈，或者将当前出栈序列的元素入栈
                while (x < pushed.size() && pushed[x] != popped[i]) {
                    s.push(pushed[x]);
                    x += 1;
                }
                // 所有元素都入栈了，栈顶也不是当前出栈序列的元素时，序列非法
                if (x == pushed.size()) return false;
                s.push(pushed[x]);
                x += 1;
            }
            s.pop();
        }
        return true;
    }
};