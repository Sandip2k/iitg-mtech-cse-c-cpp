#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

#include "data.h"

typedef struct BinaryTreeNode {
    int key;
    Data *data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *parent;
} BinaryTreeNode;

typedef BinaryTreeNode BTNode;

BinaryTreeNode *createNewNode(int key, Data *data);
void deleteNode(BinaryTreeNode *node);

#endif