/**
 * @file lc_sort_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stdio.h"
#include "stdlib.h"

#include "utils.h"

/* https://leetcode.cn/problems/minimum-difference-between-highest-and-lowest-of-k-scores/ */
int minimumDifference(int *nums, int numsSize, int k)
{
    int i;
    int ans = INT_MAX;
    int tmp;

    qsort(nums, numsSize, sizeof(int), cmp);
    for (i = 0; i < numsSize - k + 1; i++) {
        tmp = abs(nums[i] - nums[i + k - 1]);
        ans = tmp < ans ? tmp : ans;
    }

    return ans;
}

/* https://leetcode.cn/problems/relative-ranks/ */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findRelativeRanks(int *score, int scoreSize, int *returnSize)
{
    int i;
    char *str[] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
    char **ans = (char **)malloc(sizeof(char *) * scoreSize);
    int arr[scoreSize][2];

    *returnSize = scoreSize;

    for (i = 0; i < scoreSize; i++) {
        arr[i][0] = -score[i];
        arr[i][1] = i;
    }

    qsort(arr, scoreSize, sizeof(arr[0]), cmp);
    for (i = 0; i < scoreSize; i++) {
        if (i < 3) {
            ans[arr[i][1]] = str[i];
        } else {
            ans[arr[i][1]] = (char *)malloc(sizeof(char) * 8);
            sprintf(ans[arr[i][1]], "%d", i + 1);
        }
    }
    return ans;
}

/* https://leetcode.cn/problems/maximum-product-of-three-numbers/ */
int maximumProduct(int *nums, int numsSize)
{
    int n1, n2;

    qsort(nums, numsSize, sizeof(int), cmp);
    n1 = nums[0] * nums[1] * nums[numsSize - 1];
    n2 = nums[numsSize - 1] * nums[numsSize - 2] * nums[numsSize - 3];
    return (n1 > n2 ? n1 : n2);
}

/* https://leetcode.cn/problems/assign-cookies/ */
int findContentChildren(int *g, int gSize, int *s, int sSize)
{
    if (s == NULL || sSize == 0) {
        return 0;
    }
    qsort(g, gSize, sizeof(int), cmp);
    qsort(s, sSize, sizeof(int), cmp);

    int t1 = gSize - 1, t2 = sSize - 1;
    int ans = 0;
    while (t1 != -1 && t2 != -1) {
        if (s[t2] >= g[t1]) {
            ans++;
            t2--;
            t1--;
        } else {
            t1--;
        }
    }
    return ans;
}
