/*
单词接龙是一个与我们经常玩的成语接龙相类似的游戏，
现在我们已知一组单词，且给定一个开头的字母，要求出以这个字母开头的最长的“龙”（每个单词都最多在“龙”中出现两次），
在两个单词相连时，其重合部分合为一部分，例如 beast 和 astonish，如果接成一条龙则变为 beastonish，
另外相邻的两部分不能存在包含关系，例如 at 和 atide 间不能相连。
输入格式:
输入的第一行为一个单独的整数 n 表示单词数，
以下 n 行每行有一个单词，输入的最后一行为一个单个字符，表示“龙”开头的字母。
你可以假定以此字母开头的“龙”一定存在。
输出格式:
只需输出以此字母开头的最长的“龙”的长度。
样例输入:
5
at
touch
cheat
choose
tact
a
样例输出:
23
样例解释：连成的“龙”为 atoucheatactactouchoose。
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_N 20
string s[MAX_N + 5]; // s[i]为单词，s[i][j]为字母
char start;
int d[MAX_N + 5][MAX_N + 5] = {0}; // d[i][j]表示第i个单词和第j个单词之间的重叠部分长度
int n, ans;
int vis[MAX_N + 5] = {0};

// 找s1末尾和s2开头的重叠长度
int f(string &s1, string &s2) {
    for (int i = s1.size() - 1; i >= 1; --i) {
        int flag = 1;
        for (int j = 0; j < s1.size() - i; ++j) {
            if (s1[i + j] == s2[j]) {
                continue;
            }
            flag = 0;
            break;
        }
        if (flag == 1) {
            return s1.size() - i;
        }
    }
    return 0;
}

// 参数说明: 
// x: 当前接龙最后一个单词的下标
// L: 当前龙的总长度
void dfs(int x, int L) {
    vis[x] += 1;
    if (L > ans) ans = L;
    for (int y = 0; y < n; ++y) {
        if (d[x][y] == 0) continue;
        if (vis[y] == 2) continue;
        dfs(y, L + s[y].size() - d[x][y]);
    }
    vis[x] -= 1;
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    cin >> start;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = f(s[i], s[j]);
        }
    }
    // 找第一个单词
    for (int i = 0; i < n; ++i) {
        if (s[i][0] != start) continue;
        dfs(i, s[i].size());
    }
    cout << ans << endl;
    return 0;
}