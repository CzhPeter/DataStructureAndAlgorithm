/*
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:
1. Starting with any positive integer, replace the number by the sum of the squares of its digits.
2. Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
3. Those numbers for which this process ends in 1 are happy.

Return true if n is a happy number, and false if not.
*/

class Solution {
public:
    // 计算数字每一位的平方和
    int getNext(int x) {
        int d, y = 0;
        while(x) {
            d = x % 10;
            y += d * d;
            x /= 10;
        }
        return y;
    }

    bool isHappy(int n) {
        // 通过链表思想，将问题转换为判断环形链表的问题
        // 19->82->68->100->1
        // 把1看作空地址，每个中间数看成链表的节点
        int p = n, q = n;
        while (q != 1) {
            p = getNext(p);
            q = getNext(getNext(q));
            if (p == q && q != 1) return false;
        }
        return true;
    }
};