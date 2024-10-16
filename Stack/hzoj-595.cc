/*
在这道题目中，我们会给定一篇代码，并希望你能找到指定函数第一次被调用时的调用链，将其打印出来；
当然，你有可能会发现给定的函数没有在代码中出现，那么你应该打印一行“NOT REFERENCED”并结束你的程序。
输入
​ 第一行是一个数字 N ，代表代码共有 N 行；　
 接下来的 N 行，第 i+1 行是一个字符串 S[i]，代表第 i 行代码：　
​ 　1. 这行代码是一个函数调用，那么它的形式类似“fun()”；　
​ 　2. 这行代码是返回语句，它的内容固定为“return”；　
​ 第 N+2 行是一个字符串，代表欲寻找到的函数。
​ （0<N≤100000，0<|S[i]|≤110；给定的被调用函数名保证合法，其一定以“()”结尾并只由大小写字母和下划线组成）
输出
​ 输出一行：
　 1. 如果指定的函数在代码中出现了，那么打印出其调用关系链，用“->”连接；
　 2. 否则，打印一行“NOT REFERENCED”。
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> ops(n);
    string target;
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        cin >> ops[i];
    }
    cin >> target;
    stack<string> func_stack;
    for (int i = 0; i < n; ++i) {
        if (target == ops[i]) {
            func_stack.push(ops[i]);
            flag = 1;
            break;
        }
        if (ops[i] == "return") {
            func_stack.pop();
        } else {
            func_stack.push(ops[i]);
        }
    }
    vector<string> res;
    if (flag) {
        while (!func_stack.empty()) {
            res.push_back(func_stack.top());
            func_stack.pop();
        }
        for (int i = res.size() - 1; i >= 1; --i) {
            cout << res[i] << "->";
        }
        cout << res[0] << endl;
    } else {
        cout << "NOT REFERENCED" << endl;
    }
}