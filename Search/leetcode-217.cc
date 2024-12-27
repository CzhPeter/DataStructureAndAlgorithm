/*
Given an integer array nums, 
return true if any value appears at least twice in the array, 
and return false if every element is distinct.
Input: nums = [1,2,3,1]
Output: true
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> h;
        for (auto x : nums) {
            if (h.find(x) != h.end()) return true;
            h.insert(x);
        }
        return false;
    }
};