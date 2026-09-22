#include <stdio.h>
#include <stdlib.h>
#include "b_tree_node.h"

BTreeNode *createNewNode(int order, int isLeaf) {
    BTreeNode *newNode = (BTreeNode *) malloc(sizeof(BTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    int totalKeys = 2 * order - 1;
    newNode->keys = (int *) malloc(totalKeys * sizeof(int));
    newNode->children = (BTreeNode **) malloc((totalKeys + 1) * sizeof(BTreeNode *));
    for (int i = 0; i <= totalKeys; ++i) {
        newNode->children[i] = NULL;
    }
    return newNode;
}