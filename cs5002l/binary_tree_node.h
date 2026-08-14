#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

#include "data.h"

typedef struct BinaryTreeNode {
    Data *key;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *parent;
} BinaryTreeNode;

typedef BinaryTreeNode BTNode;

BinaryTreeNode *createNewNode(Data *key);
void deleteNode(BinaryTreeNode *node);

#endif