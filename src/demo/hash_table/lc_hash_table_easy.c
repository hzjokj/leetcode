/**
 * @file lc_hash_table_easy.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#include "utils.h"
#include "uthash.h"

/* 查找元素 元素去重 存储元素 */

/* https://leetcode.cn/problems/check-permutation-lcci/ */
#if defined(HASH_TABLE_CheckPermutation)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

bool CheckPermutation(char *s1, char *s2)
{
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int i;
    int tmp;

    for (i = 0; s1[i] != 0; i++) {
        tmp = s1[i];
        HASH_FIND_INT(ht, &tmp, curr);
        if (curr == NULL) {
            curr = (ht_t *)malloc(sizeof *curr);
            curr->key = tmp;
            curr->val = 1;
            HASH_ADD_INT(ht, key, curr);
        } else {
            curr->val++;
        }
    }

    for (i = 0; s2[i] != 0; i++) {
        tmp = s2[i];
        HASH_FIND_INT(ht, &tmp, curr);
        if (curr == NULL) {
            HASH_ITER(hh, ht, curr, next)
            {
                HASH_DEL(ht, curr);
                free(curr);
            }
            return false;
        } else {
            curr->val--;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        if (curr->val) {
            HASH_ITER(hh, ht, curr, next)
            {
                HASH_DEL(ht, curr);
                free(curr);
            }
            return false;
        }
    }
    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr);
    }
    return true;
}
#endif

/* https://leetcode.cn/problems/rings-and-rods/ */
#if defined(HASH_TABLE_countPoints)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

int countPoints(char *rings)
{
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int i;
    int ans = 0;
    int len = strlen(rings);
    int tmp;

    for (i = 1; i < len; i += 2) {
        tmp = rings[i];
        HASH_FIND_INT(ht, &tmp, curr);
        if (curr == NULL) {
            curr = (ht_t *)malloc(sizeof *curr);
            curr->key = rings[i];
            if (rings[i - 1] == 'R') {
                curr->val = 1;
            } else if (rings[i - 1] == 'G') {
                curr->val = 2;
            } else {
                curr->val = 4;
            }
            HASH_ADD_INT(ht, key, curr);
        } else {
            if (rings[i - 1] == 'R') {
                curr->val |= 1;
            } else if (rings[i - 1] == 'G') {
                curr->val |= 2;
            } else {
                curr->val |= 4;
            }
        }
    }
    HASH_ITER(hh, ht, curr, next)
    {
        if ((curr->val & 0x7) == 0x7) {
            ans++;
        }
    }
    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/number-of-good-pairs/ */
#if defined(HASH_TABLE_numIdenticalPairs)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

/*
    1 1 -1
    1 1 1 -3
    1 1 1 1 -6
    1 1 1 1 1 -10
    (n*(n+1))/2
*/
int numIdenticalPairs(int *nums, int numsSize)
{
    int i;
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int ans = 0;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], curr);
        if (curr == NULL) {
            curr = (ht_t *)malloc(sizeof *curr);
            curr->key = nums[i];
            curr->val = 0;
            HASH_ADD_INT(ht, key, curr);
        } else {
            curr->val++;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        if (curr->val) {
            ans += (curr->val * (curr->val + 1) / 2);
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/count-largest-group/ */
#if defined(HASH_TABLE_countLargestGroup)
typedef struct {
    int key;
    int cnt;
    UT_hash_handle hh;
} ht_t;

int countLargestGroup(int n)
{
    int i;
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int x, y;
    int sum = 0;
    int tmp = 1;
    int ans = 0;

    for (i = 1; i <= n; i++) {
        x = i;
        while (x) {
            y = x % 10;
            x /= 10;
            sum += y;
        }
        HASH_FIND_INT(ht, &sum, curr);
        if (curr == NULL) {
            curr = (ht_t *)malloc(sizeof *curr);
            curr->key = sum;
            curr->cnt = 1;
            HASH_ADD_INT(ht, key, curr);
        } else {
            curr->cnt++;
            tmp = (curr->cnt > tmp) ? curr->cnt : tmp;
        }
        sum = 0;
    }

    HASH_ITER(hh, ht, curr, next)
    {
        if (curr->cnt == tmp) {
            ans++;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/destination-city/ */
#if defined(HASH_TABLE_destCity)
typedef struct {
    char *str;
    int idx;
    int cnt;
    UT_hash_handle hh;
} ht_t;

char *destCity(char ***paths, int pathsSize, int *pathsColSize)
{
    int i, j;
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int tmp;
    char *ans;

    for (i = 0; i < pathsSize; i++) {
        for (j = 0; j < *pathsColSize; j++) {
            HASH_FIND_STR(ht, paths[i][j], curr);
            if (curr == NULL) {
                curr = (ht_t *)malloc(sizeof *curr);
                tmp = strlen(paths[i][j]) + 1;
                curr->str = (char *)malloc(tmp);
                strcpy(curr->str, paths[i][j]);
                if (j) {
                    curr->idx = 1;
                } else {
                    curr->idx = 0;
                }
                curr->cnt = 1;
                HASH_ADD_STR(ht, str, curr);
            } else {
                curr->cnt++;
            }
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        if (curr->cnt == 1 && curr->idx == 1) {
            tmp = strlen(curr->str) + 1;
            ans = (char *)malloc(tmp);
            strcpy(ans, curr->str);
            break;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr->str);
        free(curr);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/find-the-difference-of-two-arrays/ */
#if defined(HASH_TABLE_findDifference)
typedef struct {
    int key;
    UT_hash_handle hh;
} ht_t;

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **findDifference(int *nums1, int nums1Size, int *nums2, int nums2Size,
                     int *returnSize, int **returnColumnSizes)
{
    ht_t *ht1 = NULL, *ht2 = NULL;
    ht_t *curr1, *next1, *curr2, *next2;
    int i;
    int idx1 = 0, idx2 = 0;
    int **ans = (int **)malloc(sizeof(int *) * 2);

    *returnSize = 2;
    ans[0] = (int *)malloc(sizeof(int) * nums1Size);
    ans[1] = (int *)malloc(sizeof(int) * nums2Size);

    *returnColumnSizes = (int *)malloc(sizeof(int) * 2);

    for (i = 0; i < nums1Size; i++) {
        HASH_FIND_INT(ht1, &nums1[i], curr1);
        if (curr1 == NULL) {
            curr1 = (ht_t *)malloc(sizeof *curr1);
            curr1->key = nums1[i];
            HASH_ADD_INT(ht1, key, curr1);
        }
    }

    for (i = 0; i < nums2Size; i++) {
        HASH_FIND_INT(ht2, &nums2[i], curr2);
        if (curr2 == NULL) {
            curr2 = (ht_t *)malloc(sizeof *curr2);
            curr2->key = nums2[i];
            HASH_ADD_INT(ht2, key, curr2);
        }
    }

    HASH_ITER(hh, ht1, curr1, next1)
    {
        HASH_FIND_INT(ht2, &curr1->key, curr2);
        if (curr2 == NULL) {
            ans[0][idx1++] = curr1->key;
        }
    }
    (*returnColumnSizes)[0] = idx1;

    HASH_ITER(hh, ht2, curr2, next2)
    {
        HASH_FIND_INT(ht1, &curr2->key, curr1);
        if (curr1 == NULL) {
            ans[1][idx2++] = curr2->key;
        }
    }
    (*returnColumnSizes)[1] = idx2;

    HASH_ITER(hh, ht1, curr1, next1)
    {
        HASH_DEL(ht1, curr1);
        free(curr1);
    }

    HASH_ITER(hh, ht2, curr2, next2)
    {
        HASH_DEL(ht2, curr2);
        free(curr2);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/divide-array-into-equal-pairs/ */
#if defined(HASH_TABLE_divideArray)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

bool divideArray(int *nums, int numsSize)
{
    int k = numsSize / 2;
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int i;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], curr);
        if (curr == NULL) {
            curr = (ht_t *)malloc(sizeof *curr);
            curr->key = nums[i];
            curr->val = 1;
            HASH_ADD_INT(ht, key, curr);
        } else {
            curr->val++;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        if ((curr->val & 1) == 1) {
            return false;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr);
    }
    return true;
}
#endif

/* https://leetcode.cn/problems/increasing-decreasing-string/ */
#if defined(HASH_TABLE_findLucky)
typedef struct {
    int key;
    int cnt;
    UT_hash_handle hh;
} ht_t;

int findLucky(int *arr, int arrSize)
{
    ht_t *ht = NULL;
    ht_t *it, *t;
    int ans = -1;
    int i;

    for (i = 0; i < arrSize; i++) {
        HASH_FIND_INT(ht, &arr[i], t);
        if (t == NULL) {
            t = (ht_t *)malloc(sizeof *t);
            t->key = arr[i];
            t->cnt = 1;
            HASH_ADD_INT(ht, key, t);
        } else {
            t->cnt++;
        }
    }
    HASH_ITER(hh, ht, it, t)
    {
        if (it->key == it->cnt) {
            ans = it->key > ans ? it->key : ans;
        }
    }
    HASH_ITER(hh, ht, it, t)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    return ans;
}
#endif

char *sortString(char *s)
{
    char t[26] = {0};
    int len = strlen(s);
    char *ans = (char *)malloc(sizeof(char) * (len + 1));
    int pos = 0;
    int i;

    ans[len] = '\0';
    for (i = 0; s[i] != 0; i++) {
        t[s[i] - 'a']++;
    }
    while (pos < len) {
        for (i = 0; i < 26; i++) {
            if (t[i]) {
                ans[pos++] = i + 'a';
                t[i]--;
            }
        }
        for (i = 25; i >= 0; i--) {
            if (t[i]) {
                ans[pos++] = i + 'a';
                t[i]--;
            }
        }
    }
    return ans;
}

/* https://leetcode.cn/problems/rank-transform-of-an-array/ */
#if defined(HASH_TABLE_arrayRankTransform)
typedef struct {
    int key;
    int idx;
    UT_hash_handle hh;
} ht_t;

int key_cmp(const ht_t *a, const ht_t *b)
{
    return (a->key - b->key);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *arrayRankTransform(int *arr, int arrSize, int *returnSize)
{
    if (arrSize == 0 || arrSize == NULL) {
        *returnSize = 0;
        return NULL;
    }
    ht_t *ht = NULL;
    ht_t *it, *t;
    int *ans = (int *)malloc(sizeof(int) * arrSize);
    *returnSize = arrSize;
    int i;

    for (i = 0; i < arrSize; i++) {
        t = NULL;
        t = (ht_t *)malloc(sizeof *t);
        t->key = arr[i];
        t->idx = i;
        HASH_ADD_INT(ht, key, t);
    }

    HASH_SORT(ht, key_cmp);

    i = 1;
    HASH_ITER(hh, ht, it, t)
    {
        ans[it->idx] = i;
        if (it && t) {
            if (it->key != t->key) {
                i++;
            }
        }
    }

    HASH_ITER(hh, ht, it, t)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/find-winner-on-a-tic-tac-toe-game/ */
char *tictactoe(int **moves, int movesSize, int *movesColSize)
{
    // 将 moves 填入虚拟棋盘， a 为 -1 ， b 为 1
    int s[3][3] = {0};
    for (int i = 0; i < movesSize; i++) {
        int x = moves[i][0], y = moves[i][1];
        if (i & 1)
            s[x][y]++;
        else
            s[x][y]--;
    }
    // 对角线判断
    int sumD1 = s[0][0] + s[1][1] + s[2][2];
    int sumD2 = s[0][2] + s[1][1] + s[2][0];
    if (sumD1 == 3 || sumD2 == 3)
        return (char *)"B";
    if (sumD1 == -3 || sumD2 == -3)
        return (char *)"A";
    // 横向、纵向判断
    for (int i = 0; i < 3; i++) {
        int sumR = s[i][0] + s[i][1] + s[i][2];
        int sumC = s[0][i] + s[1][i] + s[2][i];
        if (sumR == 3 || sumC == 3)
            return (char *)"B";
        if (sumR == -3 || sumC == -3)
            return (char *)"A";
    }
    // 无胜者情况
    return (movesSize < 9) ? (char *)"Pending" : (char *)"Draw";
}

/* https://leetcode.cn/problems/unique-number-of-occurrences/ */
#if defined(HASH_TABLE_uniqueOccurrences)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

bool uniqueOccurrences(int *arr, int arrSize)
{
    ht_t *ht = NULL, *ht1 = NULL;
    ht_t *it, *t, *t1, *it1;
    int i;

    for (i = 0; i < arrSize; i++) {
        HASH_FIND_INT(ht, &arr[i], t);
        if (t == NULL) {
            t = (ht_t *)malloc(sizeof *t);
            t->key = arr[i];
            t->val = 1;
            HASH_ADD_INT(ht, key, t);
        } else {
            t->val++;
        }
    }

    HASH_ITER(hh, ht, it, t)
    {
        HASH_FIND_INT(ht1, &it->val, t1);
        if (t1 == NULL) {
            t1 = (ht_t *)malloc(sizeof *t1);
            t1->key = it->val;
            t1->val = 1;
            HASH_ADD_INT(ht1, key, t1);
        } else {
            HASH_ITER(hh, ht1, it1, t1)
            {
                HASH_DEL(ht1, it1);
                free(it1);
            }
            return false;
        }
    }
    HASH_ITER(hh, ht, it, t)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    return true;
}
#endif

/* https://leetcode.cn/problems/maximum-number-of-balloons/ */
int maxNumberOfBalloons(char *text)
{
    int s[26] = {0};
    int st[26] = {0};
    int ans = INT_MAX;
    int i;
    char c[] = "balloon";

    for (i = 0; c[i] != 0; i++) {
        s[c[i] - 'a']++;
    }

    for (i = 0; text[i] != 0; i++) {
        st[text[i] - 'a']++;
    }

    for (i = 0; i < 26; i++) {
        if (!s[i]) {
            continue;
        }

        if (!st[i]) {
            ans = 0;
            break;
        }
        st[i] /= s[i];
        ans = st[i] < ans ? st[i] : ans;
    }

    return ans;
}

/* https://leetcode.cn/problems/find-words-that-can-be-formed-by-characters/ */
int countCharacters(char **words, int wordsSize, char *chars)
{
    int s[26] = {0};
    int st[26] = {0};
    int ans = 0;
    int cnt = 0;
    int i, j;

    for (i = 0; chars[i] != 0; i++) {
        s[chars[i] - 'a']++;
    }

    for (i = 0; i < wordsSize; i++) {
        for (j = 0; words[i][j] != 0; j++) {
            st[words[i][j] - 'a']++;
        }

        cnt = 0;
        for (j = 0; j < 26; j++) {
            if (st[j]) {
                if (st[j] <= s[j]) {
                    cnt += st[j];
                } else {
                    cnt = 0;
                    break;
                }
            }
        }
        memset(st, 0, sizeof(int) * 26);
        ans += cnt;
    }
    return ans;
}

/* https://leetcode.cn/problems/verifying-an-alien-dictionary/ */
bool isAlienSorted(char **words, int wordsSize, char *order)
{
    int s[26];
    int len = strlen(order);
    int i, j;

    for (i = 0; i < len; i++) {
        s[order[i] - 'a'] = i;
    }

    for (i = 1; i < wordsSize; i++) {
        bool valid = false;
        int l1 = strlen(words[i - 1]);
        int l2 = strlen(words[i]);
        int lmin = l1 < l2 ? l1 : l2;

        for (j = 0; j < lmin; j++) {
            int prev = s[words[i - 1][j] - 'a'];
            int curr = s[words[i][j] - 'a'];
            if (prev < curr) {
                valid = true;
                break;
            } else if (prev > curr) {
                return false;
            }
        }
        if (!valid) {
            if (l1 > l2) {
                return false;
            }
        }
    }
    return true;
}

/* https://leetcode.cn/problems/count-the-number-of-consistent-strings/ */
int countConsistentStrings(char *allowed, char **words, int wordsSize)
{
    char sa[26] = {0};
    char sw[26] = {0};
    int i, j;
    int ans = 0;

    for (i = 0; allowed[i] != 0; i++) {
        sa[allowed[i] - 'a'] = 1;
    }

    for (i = 0; i < wordsSize; i++) {
        for (j = 0; words[i][j] != 0; j++) {
            sw[words[i][j] - 'a'] = 1;
        }

        for (j = 0; j < 26; j++) {
            if (sw[j]) {
                if (!sa[j]) {
                    break;
                }
            }
        }
        if (j == 26) {
            ans++;
        }
        memset(sw, 0, 26);
    }
    return ans;
}

/* https://leetcode.cn/problems/find-common-characters/submissions/ */
/* 找重复，找最小值 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **commonChars(char **words, int wordsSize, int *returnSize)
{
    char s[26] = {0};
    char smin[26] = {0};
    int i, j;

    for (i = 0; i < wordsSize; i++) {
        for (j = 0; words[i][j] != 0; j++) {
            s[words[i][j] - 'a']++;
        }

        for (j = 0; j < 26; j++) {
            if (i == 0 && smin[j] == 0) {
                smin[j] = s[j];
            } else {
                smin[j] = s[j] < smin[j] ? s[j] : smin[j];
            }
        }
        memset(s, 0, sizeof(char) * 26);
    }

    char **ans = (char **)malloc(sizeof(char *) * strlen(words[0]));
    *returnSize = 0;
    for (i = 0; i < 26; i++) {
        if (smin[i]) {
            for (j = 0; j < smin[i]; j++) {
                ans[(*returnSize)] = (char *)malloc(sizeof(char) * 2);
                ans[(*returnSize)][0] = i + 'a';
                ans[(*returnSize)][1] = '\0';
                (*returnSize)++;
            }
        }
    }
    return ans;
}

/* https://leetcode.cn/problems/check-if-the-sentence-is-pangram/ */
bool checkIfPangram(char *sentence)
{
    char s[26] = {0};
    int i;

    for (i = 0; sentence[i] != 0; i++) {
        s[sentence[i] - 'a']++;
    }

    for (i = 0; i < 26; i++) {
        if (!s[i]) {
            return false;
        }
    }
    return true;
}

/* https://leetcode.cn/problems/is-unique-lcci/submissions/ */
#if defined(HASH_TABLE_isUnique)
typedef struct {
    char key;
    UT_hash_handle hh;
} ht_t;

bool isUnique(char *astr)
{
    ht_t *ht = NULL;
    ht_t *t, *it;
    bool ans = true;
    for (int i = 0; astr[i] != '\0'; i++) {
        HASH_FIND(hh, ht, &astr[i], sizeof(char), t);
        if (t == NULL) {
            t = (ht_t *)malloc(sizeof(ht_t));
            t->key = astr[i];
            HASH_ADD(hh, ht, key, sizeof(char), t);
        } else {
            ans = false;
            break;
        }
    }
    HASH_ITER(hh, ht, it, t)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/unique-email-addresses/ */
/* 每个 有效电子邮件地址 都由一个 本地名 和一个 域名 组成，以 '@' 符号分隔。除小写字母之外，电子邮件地址还可以含有一个或多个 '.' 或 '+' 。

例如，在 alice@leetcode.com中， alice 是 本地名 ，而 leetcode.com 是 域名 。
如果在电子邮件地址的 本地名 部分中的某些字符之间添加句点（'.'），则发往那里的邮件将会转发到本地名中没有点的同一地址。请注意，
此规则 不适用于域名 。

例如，"alice.z@leetcode.com” 和 “alicez@leetcode.com” 会转发到同一电子邮件地址。
如果在 本地名 中添加加号（'+'），则会忽略第一个加号后面的所有内容。这允许过滤某些电子邮件。同样，此规则 不适用于域名 。

例如 m.y+name@email.com 将转发到 my@email.com。
可以同时使用这两个规则。

给你一个字符串数组 emails，我们会向每个 emails[i] 发送一封电子邮件。返回实际收到邮件的不同地址数目。

示例 1：

输入：emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
输出：2
解释：实际收到邮件的是 "testemail@leetcode.com" 和 "testemail@lee.tcode.com"。
示例 2：

输入：emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
输出：3

提示：

1 <= emails.length <= 100
1 <= emails[i].length <= 100
emails[i] 由小写英文字母、'+'、'.' 和 '@' 组成
每个 emails[i] 都包含有且仅有一个 '@' 字符
所有本地名和域名都不为空
本地名不会以 '+' 字符作为开头 */
#if defined(HASH_TABLE_numUniqueEmails)
typedef struct {
    char *word;
    UT_hash_handle hh;
} ht_t;

int numUniqueEmails(char **emails, int emailsSize)
{
    ht_t *ht = NULL;
    ht_t *t, *it;
    int i, j;

    for (i = 0; i < emailsSize; i++) {
        char local[101];
        int pos = 0;
        for (j = 0; emails[i][j] != 0; j++) {
            if (emails[i][j] == '+' || emails[i][j] == '@') {
                break;
            }
            if (emails[i][j] != '.') {
                local[pos++] = emails[i][j];
            }
        }
        sprintf(local + pos, "%s", strchr(emails[i], '@'));
        HASH_FIND_STR(ht, local, t);
        if (t == NULL) {
            t = (ht_t *)malloc(sizeof *t);
            t->word = (char *)malloc(strlen(local) + 1);
            strcpy(t->word, local);
            HASH_ADD_STR(ht, word, t);
        }
    }
    int ans = HASH_COUNT(ht);
    HASH_ITER(hh, ht, it, t)
    {
        HASH_DEL(ht, it);
        /* valgrind --tool=memcheck --leak-check=full ./out/main */
        free(it->word);
        free(it);
    }
    return ans;
}

int numUniqueEmailsTest(void)
{
    // char *s[] = {"test.email+alex@leetcode.com",
    //              "test.e.mail+bob.cathy@leetcode.com",
    //              "testemail+david@lee.tcode.com"};
    // char *s[] = {"a@leetcode.com", "b@leetcode.com", "c@leetcode.com"};
    char *s[] = {"test.email+alex@leetcode.com", "test.email@leetcode.com"};
    int size = ARRAY_SIZE(s);

    char **emails = (char **)malloc(sizeof(char *) * size);
    for (int i = 0; i < size; i++) {
        emails[i] = (char *)malloc(128);
        strcpy(emails[i], s[i]);
    }

    printf("input:\n");
    PRINT_ARRAY(s, size, "%s ");
    int ret = numUniqueEmails(emails, size);
    printf("output=%d\n", ret);
    for (int i = 0; i < size; i++) {
        free(emails[i]);
    }
    free(emails);
    return 0;
}
#endif

/* https://leetcode.cn/problems/most-common-word/description/ */
/* 给定一个段落 (paragraph) 和一个禁用单词列表 (banned)。返回出现次数最多，同时不在禁用列表中的单词。

题目保证至少有一个词不在禁用列表中，而且答案唯一。

禁用列表中的单词用小写字母表示，不含标点符号。段落中的单词不区分大小写。答案都是小写字母。

示例：

输入:
paragraph = "Bob hit a ball, the hit BALL flew far after it was hit."
banned = ["hit"]
输出: "ball"
解释:
"hit" 出现了3次，但它是一个禁用的单词。
"ball" 出现了2次 (同时没有其他单词出现2次)，所以它是段落里出现次数最多的，且不在禁用列表中的单词。
注意，所有这些单词在段落里不区分大小写，标点符号需要忽略（即使是紧挨着单词也忽略， 比如 "ball,"），
"hit"不是最终的答案，虽然它出现次数更多，但它在禁用单词列表中。


提示：

1 <= 段落长度 <= 1000
0 <= 禁用单词个数 <= 100
1 <= 禁用单词长度 <= 10
答案是唯一的, 且都是小写字母 (即使在 paragraph 里是大写的，即使是一些特定的名词，答案都是小写的。)
paragraph 只包含字母、空格和下列标点符号!?',;.
不存在没有连字符或者带有连字符的单词。
单词里只包含字母，不会出现省略号或者其他标点符号。*/
#undef HASH_TABLE_mostCommonWord
#if defined(HASH_TABLE_mostCommonWord)
typedef struct {
    char *word;
    int cnt;
    UT_hash_handle hh;
} ht_t;

int insert(ht_t **obj, char *str)
{
    ht_t *t = NULL;
    char *token = NULL;
    char s[] = " !?',;.";

    token = strtok(str, s);
    while (token != NULL) {
        token = str2lower(token);
        HASH_FIND_STR(*obj, token, t);
        if (t == NULL) {
            t = (ht_t *)malloc(sizeof *t);
            t->word = (char *)malloc(strlen(token) + 1);
            strcpy(t->word, token);
            t->cnt = 1;
            HASH_ADD_STR(*obj, word, t);
        } else {
            t->cnt++;
        }
        token = strtok(NULL, s);
    }
    return 1;
}

char *mostCommonWord(char *paragraph, char **banned, int bannedSize)
{
    ht_t *ht = NULL;
    ht_t *t = NULL;
    char *ans = NULL;
    int max = 0;

    insert(&ht, paragraph);

    for (int i = 0; i < bannedSize; i++) {
        HASH_FIND_STR(ht, banned[i], t);
        if (t) {
            t->cnt = 0;
        }
    }

    ht_t *it = NULL;
    HASH_ITER(hh, ht, it, t)
    {
        if (it->cnt > max) {
            max = it->cnt;
            ans = it->word;
        }
    }

    HASH_ITER(hh, ht, it, t)
    {
        // printf("word=%s, cnt=%d\n", it->word, it->cnt);
        HASH_DEL(ht, it);
        free(it->word);
        free(it);
    }
    return ans;
}

int mostCommonWordTest(void)
{
    char paragraph[] =
        "Bob hit a ball, the hit BALL flew far after it was hit.";
    char *banned[] = {"hit"};
    int bannedSize = ARRAY_SIZE(banned);
    printf("input:%d\n", bannedSize);
    PRINT_ARRAY(paragraph, strlen(paragraph), "%c");
    char *ret = mostCommonWord(paragraph, banned, bannedSize);
    if (ret == NULL) {
        return -1;
    }
    printf("output:%s\n", ret);
    return 0;
}
#endif

/* https://leetcode.cn/problems/uncommon-words-from-two-sentences/submissions/ */
#if defined(HASH_TABLE_uncommonFromSentences)
typedef struct {
    char *key;
    int val;
    UT_hash_handle hh;
} ht_t;

bool insert(char *s, ht_t **obj)
{
    ht_t *t = NULL;
    char *token = NULL;

    token = strtok(s, " ");
    while (token != NULL) {
        HASH_FIND_STR(*obj, token, t);
        if (t == NULL) {
            t = (ht_t *)malloc(sizeof *t);
            t->key = (char *)malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(t->key, token);
            t->val = 1;
            HASH_ADD_STR(*obj, key, t);
        } else {
            t->val++;
        }
        token = strtok(NULL, " ");
    }
    return true;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **uncommonFromSentences(char *s1, char *s2, int *returnSize)
{
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int len = 0;

    insert(s1, &ht);
    insert(s2, &ht);

    len = HASH_COUNT(ht);
    char **ans = (char **)malloc(sizeof(char *) * len);
    int idx = 0;

    HASH_ITER(hh, ht, curr, next)
    {
        if (curr->val == 1) {
            ans[idx] = (char *)malloc(sizeof(char) * (strlen(curr->key) + 1));
            strcpy(ans[idx], curr->key);
            idx++;
        }
    }

    HASH_ITER(hh, ht, curr, next)
    {
        HASH_DEL(ht, curr);
        free(curr);
    }

    *returnSize = idx;
    return ans;
}
#endif

/* https://leetcode.cn/problems/degree-of-an-array/description/ */
#if defined(HASH_TABLE_findShortestSubArray)
typedef struct {
    int key;
    int val;
    int start;
    int end;
    UT_hash_handle hh;
} ht_t;

int findShortestSubArray(int *nums, int numsSize)
{
    ht_t *ht = NULL;
    ht_t *tmp, *it;
    int i;
    int max = 1;
    int ans = INT_MAX;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = nums[i];
            tmp->start = i;
            tmp->end = i;
            tmp->val = 1;
            HASH_ADD_INT(ht, key, tmp);
        } else {
            tmp->end = i;
            tmp->val++;
            if (tmp->val >= max) {
                max = tmp->val;
            }
        }
    }
    HASH_ITER(hh, ht, it, tmp)
    {
        if (it->val == max) {
            int t = it->end - it->start + 1;
            ans = (t < ans) ? t : ans;
        }
    }
    HASH_ITER(hh, ht, it, tmp)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    return ans;
}
#endif

/* https://leetcode.cn/problems/n-repeated-element-in-size-2n-array/ */
/* 给你一个整数数组 nums ，该数组具有以下属性：

nums.length == 2 * n.
nums 包含 n + 1 个 不同的 元素
nums 中恰有一个元素重复 n 次
找出并返回重复了 n 次的那个元素。

示例 1：

输入：nums = [1,2,3,3]
输出：3
示例 2：

输入：nums = [2,1,2,5,3,2]
输出：2
示例 3：

输入：nums = [5,1,5,2,5,3,5,4]
输出：5

提示：

2 <= n <= 5000
nums.length == 2 * n
0 <= nums[i] <= 104
nums 由 n + 1 个 不同的 元素组成，且其中一个元素恰好重复 n 次 */
#undef HASH_TABLE_repeatedNTimes
#if defined(HASH_TABLE_repeatedNTimes)

typedef struct {
    int key;
    UT_hash_handle hh;
} ht_t;

int repeatedNTimes(int *nums, int numsSize)
{
    ht_t *ht = NULL;
    ht_t *tmp, *it;
    int i;
    int ans;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = nums[i];
            HASH_ADD_INT(ht, key, tmp);
        } else {
            ans = nums[i];
        }
    }
    HASH_ITER(hh, ht, it, tmp)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    return ans;
}

int repeatedNTimesTest(void)
{
    int nums[] = {5, 1, 5, 2, 5, 3, 5, 4};
    int numsSize = ARRAY_SIZE(nums);

    printf("input:\n");
    PRINT_ARRAY(nums, numsSize, "%d ");
    int ret = repeatedNTimes(nums, numsSize);
    printf("output:%d\n", ret);
    return 0;
}
#endif

/* https://leetcode.cn/problems/x-of-a-kind-in-a-deck-of-cards/ */
/* 给定一副牌，每张牌上都写着一个整数。

此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：

每组都有 X 张牌。
组内所有的牌上都写着相同的整数。
仅当你可选的 X >= 2 时返回 true。

示例 1：

输入：deck = [1,2,3,4,4,3,2,1]
输出：true
解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
示例 2：

输入：deck = [1,1,1,2,2,2,3,3]
输出：false
解释：没有满足要求的分组。

提示：

1 <= deck.length <= 104
0 <= deck[i] < 104 */
/*
    [0,0,0,1,1,1,2,2,2] 0<3> 1<3> 2<3> -- 3 3 3
    [1,1,2,2,2,2] 2 4 -- 3 3
    [1,1,1,1,2,2,2,2,2,2] 4 6 -- 5 5
    [0,0,0,0,0,0,0,1,2,3,3,3,4,5,6] 7 1 1 3 1 1 1
    [1,2,2,3,3,3] 1 2 3
*/
#undef HASH_TABLE_hasGroupsSizeX
#if defined(HASH_TABLE_hasGroupsSizeX)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

bool hasGroupsSizeX(int *deck, int deckSize)
{
    ht_t *ht = NULL;
    ht_t *it, *tmp, *it;
    int i;

    if (deckSize < 2) {
        return 0;
    }
    for (i = 0; i < deckSize; i++) {
        HASH_FIND_INT(ht, &deck[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = deck[i];
            tmp->val = 1;
            HASH_ADD_INT(ht, key, tmp);
        } else {
            tmp->val++;
        }
    }

    int max, flag;
    for (i = deckSize; i > 0; i--) {
        flag = 1;
        for (tmp = ht; tmp != NULL; tmp = tmp->hh.next) {
            if ((tmp->val) % i != 0) {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            max = i;
            break;
        }
    }

    HASH_ITER(hh, ht, it, tmp)
    {
        HASH_DEL(ht, it);
        free(it);
    }
    if (max >= 2)
        return true;
    else
        return false;
}

int hasGroupsSizeXTest(void)
{
    int deck[] = {1, 1, 2, 2, 2, 2};
    int deckSize = ARRAY_SIZE(deck);

    printf("intput:\n");
    PRINT_ARRAY(deck, deckSize, "%d ");
    printf("output:%s\n",
           (hasGroupsSizeX(deck, deckSize) == 1) ? "true" : "false");
    return 0;
}
#endif

/* https://leetcode.cn/problems/set-mismatch/ */
/* 集合 s 包含从 1 到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制了成了集合里面的另外一个数字的值，
导致集合 丢失了一个数字 并且 有一个数字重复 。

给定一个数组 nums 代表了集合 S 发生错误后的结果。

请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。

示例 1：

输入：nums = [1,2,2,4]
输出：[2,3]
示例 2：

输入：nums = [1,1]
输出：[1,2]


提示：

2 <= nums.length <= 104
1 <= nums[i] <= 104 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#undef HASH_TABLE_findErrorNums
#if defined(HASH_TABLE_findErrorNums)

typedef struct {
    int key;
    UT_hash_handle hh;
} ht_t;

int *findErrorNums(int *nums, int numsSize, int *returnSize)
{
    int i;
    int *ans = (int *)malloc(sizeof(int) * 2);
    *returnSize = 2;
    ht_t *ht = NULL;
    ht_t *tmp;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = nums[i];
            HASH_ADD_INT(ht, key, tmp);
        } else {
            ans[0] = nums[i];
        }
    }

    ht_t *tmp1;
    for (i = 1; i <= numsSize; i++) {
        HASH_FIND_INT(ht, &i, tmp1);
        if (tmp1 == NULL) {
            ans[1] = i;
            break;
        }
    }

    HASH_ITER(hh, ht, tmp, tmp1)
    {
        // printf("del tmp->key=%d\n", tmp->key);
        HASH_DEL(ht, tmp);
        free(tmp);
    }
    return ans;
}

int findErrorNumsTest(void)
{
    int nums[] = {1, 2, 2, 4};
    int numsSize = ARRAY_SIZE(nums);
    int returnSize;

    printf("input:\n");
    PRINT_ARRAY(nums, numsSize, "%d ");
    int *ret = findErrorNums(nums, numsSize, &returnSize);
    if (ret == NULL) {
        return -1;
    }
    printf("output:\n");
    PRINT_ARRAY(ret, returnSize, "%d ");
    return 0;
}
#endif

/* https://leetcode.cn/problems/longest-harmonious-subsequence/ */
/* 和谐数组是指一个数组里元素的最大值和最小值之间的差别 正好是 1 。

现在，给你一个整数数组 nums ，请你在所有可能的子序列中找到最长的和谐子序列的长度。

数组的子序列是一个由数组派生出来的序列，它可以通过删除一些元素或不删除元素、且不改变其余元素的顺序而得到。

示例 1：

输入：nums = [1,3,2,2,5,2,3,7]
输出：5
解释：最长的和谐子序列是 [3,2,2,2,3]
示例 2：

输入：nums = [1,2,3,4]
输出：2
示例 3：

输入：nums = [1,1,1,1]
输出：0


提示：

1 <= nums.length <= 2 * 104
-109 <= nums[i] <= 109 */
#undef HASH_TABLE_findLHS
#if defined(HASH_TABLE_findLHS)

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

int findLHS(int *nums, int numsSize)
{
    ht_t *ht = NULL;
    ht_t *tmp;
    int ans = 0;
    int i;

    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT(ht, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (ht_t *)malloc(sizeof *tmp);
            tmp->key = nums[i];
            tmp->val = 1;
            HASH_ADD_INT(ht, key, tmp);
        } else {
            tmp->val++;
        }
    }

    ht_t *it, *tmp1;
    HASH_ITER(hh, ht, it, tmp)
    {
        if (it) {
            int next_key = it->key + 1;
            HASH_FIND_INT(ht, &next_key, tmp1);
            if (tmp1) {
                ans = (it->val + tmp1->val > ans) ? (it->val + tmp1->val) : ans;
            }
        }
    }

    HASH_ITER(hh, ht, it, tmp)
    {
        printf("it->key=%d\n", it->key);
        HASH_DEL(ht, it); /* delete it */
        free(it); /* free it */
    }

    return ans;
}

void findLHSTest(void)
{
    int nums[] = {1, 3, 2, 2, 5, 2, 3, 7};
    int numsSize = ARRAY_SIZE(nums);

    printf("input:\n");
    PRINT_ARRAY(nums, numsSize, "%d ");
    int ret = findLHS(nums, numsSize);
    printf("output:%d\n", ret);
}
#endif

/* Alice 有 n 枚糖，其中第 i 枚糖的类型为 candyType[i] 。Alice 注意到她的体重正在增长，所以前去拜访了一位医生。

医生建议 Alice 要少摄入糖分，只吃掉她所有糖的 n / 2 即可（n 是一个偶数）。Alice 非常喜欢这些糖，她想要在遵循医生建议的情况下，
尽可能吃到最多不同种类的糖。

给你一个长度为 n 的整数数组 candyType ，返回： Alice 在仅吃掉 n / 2 枚糖的情况下，可以吃到糖的 最多 种类数。

示例 1：

输入：candyType = [1,1,2,2,3,3]
输出：3
解释：Alice 只能吃 6 / 2 = 3 枚糖，由于只有 3 种糖，她可以每种吃一枚。
示例 2：

输入：candyType = [1,1,2,3]
输出：2
解释：Alice 只能吃 4 / 2 = 2 枚糖，不管她选择吃的种类是 [1,2]、[1,3] 还是 [2,3]，她只能吃到两种不同类的糖。
示例 3：

输入：candyType = [6,6,6,6]
输出：1
解释：Alice 只能吃 4 / 2 = 2 枚糖，尽管她能吃 2 枚，但只能吃到 1 种糖。


提示：

n == candyType.length
2 <= n <= 104
n 是一个偶数
-105 <= candyType[i] <= 105 */

/* https://leetcode.cn/problems/distribute-candies/ */
#undef HASH_TABLE_distributeCandies
#if defined(HASH_TABLE_distributeCandies)
typedef struct {
    int key;
    UT_hash_handle hh;
} ht_t;

ht_t *ht = NULL;

void insert(int key)
{
    ht_t *it;
    HASH_FIND_INT(ht, &key, it);
    if (it == NULL) {
        it = (ht_t *)malloc(sizeof *it);
        it->key = key;
        HASH_ADD_INT(ht, key, it);
    }
}

void deelte_all(void)
{
    ht_t *it;
    ht_t *tmp;

    HASH_ITER(hh, ht, it, tmp)
    {
        printf("it->key=%d\n", it->key);
        HASH_DEL(ht, it); /* delete it */
        free(it); /* free it */
    }
}

int distributeCandies(int *candyType, int candyTypeSize)
{
    ht = NULL;
    int ans;
    for (int i = 0; i < candyTypeSize; i++) {
        insert(candyType[i]);
    }
    if (candyTypeSize / 2 >= HASH_COUNT(ht)) {
        ans = HASH_COUNT(ht);
    } else {
        ans = candyTypeSize / 2;
    }
    return ans;
}

void distributeCandiesTest(void)
{
    int candyType[] = {6, 6, 6, 6};
    int candyTypeSize = ARRAY_SIZE(candyType);

    printf("input:\n");
    PRINT_ARRAY(candyType, candyTypeSize, "%d ");
    int ret = distributeCandies(candyType, candyTypeSize);
    printf("output:%d\n", ret);
    deelte_all();
}
#endif

/* https://leetcode.cn/problems/longest-palindrome/ */
/* 给定一个包含大写字母和小写字母的字符串 s ，返回 通过这些字母构造成的 最长的回文串 。

在构造过程中，请注意 区分大小写 。比如 "Aa" 不能当做一个回文字符串。

示例 1:

输入:s = "abccccdd"
输出:7
解释:
我们可以构造的最长的回文串是"dccaccd", 它的长度是 7。
示例 2:

输入:s = "a"
输出:1
示例 3：

输入:s = "aaaaaccc"
输出:7


提示:

1 <= s.length <= 2000
s 只由小写 和/或 大写英文字母组成 */
#if defined(HASH_TABLE_xlongestPalindrome)
int xlongestPalindrome(char *s)
{
    int t1[26] = {0}; // lower
    int t2[26] = {0}; // upper
    int ans = 0;
    int i;

    for (i = 0; s[i] != 0; i++) {
        if (islower(s[i])) {
            t1[s[i] - 'a']++;
        } else {
            t2[s[i] - 'A']++;
        }
    }

    int flag = 0;
    for (i = 0; i < 26; i++) {
        if (t1[i] % 2 == 0) {
            ans += t1[i];
        } else {
            flag = 1;
            ans += (t1[i] - 1);
        }

        if (t2[i] % 2 == 0) {
            ans += t2[i];
        } else {
            flag = 1;
            ans += (t2[i] - 1);
        }
    }
    return ans + flag;
}

void xlongestPalindromeTest(void)
{
    char s[] = "abccccdd";

    printf("input:%s\n", s);
    int ret = xlongestPalindrome(s);
    printf("output:%d\n", ret);
}
#endif
/* https://leetcode.cn/problems/happy-number/ */
/* 编写一个算法来判断一个数 n 是不是快乐数。

「快乐数」 定义为：

对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
如果这个过程 结果为 1，那么这个数就是快乐数。
如果 n 是 快乐数 就返回 true ；不是，则返回 false 。

示例 1：

输入：n = 19
输出：true
解释：
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
示例 2：

输入：n = 2
输出：false
提示：

1 <= n <= 231 - 1 */
#if defined HASH_TABLE_isHappy
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

ht_t *ht = NULL;

ht_t *find(int key)
{
    ht_t *tmp;
    HASH_FIND_INT(ht, &key, tmp);
    return tmp;
}

ht_t *insert(int key)
{
    ht_t *it;
    HASH_FIND_INT(ht, &key, it);
    if (it == NULL) {
        it = (ht_t *)malloc(sizeof *it);
        it->key = key;
        it->val = 0;
        HASH_ADD_INT(ht, key, it);
    } else {
        it->val = 1;
    }
    return it;
}

void deelte_all(void)
{
    ht_t *it;
    ht_t *tmp;

    HASH_ITER(hh, ht, it, tmp)
    {
        printf("it->key=%d\n", it->key);
        HASH_DEL(ht, it); /* delete it */
        free(it); /* free it */
    }
}

void print_users(void)
{
    ht_t *it;

    for (it = ht; it != NULL; it = (ht_t *)(it->hh.next)) {
        printf("key:%d\n", it->key);
    }
}

bool isHappy(int n)
{
    int sum = 0;
    int m = 0;
    ht = NULL;
    insert(n);
    while (1) {
        while (n != 0) {
            m = n % 10;
            n /= 10;
            sum += pow(m, 2);
        }
        printf("sum=%d\n", sum);
        if (sum == 1) {
            return true;
        }
        n = sum;
        sum = 0;
        ht_t *it = insert(n);
        printf("it->val=%d\n", it->val);
        if (it->val) {
            return false;
        }
    }
    return 0;
}

void isHappyTest(void)
{
    int n = 13;
    printf("input:%d\n", n);
    printf("output:%s\n", (isHappy(n) == 1) ? "true" : "false");
    deelte_all();
}
#endif

/* https://leetcode.cn/problems/design-hashset/solutions/652778/she-ji-ha-xi-ji-he-by-leetcode-solution-xp4t/ */
struct List {
    int val;
    struct List *next;
};

void listPush(struct List *head, int x)
{
    struct List *tmp = (struct List*)malloc(sizeof(struct List));
    tmp->val = x;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct List *head, int x)
{
    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            struct List *tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

bool listContains(struct List *head, int x)
{
    for (struct List *it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            return true;
        }
    }
    return false;
}

void listFree(struct List *head)
{
    while (head->next) {
        struct List *tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

const int base = 769;

int hash(int key)
{
    return key % base;
}

typedef struct {
    struct List *data;
} MyHashSet;

MyHashSet *myHashSetCreate()
{
    MyHashSet *ret = (MyHashSet *)malloc(sizeof(MyHashSet));
    ret->data = (struct List *)malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++) {
        ret->data[i].val = 0;
        ret->data[i].next = NULL;
    }
    return ret;
}

void myHashSetAdd(MyHashSet *obj, int key)
{
    int h = hash(key);
    if (!listContains(&(obj->data[h]), key)) {
        listPush(&(obj->data[h]), key);
    }
}

void myHashSetRemove(MyHashSet *obj, int key)
{
    int h = hash(key);
    listDelete(&(obj->data[h]), key);
}

bool myHashSetContains(MyHashSet *obj, int key)
{
    int h = hash(key);
    return listContains(&(obj->data[h]), key);
}

void myHashSetFree(MyHashSet *obj)
{
    for (int i = 0; i < base; i++) {
        listFree(&(obj->data[i]));
    }
    free(obj->data);
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);

 * myHashSetRemove(obj, key);

 * bool param_3 = myHashSetContains(obj, key);

 * myHashSetFree(obj);
*/
int myHashTest(void)
{
    return 0;
}

int lc_hash_table_easy_test(void)
{
    int ret = -1;
    // isHappyTest();
    // xlongestPalindromeTest();
    // distributeCandiesTest();
    // findLHSTest();
    // ret = findErrorNumsTest();
    // ret = myHashTest();
    // ret = hasGroupsSizeXTest();
    // ret = repeatedNTimesTest();
    // ret = mostCommonWordTest();
    // ret = numUniqueEmailsTest();
    return ret;
}
