#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_node.h"

int isLeaf(BTNode *node) {
    return !node->left && !node->right;
}

BTNode *createTree(int key, Data *data) {
    return createNewNode(key, data);
}

BTNode *makeTree(int key, Data *data, BTNode *left, BTNode *right) {
    BTNode *root = createNewNode(key, data);
    left->parent = root;
    right->parent = root;
    root->left = left;
    root->right = right;
    return root;
}

BTNode *getLeftNode(BTNode *node) {
    if (!node) {
        printf("Invalid node.\n");
        return NULL;
    }
    return node->left;
}

BTNode *getRightNode(BTNode *node) {
    if (!node) {
        printf("Invalid node.\n");
        return NULL;
    }
    return node->right;
}

// flag for left or right if child is already present.
// flag = 1 for left child, flag = 0 for right child.
int insertLeftNode(BTNode *node, int key, Data *data, int flag) {
    if (!node) {
        printf("Invalid node.\n");
        return 0;
    }

    BTNode *newNode = createNewNode(key, data);

    if (node->left) {
        node->left->parent = newNode;
        if (flag) {
            newNode->left = node->left;
        } else {
            newNode->right = node->left;
        }
    }

    newNode->parent = node;
    node->left = newNode;
    return 1;
}

// flag for left or right if child is already present.
// flag = 1 for left child, flag = 0 for right child.
int insertRightNode(BTNode *node, int key, Data *data, int flag) {
    if (!node) {
        printf("Invalid node.\n");
        return 0;
    }

    BTNode *newNode = createNewNode(key, data);

    if (node->right) {
        node->right->parent = newNode;
        if (flag) {
            newNode->left = node->right;
        } else {
            newNode->right = node->right;
        }
    }

    newNode->parent = node;
    node->right = newNode;
    return 1;
}

void preOrder(BTNode *node) {
    if (!node) {
        return;
    }

    printf("%d ", node->key);
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(BTNode *node) {
    if (!node) {
        return;
    }

    inOrder(node->left);
    printf("%d ", node->key);
    inOrder(node->right);
}

void postOrder(BTNode *node) {
    if (!node) {
        return;
    }

    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->key);
}

int equal(BTNode *a, BTNode *b) {
    if (a == b) {
        return 1;
    }

    if (!a || !b) {
        return 0;
    }

    return 
        a->key == b->key &&
        equal(a->left, b->left) &&
        equal(a->right, b->right);
}

int main() {
    BTNode *left = createTree(2, createNewData(2));
    BTNode *right = createTree(3, createNewData(3));
    BTNode *root = makeTree(1, createNewData(1), left, right);
    insertLeftNode(root, 4, createNewData(4), 1);
    insertLeftNode(root, 5, createNewData(5), 0);
    insertRightNode(root, 6, createNewData(6), 0);
    insertRightNode(root, 7, createNewData(7), 1);

    preOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
}