/**
 * @file lc_bin_search_medium.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-30
 *
 * @copyright Copyright (c) 2023
 *
 */

/* https://leetcode.cn/problems/h-index-ii/ */
int hIndex(int *citations, int citationsSize)
{
    int l = 0, r = citationsSize - 1;
    int m;

    while (l <= r) {
        m = (l + (r - l) / 2);
        if (citations[m] >= citationsSize - m) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return citationsSize - l;
}
