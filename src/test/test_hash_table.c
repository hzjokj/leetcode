/**
 * @file test_hash_table.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi, malloc */
#include <string.h> /* strcpy */
#include "uthash.h"

struct my_struct {
    int id; /* key */
    char name[21];
    UT_hash_handle hh; /* makes this structure hashable */
};

struct my_struct *users = NULL;

void add_user(int user_id, const char *name)
{
    struct my_struct *s;

    HASH_FIND_INT(users, &user_id, s); /* id already in the hash? */
    if (s == NULL) {
        s = (struct my_struct *)malloc(sizeof *s);
        s->id = user_id;
        HASH_ADD_INT(users, id, s); /* id is the key field */
    }
    strcpy(s->name, name);
}

struct my_struct *find_user(int user_id)
{
    struct my_struct *s;

    HASH_FIND_INT(users, &user_id, s); /* s: output pointer */
    return s;
}

void delete_user(struct my_struct *user)
{
    HASH_DEL(users, user); /* user: pointer to delete */
    free(user);
}

void delete_all(void)
{
    struct my_struct *current_user;
    struct my_struct *tmp;

    HASH_ITER(hh, users, current_user, tmp)
    {
        printf("current_user->id=%d\n", current_user->id);
        HASH_DEL(users, current_user); /* delete it (users advances to next) */
        free(current_user); /* free it */
    }
}

void print_users(void)
{
    struct my_struct *s;

    for (s = users; s != NULL; s = (struct my_struct *)(s->hh.next)) {
        printf("user id %d: name %s\n", s->id, s->name);
    }
}

int by_name(const struct my_struct *a, const struct my_struct *b)
{
    return strcmp(a->name, b->name);
}

int by_id(const struct my_struct *a, const struct my_struct *b)
{
    return (a->id - b->id); // 升序
    // return (b->id - a->id); // 降序
}

const char *getl(const char *prompt)
{
    static char buf[21];
    char *p;
    printf("%s? ", prompt);
    fflush(stdout);
    p = fgets(buf, sizeof(buf), stdin);
    if (p == NULL || (p = strchr(buf, '\n')) == NULL) {
        puts("Invalid input!");
        exit(EXIT_FAILURE);
    }
    *p = '\0';
    return buf;
}

int test_hash_table(void)
{
    int id = 1;
    int running = 1;
    struct my_struct *s;
    int temp;

    while (running) {
        printf(" 1. add user\n");
        printf(" 2. add or rename user by id\n");
        printf(" 3. find user\n");
        printf(" 4. delete user\n");
        printf(" 5. delete all users\n");
        printf(" 6. sort items by name\n");
        printf(" 7. sort items by id\n");
        printf(" 8. print users\n");
        printf(" 9. count users\n");
        printf("10. quit\n");
        switch (atoi(getl("Command"))) {
        case 1:
            add_user(id++, getl("Name (20 char max)"));
            break;
        case 2:
            temp = atoi(getl("ID"));
            add_user(temp, getl("Name (20 char max)"));
            break;
        case 3:
            s = find_user(atoi(getl("ID to find")));
            printf("user: %s\n", s ? s->name : "unknown");
            break;
        case 4:
            s = find_user(atoi(getl("ID to delete")));
            if (s) {
                delete_user(s);
            } else {
                printf("id unknown\n");
            }
            break;
        case 5:
            delete_all();
            break;
        case 6:
            HASH_SORT(users, by_name);
            break;
        case 7:
            HASH_SORT(users, by_id);
            break;
        case 8:
            print_users();
            break;
        case 9:
            temp = HASH_COUNT(users);
            printf("there are %d users\n", temp);
            break;
        case 10:
            running = 0;
            break;
        }
    }

    delete_all(); /* free any structures */
    return 0;
}

// 定义键值对结构
struct key_value {
    char *key;
    int value;
    struct key_value *next;
};

// 定义哈希表结构
struct hash_table {
    struct key_value **table;
    size_t size;
};

// 创建一个新的哈希表
struct hash_table *create_hash_table(size_t size)
{
    struct hash_table *hash_table =
        (struct hash_table *)malloc(sizeof(struct hash_table));
    if (!hash_table) {
        perror("Failed to allocate memory for the hash table");
        exit(EXIT_FAILURE);
    }

    hash_table->size = size;
    hash_table->table =
        (struct key_value **)malloc(sizeof(struct key_value *) * size);
    if (!hash_table->table) {
        perror("Failed to allocate memory for the hash table array");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; i++) {
        hash_table->table[i] = NULL;
    }

    return hash_table;
}

// 哈希函数，简单地将字符串的字符相加，并取余哈希表大小
size_t xhash(const char *key, size_t size)
{
    size_t hash_value = 0;
    while (*key) {
        hash_value += *key;
        key++;
    }
    return hash_value % size;
}

// 插入键值对到哈希表
void insert(struct hash_table *hash_table, const char *key, int value)
{
    size_t index = xhash(key, hash_table->size);

    struct key_value *new_key_value =
        (struct key_value *)malloc(sizeof(struct key_value));
    if (!new_key_value) {
        perror("Failed to allocate memory for a key-value pair");
        exit(EXIT_FAILURE);
    }

    new_key_value->key = strdup(key);
    if (!new_key_value->key) {
        perror("Failed to duplicate key string");
        exit(EXIT_FAILURE);
    }

    new_key_value->value = value;
    new_key_value->next = hash_table->table[index];
    hash_table->table[index] = new_key_value;
}

// 查找键对应的值
int find(struct hash_table *hash_table, const char *key)
{
    size_t index = xhash(key, hash_table->size);
    struct key_value *current = hash_table->table[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    // 键未找到
    return -1;
}

// 从哈希表中删除键值对
void delete_key(struct hash_table *hash_table, const char *key)
{
    size_t index = xhash(key, hash_table->size);
    struct key_value *current = hash_table->table[index];
    struct key_value *prev = NULL;

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                hash_table->table[index] = current->next;
            }

            free(current->key);
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

// 释放哈希表内存
void destroy_hash_table(struct hash_table *hash_table)
{
    for (size_t i = 0; i < hash_table->size; i++) {
        struct key_value *current = hash_table->table[i];
        while (current) {
            struct key_value *temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(hash_table->table);
    free(hash_table);
}

int test_hash_table_customize(void)
{
    struct hash_table *hash_table = create_hash_table(100);

    insert(hash_table, "apple", 5);
    insert(hash_table, "banana", 10);
    insert(hash_table, "cherry", 15);

    printf("apple: %d\n", find(hash_table, "apple")); // 输出 5
    printf("banana: %d\n", find(hash_table, "banana")); // 输出 10

    delete_key(hash_table, "banana");
    printf("banana: %d\n", find(hash_table, "banana")); // 输出 -1，因为已删除

    destroy_hash_table(hash_table);

    return 0;
}
