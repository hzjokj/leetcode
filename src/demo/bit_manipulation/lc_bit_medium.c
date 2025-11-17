/**
 * @file lc_bit_medium.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-11-01
 *
 * @copyright Copyright (c) 2023
 *
 */

/* https://leetcode.cn/problems/gray-code/ */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *grayCode(int n, int *returnSize)
{
    int size = 1 << n;
    int *ans = (int *)malloc(sizeof(int) * size);
    int i;

    for (i = 0; i < size; i++) {
        ans[i] = (i >> 1) ^ i;
    }
    *returnSize = size;
    return ans;
}

/* https://leetcode.cn/problems/subsets/ */
/* 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

示例 1：

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
示例 2：

输入：nums = [0]
输出：[[],[0]]


提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int **ans = (int **)malloc(sizeof(int *) * (1 << numsSize));
    *returnColumnSizes = (int *)malloc(sizeof(int) * (1 << numsSize));
    *returnSize = (1 << numsSize);

    int t[numsSize];
    int tsize;
    int mask, i;

    for (mask = 0; mask < (1 << numsSize); mask++) {
        tsize = 0;
        for (i = 0; i < numsSize; i++) {
            if (mask & (1 << i)) {
                t[tsize++] = nums[i];
            }
        }
        ans[mask] = (int *)malloc(sizeof(int) * tsize);
        memcpy(ans[mask], t, sizeof(int) * tsize);
        (*returnColumnSizes)[mask] = tsize;
    }
    return ans;
}
