/**
 * @file test_queue.c
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

/* queue
    |       | front
    |       |
    |       |
    |       | rear
*/

#define QUEUE_SIZE 10

typedef struct {
    int data[QUEUE_SIZE];
    int front;
    int rear;
} queue_t;

void queue_init(queue_t *q)
{
    memset(q->data, 0, sizeof(int) * QUEUE_SIZE);
    q->front = -1;
    q->rear = -1;
}

bool queue_is_empty(queue_t *q)
{
    return (q->front == -1);
}

bool queue_is_full(queue_t *q)
{
    return (q->rear == QUEUE_SIZE - 1);
}

void queue_enqueue(queue_t *q, int val)
{
    if (queue_is_full(q)) {
        printf("queue is full\n");
        return;
    }

    if (queue_is_empty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = val;
}

int queue_dequeue(queue_t *q)
{
    int val;
    if (queue_is_empty(q)) {
        printf("queue is empty\n");
        return -1;
    }
    val = q->data[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return val;
}

void queue_display(queue_t *q)
{
    if (queue_is_empty(q)) {
        printf("queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

void queue_test(void)
{
    queue_t q;

    queue_init(&q);

    queue_enqueue(&q, 1);
    queue_enqueue(&q, 2);
    queue_enqueue(&q, 3);
    queue_enqueue(&q, 4);
    queue_enqueue(&q, 5);

    queue_display(&q);

    printf("dequeue: %d\n", queue_dequeue(&q));
    printf("dequeue: %d\n", queue_dequeue(&q));

    queue_display(&q);
}

#define CIRCULAR_QUEUE_SIZE 10

typedef struct {
    int *array;
    int front;
    int rear;
    int size;
} circular_queue;

circular_queue *create_queue(void)
{
    circular_queue *queue = (circular_queue *)malloc(sizeof(circular_queue));
    if (!queue) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    queue->array = (int *)malloc(sizeof(int) * CIRCULAR_QUEUE_SIZE);
    if (!queue->array) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    queue->front = queue->rear = -1;
    queue->size = CIRCULAR_QUEUE_SIZE;
    return queue;
}

int is_full(circular_queue *queue)
{
    return (queue->front == 0 && queue->rear == queue->size - 1) ||
           (queue->front == queue->rear + 1);
}

int is_empty(circular_queue *queue)
{
    return queue->front == -1;
}

void enqueue(circular_queue *queue, int data)
{
    if (is_full(queue)) {
        printf("Queue is full. Enqueue operation failed.\n");
        return;
    }

    if (is_empty(queue)) {
        queue->front = queue->rear = 0;
    } else if (queue->rear == queue->size - 1) {
        queue->rear = 0;
    } else {
        queue->rear++;
    }
    queue->array[queue->rear] = data;
}

int dequeue(circular_queue *queue)
{
    if (is_empty(queue)) {
        printf("Queue is empty. Dequeue operation failed.\n");
        return -1;
    }

    int data = queue->array[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else if (queue->front == queue->size - 1) {
        queue->front = 0;
    } else {
        queue->front++;
    }
    return data;
}

void free_queue(circular_queue *queue)
{
    free(queue->array);
    free(queue);
}

int test_circular_queue(void)
{
    circular_queue *queue = create_queue();

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);

    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));

    enqueue(queue, 4);
    enqueue(queue, 5);

    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));
    printf("Dequeued: %d\n", dequeue(queue));

    free_queue(queue);

    return 0;
}
