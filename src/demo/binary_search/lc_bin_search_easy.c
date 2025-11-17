/**
 * @file lc_bin_search_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 *
 * @copyr Copyr (c) 2023
 *
 */

#include <stdio.h>

#include "utils.h"

/* 查找特定值 求算术平方根 */

/* https://leetcode.cn/leetbook/read/binary-search/xem7js/ */
/* 峰值元素是指其值严格大于左右相邻值的元素。

给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

你必须实现时间复杂度为 O(log n) 的算法来解决此问题。

示例 1：

输入：nums = [1,2,3,1]
输出：2
解释：3 是峰值元素，你的函数应该返回其索引 2。
示例 2：

输入：nums = [1,2,1,3,5,6,4]
输出：1 或 5
解释：你的函数可以返回索引 1，其峰值元素为 2；
     或者返回索引 5， 其峰值元素为 6。

提示：

1 <= nums.length <= 1000
-231 <= nums[i] <= 231 - 1
对于所有有效的 i 都有 nums[i] != nums[i + 1] */
int findPeakElement(int *nums, int numsSize)
{
    int l = 0, r = numsSize - 1;
    int m = 0;

    while (1) {
        m = l + ((r - l) >> 1);
        if (m + 1 <= r && nums[m] < nums[m + 1]) {
            l = m + 1;
        } else if (m - 1 >= l && nums[m] < nums[m - 1]) {
            r = m;
        } else {
            break;
        }
    }
    return m;
}

int findPeakElementTest(void)
{
    int nums[] = {2, 1}; // 3 2 1 1
    int numsSize = ARRAY_SIZE(nums);

    int ret = findPeakElement(nums, numsSize);
    printf("output:%d\n", ret);
    return 0;
}

/* https://leetcode.cn/leetbook/read/binary-search/xepthr/ */
/* 你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，
所以错误的版本之后的所有版本都是错的。

假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。

你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。
你应该尽量减少对调用 API 的次数。

示例 1：

输入：n = 5, bad = 4
输出：4
解释：
调用 isBadVersion(3) -> false
调用 isBadVersion(5) -> true
调用 isBadVersion(4) -> true
所以，4 是第一个错误的版本。
示例 2：

输入：n = 1, bad = 1
输出：1

提示：

1 <= bad <= n <= 231 - 1 */
// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

bool isBadVersion(int version)
{
    int bad = 7;
    return (version >= bad) ? true : false;
}

/* 1 2 3 4 5 6 7 */
int firstBadVersion(int n)
{
    int l = 1, r = n;
    int m;

    while (l != r) {
        m = l + ((r - l) >> 1);
        if (isBadVersion(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int firstBadVersionTest(void)
{
    int n = 7;
    int ret = firstBadVersion(n);
    printf("output:%d\n", ret);
    return 0;
}

/* https://leetcode.cn/leetbook/read/binary-search/xeog5j/ */
int xsearch(int *nums, int numsSize, int target)
{
    int l = 0, r = numsSize - 1;
    int ret = -1;
    int mid;

    while (l <= r) {
        mid = l + (r - l) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[l] <= nums[mid]) {
            if (nums[l] <= target && nums[mid] > target) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (nums[r] >= target && nums[mid] < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return ret;
}

/* https://leetcode.cn/leetbook/read/binary-search/xee4ev/ */
/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */
int guess(int n)
{
    int pick = 6;
    if (pick < n) {
        return -1;
    } else if (pick > n) {
        return 1;
    } else {
        return 0;
    }
}

int guessNumber(int n)
{
    int l = 1, r = n;
    while (1) {
        if (guess(n) == 0) {
            break;
        } else if (guess(n) == -1) {
            r = n;
        } else {
            l = n;
        }
        n = l + (r - l) / 2;
    }
    return n;
}

/* https://leetcode.cn/leetbook/read/binary-search/xe9cog/ */
/* 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。

由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。

注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。

示例 1：

输入：x = 4
输出：2
示例 2：

输入：x = 8
输出：2
解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
 

提示：

0 <= x <= 231 - 1 */
/*
    x=8 mid=1+(8-1)/2=4
    8/4=2 r=4-1=3 mid=1+(3-1)/2=2
    l=2+1=3
*/
int mySqrt(int x)
{
    if (x < 2) {
        return x;
    }
    int l = 1, r = x;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (x / mid == mid) {
            return mid;
        } else if (x / mid < mid) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

int mySqrtTest(void)
{
    int x = 8;
    printf("input:%d\n", x);
    int ret = mySqrt(x);
    printf("output:%d\n", ret);
    return 0;
}

/* https://leetcode.cn/leetbook/read/binary-search/xexoac/ */
/* 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target，
写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
示例 1:

输入: nums = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 出现在 nums 中并且下标为 4
示例 2:

输入: nums = [-1,0,3,5,9,12], target = 2
输出: -1
解释: 2 不存在 nums 中因此返回 -1
 

提示：

你可以假设 nums 中的所有元素是不重复的。
n 将在 [1, 10000]之间。
nums 的每个元素都将在 [-9999, 9999]之间。*/
int search(int *nums, int numsSize, int target)
{
    int l = 0, r = numsSize - 1;
    int ret = -1;
    /*
    (r+l)/2 平均可能会溢出，原因是(r+l)/2有可能超出int类型范围
    可以采取l+(r-l)/2，也可以用l+(r-l)>>1
*/

    int mid;
    while (l <= r) {
        mid = l + (r - l) / 2;
        if (nums[mid] > target) {
            r = mid - 1;
        } else if (nums[mid] < target) {
            l = mid + 1;
        } else {
            ret = mid;
            break;
        }
    }

    return ret;
}

int searchTest(void)
{
    int nums[] = {-1, 0, 3, 5, 9, 12};
    int numsSize = ARRAY_SIZE(nums);
    int target = 9;

    printf("input:\n");
    PRINT_ARRAY(nums, numsSize, "%d ");
    int ret = search(nums, numsSize, target);
    printf("output:%d\n", ret);
    return 0;
}

int lc_bin_search_easy_test(void)
{
    int ret = -1;
    // searchTest();
    // ret = firstBadVersionTest();
    // ret = findPeakElementTest();
    return ret;
}
