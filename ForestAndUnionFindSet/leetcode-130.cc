/*
You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
Connect: A cell is connected to adjacent cells horizontally or vertically.
Region: To form a region connect every 'O' cell.
Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.
Example:
Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    class UnionSet {
    public:
        UnionSet(int n) : fa(n + 1) {
            for(int i = 0; i <= n; ++i) {
                fa[i] = i;
            }
        }

        int get(int x) {
            return fa[x] = (fa[x] == x ? x : get(fa[x]));
        }

        void merge(int a, int b) {
            if (get(a) == get(b)) return;
            fa[get(a)] = get(b);
            return;
        }

        vector<int> fa;
    };

    void solve(vector<vector<char>>& board) {
        int m = board.size(), n = board[0].size();
        UnionSet u(n * m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int index = i * n + j + 1; // 映射点在board内的坐标和并查集的节点下标
                if (board[i][j] != 'O') continue;
                // O点在边上
                if (i == 0 || i == m - 1) {
                    u.merge(index, 0);
                }
                if (j == 0 || j == n - 1) {
                    u.merge(index, 0);
                }
                // 和右向连通
                if (j + 1 < n && board[i][j + 1] == 'O') {
                    u.merge(index, index + 1);
                }
                // 和下面连通
                if (i + 1 < m && board[i + 1][j] == 'O') {
                    u.merge(index, index + n);
                }
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != 'O') continue;
                int index = i * n + j + 1;
                // 把不与边相连的O都改成X
                if (u.get(index) != u.get(0)) {
                    board[i][j] = 'X';
                }
            }
        }
        return;
    }
};