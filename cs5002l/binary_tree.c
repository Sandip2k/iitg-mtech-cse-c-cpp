#include <stdio.h>
#include <stdlib.h>
#include "binary_tree_node.h"

int isLeaf(BTNode *node) {
    return !node->left && !node->right;
}

BTNode *createTree(Data *key) {
    return createNewNode(key);
}

BTNode *makeTree(Data *key, BTNode *left, BTNode *right) {
    BTNode *root = createNewNode(key);
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
int insertLeftNode(BTNode *node, Data *key, int flag) {
    if (!node) {
        printf("Invalid node.\n");
        return 0;
    }

    BTNode *newNode = createNewNode(key);

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
int insertRightNode(BTNode *node, Data *key, int flag) {
    if (!node) {
        printf("Invalid node.\n");
        return 0;
    }

    BTNode *newNode = createNewNode(key);

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

    printf("%d ", node->key ? node->key->value : INT_MIN);
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(BTNode *node) {
    if (!node) {
        return;
    }

    inOrder(node->left);
    printf("%d ", node->key ? node->key->value : INT_MIN);
    inOrder(node->right);
}

void postOrder(BTNode *node) {
    if (!node) {
        return;
    }

    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->key ? node->key->value : INT_MIN);
}

int equal(BTNode *a, BTNode *b) {
    if (a == b) {
        return 1;
    }

    if (!a || !b) {
        return 0;
    }

    return 
        (a->key && b->key && a->key->value == b->key->value) &&
        equal(a->left, b->left) &&
        equal(a->right, b->right);
}

int main() {
    BTNode *left = createTree(createNewData(2));
    BTNode *right = createTree(createNewData(3));
    BTNode *root = makeTree(createNewData(1), left, right);
    insertLeftNode(root, createNewData(4), 1);
    insertLeftNode(root, createNewData(5), 0);
    insertRightNode(root, createNewData(6), 0);
    insertRightNode(root, createNewData(7), 1);

    preOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
}