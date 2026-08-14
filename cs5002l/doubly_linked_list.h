#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "doubly_linked_list_node.h"

// Assume distinct entries.

typedef struct DoublyLinkedList {
    DLLNode *head;
    DLLNode *tail;
    int size;
} DoublyLinkedList;

typedef struct DoublyLinkedList DLL;

DLL *createNewList();
int isEmpty(DLL *list);
int insertAtHead(DLL *list, int data);
int insertAtTail(DLL *list, int data);
int insertAtPosition(DLL *list, int data, int position);
Data *deleteFromHead(DLL *list);
Data *deleteFromTail(DLL *list);
Data *deleteByValue(DLL *list, int value);
Data *deleteFromPosition(DLL *list, int position);
DLLNode *search(DLL *list, int value);
void traverse(DLL *list);
void traversInReverse(DLL *list);
void reverse(DLL *list);

#endif