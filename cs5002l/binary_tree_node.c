#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "binary_tree_node.h"

BinaryTreeNode *createNewNode(int key, Data *data) {
    BinaryTreeNode *node = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
    if (!node) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    node->key = key;
    node->data = data;
    node->parent = node->left = node->right = NULL;
    return node;
}

void deleteNode(BinaryTreeNode *node) {
    if (!node) {
        return;
    }

    deleteNode(node->left);
    deleteNode(node->right);
    deleteData(node->data);
    free(node);
}