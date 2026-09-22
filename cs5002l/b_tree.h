#ifndef B_TREE_H
#define B_TREE_H

#include "b_tree_node.h"

typedef struct BTree {
    int order;
    BTreeNode *root;
} BTree;

BTree *create(int order);
void insertKey(BTree *btree, int key);
void traverse(BTree *btree);
void deleteKey(BTree *btree, int key);
BTreeNode *search(BTree *btree, int key);

#endif