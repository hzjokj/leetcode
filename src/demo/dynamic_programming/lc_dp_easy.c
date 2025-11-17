/**
 * @file lc_dp_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "stdio.h"

#include "utils.h"

/* 数学归纳法 */

/* https://leetcode.cn/problems/get-maximum-in-generated-array/ */
int getMaximumGenerated(int n)
{
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    int dp[n + 1];
    int i;
    int ans = 0;

    dp[1] = 1;
    for (i = 2; i <= n; i++) {
        if ((i & 1) == 0) {
            dp[i] = dp[i / 2];
        } else {
            dp[i] = dp[i / 2] + dp[(i / 2) + 1];
        }
        ans = (dp[i] > ans) ? dp[i] : ans;
    }
    return ans;
}

/* https://leetcode.cn/problems/n-th-tribonacci-number/ */
int tribonacci(int n)
{
    if (n == 0) {
        return 0;
    }

    if (n <= 2) {
        return 1;
    }

    int p = 0, q = 0, r = 1, s = 1;
    int i;
    for (i = 3; i <= n; i++) {
        p = q;
        q = r;
        r = s;
        s = p + q + r;
    }
    return s;
}

/* https://leetcode.cn/problems/min-cost-climbing-stairs/ */
int minCostClimbingStairs(int *cost, int costSize)
{
    int dp[costSize + 1];
    int i;

    dp[0] = dp[1] = 0;
    for (i = 2; i <= costSize; i++) {
        dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]);
    }
    return dp[costSize];
}

int minCostClimbingStairsTest(void)
{
    int cost[] = {10, 15, 20};
    int costSize = ARRAY_SIZE(cost);
    printf("input:\n");
    PRINT_ARRAY(cost, costSize, "%d ");
    int ret = minCostClimbingStairs(cost, costSize);
    printf("output:%d\n", ret);
    return 0;
}

/* https://leetcode.cn/problems/fibonacci-number/description/ */
/* 斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1
给定 n ，请计算 F(n) 。

示例 1：

输入：n = 2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1
示例 2：

输入：n = 3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2
示例 3：

输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3


提示：

0 <= n <= 30 */
int fib(int n)
{
    if (n < 2) {
        return n;
    }

    int dp[n + 1];
    int i;

    dp[0] = 0;
    dp[1] = 1;

    for (i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

/* https://leetcode.cn/problems/climbing-stairs/ */
/*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶

提示：

1 <= n <= 45 */
int climbStairs(int n)
{
    if (n <= 2) {
        return n;
    }

    int dp[n + 1];
    int i;

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;

    for (i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int climbStairsTest(void)
{
    int n = 4;
    printf("input:%d\n", n);
    int ret = climbStairs(n);
    printf("output:%d\n", ret);
    return 0;
}

int lc_dp_easy_test(void)
{
    int ret = -1;
    // ret = climbStairsTest();
    // ret = minCostClimbingStairsTest();
    return ret;
}
