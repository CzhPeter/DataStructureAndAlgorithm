/*
An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.
Given an integer n, return the nth ugly number.
Input: n = 10
Output: 12
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        set<long long> s;
        s.insert(1);
        long long ans = 0;
        while (n--) {
            ans = *s.begin();
            s.erase(s.begin());
            if (ans % 5 == 0) {
                s.insert(ans * 5);
            } else if (ans % 3 == 0) {
                s.insert(ans * 3);
                s.insert(ans * 5);
            } else {
                s.insert(ans * 2);
                s.insert(ans * 3);
                s.insert(ans * 5);
            }
        }
        return ans;
    }
};