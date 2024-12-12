/*
Given an array of integers nums and an integer target, 
return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, 
and you may not use the same element twice.
You can return the answer in any order.
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> index(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            index[i] = i;
        }
        sort(index.begin(), index.end(), [&](int i, int j) -> bool {
            return nums[i] < nums[j];
        });
        int p1 = 0, p2 = nums.size() - 1;
        while (p1 < p2) {
            if (nums[index[p1]] + nums[index[p2]] > target) {
                p2 -= 1;
            } else if (nums[index[p1]] + nums[index[p2]] < target) {
                p1 += 1;
            } else {
                break;
            }
        }
        return vector<int>{index[p1], index[p2]};
    }
};