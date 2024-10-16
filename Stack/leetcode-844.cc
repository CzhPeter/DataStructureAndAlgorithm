/*
Given two strings s and t, 
return true if they are equal when both are typed into empty text editors. 
'#' means a backspace character.
Note that after backspacing an empty text, the text will continue empty.
Input: s = "ab#c", t = "ad#c"
Output: true
Explanation: Both s and t become "ac".
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    bool backspaceCompare(string s, string t) {
        vector<char> s_stack;
        vector<char> t_stack;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != '#') {
                s_stack.push_back(s[i]);
            } else {
                if (!s_stack.empty()) {
                    s_stack.pop_back();
                }
                continue;
            }
        }
        for (int i = 0; i < t.size(); ++i) {
            if (t[i] != '#') {
                t_stack.push_back(t[i]);
            } else {
                if (!t_stack.empty()) {
                    t_stack.pop_back();
                }
                continue;
            }
        }
        if (s_stack.size() != t_stack.size()) {
            return false;
        } else {
            for (int i = 0; i < s_stack.size(); ++i) {
                if (s_stack[i] != t_stack[i]) {
                    return false;
                }
            }
        }
        return true;
    }
};