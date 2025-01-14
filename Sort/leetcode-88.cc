/*
You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, 
and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
Merge nums1 and nums2 into a single array sorted in non-decreasing order.
The final sorted array should not be returned by the function, 
but instead be stored inside the array nums1. 
To accommodate this, nums1 has a length of m + n, 
where the first m elements denote the elements that should be merged, 
and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // 相当于从后往前进行归并过程
        int p1 = m - 1, p2 = n - 1, k = m + n - 1;
        while (p1 != -1 || p2 != -1) {
            if (p2 == -1 || (p1 != -1 && nums1[p1] >= nums2[p2])) {
                nums1[k--] = nums1[p1--];
            } else {
                nums1[k--] = nums2[p2--];
            }
        }
        return;
    }
};