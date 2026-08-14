#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "singly_linked_list_node.h"

// Assume distinct entries.

typedef struct SinglyLinkedList {
    SLLNode *head;
    SLLNode *tail;
    int size;
} SinglyLinkedList;

typedef struct SinglyLinkedList SLL;

SLL *createNewList();
int isEmpty(SLL *list);
int insertAtHead(SLL *list, int data);
int insertAtTail(SLL *list, int data);
int insertAtPosition(SLL *list, int data, int position);
Data *deleteFromHead(SLL *list);
Data *deleteFromTail(SLL *list);
Data *deleteByValue(SLL *list, int value);
Data *deleteFromPosition(SLL *list, int position);
SLLNode *search(SLL *list, int value);
void traverse(SLL *list);
void reverse(SLL *list);

#endif