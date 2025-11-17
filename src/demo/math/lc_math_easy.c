/**
 * @file lc_math_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stdio.h"
#include "string.h"
#include "stdbool.h"
#include "stdlib.h"

#include "utils.h"

/* https://leetcode.cn/problems/largest-perimeter-triangle/ */
int largestPerimeter(int *nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(int), cmp);

    for (int i = numsSize - 1; i >= 2; i--) {
        if (nums[i - 2] + nums[i - 1] > nums[i]) {
            return (nums[i - 2] + nums[i - 1] + nums[i]);
        }
    }
    return 0;
}

/* https://leetcode.cn/problems/palindrome-number/ */
bool xisPalindrome(int x)
{
    char s[12] = {0};
    int l, r;

    sprintf(s, "%d", x);
    if (s[0] == '-') {
        return false;
    }
    l = 0, r = strlen(s) - 1;

    while (l < r) {
        if (s[l] != s[r]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}
