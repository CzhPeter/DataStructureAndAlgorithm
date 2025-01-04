/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), 
return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
You may assume all four edges of the grid are all surrounded by water.
Example:
Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
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
            for (int i = 0; i < n; ++i) {
                fa[i] = i;
            }
        }

        int get(int x) {
            return fa[x] = (fa[x] == x ? x : get(fa[x]));
        }

        void merge(int a, int b) {
            fa[get(a)] = get(b);
            return;
        }

        vector<int> fa;
    };

    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        UnionSet u(n * m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '0') continue;
                int index = i * m + j;
                if (j + 1 < m && grid[i][j + 1] == '1') {
                    u.merge(index, index + 1);
                }
                if (i + 1 < n && grid[i + 1][j] == '1') {
                    u.merge(index, index + m);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int index = i * m + j;
                if (grid[i][j] == '1' && u.get(index) == index) {
                    ans += 1;
                }
            }
        }
        return ans;
    }
};