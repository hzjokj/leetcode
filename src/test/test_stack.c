/**
 * @file test_stack.c
 * @author hongzhijun (eehongzhijun@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/* stack */
/*
    |       |
    |       |
    |       |
    |       |
    |______|
*/
#define STACK_SIZE 10

typedef struct {
    int data[STACK_SIZE];
    int top;
} stack_t;

void stack_init(stack_t *s)
{
    memset(s->data, 0, sizeof(int) * STACK_SIZE);
    s->top = 0;
}

bool stack_is_full(stack_t *s)
{
    return (s->top == STACK_SIZE - 1);
}

bool stack_is_empty(stack_t *s)
{
    return (s->top == 0);
}

void stack_push(stack_t *s, int val)
{
    if (stack_is_full(s)) {
        printf("stack is full\n");
        return;
    }
    s->data[s->top] = val;
    s->top++;
}

int stack_pop(stack_t *s)
{
    if (stack_is_empty(s)) {
        printf("stack is empty\n");
        return -1;
    }

    int val = s->data[s->top - 1];
    s->top--;
    return val;
}

int stack_top(stack_t *s)
{
    if (stack_is_empty(s)) {
        printf("stack is empty\n");
        return -1;
    }
    return s->data[s->top - 1];
}

void test_stack(void)
{
    stack_t stack;

    stack_init(&stack);

    printf("stack push\n");
    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_push(&stack, 4);
    stack_push(&stack, 5);

    printf("stack top element is %d\n", stack_top(&stack));

    while (!stack_is_empty(&stack)) {
        printf("stack pop %d\n", stack_pop(&stack));
    }
}
