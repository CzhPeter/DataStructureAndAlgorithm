/*
Given an integer array nums and an integer k, 
return true if there are two distinct indices i and j in the array such that 
nums[i] == nums[j] and abs(i - j) <= k.
Input: nums = [1,2,3,1], k = 3
Output: true
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> index(n);
        for (int i = 0; i < n; ++i) {
            index[i] = i;
        }
        sort(index.begin(), index.end(), [&](int i, int j) -> bool {
            if (nums[i] != nums[j]) {
                return nums[i] < nums[j];
            }
            return i < j;          
        });
        for (int i = 0; i < n - 1; ++i) {
            if (nums[index[i]] != nums[index[i + 1]]) continue;
            if (index[i + 1] - index[i] <= k) {
                return true;
            }
        }
        return false;
    }
};