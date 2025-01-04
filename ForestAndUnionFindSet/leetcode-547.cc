/*
There are n cities. Some of them are connected, while some are not. 
If city a is connected directly with city b, 
and city b is connected directly with city c, 
then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.
You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, 
nd isConnected[i][j] = 0 otherwise.
Return the total number of provinces
Example:
Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2
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

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionSet u(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j]) {
                    u.merge(i, j);
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (u.get(i) == i) {
                ans += 1;
            }
        }
        return ans;
    }
};