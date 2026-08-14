#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

int isEmpty(DLL *list) {
    return (list->size == 0);
}

DLL *createNewList() {
    DLL *list = (DLL *) malloc(sizeof(DLL));
    if (!list) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

int insertAtHead(DLL *list, int value) {
    if (!list) {
        printf("List not initialized.\n");
        return 0;
    }

    Data *data = createNewData(value);
    if (!data) {
        printf("Failed to allocate memory.\n");
        return 0;
    }

    DLLNode *newNode = createNewNode(data);

    if (!newNode) {
        printf("Failed to allocate memory.\n");
        free(data);
        return 0;
    }

    if (!list->head) { // First node being inserted.
        list->head = list->tail = newNode;
    } else {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
    }

    list->size++;
    return 1;
}

int insertAtTail(DLL *list, int value) {
    if (!list) {
        printf("List not initialized.\n");
        return 0;
    }

    Data *data = createNewData(value);
    if (!data) {
        printf("Failed to allocate memory.\n");
        return 0;
    }

    DLLNode *newNode = createNewNode(data);

    if (!newNode) {
        printf("Failed to allocate memory.\n");
        free(data);
        return 0;
    }

    if (!list->head) { // First node being inserted.
        list->head = list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
    return 1;
}

int insertAtPosition(DLL *list, int value, int position) {
    if (!list) {
        printf("List not initialized.\n");
        return 0;
    }

    Data *data = createNewData(value);
    if (!data) {
        printf("Failed to allocate memory.\n");
        return 0;
    }

    DLLNode *newNode = createNewNode(data);

    if (!newNode) {
        printf("Failed to allocate memory.\n");
        free(data);
        return 0;
    }

    if (position < 0 || position > list->size) {
        printf("Invalid position.\n");
        free(data);
        free(newNode);
        return 0;
    }

    if (position == 0) {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
        if (isEmpty(list)) {
            list->tail = newNode;
        }
    } else if (position == list->size) {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    } else {
        DLLNode *current = list->head;
        for (int i = 0; i < position - 1; i++) { // Find the node just before the desired position.
            current = current->next;
        }
        newNode->prev = current;
        current->next->prev = newNode;
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
    return 1;
}
Data *deleteFromHead(DLL *list) {
    if (!list) {
        printf("List not initialized.\n");
        return NULL;
    }

    if (isEmpty(list)) {
        printf("List is empty.\n");
        return NULL;
    }

    DLLNode *temp = list->head;
    Data *data = temp->data;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    free(temp);
    list->size--;
    return data;
}

Data *deleteFromTail(DLL *list) {
    if (!list) {
        printf("List not initialized.\n");
        return NULL;
    }

    if (isEmpty(list)) {
        printf("List is empty.\n");
        return NULL;
    }

    DLLNode *temp = list->tail;
    Data *data = temp->data;
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    free(temp);
    list->size--;
    return data;
}

Data *deleteByValue(DLL *list, int value) {
    if (!list) {
        printf("List not initialized.\n");
        return NULL;
    }

    if (isEmpty(list)) {
        printf("List is empty.\n");
        return NULL;
    }

    DLLNode *current = list->head;
    DLLNode *previous = NULL;
    while (current) {
        if (current->data && current->data->value == value) {
            if (previous) {
                if (current->next) {
                    current->next->prev = previous;
                }
                previous->next = current->next;
            } else {
                list->head = current->next;
                if (list->head) {
                    list->head->prev = NULL;
                }
            }
            if (current == list->tail) {
                list->tail = previous;
                if (list->tail) {
                    list->tail->next = NULL;
                }
            }
            Data *data = current->data;
            free(current);
            list->size--;
            return data;
        }
        previous = current;
        current = current->next;
    }
    printf("Value not found.\n");
    return NULL;
}
Data *deleteFromPosition(DLL *list, int position) {
    if (!list) {
        printf("List not initialized.\n");
        return NULL;
    }

    if (position < 0 || position >= list->size) {
        printf("Invalid position.\n");
        return NULL;
    }

    if (position == 0) {
        return deleteFromHead(list);
    } else if (position == list->size - 1) {
        return deleteFromTail(list);
    }

    DLLNode *current = list->head;
    for (int i = 0; i < position - 1; i++) { // Find the node just before the desired position.
        current = current->next;
    }
    DLLNode *temp = current->next;
    Data *data = temp->data;
    current->next = current->next->next;
    if (current->next) {
        current->next->prev = current;
    }
    free(temp);
    list->size--;
    return data;
}

DLLNode *search(DLL *list, int value) {
    if (!list) {
        printf("List not initialized.\n");
        return NULL;
    }

    if (isEmpty(list)) {
        printf("List is empty.\n");
        return NULL;
    }

    DLLNode *current = list->head;
    while (current) {
        if (current->data && current->data->value == value) {
            return current;
        }
        current = current->next;
    }
    printf("Value not found.\n");
    return NULL;
}

void traverse(DLL *list) {
    DLLNode *curr = list->head;
    while (curr) {
        printf("%d ", (curr->data ? curr->data->value : INT_MIN));

        if (curr == list->tail)
            break;

        curr = curr->next;
    }
    printf("\n");
}

void traverseInReverse(DLL *list) {
    DLLNode *curr = list->tail;
    while (curr) {
        printf("%d ", (curr->data ? curr->data->value : INT_MIN));

        if (curr == list->head)
            break;

        curr = curr->prev;
    }
    printf("\n");
}

void reverse(DLL *list) {

}

int main() {
    DLL *list = createNewList();
    insertAtHead(list, 1);
    insertAtHead(list, 2);
    insertAtHead(list, 3);
    insertAtTail(list, 4);
    insertAtTail(list, 5);
    insertAtTail(list, 6);
    insertAtPosition(list, 7, 3);
    insertAtPosition(list, 8, 0);
    insertAtTail(list, 9);
    insertAtHead(list, 10);
    insertAtPosition(list, 11, list->size);
    traverse(list);
    traverseInReverse(list);

    deleteFromHead(list); // 10
    deleteFromTail(list); // 11
    deleteByValue(list, 7);
    deleteFromPosition(list, 2); // 2
    deleteFromPosition(list, list->size - 1); // 9 <- check this.
    traverse(list);
    traverseInReverse(list);

    DLLNode *searchResult1 = search(list, 5);
    DLLNode *searchResult2 = search(list, 12);

    printf(
        "Found: %d\n",
        (searchResult1 && searchResult1->data ? searchResult1->data->value : INT_MIN)
    );
    printf(
        "Not Found: %d\n",
        (searchResult2 && searchResult2->data ? searchResult2->data->value : INT_MIN)
    );
    return 0;
}