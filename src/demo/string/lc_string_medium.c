/**
 * @file lc_string_medium.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"

/* https://leetcode.cn/problems/string-to-integer-atoi/ */
/* 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。

函数 myAtoi(string s) 的算法如下：

读入字符串并丢弃无用的前导空格
检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
返回整数作为最终结果。
注意：

本题中的空白字符只包括空格字符 ' ' 。
除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。


示例 1：

输入：s = "42"
输出：42
解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
第 1 步："42"（当前没有读入字符，因为没有前导空格）
         ^
第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
         ^
第 3 步："42"（读入 "42"）
           ^
解析得到整数 42 。
由于 "42" 在范围 [-231, 231 - 1] 内，最终结果为 42 。
示例 2：

输入：s = "   -42"
输出：-42
解释：
第 1 步："   -42"（读入前导空格，但忽视掉）
            ^
第 2 步："   -42"（读入 '-' 字符，所以结果应该是负数）
             ^
第 3 步："   -42"（读入 "42"）
               ^
解析得到整数 -42 。
由于 "-42" 在范围 [-231, 231 - 1] 内，最终结果为 -42 。
示例 3：

输入：s = "4193 with words"
输出：4193
解释：
第 1 步："4193 with words"（当前没有读入字符，因为没有前导空格）
         ^
第 2 步："4193 with words"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
         ^
第 3 步："4193 with words"（读入 "4193"；由于下一个字符不是一个数字，所以读入停止）
             ^
解析得到整数 4193 。
由于 "4193" 在范围 [-231, 231 - 1] 内，最终结果为 4193 。


提示：

0 <= s.length <= 200
s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成 */
int myAtoi(char *s)
{
    if (s == NULL) {
        return 0;
    }

    int i;
    int len = strlen(s);
    double ans = 0;
    int sign = 1; // 默认为正
    bool flag = true;

    for (i = 0; i < len; i++) {
        if (flag && s[i] == ' ') {
            continue;
        }
        if (flag && s[i] == '+') {
            sign = 1;
            flag = false;
            continue;
        }
        if (flag && s[i] == '-') {
            sign = -1;
            flag = false;
            continue;
        }
        if (s[i] < '0' || s[i] > '9') {
            break;
        } else {
            flag = false;
            ans = ans * 10 + s[i] - '0';
        }
    }
    ans = sign * ans;
    if (ans <= -pow(2, 31)) {
        ans = -pow(2, 31);
    } else if (ans >= pow(2, 31) - 1) {
        ans = pow(2, 31) - 1;
    }
    return (int)ans;
}

void myAtoiTest(void)
{
    char s[] = "42";

    int ans = myAtoi(s);

    printf("output: ans=%d\n", ans);
}

/* https://leetcode.cn/problems/count-and-say/ */
char *countAndSay(int n)
{
    if (n == 1) {
        return "1";
    }

    char *s = countAndSay(n - 1);
    char *ans = (char *)malloc(5000);
    int cnt = 1, idx = 0;
    while (*s != 0) {
        if (*s == *(s + 1)) {
            cnt++;
        } else {
            ans[idx++] = cnt + '0';
            ans[idx++] = *s;
            cnt = 1;
        }
        s++;
    }
    ans[idx] = 0;

    return ans;
}

void countAndSayTest(void)
{
    int n = 4;

    char *ans = countAndSay(n);

    printf("output: ans=%s\n", ans);
    free(ans);
}

/* https://leetcode.cn/problems/longest-substring-without-repeating-characters/

无重复字符的最长子串

给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。



示例 1:

输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


提示：

0 <= s.length <= 5 * 104
s 由英文字母、数字、符号和空格组成 */
int lengthOfLongestSubstring(char *s)
{
    if (!s[0]) {
        return 0;
    }
    int max = 1, n = 0;

    for (int i = 1; s[i] != 0; i++) {
        int tmp = 1;
        for (int j = n; j < i; j++) {
            if (s[j] == s[i]) {
                n = j + 1;
                break;
            } else {
                tmp++;
            }
        }
        max = tmp > max ? tmp : max;
    }

    return max;
}

void lc_string_medium_test(void)
{
}
