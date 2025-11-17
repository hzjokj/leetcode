/**
 * @file test_list.c
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

// 定义链表节点结构
struct node {
    int data;
    struct node *next;
};

// 创建一个新节点
struct node *create_node(int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 在链表头部插入节点
void insert_node_at_head(struct node **head, int data)
{
    struct node *new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// 在链表末尾插入节点
void append_node(struct node **head, int data)
{
    struct node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// 删除指定值的节点
void delete_node(struct node **head, int data)
{
    struct node *current = *head;
    struct node *prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("node %d not found\n", data);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}

// 打印链表内容
void print_list(struct node *head)
{
    struct node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// 主函数
int list_test(void)
{
    struct node *head = NULL; // 初始化一个空链表

    // 在链表头部插入节点
    insert_node_at_head(&head, 1);
    insert_node_at_head(&head, 2);
    insert_node_at_head(&head, 3);

    // 在链表末尾插入节点
    append_node(&head, 4);
    append_node(&head, 5);

    // 打印链表内容
    printf("list: \n");
    print_list(head);

    // 删除节点
    delete_node(&head, 3);
    delete_node(&head, 6);

    // 打印链表内容
    printf("after delete list:\n");
    print_list(head);

    return 0;
}

// Define a structure for a doubly linked list node
struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

// Function to create a new node
struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new node at the beginning of the list
void insertAtBeginning(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to insert a new node at the end of the list
void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

// Function to delete a node by value
void deleteNode(struct Node **head, int key)
{
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node *current = *head;
    while (current != NULL) {
        if (current->data == key) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
    printf("Element %d not found in the list.\n", key);
}

// Function to print the doubly linked list
void printList(struct Node *head)
{
    struct Node *current = head;
    printf("Doubly Linked List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int test_doubly_list(void)
{
    struct Node *head = NULL;

    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);

    printList(head);

    insertAtBeginning(&head, 0);
    printList(head);

    deleteNode(&head, 3);
    printList(head);

    return 0;
}
