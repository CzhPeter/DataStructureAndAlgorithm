/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', 
determine if the input string is valid.

An input string is valid if:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.
*/

#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<int> brackets_stack;
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                brackets_stack.push(s[i]);
            } else {
                switch (s[i]) {
                case ')':
                    if (brackets_stack.empty() || brackets_stack.top() != '(') return false;
                    brackets_stack.pop();
                    break;
                case ']':
                    if (brackets_stack.empty() || brackets_stack.top() != '[') return false;
                    brackets_stack.pop();
                    break;
                case '}':
                    if (brackets_stack.empty() || brackets_stack.top() != '{') return false;
                    brackets_stack.pop();
                    break;
                }
            }
        }
        if (!brackets_stack.empty()) return false;
        return true;
    }
};