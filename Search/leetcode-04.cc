/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, 
return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000

泛化思路：求两个正序数组的第 K 位个元素 （二分算法）
假设两个数组各取前 k/2 个元素，选取的最后一个元素分别为 a 和 b ，且 a < b ，
此时最多有 k/2 - 1 + k/2 - 1 = k - 2 个元素比 a 小，所以 a 的最大排名就是 k - 1 。
由于数组1中 a 及其之前的元素全是排名前 k 位且不是第 k 位的元素，
所以可以舍弃掉包括 a 在内的所有 k/2 个元素，
此时问题变成：在剩下的元素中查找排名为 k/2 的元素。（每次查找范围缩小了一半，二分思想）
基于上述操作迭代若干轮，问题会变成查找排名为 1 的元素，得出结果。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // 求两个正序数组中第K位的元素
    int findK(vector<int> &n1, int index1, vector<int> &n2, int index2, int k) {
        // 返回第k位元素
        if (k == 1) {
            int a = (n1.size() == index1 ? INT32_MAX : n1[index1]);
            int b = (n2.size() == index2 ? INT32_MAX : n2[index2]);
            return min(a, b);
        }
        if (n1.size() == index1) return n2[k - 1];
        if (n2.size() == index2) return n1[k - 1];
        // 选元素，确保选的元素总和等于k
        int count1 = min(k / 2, static_cast<int>(n1.size() - index1));
        int count2 = min(k - count1, static_cast<int>(n2.size() - index2));
        count1 = k - count2;
        // 比较分别选取的最后一个元素，并通过修改指针位置来舍弃元素并迭代
        if (n1[index1 + count1 - 1] <= n2[index2 + count2 - 1]) {
            return findK(n1, index1 + count1, n2, index2, k - count1);
        }
        return findK(n1, index1, n2, index2 + count2, k - count2);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if ((n + m) % 2 == 1) return findK(nums1, 0, nums2, 0, (n + m) / 2 + 1);
        double a = findK(nums1, 0, nums2, 0, (n + m) / 2);
        double b = findK(nums1, 0, nums2, 0, (n + m) / 2 + 1);
        return (a + b) / 2.0;
    }
};