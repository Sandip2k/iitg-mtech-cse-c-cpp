#ifndef B_TREE_NODE_H
#define B_TREE_NODE_H

typedef struct BTreeNode {
    int isLeaf;
    int numKeys;
    int *keys;
    struct BTreeNode **children;
} BTreeNode;

BTreeNode *createNewNode(int order, int isLeaf);
void deleteNode(BTreeNode *node);

#endif