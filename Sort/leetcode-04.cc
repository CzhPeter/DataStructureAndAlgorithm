/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, 
return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        vector<int> temp(n + m);
        int p1 = 0, p2 = 0, k = 0;
        while (p1 < n || p2 < m) {
            if (p2 == m || (p1 != n && nums1[p1] < nums2[p2])) {
                temp[k++] = nums1[p1++];
            } else {
                temp[k++] = nums2[p2++];
            }
        }
        double a = temp[(n + m) / 2], b = a;
        if ((n + m) % 2 == 0) {
            b = temp[(n + m) / 2 - 1];
        }
        return (a + b) / 2.0;
    }
};