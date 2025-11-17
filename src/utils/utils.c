/**
 * @file utils.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>

#include <ctype.h>

/* linux lib */
#include <fcntl.h>
#include <termios.h>

#include "utils.h"

/* function template */
// #define MAXT(T) T max_##T(T a, T b) {return (a > b) ? a : b;}

// MAXT(int)
// MAXT(float)
// MAXT(double)

void bubble_sort(int arr[], int len)
{
    int i, j, temp;
    bool exchanged = true;

    for (i = 0; exchanged && i < len - 1; i++) {
        exchanged = false;
        for (j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                exchanged = true;
            }
        }
    }
}

int cmp(const void *pa, const void *pb)
{
    int a = *(int *)pa;
    int b = *(int *)pb;
    return a - b;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

int clamp(int value, int min, int max)
{
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

double roundup(double num)
{
    if (num >= 0) {
        return ceil(num);
    } else {
        return floor(num);
    }
}

double rounddown(double num)
{
    if (num >= 0) {
        return floor(num);
    } else {
        return ceil(num);
    }
}

void swap(void *lhs, void *rhs, size_t size)
{
    if (lhs == NULL || rhs == NULL || size == 0) {
        return;
    }
    void *t = malloc(size);
    memcpy(t, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, t, size);
    free(t);
}

void swap_by_temp(int *lhs, int *rhs)
{
    if (lhs == NULL || rhs == NULL) {
        return;
    }
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp;
}

void swap_by_sum(int *lhs, int *rhs)
{
    if (lhs == NULL || rhs == NULL) {
        return;
    }
    *lhs = *lhs + *rhs;
    *rhs = *lhs - *rhs;
    *lhs = *lhs - *rhs;
}

void swap_by_xor(int *lhs, int *rhs)
{
    if (lhs == NULL || rhs == NULL) {
        return;
    }
    *lhs = *lhs ^ *rhs;
    *rhs = *lhs ^ *rhs;
    *lhs = *lhs ^ *rhs;
}

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

char getch(void)
{
    char c;
    system("stty raw");
    c = getchar();
    system("stty sane");
    return c;
}

void clrscr(void)
{
    system("clear");
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

char wait_4_key(void)
{
    int pressed;

    while (!kbhit()) {
    }

    pressed = getch();
    //pressed = tolower(pressed);
    return (char)pressed;
}

void set_terminal_attributes(void)
{
    struct termios term;
    tcgetattr(STDOUT_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void restore_terminal_attributes(void)
{
    struct termios term;
    tcgetattr(STDOUT_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void hide_cursor(void)
{
    printf("\e[?25l");
}

void show_cursor(void)
{
    printf("\e[?25h");
}

int xffs(int x)
{
    if (x == 0)
        return 0;
    int position = 1;
    while ((x & 1) == 0) {
        x >>= 1;
        position++;
    }
    return position;
}

int xfls(int x)
{
    if (x == 0)
        return 0;
    int position = sizeof(x) * CHAR_BIT;
    while ((x & (1 << (position - 1))) == 0) {
        position--;
    }
    return position;
}

int xclz(int x)
{
    if (x == 0)
        return sizeof(x) * CHAR_BIT;
    int count = 0;
    while ((x & (1 << (sizeof(x) * CHAR_BIT - 1))) == 0) {
        x <<= 1;
        count++;
    }
    return count;
}

int xctz(int x)
{
    if (x == 0)
        return sizeof(x) * CHAR_BIT;
    int count = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        count++;
    }
    return count;
}

void print_int(void *elem)
{
    int *num = (int *)elem;
    printf("%d ", *num);
}

void print_float(void *elem)
{
    float *num = (float *)elem;
    printf("%f ", *num);
}

void print_string(void *elem)
{
    char **str = (char **)elem;
    printf("%s\n", *str);
}

char *int2string(int num, char *str)
{
    sprintf(str, "%d", num);
    return str;
}

int string2int(char *str)
{
    char sign = '+';
    long n = 0;

    if (*str == '-') {
        ++str;
        sign = '-';
    }

    sscanf(str, "%ld", &n);
    if (sign == '-') {
        n = -n;
    }
    return (int)n;
}

void reverse(char *s, int l, int r)
{
    while (l < r) {
        SWAP(char, &s[l], &s[r]);
        l++;
        r--;
    }
}

int hex2dec(char hex[])
{
    if (hex == NULL) {
        return -1;
    }

    int dec = 0;
    int len = strlen(hex);

    for (int i = 0; hex[i] != '\0'; i++) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            dec += pow(16, len - i - 1) * (hex[i] - '0');
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            dec += pow(16, len - i - 1) * (hex[i] - 'A' + 10);
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            dec += pow(16, len - i - 1) * (hex[i] - 'a' + 10);
        } else {
            printf("invalid char %c\n", hex[i]);
            return -1;
        }
    }
    return dec;
}

char *dec2hex(int dec)
{
    char *s;
    int r;
    int i = 0;
    int len = 0;
    int temp = dec;

    if (dec < 0) {
        return NULL;
    }

    while (temp > 0) {
        temp = temp / 16;
        len++;
    }

    if (dec == 0) {
        len++;
    }
    s = (char *)malloc(sizeof(char) * (len + 1));
    if (s == NULL) {
        printf("malloc fail/n");
        return NULL;
    }
    s[len] = '\0';

    if (dec == 0) {
        s[0] = '0';
        return s;
    }
    while (dec > 0) {
        r = dec % 16;

        if (r < 10) {
            s[i] = r + '0';
        } else {
            s[i] = r - 10 + 'A';
        }

        i++;
        dec /= 16;
    }

    reverse(s, 0, len - 1);
    return s;
}

int count_digits(int num)
{
    int count = 0;

    if (num == 0) {
        return 1;
    }

    while (num != 0) {
        num /= 10;
        count++;
    }

    return count;
}

void printf_bin(int num)
{
    int i, j;
    unsigned char *p = (unsigned char *)&num + 3;

    for (i = 0; i < 4; i++) //处理4个字节(32位）
    {
        j = *(p - i); //取每个字节的首地址
        for (int k = 7; k >= 0; k--) //处理每个字节的8个位
        {
            if (j & (1 << k))
                printf("1");
            else
                printf("0");
        }
        printf(" ");
    }
    printf("\r\n");
}

char *str2lower(char *s)
{
    char *origin = s;
    for (; *s != '\0'; s++) {
        *s = tolower(*s);
    }
    return origin;
}

char *str2upper(char *s)
{
    char *origin = s;
    for (; *s != '\0'; s++) {
        *s = toupper(*s);
    }
    return origin;
}

bool is_power_of_two(unsigned long n)
{
    return (n != 0) && ((n & (n - 1)) == 0);
}

int hamming_weight(int x)
{
    int count;
    for (count = 0; x; count++)
        x &= x - 1;
    return count;
}
