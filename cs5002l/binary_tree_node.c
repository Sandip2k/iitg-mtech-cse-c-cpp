#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "binary_tree_node.h"

BinaryTreeNode *createNewNode(Data *key) {
    BinaryTreeNode *node = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
    if (!node) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    node->key = key;
    node->parent = node->left = node->right = NULL;
    return node;
}

void deleteNode(BinaryTreeNode *node) {
    if (!node) {
        return;
    }

    deleteNode(node->left);
    deleteNode(node->right);
    free(node);
}