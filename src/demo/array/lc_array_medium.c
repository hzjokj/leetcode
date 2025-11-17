/**
 * @file lc_array_medium.c
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
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils.h"

/* https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/ */
/* 给你一个下标从 1 开始的整数数组 numbers ，该数组已按 非递减顺序排列  ，请你从数组中找出满足相加之和等于目标数 target 的两个数。如果设这两个数分别是 numbers[index1] 和 numbers[index2] ，则 1 <= index1 < index2 <= numbers.length 。

以长度为 2 的整数数组 [index1, index2] 的形式返回这两个整数的下标 index1 和 index2。

你可以假设每个输入 只对应唯一的答案 ，而且你 不可以 重复使用相同的元素。

你所设计的解决方案必须只使用常量级的额外空间。


示例 1：

输入：numbers = [2,7,11,15], target = 9
输出：[1,2]
解释：2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。
示例 2：

输入：numbers = [2,3,4], target = 6
输出：[1,3]
解释：2 与 4 之和等于目标数 6 。因此 index1 = 1, index2 = 3 。返回 [1, 3] 。
示例 3：

输入：numbers = [-1,0], target = -1
输出：[1,2]
解释：-1 与 0 之和等于目标数 -1 。因此 index1 = 1, index2 = 2 。返回 [1, 2] 。


提示：

2 <= numbers.length <= 3 * 104
-1000 <= numbers[i] <= 1000
numbers 按 非递减顺序 排列
-1000 <= target <= 1000
仅存在一个有效答案 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum2(int *numbers, int numbersSize, int target, int *returnSize)
{
    if (numbers == NULL || returnSize == NULL) {
        return NULL;
    }
    int *ans = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;

    int left = 0, right = numbersSize - 1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            ans[0] = left + 1;
            ans[1] = right + 1;
            return ans;
        } else if (sum > target) {
            right--;
        } else {
            left++;
        }
    }
    return NULL;
}

void twoSum2Test(void)
{
}

/* https://leetcode.cn/problems/3sum/ */
/* 给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请

你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
示例 2：

输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
示例 3：

输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。


提示：

3 <= nums.length <= 3000
-105 <= nums[i] <= 105 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize,
               int **returnColumnSizes)
{
    bubble_sort(nums, numsSize);

    *returnSize = 0;
    short left = 0;
    short right = numsSize - 1;

    int **ret = (int **)malloc(sizeof(int *) * (numsSize + 1) * 6);
    *returnColumnSizes = (int *)malloc(sizeof(int) * (numsSize + 1) * 6);
    ret[*returnSize] = (int *)malloc(sizeof(int) * 3);

    while (left + 1 < right) {
        int i = left + 1;
        int j = right;
        while (i < j) {
            if (nums[i] + nums[j] + nums[left] < 0) {
                i++;
            } else if (nums[i] + nums[j] + nums[left] > 0) {
                j--;
            } else {
                ret[*returnSize][0] = nums[left];
                ret[*returnSize][1] = nums[i];
                ret[*returnSize][2] = nums[j];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;
                ret[*returnSize] = (int *)malloc(sizeof(int) * 3);

                do {
                    if (nums[i] == nums[i + 1]) {
                        i++;
                    }
                } while (i < j);

                do {
                    if (nums[j] == nums[j - 1]) {
                        j--;
                    }
                } while (i < j);
            }
        }

        do {
            if (nums[left] == nums[left + 1]) {
                left++;
            }
        } while (left + 1 < right);
    }

    return ret;
}

void threeSumTest(void)
{
}

/* https://leetcode.cn/problems/zero-matrix-lcci/ */
/* 编写一种算法，若M × N矩阵中某个元素为0，则将其所在的行与列清零。

示例 1：

输入：
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
输出：
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]
示例 2：

输入：
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
输出：
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
] */
void setZeroes(int **matrix, int matrixSize, int *matrixColSize)
{
    int M = matrixSize;
    int N = *matrixColSize;
    int *rowRecord = (int *)malloc(sizeof(int *) * M);
    if (rowRecord == NULL) {
        return;
    }
    int *colRecord = (int *)malloc(sizeof(int *) * N);
    if (colRecord == NULL) {
        return;
    }

    memset(rowRecord, 0, sizeof(int *) * M);
    memset(colRecord, 0, sizeof(int *) * N);

    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (matrix[i][j] == 0) {
                rowRecord[i] = 1;
                colRecord[j] = 1;
            }
        }
    }

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (rowRecord[i] == 1 || colRecord[j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }

    free(rowRecord);
    free(colRecord);
}

void setZeroesTest(void)
{
}

/* https://leetcode.cn/problems/rotate-matrix-lcci/submissions/ */
/* 给你一幅由 N × N 矩阵表示的图像，其中每个像素的大小为 4 字节。请你设计一种算法，将图像旋转 90 度。

不占用额外内存空间能否做到？
示例 1:

给定 matrix =
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

原地旋转输入矩阵，使其变为:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
示例 2:

给定 matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
],

原地旋转输入矩阵，使其变为:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
注意：本题与主站 48 题相同：https://leetcode-cn.com/problems/rotate-image/ */
void rotate(int **matrix, int matrixSize, int *matrixColSize)
{
    // 水平翻转
    for (int i = 0; i < matrixSize / 2; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            swap(&matrix[i][j], &matrix[matrixSize - i - 1][j], sizeof(int));
        }
    }
    // 主对角线翻转
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < i; ++j) {
            swap(&matrix[i][j], &matrix[j][i], sizeof(int));
        }
    }
}

void rotateTest(void)
{
}

/* https://leetcode.cn/problems/rotate-image/ */
void rotate_image(int **matrix, int matrixSize, int *matrixColSize)
{
    int i, j, temp;

    // 上下换
    for (i = 0; i < matrixSize / 2; i++) {
        for (j = 0; j < matrixSize; j++) {
            temp = matrix[matrixSize - i - 1][j];
            matrix[matrixSize - i - 1][j] = matrix[i][j];
            matrix[i][j] = temp;
        }
    }

    // 对角线换
    for (i = 0; i < matrixSize; i++) {
        for (j = i + 1; j < matrixSize; j++) {
            temp = matrix[j][i];
            matrix[j][i] = matrix[i][j];
            matrix[i][j] = temp;
        }
    }
}

void rotateImageTest(void)
{
}

/* https://leetcode.cn/problems/minimum-size-subarray-sum/ */
/* 给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其总和大于等于 target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。



示例 1：

输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：

输入：target = 4, nums = [1,4,4]
输出：1
示例 3：

输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0


提示：

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 105


进阶：

如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。*/
int minSubArrayLen(int target, int *nums, int numsSize)
{
    if (nums == NULL) {
        return 0;
    }
    // 尺缩法
    int slow = 0, fast = 1, gap = 0, is_first_time = true;
    int sum = nums[slow];

    if (sum >= target) {
        return 1;
    }

    for (fast = 1; fast < numsSize; fast++) {
        sum += nums[fast];
        if (sum >= target) { // 2+3+1+2+4+3
            //printf("1_sum=%d\n", sum);
            for (; slow < fast + 1; slow++) {
                sum -= nums[slow];
                if (sum < target) {
                    sum += nums[slow];
                    if (is_first_time) {
                        gap = fast - slow + 1;
                        is_first_time = false;
                    }
                    if (fast - slow + 1 < gap) {
                        gap = fast - slow + 1;
                    }
                    //printf("2_sum=%d, gap=%d\n", sum, gap);
                    if (gap == 1) {
                        return 1;
                    }
                    break;
                }
            }
        }
    }

    return gap;
}

void minSubArrayLenTest(void)
{
}

/* https://leetcode.cn/problems/merge-intervals/ */
/* 以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。



示例 1：

输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：

输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。


提示：

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int **merge_intervals(int **intervals, int intervalsSize, int *intervalsColSize,
                      int *returnSize, int **returnColumnSizes)
{
    if (intervalsSize == 1) {
        *returnSize = 1;
        return intervals;
    }
    qsort(intervals, intervalsSize, sizeof(int *), cmp);
    int **result = (int **)malloc(sizeof(int *) * intervalsSize);
    for (int i = 0; i < intervalsSize; i++) {
        result[i] = (int *)malloc(sizeof(int) * 2);
    }
    *returnSize = 0;
    int temp[2] = {intervals[0][0], intervals[0][1]};
    for (int i = 1; i < intervalsSize; i++) {
        if (intervals[i][0] <= temp[1]) { //如果遍历到的为重叠的区间，进行合并
            temp[1] = fmax(temp[1], intervals[i][1]);
        } else { //不重叠
            result[*returnSize][0] = temp[0];
            result[*returnSize][1] = temp[1];
            temp[0] = intervals[i][0];
            temp[1] = intervals[i][1];
            (*returnSize) += 1;
        }
    }
    result[*returnSize][0] = temp[0];
    result[*returnSize][1] = temp[1];
    *returnSize += 1;
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return result;
}

void merge2Test(void)
{
}

/* https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/ */
/* 给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。



示例 1：

输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     随后，在第 4 天（股票价格 = 3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3 = 3 。
     总利润为 4 + 3 = 7 。
示例 2：

输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。
     总利润为 4 。
示例 3：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。


提示：

1 <= prices.length <= 3 * 104
0 <= prices[i] <= 104 */
int maxProfit2(int *prices, int pricesSize)
{
    if (prices == NULL || pricesSize < 2) {
        return 0;
    }

    int index = 0, tatol = 0;
    while (index < pricesSize) {
        while (index < pricesSize - 1 && prices[index] >= prices[index + 1]) {
            index++;
        }

        int min = prices[index];
        while (index < pricesSize - 1 && prices[index] <= prices[index + 1]) {
            index++;
        }

        tatol += prices[index++] - min;
    }
    return tatol;
}

void maxProfit2Test(void)
{
}

/* https://leetcode.cn/problems/valid-sudoku/ */
bool isValidSudoku(char **board, int boardSize, int *boardColSize)
{
    int cnt[9];
    int i, j;

    memset(cnt, 0, sizeof(int) * 9);

    // 行检查
    for (i = 0; i < 9; i++) {
        memset(cnt, 0, sizeof(int) * 9);
        for (j = 0; j < 9; j++) {
            if (board[i][j] >= '1' && board[i][j] <= '9') {
                int value = board[i][j] - '0' - 1;
                if (cnt[value]) {
                    return false;
                }
                cnt[value]++;
            }
        }
    }

    // 列检查
    for (i = 0; i < 9; i++) {
        memset(cnt, 0, sizeof(int) * 9);
        for (j = 0; j < 9; j++) {
            if (board[j][i] >= '1' && board[j][i] <= '9') {
                int value = board[j][i] - '0' - 1;
                if (cnt[value]) {
                    return false;
                }
                cnt[value]++;
            }
        }
    }

    // 宫检查
    int k;
    for (k = 0; k < 9; k++) {
        memset(cnt, 0, sizeof(int) * 9);
        i = (k % 3) * 3;
        j = (k / 3) * 3;
        int tempi, tempj;
        for (tempi = 0; tempi < 3; tempi++) {
            for (tempj = 0; tempj < 3; tempj++) {
                if (board[i + tempi][j + tempj] >= '1' &&
                    board[i + tempi][j + tempj] <= '9') {
                    int value = board[i + tempi][j + tempj] - '0' - 1;
                    if (cnt[value]) {
                        return false;
                    }
                    cnt[value]++;
                }
            }
        }
    }
    return true;
}

void isValidSudokuTest(void)
{
}

/* https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/ */
/* 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。



示例 1：

输入：nums = [3,4,5,1,2]
输出：1
解释：原数组为 [1,2,3,4,5] ，旋转 3 次得到输入数组。
示例 2：

输入：nums = [4,5,6,7,0,1,2]
输出：0
解释：原数组为 [0,1,2,4,5,6,7] ，旋转 4 次得到输入数组。
示例 3：

输入：nums = [11,13,15,17]
输出：11
解释：原数组为 [11,13,15,17] ，旋转 4 次得到输入数组。


提示：

n == nums.length
1 <= n <= 5000
-5000 <= nums[i] <= 5000
nums 中的所有整数 互不相同
nums 原来是一个升序排序的数组，并进行了 1 至 n 次旋转 */
int findMin(int *nums, int numsSize)
{
    int min = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }
    return min;
}

void findMinTest(void)
{
}

/* https://leetcode.cn/problems/diagonal-traverse/ */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDiagonalOrder(int **mat, int matSize, int *matColSize, int *returnSize)
{
    if (mat == NULL) {
        return NULL;
    }
    int M = matSize; // 行数
    int N = *matColSize; // 列数
    int tot = M + N - 1; // 对角线个数
    int *res = (int *)malloc(sizeof(int) * M * N); // 申请一块存放结果的内存

    int i, index = 0;
    int r = 0, c = 0; // r:横坐标 c:纵坐标
    for (i = 0; i < tot; i++) {
        if (i % 2 == 0) { // 对角线正向
            while (r >= 0 && c < N) {
                res[index++] = mat[r][c];
                r -= 1;
                c += 1;
            }
            if (c < N) {
                r += 1;
            } else {
                r += 2;
                c -= 1;
            }
        } else { // 对角线反向
            while (c >= 0 && r < M) {
                res[index++] = mat[r][c];
                r += 1;
                c -= 1;
            }
            if (r < M) {
                c += 1;
            } else {
                c += 2;
                r -= 1;
            }
        }
    }
    *returnSize = index;
    return res;
}

void findDiagonalOrderTest(void)
{
}

/* https://leetcode.cn/problems/3sum-closest/ */
/* 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。

返回这三个数的和。

假定每组输入只存在恰好一个解。



示例 1：

输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
示例 2：

输入：nums = [0,0,0], target = 1
输出：0


提示：

3 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
-104 <= target <= 104 */
int threeSumClosest(int *nums, int numsSize, int target)
{
    int sum = 0;
    int i;
    int left;
    int right;
    int closest = 0;
    int tmp;
    int flag = false;

    qsort(nums, numsSize, sizeof(int), cmp);
    PRINT_ARRAY(nums, numsSize, "%d ");

    for (i = 0; i < numsSize - 2; i++) {
        for (left = i + 1, right = numsSize - 1; left != right;) {
            sum = nums[i] + nums[left] + nums[right];
            if (sum == target) {
                return sum;
            } else if (sum > target) {
                right--;
            } else {
                left++;
            }

            if (!flag) {
                flag = true;
                tmp = abs(target - sum);
                closest = sum;
            } else if (tmp > abs(target - sum)) {
                tmp = abs(target - sum);
                closest = sum;
            }
        }
    }

    return closest;
}

/*
    升序
    -4 -1 1 2
    -5 -5 -4 0 0 3 3 4 5
    2 3 8 9 10
*/
void threeSumClosestTest(void)
{
    // int nums[] = {-1,2,1,-4};
    // int nums[] = {4,0,5,-5,3,3,0,-4,-5};
    // int nums[] = {1,1,1,0};
    int nums[] = {2, 3, 8, 9, 10};
    int numsSize = sizeof(nums) / sizeof(int);
    int target = 16;

    int ans = threeSumClosest(nums, numsSize, target);

    printf("output: ans=%d\n", ans);
}

/* https://leetcode.cn/problems/container-with-most-water/ */
int maxArea(int *height, int heightSize)
{
    int l = 0, r = heightSize - 1;
    int maxA = 0;

    while (l < r) {
        int temp = min(height[l], height[r]) * (r - l);
        maxA = max(temp, maxA);
        if (height[l] <= height[r]) {
            ++l;
        } else {
            --r;
        }
    }
    return maxA;
}

void maxAreaTest(void)
{
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int heightSize = sizeof(height) / sizeof(int);

    int ans = maxArea(height, heightSize);

    printf("output: %d\n", ans);
}

/* https://leetcode.cn/problems/divide-two-integers/ */
/* 给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用 乘法、除法和取余运算。

整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345 将被截断为 8 ，-2.7335 将被截断至 -2 。

返回被除数 dividend 除以除数 divisor 得到的 商 。

注意：假设我们的环境只能存储 32 位 有符号整数，其数值范围是 [−231,  231 − 1] 。本题中，如果商 严格大于 231 − 1 ，则返回 231 − 1 ；如果商 严格小于 -231 ，则返回 -231 。



示例 1:

输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = 3.33333.. ，向零截断后得到 3 。
示例 2:

输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = -2.33333.. ，向零截断后得到 -2 。


提示：

-231 <= dividend, divisor <= 231 - 1
divisor != 0 */
int divide(int dividend, int divisor)
{
    // -2^32 / -1 = 2^32 -- 2^32-1
    if (dividend == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    int sign = ((dividend > 0) ^ (divisor > 0)) ? -1 : 1;

    // dividend = abs(dividend);
    // divisor = abs(divisor);
    if (dividend > 0) {
        dividend = -dividend;
    }
    if (divisor > 0) {
        divisor = -divisor;
    }
    // printf("%d %d\n", dividend, divisor);

    int res = 0;
    while (dividend <= divisor) {
        int value = divisor;
        int k = 1;

        while ((unsigned)value >= 0xC0000000 && dividend <= value + value) {
            value += value;
            if (k > INT_MAX / 2) {
                return INT_MIN;
            }
            k += k;
        }
        dividend -= value;
        res += k;
    }
    return sign * res;
}

void divideTest(void)
{
    int dividend = 10;
    int divisor = 3;

    int ans = divide(dividend, divisor);

    printf("output: %d\n", ans);
}

void lc_array_medium_test(void)
{
    // divideTest();
    // maxAreaTest();
    // threeSumClosestTest();
    // findDiagonalOrderTest();
    // findMinTest();
}
