/**
 * @file lc_array_diffcult.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>

#include "utils.h"

/* https://leetcode.cn/problems/median-of-two-sorted-arrays/ */
/* 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

算法的时间复杂度应该为 O(log (m+n)) 。



示例 1：

输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：

输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

提示：

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106 */
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size)
{
    int size = nums1Size + nums2Size;
    int arr[size];

    for (int i = 0; i < size; i++) {
        if (i < nums1Size) {
            arr[i] = nums1[i];
        } else {
            arr[i] = nums2[i - nums1Size];
        }
    }

    bubble_sort(arr, size);

    if (size % 2 != 0) {
        return (double)arr[(size - 1) / 2];
    }
    return (double)(arr[size / 2] + arr[size / 2 - 1]) / 2;
}

void findMedianSortedArraysTest(void)
{
    int nums1[2] = {1, 3};
    int nums2[1] = {2};
    int nums1Size = sizeof(nums1) / sizeof(int);
    int nums2Size = sizeof(nums2) / sizeof(int);

    double ans = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);

    printf("output: %fd\n", ans);
}

void lc_array_diffcult_test(void)
{
    // findMedianSortedArraysTest();
}
