/**
 * @file lc_hash_table_medium.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

/* https://leetcode.cn/problems/sort-characters-by-frequency/ */
#if defined(HASH_TABLE_frequencySort)
typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} ht_t;

int val_cmp(const ht_t *a, const ht_t *b)
{
    return (b->val - a->val);
}

char *frequencySort(char *s)
{
    ht_t *ht = NULL;
    ht_t *curr, *next;
    int i;
    int len = strlen(s);
    char *ans = (char *)malloc(len + 1);
    int tmp;
    int idx = 0;

    ans[len] = '\0';

    for (i = 0; s[i] != 0; i++) {
        tmp = s[i];
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

    HASH_SORT(ht, val_cmp);
    HASH_ITER(hh, ht, curr, next)
    {
        i = 0;
        while (i < curr->val) {
            ans[idx++] = curr->key;
            i++;
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
