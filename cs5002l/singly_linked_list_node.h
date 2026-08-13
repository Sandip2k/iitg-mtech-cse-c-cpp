#ifndef SINGLY_LINKED_LIST_NODE_H
#define SINGLY_LINKED_LIST_NODE_H

#include "data.h"

typedef struct SinglyLinkedListNode {
    Data *data;
    struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

typedef struct SinglyLinkedListNode SLLNode;

SLLNode *createNewNode(Data *data);
int deleteNode(SLLNode *node);

#endif