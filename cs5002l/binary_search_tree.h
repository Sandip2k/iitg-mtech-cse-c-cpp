#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "binary_tree_node.h"

typedef struct BinarySearchTree {
    BinaryTreeNode *root;
} BinarySearchTree;

typedef BinarySearchTree BST;

Data *findMax(BST *bst);
Data *findMin(BST *bst);
BST *createNewBST();
void insertBSTNode(BST *bst, Data *key);
void deleteBSTNode(BST *bst, Data *key);
BTNode *search(BST *bst, Data *key);
BST *join(BST *bst1, BST *bst2); // assume that all nodes in bst1 <= all nodes in bst2
BST **split(BST *bst, Data *key);

void inOrderTraversal(BST *bst);
void preOrderTraversal(BST *bst);
void postOrderTraversal(BST *bst);

int height(BST *bst);

#endif