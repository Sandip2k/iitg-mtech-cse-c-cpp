#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list_node.h"

DLLNode *createNewNode(Data *data) {
    DLLNode *newNode = (DLLNode *) malloc(sizeof(DLLNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

int deleteNode(DLLNode *node) {
    if (node) {
        free(node);
        return 1;
    }
    return 0;
}