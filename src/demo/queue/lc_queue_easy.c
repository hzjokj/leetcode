/**
 * @file lc_queue_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* https://leetcode.cn/problems/implement-stack-using-queues/ */
/* 请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。


注意：

你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size 和 is empty 这些操作。
你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。


示例：

输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False


提示：

1 <= x <= 9
最多调用100 次 push、pop、top 和 empty
每次调用 pop 和 top 都保证栈不为空


进阶：你能否仅用一个队列来实现栈。*/
typedef struct {
} MyStack;

MyStack *myStackCreate()
{
    return 0;
}

void myStackPush(MyStack *obj, int x)
{
}

int myStackPop(MyStack *obj)
{
    return 0;
}

int myStackTop(MyStack *obj)
{
    return 0;
}

bool myStackEmpty(MyStack *obj)
{
    return 0;
}

void myStackFree(MyStack *obj)
{
}

/* https://leetcode.cn/leetbook/read/queue-stack/kzlb5/ */
/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/

/* 设计你的循环队列实现。 循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。
它也被称为“环形缓冲器”。

循环队列的一个好处是我们可以利用这个队列之前用过的空间。在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，
即使在队列前面仍有空间。但是使用循环队列，我们能使用这些空间去存储新的值。

你的实现应该支持如下操作：

MyCircularQueue(k): 构造器，设置队列长度为 k 。
Front: 从队首获取元素。如果队列为空，返回 -1 。
Rear: 获取队尾元素。如果队列为空，返回 -1 。
enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
isEmpty(): 检查循环队列是否为空。
isFull(): 检查循环队列是否已满。
 

示例：

MyCircularQueue circularQueue = new MyCircularQueue(3); // 设置长度为 3
circularQueue.enQueue(1);  // 返回 true
circularQueue.enQueue(2);  // 返回 true
circularQueue.enQueue(3);  // 返回 true
circularQueue.enQueue(4);  // 返回 false，队列已满
circularQueue.Rear();  // 返回 3
circularQueue.isFull();  // 返回 true
circularQueue.deQueue();  // 返回 true
circularQueue.enQueue(4);  // 返回 true
circularQueue.Rear();  // 返回 4
 

提示：

所有的值都在 0 至 1000 的范围内；
操作数将在 1 至 1000 的范围内；
请不要使用内置的队列库。*/
typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} MyCircularQueue;

bool myCircularQueueIsEmpty(MyCircularQueue *obj);
bool myCircularQueueIsFull(MyCircularQueue *obj);

MyCircularQueue *myCircularQueueCreate(int k)
{
    MyCircularQueue *obj = (MyCircularQueue *)malloc(sizeof(MyCircularQueue));
    if (!obj) {
        printf("malloc MyCircularQueue failed\n");
        return NULL;
    }
    obj->data = (int *)malloc(sizeof(int) * k);
    if (!obj->data) {
        printf("malloc obj->data failed\n");
        return NULL;
    }
    memset(obj->data, 0, sizeof(int) * k);
    obj->front = -1;
    obj->rear = -1;
    obj->size = k;
    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue *obj, int value)
{
    if (myCircularQueueIsFull(obj)) {
        printf("queue is full\n");
        return false;
    }
    if (myCircularQueueIsEmpty(obj)) {
        obj->front = obj->rear = 0;
    } else if (obj->rear == obj->size - 1) {
        obj->rear = 0;
    } else {
        obj->rear++;
    }

    obj->data[obj->rear] = value;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue *obj)
{
    if (myCircularQueueIsEmpty(obj)) {
        printf("queue if empty\n");
        return false;
    }
    if (obj->front == obj->rear) {
        obj->front = obj->rear = -1;
    } else if (obj->front == obj->size - 1) {
        obj->front = 0;
    } else {
        obj->front++;
    }
    return true;
}

int myCircularQueueFront(MyCircularQueue *obj)
{
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->data[obj->front];
}

int myCircularQueueRear(MyCircularQueue *obj)
{
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->data[obj->rear];
}

bool myCircularQueueIsEmpty(MyCircularQueue *obj)
{
    return (obj->front == -1) ? true : false;
}

bool myCircularQueueIsFull(MyCircularQueue *obj)
{
    if ((obj->front == 0 && obj->rear == obj->size - 1) ||
        obj->front == obj->rear + 1) {
        return true;
    }
    return false;
}

void myCircularQueueFree(MyCircularQueue *obj)
{
    free(obj->data);
    free(obj);
}

void myCircularQueueTest(void)
{
    int ret = 0;
    MyCircularQueue *obj = myCircularQueueCreate(3);
    myCircularQueueEnQueue(obj, 1);
    myCircularQueueEnQueue(obj, 2);
    myCircularQueueEnQueue(obj, 3);
    myCircularQueueEnQueue(obj, 4);
    ret = myCircularQueueRear(obj);
    printf("rear=%d\n", ret);
    myCircularQueueIsFull(obj);
    myCircularQueueDeQueue(obj);
    myCircularQueueEnQueue(obj, 4);
    ret = myCircularQueueRear(obj);
    printf("rear=%d\n", ret);
    myCircularQueueFree(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/

void lc_queue_easy_test(void)
{
    // myCircularQueueTest();
}
