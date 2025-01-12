/*
输入一个高精度的正整数 n（长度不大于 240 位），
去掉其中任意 s 个数字后剩下的数字按原左右次序将组成一个新的正整数，现求一种方案，使得新的正整数数值最小。
输入:
​第一行一个整数 n。
​第二行一个正整数 s。
输出:
​输出一个数表示最小值，输出时忽略数字的前导零。
样例输入:
179566
4
样例输出:
15
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_N 500
char s[MAX_N + 5];
int k;

// 贪心策略: 每次删除一个离最高位最近的逆序位的第一个数字，进行 n 次删除
int main() {
    cin >> s >> k;
    for (int i = 0; i < k; ++i) {
        int j = 0;
        while (s[j + 1] != '\0' && s[j] <= s[j + 1]) {
            j += 1;
        }
        while (s[j]) {
            s[j] = s[j + 1];
            j += 1;
        }
    }
    for (int i = 0, flag = 1; s[i]; ++i) {
        if (s[i] == '0' && flag) {
            continue;
        }
        cout << s[i];
        flag = 0;
    }
    cout << endl;
}