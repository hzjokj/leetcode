/**
 * @file lc_stack_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#include "utils.h"

/* https://leetcode.cn/leetbook/read/queue-stack/gomvm/ */
/* 给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。

请你计算该表达式。返回一个表示表达式值的整数。

注意：

有效的算符为 '+'、'-'、'*' 和 '/' 。
每个操作数（运算对象）都可以是一个整数或者另一个表达式。
两个整数之间的除法总是 向零截断 。
表达式中不含除零运算。
输入是一个根据逆波兰表示法表示的算术表达式。
答案及所有中间计算结果可以用 32 位 整数表示。
 

示例 1：

输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
示例 2：

输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
示例 3：

输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22
 

提示：

1 <= tokens.length <= 104
tokens[i] 是一个算符（"+"、"-"、"*" 或 "/"），或是在范围 [-200, 200] 内的一个整数
 

逆波兰表达式：

逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。

平常使用的算式则是一种中缀表达式，如 ( 1 + 2 ) * ( 3 + 4 ) 。
该算式的逆波兰表达式写法为 ( ( 1 2 + ) ( 3 4 + ) * ) 。
逆波兰表达式主要有以下两个优点：

去掉括号后表达式无歧义，上式即便写成 1 2 + 3 4 + * 也可以依据次序计算出正确结果。
适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中 */
int evalRPN(char **tokens, int tokensSize)
{
    int i, m, n;
    int stk[tokensSize];
    int top = -1;
    bool sign = false;

    memset(stk, 0, sizeof(int) * tokensSize);

    for (i = 0; i < tokensSize; i++) {
        if (top >= 1) {
            if (strcmp(tokens[i], "+") == 0) {
                sign = true;
                m = stk[top--];
                n = stk[top--];
                stk[++top] = n + m;
            }

            if (strcmp(tokens[i], "-") == 0) {
                sign = true;
                m = stk[top--];
                n = stk[top--];
                stk[++top] = n - m;
            }

            if (strcmp(tokens[i], "*") == 0) {
                sign = true;
                m = stk[top--];
                n = stk[top--];
                stk[++top] = n * m;
            }

            if (strcmp(tokens[i], "/") == 0) {
                sign = true;
                m = stk[top--];
                n = stk[top--];
                stk[++top] = n / m;
            }
        }
        if (!sign) {
            stk[++top] = atoi(tokens[i]);
        }
        sign = false;

        printf("top=%d\n", top);
        PRINT_ARRAY(stk, tokensSize, "%d ");
    }
    return stk[0];
}

void evalRPNTest(void)
{
    char *tokens[] = {"10", "6", "9",  "3", "+", "-11", "*",
                      "/",  "*", "17", "+", "5", "+"};
    int tokensSize = ARRAY_SIZE(tokens);

    printf("input:\n");
    printf("tokensSize=%d\n", tokensSize);
    PRINT_ARRAY(tokens, tokensSize, "%s ");
    int ret = evalRPN(tokens, tokensSize);
    printf("output:%d\n", ret);
}

/* https://leetcode.cn/leetbook/read/queue-stack/genw3/ */
/* 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，
下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1:

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
示例 2:

输入: temperatures = [30,40,50,60]
输出: [1,1,1,0]
示例 3:

输入: temperatures = [30,60,90]
输出: [1,1,0]
 

提示：

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100
*/
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *dailyTemperatures(int *temperatures, int temperaturesSize, int *returnSize)
{
#if !defined(WAY1)
    int i;
    int stk[temperaturesSize];
    int top = -1;

    *returnSize = temperaturesSize;
    int *ans = (int *)malloc(sizeof(int) * (*returnSize));
    memset(ans, 0, sizeof(int) * (*returnSize));

    for (i = 0; i < temperaturesSize; i++) {
        while (top >= 0 && temperatures[i] > temperatures[stk[top]]) {
            int idx = stk[top--];
            ans[idx] = i - idx;
        }
        stk[++top] = i;
    }
#else
    int i, j;
    int idx = 0;
    int cnt = 0;

    *returnSize = temperaturesSize;
    int *ans = (int *)malloc(sizeof(int) * (*returnSize));
    memset(ans, 0, sizeof(int) * (*returnSize));

    for (i = 0; i < temperaturesSize; i++) {
        for (j = i + 1; j < temperaturesSize; j++) {
            if (temperatures[i] >= temperatures[j]) {
                cnt++;
            } else {
                ans[idx++] = cnt + 1;
                cnt = 0;
                break;
            }
        }
        if (j == temperaturesSize) {
            cnt = 0;
            ans[idx++] = 0;
        }
    }
#endif
    return ans;
}

void dailyTemperaturesTest(void)
{
    int temperatures[] = {89, 62, 70, 58, 47, 47, 46, 76, 100, 70};
    int temperaturesSize = ARRAY_SIZE(temperatures);
    int returnSize;

    printf("input:\n");
    PRINT_ARRAY(temperatures, temperaturesSize, "%d ");
    int *ret = dailyTemperatures(temperatures, temperaturesSize, &returnSize);
    printf("output:\n");
    PRINT_ARRAY(ret, returnSize, "%d ");
    free(ret);
}

/* https://leetcode.cn/leetbook/read/queue-stack/g5l7d/ */
/* 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.

提示：

-231 <= val <= 231 - 1
pop、top 和 getMin 操作总是在 非空栈 上调用
push, pop, top, and getMin最多被调用 3 * 104 次
*/

#define STACK_SIZE 30000

typedef struct {
    int data[STACK_SIZE];
    int top;
} MinStack;

MinStack *minStackCreate(void)
{
    MinStack *obj = (MinStack *)malloc(sizeof(MinStack));
    if (obj == NULL) {
        printf("malloc failed\n");
        return NULL;
    }
    memset(obj->data, 0, sizeof(int) * STACK_SIZE);
    obj->top = -1;
    return obj;
}

void minStackPush(MinStack *obj, int val)
{
    obj->top++;
    obj->data[obj->top] = val;
}

void minStackPop(MinStack *obj)
{
    obj->top--;
}

int minStackTop(MinStack *obj)
{
    return obj->data[obj->top];
}

int minStackGetMin(MinStack *obj)
{
    int min = obj->data[obj->top];
    for (int i = obj->top; i >= 0; i--) {
        if (obj->data[i] < min) {
            min = obj->data[i];
        }
    }
    return min;
}

void minStackFree(MinStack *obj)
{
    if (obj != NULL) {
        free(obj);
        obj = NULL;
    }
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/
void minStackTest(void)
{
    int ret = 0;
    MinStack *obj = minStackCreate();

    minStackPush(obj, -2);
    minStackPush(obj, 0);
    minStackPush(obj, -3);
    ret = minStackGetMin(obj);
    printf("min=%d\n", ret);
    minStackPop(obj);
    ret = minStackTop(obj);
    printf("top=%d\n", ret);
    ret = minStackGetMin(obj);
    printf("min=%d\n", ret);
    minStackFree(obj);
}

void lc_stack_easy_test(void)
{
    // minStackTest();
    // dailyTemperaturesTest();
    // evalRPNTest();
}
