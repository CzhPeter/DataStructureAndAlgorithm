/*
给一 n×n 的字母方阵，内可能蕴含多个 yizhong 单词。单词在方阵中是沿着同一方向连续摆放的。
摆放可沿着 8 个方向的任一方向，同一单词摆放时不再改变方向，单词与单词之间可以交叉，因此有可能共用字母。
输出时，将不是单词的字母用 * 代替，以突出显示单词。
输入格式:
第一行输入一个数 n。(7≤n≤100)。
第二行开始输入 n×n 的字母矩阵。
输出格式:
突出显示单词的 n×n 矩阵。
样例输入:
8
qyizhong
gydthkjy
nwidghji
orbzsfgz
hhgrhwth
zzzzzozo
iwdfrgng
yyyygggg
样例输出:
*yizhong
gy******
n*i*****
o**z****
h***h***
z****o**
i*****n*
y******g
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_N 100
int n;
int direct[8][2] = {
    {1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {-1, 1}
};
char g[MAX_N + 5][MAX_N + 5] = {0};
int vis[MAX_N + 5][MAX_N + 5] = {0}; // vis[i][j]表示(i, j)位置的字母是否访问过
int ans[MAX_N + 5][MAX_N + 5] = {0}; // ans[i][j] = 1表示该位置的字母保留，0表示改成*
char match[8] = "yizhong";

void get_ans(int x, int y) {
    for (int k = 0; k < 8; ++k) {
        int flag = 1;
        for (int i = 0; match[i]; ++i) {
            int dx = x + i * direct[k][0];
            int dy = y + i * direct[k][1];
            if (match[i] == g[dx][dy]) continue;
            flag = 0;
            break;
        }
        if (flag == 1) {
            for (int i = 0; match[i]; ++i) {
                int dx = x + i * direct[k][0];
                int dy = y + i * direct[k][1];
                ans[dx][dy] = 1;
            }
        }
    }
    return;
}

// 参数说明: i, j: 当前搜索的坐标
void dfs(int i, int j) {
    if (g[i][j] == '\0') return;
    if (vis[i][j]) return;
    if (g[i][j] == 'y') {
        get_ans(i, j);
    }
    vis[i][j] = 1;
    dfs(i, j + 1);
    dfs(i + 1, j);
    return;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> g[i][j];
        }
    }
    dfs(1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (ans[i][j]) cout << g[i][j];
            else cout << "*";
        }
        cout << endl;
    }
    return 0;
}