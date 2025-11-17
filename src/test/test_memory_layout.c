/**
 * @file test_memory_layout.c
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

#include "utils.h"
/* memory layout test */
static int u_s_g_var_a; /* 未初始化静态全局变量a 存放在bss段 */
static int i_s_g_var_b = 10; /* 已初始化静态全局变量b 存在在data段 */

static int *u_s_g_var_p;
static int *i_s_g_val_p = &u_s_g_var_a;

int u_g_var_c; /* 未初始化全局变量c */
int i_g_var_d = 10; /* 已初始化全局变量d */

const int u_g_c_var_e = 0; /* const 修饰未初始化全局常量 */
const int i_g_c_var_f = 10; /* const 修饰初始化全局常量 */

void func_test(void)
{
    printf("func\n");
}

int test_memory_layout(void)
{
    int l_var_a;
    int l_var_b = 10;
    int *l_var_c = NULL;
    int *l_var_d = NULL;
    static int u_s_l_var_e;
    static int i_s_l_var_f = 10;
    const int u_l_c_var_g = 0;
    const int i_l_c_var_h = 10;
    char *l_var_s = "Hello World";
    char l_var_arr[] = "Hello World";
    const int *l_p_a = &l_var_a; /* 常量指针 */
    int *const l_p_b = &l_var_b; /* 指针常量 */
    const int *const l_p_c = &i_l_c_var_h; /* 指向常量的常指针 */
    int *l_var_aa = (int *)alloca(sizeof(int) * 4); /* 从栈分配内存 */
    static int *i_s_l_var_p = &u_g_var_c;

    printf("-----------------------------------------------------\n");
    printf("栈区\n");
    printf("%s\t\t%p\n", STR(l_var_aa), l_var_aa);
    printf("%s\t\t\t%p\n", STR(l_var_a), &l_var_a);
    printf("%s\t\t\t%p\n", STR(l_var_b), &l_var_b);
    printf("%s\t\t%p\n", STR(&l_var_c), &l_var_c);
    printf("%s\t\t%p\n", STR(&l_var_d), &l_var_d);
    printf("%s\t\t%p\n", STR(u_l_c_var_g), &u_l_c_var_g);
    printf("%s\t\t%p\n", STR(i_l_c_var_h), &i_l_c_var_h);
    printf("%s\t\t%p\n", STR(&l_var_s), &l_var_s);
    printf("%s\t\t\t%p\n", STR(&l_p_a), &l_p_a);
    printf("%s\t\t\t%p\n", STR(&l_p_b), &l_p_b);
    printf("%s\t\t\t%p\n", STR(&l_p_c), &l_p_c);
    printf("%s\t\t%p\n", STR(l_var_arr), l_var_arr);

    l_var_c = (int *)malloc(sizeof(int) * 4);
    l_var_d = (int *)malloc(sizeof(int) * 4);
    printf("-----------------------------------------------------\n");
    printf("堆区\n");
    printf("%s\t\t\t%p\n", STR(l_var_c), l_var_c);
    printf("%s\t\t\t%p\n", STR(l_var_d), l_var_d);

    printf("-----------------------------------------------------\n");
    printf("bss区\n");
    printf("%s\t\t%p\n", STR(u_s_g_var_a), &u_s_g_var_a);
    printf("%s\t\t%p\n", STR(u_g_var_c), &u_g_var_c);
    printf("%s\t\t%p\n", STR(u_s_l_var_e), &u_s_l_var_e);
    printf("%s\t\t%p\n", STR(u_g_c_var_e), &u_g_c_var_e);
    printf("%s\t\t%p\n", STR(i_s_l_var_p), i_s_l_var_p);
    printf("%s\t\t%p\n", STR(&i_s_l_var_p), &i_s_l_var_p);
    printf("%s\t\t%p\n", STR(&u_s_g_var_p), &u_s_g_var_p);
    printf("%s\t\t%p\n", STR(&i_s_g_val_p), &i_s_g_val_p);

    printf("-----------------------------------------------------\n");
    printf("data区\n");
    printf("%s\t\t%p\n", STR(i_s_g_var_b), &i_s_g_var_b);
    printf("%s\t\t%p\n", STR(i_g_var_d), &i_g_var_d);
    printf("%s\t\t%p\n", STR(i_s_l_var_f), &i_s_l_var_f);

    printf("-----------------------------------------------------\n");
    printf("text区\n");
    printf("常量\n");
    printf("%s\t\t%p\n", STR(i_g_c_var_f), &i_g_c_var_f);
    printf("%s\t\t\t%p\n", STR(l_var_s), l_var_s);

    printf("代码\n");
    printf("%s\t%p\n", STR(test_memory_layout), test_memory_layout);
    printf("%s\t\t%p\n", STR(func_test), func_test);

    free(l_var_c);
    l_var_c = NULL;
    free(l_var_d);
    l_var_d = NULL;
    return 0;
}
