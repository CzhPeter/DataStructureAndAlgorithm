/*
Candela 是一名漫画家，她有一个奇特的爱好，就是在纸上画括号。
这一天，刚刚起床的 Candela 画了一排括号序列，其中包含小括号 ()、中括号 [] 和大括号 {}，总长度为 N。
这排随意绘制的括号序列显得杂乱无章，于是 Candela 定义了什么样的括号序列是美观的：
 1. 空的括号序列是美观的；
 2. 若括号序列 `A` 是美观的，则括号序列 `(A)、[A]、{A}` 也是美观的；
 3. 若括号序列 `A、B` 都是美观的，则括号序列 `AB` 也是美观的；
现在 Candela 想在她绘制的括号序列中，找出其中连续的一段，满足这段子序列是美观的，并且长度尽量大。你能帮帮她吗？
输入：[[[[]]{}]]
输出：10

解题思路：
1、用栈处理得到每对括号的匹配关系
2、根据匹配关系，获得最长的连续合法括号长度
*/

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define MAX_N 10000
char str[MAX_N + 5];
int match[MAX_N + 5] = {0}; // match[i]对应的是与i位置括号匹配的括号位置，match[i] == 0 表示无合法匹配括号
stack<int> s;

int main() {
    cin >> (str + 1); // 第一个字符会存储在字符数组的1位置
    for (int i = 1; str[i]; ++i) {
        switch (str[i]) {
            case '(':
            case '[':
            case '{':
                s.push(i);
                break;
            case ')':
                if (!s.empty() && str[s.top()] == '(') {
                    match[s.top()] = i; // 记录匹配信息
                    match[i] = s.top(); // 可以不存
                    s.pop();
                } else {
                    s.push(i); // 当前位置之前的括号序列必定非法，压入右括号进行阻隔
                }
                break;
            case ']':
                if (!s.empty() && str[s.top()] == '[') {
                    match[s.top()] = i;
                    match[i] = s.top();
                    s.pop();
                } else {
                    s.push(i);
                }
                break;
            case '}':
                if (!s.empty() && str[s.top()] == '{') {
                    match[s.top()] = i;
                    match[i] = s.top();
                    s.pop();
                } else {
                    s.push(i);
                }
                break;
        }
    }

    int temp_ans = 0, ans = 0, i = 1;
    while (str[i]) {
        if (match[i]) {
            // 记录匹配长度，并且从当前合法序列的末尾往后一位再继续记录
            temp_ans += match[i] - i + 1;
            i = match[i] + 1;
        } else {
            i += 1;
            temp_ans = 0;
        }
        if (temp_ans > ans) {
            ans = temp_ans;
        }
    }
    printf("%d\n", ans);
    
    return 0;
}
