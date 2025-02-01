/*
魔族现在使用一种新型的密码系统。每一个密码都是一个给定的仅包含小写字母的英文单词表，
每个单词至少包含 1 个字母，至多 75 个字母。
如果在一个由一个词或多个词组成的表中，除了最后一个以外，每个单词都被其后的一个单词所包含，
即前一个单词是后一个单词的前缀，则称词表为一个词链。例如下面单词组成了一个词链：
i；
int；
integer。
但下面的单词不组成词链：
integer；
intern。
现在你要做的就是在一个给定的单词表中取出一些词，组成最长的词链，就是包含单词数最多的词链。
将它的单词数统计出来，就得到密码了。
输入格式:
这些文件的格式是，第一行为单词表中的单词数 N（1≤N≤2000），
下面每一行有一个单词，按字典顺序排列，中间也没有重复的单词。
输出格式:
输出共一行，一个整数，表示密码。
样例输入:
5
i
int
integer
intern
internet
样例输出:
4
*/

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstring>

using namespace std;

// dp状态: dp[i] 代表以第 i 位单词为结尾的最长词链的长度
// 状态转移: dp[i] = max(dp[j]) + 1
// 合法的 j 表示 j 单词是 i 单词的前缀

#define MAX_N 2000
string word[MAX_N + 5]; // 存储每一个单词
int dp[MAX_N + 5];

bool is_prefix(int j, int i) {
    if (word[j].size() > word[i].size()) return false;
    for (int k = 0; word[j][k]; ++k) {
        if (word[j][k] - word[i][k]) return false;
    }
    return true;
}

int main() {
    int n, ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> word[i];
    }
    for (int i = 0; i < n; ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (is_prefix(j, i)) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}