#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"

static int isLeaf(BTNode *node) {
    return (!node->left && !node->right);
}

static void inorder(BTNode *node) {
    if (!node) 
        return;

    inorder(node->left);
    printf("{ Data->value: %d }\n", node->key->value);
    inorder(node->right);
}

static int nodeHeight(BTNode *node) {
    if (!node) 
        return 0;

    int leftHeight = nodeHeight(node->left);
    int rightHeight = nodeHeight(node->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

static void preorder(BTNode *node) {
    if (!node) 
        return;

    printf("{ Data->value: %d }\n", node->key->value);
    preorder(node->left);
    preorder(node->right);
}

static void postorder(BTNode *node) {
    if (!node) 
        return;

    postorder(node->left);
    postorder(node->right);
    printf("{ Data->value: %d }\n", node->key->value);
}

BST *createNewBST() {
    BST *bst = (BST *)malloc(sizeof(BST));
    if (!bst) {
        printf("Memory allocation failed for BST.\n");
        return NULL;
    }

    bst->root = NULL;
    return bst;
}

void insertBSTNode(BST *bst, Data *key) {
    if (!bst) {
        printf("Invalid BST configuration.\n");
        return;
    }

    BTNode *newNode = createNewNode(key);

    BTNode *prev = NULL;
    BTNode *curr = bst->root;
    while (curr) {
        prev = curr;
        if (key->value <= curr->key->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (!prev) {
        bst->root = newNode;
    } else {
        if (key->value <= prev->key->value) {
            prev->left = newNode;
        } else {
            prev->right = newNode;
        }
        newNode->parent = prev;
    }
}

BTNode *search(BST *bst, Data *key) {
    BTNode *curr = bst->root; 
    while (curr) {
        if (curr->key->value == key->value) {
            break;
        } else if (curr->key->value < key->value) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }

    return curr;
}

Data *findMax(BST *bst) {
    BTNode *curr = bst->root; 
    while (curr) {
        if (curr->right) {
            curr = curr->right;
        } else {
            break;
        }
    }

    return curr ? curr->key : NULL;
}

Data *findMin(BST *bst) {
    BTNode *curr = bst->root; 
    while (curr) {
        if (curr->left) {
            curr = curr->left;
        } else {
            break;
        }
    }

    return curr ? curr->key : NULL;
}

void inOrderTraversal(BST *bst) {
    inorder(bst->root);
}

void preOrderTraversal(BST *bst) {
    preorder(bst->root);
}

void postOrderTraversal(BST *bst) {
    postorder(bst->root);
}

int height(BST *bst) {
    return nodeHeight(bst->root);
}

int main() {
    BST *bst = createNewBST();
    insertBSTNode(bst, createNewData(5));
    insertBSTNode(bst, createNewData(1));
    insertBSTNode(bst, createNewData(3));
    insertBSTNode(bst, createNewData(8));
    insertBSTNode(bst, createNewData(4));
    insertBSTNode(bst, createNewData(2));

    preOrderTraversal(bst);
    printf("\n");
    inOrderTraversal(bst);

    printf("\nHeight of the BST: %d\n", height(bst));

    BTNode *r1 = search(bst, createNewData(5));
    BTNode *r2 = search(bst, createNewData(-3));

    if (r1) {
        printf("Found r1: %d\n", r1->key->value);
    }

    if (r2) {
        printf("Found r2: %d\n", r2->key->value);
    }

    Data *min = findMin(bst);
    Data *max = findMax(bst);

    if (min) {
        printf("Found min: %d\n", min->value);
    }

    if (max) {
        printf("Found max: %d\n", max->value);
    }

    return 0;
}