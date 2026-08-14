#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

#include "data.h"

typedef struct DoublyLinkedListNode {
    Data *data;
    struct DoublyLinkedListNode *prev;
    struct DoublyLinkedListNode *next;
} DoublyLinkedListNode;

typedef struct DoublyLinkedListNode DLLNode;

DLLNode *createNewNode(Data *data);
int deleteNode(DLLNode *node);

#endif