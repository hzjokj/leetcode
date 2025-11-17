/**
 * @file main.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include "calc.h"

/*
https://www.cnblogs.com/eezhijun/p/17734333.html

-I 指定保护头文件路径
-L 指定库链接路径
-l 指定库名称
静态库：
gcc src/main.c -I include/ -L lib/ -l calc -o ./bin/main
动态库：
gcc src/main.c -I include/ -L lib/ -Wl,-rpath="/home/hongzhijun/prj/leetcode/src/test/libtest/lib" -lcalc -o ./bin/main
*/

int main(void)
{
    int m, n;

    printf("MAIN ENTRY\n");
    printf("please input m and n:\n");
    scanf("%d %d", &m, &n);

    printf("%d+%d=%d\n", m, n, add(m, n));
    printf("%d-%d=%d\n", m, n, sub(m, n));
    printf("%dx%d=%d\n", m, n, mul(m, n));
    printf("%d/%d=%d\n", m, n, div(m, n));

    return 0;
}
