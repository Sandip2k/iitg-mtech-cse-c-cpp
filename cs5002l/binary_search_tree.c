#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "binary_search_tree.h"

static int isLeaf(BTNode *node) {
    return (!node->left && !node->right);
}

static void inorder(BTNode *node) {
    if (!node) 
        return;

    inorder(node->left);
    printf("{ Key: %d, Data->value: %d }\n", node->key, node->data->value);
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

    printf("{ Key: %d, Data->value: %d }\n", node->key, node->data->value);
    preorder(node->left);
    preorder(node->right);
}

static void postorder(BTNode *node) {
    if (!node) 
        return;

    postorder(node->left);
    postorder(node->right);
    printf("{ Key: %d, Data->value: %d }\n", node->key, node->data->value);
}

static BTNode *inorderPredecessor(BTNode *node) {
    if (node->left) {
        BTNode *curr = node->left;
        while (curr && curr->right) { // Find the rightmost node in the left subtree.
            curr = curr->right;
        }
        return curr;
    } else {
        return NULL;
    }
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

void insertBSTNode(BST *bst, int key, Data *data) {
    if (!bst) {
        printf("Invalid BST configuration.\n");
        return;
    }

    BTNode *newNode = createNewNode(key, data);

    BTNode *prev = NULL;
    BTNode *curr = bst->root;
    while (curr) { // Insertion is done at the leaves, so we traverse until we find a NULL position.
        prev = curr;
        if (key <= curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    if (!prev) {
        bst->root = newNode;
    } else {
        if (key <= prev->key) {
            prev->left = newNode;
        } else {
            prev->right = newNode;
        }
        newNode->parent = prev;
    }
}

BTNode *search(BST *bst, int key) {
    if (!bst) {
        printf("Invalid BST configuration.\n");
        return NULL;
    }

    BTNode *curr = bst->root; 
    while (curr) {
        if (curr->key == key) {
            break;
        } else if (curr->key < key) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }

    return curr;
}

Data *findMax(BST *bst) {
    BTNode *curr = bst->root;
    while (curr) { // Traverse down the right spine of the tree to find the maximum value.
        if (curr->right) {
            curr = curr->right;
        } else {
            break;
        }
    }

    return curr ? curr->data : NULL;
}

Data *findMin(BST *bst) {
    BTNode *curr = bst->root;
    while (curr) { // Traverse down the left spine of the tree to find the minimum value.
        if (curr->left) {
            curr = curr->left;
        } else {
            break;
        }
    }

    return curr ? curr->data : NULL;
}

void deleteBSTNode(BST *bst, int key) {
    if (!bst) {
        printf("Invalid BST configuration.\n");
        return;
    }

    BTNode *searchResult = search(bst, key);
    if (!searchResult) {
        return;
    }

    BTNode *parent = searchResult->parent;

    if (isLeaf(searchResult)) { // Case 1: leaf node.
        if (!parent) { // if the root is being deleted and it is a leaf node, set the root to NULL.
            bst->root = NULL;
        } else {
            if (parent->left == searchResult) { // just detach the node from its parent.
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
    } else if (
        (!searchResult->left && searchResult->right) || 
        (searchResult->left && !searchResult->right)
    ) { // Case 2: node with one child.
        if (!parent) { // if the root is being deleted and it has one child, set the root to that child.
            bst->root = (searchResult->left) ? searchResult->left : searchResult->right;
            bst->root->parent = NULL;
        } else { // else, just bypass the node and connect its parent to its child.
            if (parent->left == searchResult) {
                parent->left = (searchResult->left) ? searchResult->left : searchResult->right;
                parent->left->parent = parent;
            } else {
                parent->right = (searchResult->left) ? searchResult->left : searchResult->right;
                parent->right->parent = parent;
            }
        }
    } else { // Case 3: node with two children.
        BTNode *predecessor = inorderPredecessor(searchResult);

        if (predecessor->parent != searchResult) { // predecessor is not the direct left child of the node to be deleted.
            predecessor->parent->right = predecessor->left;

            if (predecessor->left) {
                predecessor->left->parent = predecessor->parent;
            }

            predecessor->left = searchResult->left;
            predecessor->left->parent = predecessor;
        }

        predecessor->parent = parent;

        if (!parent) { // if the root is being deleted and it has two children, set the root to the predecessor.
            bst->root = predecessor;
        } else if (parent->left == searchResult) { // else, just bypass the node and connect its parent to its predecessor.
            parent->left = predecessor;
        } else {
            parent->right = predecessor;
        }

        predecessor->right = searchResult->right;
        predecessor->right->parent = predecessor;
    }

    free(searchResult); // only free the node, not the data, as the data might be used elsewhere.
}

/*
* Assuming all the nodes in bst1 <= all the nodes in bst2.
*/
BST *join(BST *bst1, BST *bst2) {
    if (!bst1 || !bst1->root) {
        return bst2;
    }

    if (!bst2 || !bst2->root) {
        return bst1;
    }

    BTNode *curr = bst1->root;
    while (curr && curr->right) {
        curr = curr->right;
    }

    if (curr->parent) {
        if (curr->left) {
            curr->parent->right = curr->left;
            curr->left->parent = curr->parent;
        } else {
            curr->parent->right = NULL;
        }
    } else {
        bst1->root = curr->left;
        if (bst1->root) {
            bst1->root->parent = NULL;
        }
    }
    
    curr->parent = NULL;
    curr->left = bst1->root;
    if (bst1->root) {
        bst1->root->parent = curr;
    }

    curr->right = bst2->root;
    if (bst2->root) {
        bst2->root->parent = curr;
    }

    BST *result = createNewBST();
    result->root = curr;
    return result;
}

BST **split(BST *bst, int key) {
    BST **res = (BST **) malloc(2 * sizeof(BST *));
    res[0] = createNewBST();
    res[1] = createNewBST();

    BTNode *curr = bst->root;

    while (curr) {
        BTNode *next = NULL;
        if (curr->key <= key) {
            next = curr->right;
            curr->right = res[0]->root;
            if (res[0]->root) res[0]->root->parent = curr;
            curr->parent = NULL;
            res[0]->root = curr;
        } else {
            next = curr->left;
            curr->left = res[1]->root;
            if (res[1]->root) res[1]->root->parent = curr;
            curr->parent = NULL;
            res[1]->root = curr;
        }
        curr = next;
    }

    bst->root = NULL;
    return res;
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
    insertBSTNode(bst, 5, createNewData(5));
    insertBSTNode(bst, 1, createNewData(1));
    insertBSTNode(bst, 3, createNewData(3));
    insertBSTNode(bst, 8, createNewData(8));
    insertBSTNode(bst, 4, createNewData(4));
    insertBSTNode(bst, 2, createNewData(2));
    insertBSTNode(bst, -1, createNewData(-1));
    insertBSTNode(bst, 6, createNewData(6));
    insertBSTNode(bst, 10, createNewData(10));

    BST *bst1 = createNewBST();
    insertBSTNode(bst1, 2, createNewData(2));
    insertBSTNode(bst1, 1, createNewData(1));
    insertBSTNode(bst1, 3, createNewData(3));

    BST *bst2 = createNewBST();
    insertBSTNode(bst2, 6, createNewData(6));
    insertBSTNode(bst2, 5, createNewData(5));
    insertBSTNode(bst2, 3, createNewData(3));
    insertBSTNode(bst2, 4, createNewData(4));
    insertBSTNode(bst2, 9, createNewData(9));

    preOrderTraversal(bst);
    printf("\n");
    inOrderTraversal(bst);

    printf("\nHeight of the BST: %d\n", height(bst));

    BTNode *r1 = search(bst, 5);
    BTNode *r2 = search(bst, -3);

    if (r1) {
        printf("Found r1: %d\n", r1->key);
    }

    if (r2) {
        printf("Found r2: %d\n", r2->key);
    }

    Data *min = findMin(bst);
    Data *max = findMax(bst);

    if (min) {
        printf("Found min: %d\n", min->value);
    }

    if (max) {
        printf("Found max: %d\n", max->value);
    }

    deleteBSTNode(bst, 6);
    printf("\nAfter deleting 6:\n");
    inOrderTraversal(bst);

    deleteBSTNode(bst, 4);
    printf("\nAfter deleting 4:\n");
    inOrderTraversal(bst);

    deleteBSTNode(bst, 1);
    printf("\nAfter deleting 1:\n");
    inOrderTraversal(bst);

    BST *result = join(bst1, bst2);
    printf("\n");
    preOrderTraversal(result);
    printf("\n");
    inOrderTraversal(result);

    BST **splitResult = split(bst, 2);
    printf("\n");
    preOrderTraversal(splitResult[0]);
    printf("\n");
    inOrderTraversal(splitResult[0]);
    printf("\n");
    preOrderTraversal(splitResult[1]);
    printf("\n");
    inOrderTraversal(splitResult[1]);

    return 0;
}