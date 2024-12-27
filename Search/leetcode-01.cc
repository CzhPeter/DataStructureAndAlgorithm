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
#include <unordered_map>
#include <algorithm>

using namespace std;

class SolutionHashMap {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> h;
        vector<int> res(2);
        for (int i = 0; i < nums.size(); ++i) {
            if (h.find(target - nums[i]) != h.end()) {
                res[0] = h[target - nums[i]];
                res[1] = i;
                break;
            }
            h[nums[i]] = i;
        }
        return res;
    }
};

class SolutionBinarySearch {
public:
    int binary_search(vector<int>& nums, vector<int>& index, int b, int x) {
        int head = b, tail = nums.size() - 1, mid;
        while (head <= tail) {
            mid = (head + tail) / 2;
            if (nums[index[mid]] == x) return mid;
            if (nums[index[mid]] < x) head = mid + 1;
            else tail = mid - 1;
        }
        return -1;
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> index(n, 0);
        for (int i = 0; i < n; ++i) {
            index[i] = i;
        }
        sort(index.begin(), index.end(), [&](int i, int j) -> bool {
            return nums[i] < nums[j];
        });
        vector<int> res(2);
        for (int i = 0; i < n; ++i) {
            int j = binary_search(nums, index, i + 1, target - nums[index[i]]);
            if (j == -1) continue;
            res[0] = index[j];
            res[1] = index[i];
        }
        if (res[0] > res[1]) swap(res[0], res[1]);
        return res;
    }
};