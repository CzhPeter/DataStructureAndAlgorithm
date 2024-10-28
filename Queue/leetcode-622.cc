/*
Design your implementation of the circular queue. 
The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle, 
and the last position is connected back to the first position to make a circle. 
It is also called "Ring Buffer".
*/

typedef struct Node {
    int data;
    Node *next;
} Node;

// 单向循环链表实现
class MyCircularQueue {
public:
    int count, size;
    Node *head, *tail;
    MyCircularQueue(int k) {
        // 初始化单向循环链表
        head = new Node();
        tail = head;
        for (int i  = 1; i < k; ++i) {
            tail->next = new Node();
            tail = tail->next;
        }
        tail->next = head;
        count = 0;
        size = k;
        return;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        tail = tail->next;
        tail->data = value;
        count += 1;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        head = head->next;
        count -= 1;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return head->data;
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return tail->data;
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == size;
    }
};