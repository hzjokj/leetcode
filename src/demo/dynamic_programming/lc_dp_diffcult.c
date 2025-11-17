/**
 * @file lc_dp_diffcult.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "stdio.h"

#include "utils.h"

/* https://leetcode.cn/problems/edit-distance/ */
/* 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符


示例 1：

输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
示例 2：

输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')


提示：

0 <= word1.length, word2.length <= 500
word1 和 word2 由小写英文字母组成 */
int minDistance(char *word1, char *word2)
{
    return 0;
}

int minDistanceTest(void)
{
    char word1[] = "horse";
    char word2[] = "ros";

    printf("input word1:%s and word2:%s\n", word1, word2);
    int ret = minDistance(word1, word2);
    printf("output:%d\n", ret);
    return 0;
}

int lc_dp_diffcult_test(void)
{
    int ret = -1;
    // ret = minDistanceTest();
    return ret;
}
