/*
Given two integer arrays nums1 and nums2, return an array of their intersection. 
Each element in the result must be unique and you may return the result in any order.
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> h;
        vector<int> ret;
        for (int i = 0; i < nums1.size(); ++i) {
            h.insert(nums1[i]);
        }
        for (int i = 0; i < nums2.size(); ++i) {
            if (h.find(nums2[i]) == h.end()) continue;
            ret.push_back(nums2[i]);
            h.erase(nums2[i]);
        }
        return ret;
    }
};