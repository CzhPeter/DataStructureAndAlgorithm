/*
给出一个表达式,其中运算符仅包含 +,-,*,/,^ 要求求出表达式的最终值。
数据可能会出现括号情况，还有可能出现多余括号情况，忽略多余括号，正常计算即可；
​数据保证不会出现大于 max long int 的数据；
数据可能会出现负数情况，幂次不可能为负数，除法采用向 0 取整。
​注意：−9 和 +9 分别代表负数和正数的 9

输入：(2+2)^(1+1)
输出：16

输入：9/-9
输出：-1
*/

#include <iostream>
#include <cmath>
#include <stack>
#include <unordered_map>
using namespace std;

#define INF 0x3f3f3f3f

bool is_operator(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^': return true;
        default: return false;
    }
    return false;
}

// 把表达式看成树结构的递归计算法
long long calc(string &s, long long l, long long r) {
    long long pos = -1, pri = INF - 1, cur_pri, temp_pri = 0;
    // 找到优先级权重最低的符号位置，即最后一个计算的符号
    for (long long i = l; i < r; ++i) {
        cur_pri = INF;
        switch (s[i]) {
            case '(': temp_pri += 100; break;
            case ')': temp_pri -= 100; break;
            case '+': 
            case '-': cur_pri = 1 + temp_pri; break;
            case '*':
            case '/': cur_pri = 2 + temp_pri; break;
            case '^': cur_pri = 3 + temp_pri; break;
        }
        // 对负数的特殊处理
        if ((s[i] == '-' || s[i] == '+') &&
            (i - 1 < 0 || is_operator(s[i - 1]))) {
            cur_pri += 1000;
        }
        // 优先级相同的情况下，越后出现的符号越后计算
        if (pri >= cur_pri) {
            pri = cur_pri;
            pos = i;
        }
    }
    if (pos == -1) { // 没有运算符
        // 返回纯数字
        long long num = 0;
        for (long long i = l; i < r; ++i) {
            if (s[i] < '0' || s[i] > '9') continue;
            num = num * 10 + (s[i] - '0');
        }
        return num;
    } else { // 由最后计算的运算符把表达式分为2部分递归计算
        long long a = calc(s, l, pos);
        long long b = calc(s, pos + 1, r);
        switch (s[pos]) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
            case '^': return (long long)pow(a, b);
        }
    }
    return 0;
}

// 双栈法
void replace(string& s) {
    long long pos = s.find(" ");
    while (pos != -1) {
        s.replace(pos, 1, "");
        pos = s.find(" ");
    }
}

void cal(stack<long long> &nums, stack<char> &ops) {
    if(nums.size() < 2 || ops.empty())
        return;
    long long b = nums.top(); nums.pop();
    long long a = nums.top(); nums.pop();
    char op = ops.top(); ops.pop();
    long long ans;
    switch (op) {
        case '+': ans = a + b; break;
        case '-': ans = a - b; break;
        case '*': ans = a * b; break;
        case '/': ans = a / b; break;
        case '^': ans = pow(a, b); break;
    }
    nums.push(ans);
}

int get_priority(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':   
        case '/': return 2;
        case '^': return 3;
    }
    return 0;
}

long long calculate(string s) {
    // 存放所有的数字
    stack<long long> nums;
    // 为了防止第一个数为负数，先往 nums 加个 0
    nums.push(0);
    // 将所有的空格去掉
    replace(s);
    // 存放所有的操作
    stack<char> ops;
    long long n = s.size();
    bool negative_flag = false;
    for(long long i = 0; i < n; i++) {
        char c = s[i];
        if(c == '(')
            ops.push(c);
        else if(c == ')') {
            // 计算到最近一个左括号为止
            while(!ops.empty()) {
                char op = ops.top();
                if(op != '(')
                    cal(nums, ops);
                else {
                    ops.pop();
                    break;
                }
            }
        }
        else {
            if(isdigit(c)) {
                long long cur_num = 0;
                long long j = i;
                // 将从 i 位置开始后面的连续数字整体取出，加入 nums
                while(j < n && isdigit(s[j]))
                    cur_num = cur_num * 10 + (s[j++] - '0');
                // 注意上面的计算一定要有括号，否则有可能会溢出
                if (negative_flag) {
                    cur_num = 0 - cur_num;
                    negative_flag = true;
                }
                nums.push(cur_num);
                i = j - 1;
            }
            else {
                if (i > 0 && 
                    (s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-')) {
                    nums.push(0);
                }
                if (s[i] == '-' && !isdigit(s[i - 1])) {
                    negative_flag = true;
                    continue;
                }
                // 有一个新操作要入栈时，先把栈内可以算的都算了
                while(!ops.empty() && ops.top() != '(') {
                    char prev = ops.top();
                    if (get_priority(prev) >= get_priority(c)) {
                        cal(nums, ops);
                    } else {
                        break;
                    }
                }
                ops.push(c);
            }
        }
    }
    while(!ops.empty())
        cal(nums, ops);
    return nums.top();
}

int main() {
    string str;
    cin >> str;
    cout << calc(str, 0, str.size()) << endl;
    cout << calculate(str) << endl;
    return 0;
}



