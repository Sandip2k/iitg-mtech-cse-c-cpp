#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "singly_linked_list_node.h"
#include "singly_linked_list.h"

SLLNode *createNewNode(Data *data) {
    SLLNode *newNode = (SLLNode *) malloc(sizeof(SLLNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int deleteNode(SLLNode *node) {
    if (node) {
        free(node);
        return 1;
    }
    return 0;
}
