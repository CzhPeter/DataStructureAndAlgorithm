/*
Given a string s, find the length of the longest substring without repeating characters.
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

思路：二分算法问题
假设最长不含重复字符的子串的长度为l，能否找到长度为1 ~ n的不含重复字符的子串
x->长度：1 2 3 ... l l+1 l+2 ... n
y->能否：1 1 1 ... 1  0   0  ... 0
模型：前1后0找最后一个1的二分算法，设计x->y的函数即可
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 检查是否存在l长度的不含重复字符的子串
    bool check(string &s, int l) {
        int count[256] = {0}, k = 0; // count记录每一种字符出现的次数，k记录不同字符的数量
        for (int i = 0; s[i]; ++i) {
            count[s[i]] += 1;
            if (count[s[i]] == 1) k += 1;
            if (i >= l) {
                count[s[i - l]] -= 1;
                if (count[s[i - l]] == 0) {
                    k -= 1;
                }
            }
            if (l == k) return true;
        }
        return false;
    }

    int lengthOfLongestSubstring(string s) {
        int head = 0, tail = s.size(), mid;
        while (head < tail) {
            mid = (head + tail + 1) / 2;
            if (check(s, mid)) head = mid;
            else tail = mid - 1;
        }
        return head;
    }
};