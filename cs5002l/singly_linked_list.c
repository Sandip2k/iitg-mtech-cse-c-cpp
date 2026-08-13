#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "data.h"
#include "singly_linked_list_node.h"
#include "singly_linked_list.h"

int isEmpty(SLL *list) {
    return (list->size == 0);
}

SLL *createNewList() {
    SLL *list = (SLL *) malloc(sizeof(SLL));
    if (!list) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int insertAtHead(SLL *list, int value) {
    if (!list) {
        printf("List not initialized.\n");
        return 0;
    }

    Data *data = createNewData(value);
    if (!data) {
        printf("Failed to allocate memory.\n");
        return 0;
    }

    SLLNode *newNode = createNewNode(data);

    if (!newNode) {
        printf("Failed to allocate memory.\n");
        free(data);
        return 0;
    }

    if (!list->head) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }

    list->size++;
    return 1;
}

int insertAtTail(SLL *list, int value) {
    if (!list) {
        printf("List not initialized.\n");
        return 0;
    }

    Data *data = createNewData(value);
    if (!data) {
        printf("Failed to allocate memory.\n");
        return 0;
    }

    SLLNode *newNode = createNewNode(data);

    if (!newNode) {
        printf("Failed to allocate memory.\n");
        free(data);
        return 0;
    }

    if (!list->head) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
    return 1;
}

int insertAtPosition(SLL *list, int value, int position) {
    return 1;
}

int deleteFromHead(SLL *list) {
    return 1;
}

int deleteFromTail(SLL *list) {
    return 1;
}

int deleteByValue(SLL *list, int value) {
    return 1;
}

int deleteFromPosition(SLL *list, int position) {
    return 1;
}

SLLNode *search(SLL *list, int value) {
    return NULL;
}

void traverse(SLL *list) {
    SLLNode *curr = list->head;
    while (curr) {
        printf("%d ", (curr->data ? curr->data->value : INT_MIN));

        if (curr == list->tail)
            break;

        curr = curr->next;
    }
    printf("\n");
}

void reverse(SLL *list) {

}

int main() {
    SLL *list = createNewList();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    insertAtTail(list, 4);
    insertAtTail(list, 5);
    insertAtTail(list, 6);

    traverse(list);
    return 0;
}