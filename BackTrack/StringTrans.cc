/*
已知有两个字串 A,B 及一组字串变换的规则（至多 6 个规则），形如：
A1→B1。
A2→B2。
规则的含义为：在 A 中的子串 A1 可以变换为 B1，A2 可以变换为 B2 ⋯。
例如：A=abcd，B＝xyz，
变换规则为：abc→xu，ud→y，y→yz。
则此时，A 可以经过一系列的变换变为 B，其变换的过程为：
abcd→xud→xy→xyz。
共进行了 3 次变换，使得 A 变换为 B。
输入格式:
第一行有两个字符串 A,B。
接下来若干行，每行有两个字符串 Ai,Bi，表示一条变换规则。
输出格式:
若在 10 步（包含 10 步）以内能将 A 变换为 B，则输出最少的变换步数；否则输出 NO ANSWER!。
样例输入:
abcd xyz
abc xu
ud y
y yz
样例输出:
3
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define MAX_NUM 100
int trans_count = 0, ans = MAX_NUM, ans_k;
string a, b;
string from[10], to[10]; // 变换前后的字符串
map<string, int> dp; // 搜索剪枝，记录已经变换过的字符串与其变换的最小次数

// 参数说明:
// now: 当前要变换的字符串
// step: 当前已经变换的次数
void dfs(string &now, int step) {
    if (step > ans_k) return;
    dp[now] = step;
    if (step > 10) return;
    if (now == b) {
        ans = step;
        return;
    }
    for (int i = 0; i < trans_count; ++i) {
        int pos = -1;
        pos = now.find(from[i]);
        while (pos != -1) {
            string changed = now;
            changed.erase(pos, from[i].size());
            changed.insert(pos, to[i]);
            if (dp.find(changed) == dp.end() || dp[changed] > step + 1) {
                dfs(changed, step + 1);
            }
            pos = now.find(from[i], pos + 1);
        }
    }
}

int main() {
    cin >> a >> b;
    while (cin >> from[trans_count] >> to[trans_count]) {
        trans_count++;
    }
    // 迭代加深：找到变换次数少的就直接输出，不做更多搜索
    for (int i = 1; i <= 10; ++i) {
        ans_k = i;
        dp.clear();
        dfs(a, 0);
        if (ans != MAX_NUM) break;
    }
    if (ans == MAX_NUM) cout << "NO ANSWER!" << endl;
    else cout << ans << endl;
    return 0;
}