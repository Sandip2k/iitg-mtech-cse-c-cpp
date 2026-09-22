#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

// ! Assuming the keys are distinct.

BTree *create(int order) {
    BTree *btree = (BTree *) malloc(sizeof(BTree));
    btree->order = order;
    btree->root = NULL;
    return btree;
}

static void traverseHelper(BTreeNode *node) {
    if (!node) {
        return;
    }

    for (int i = 0; i < node->numKeys; ++i) {
        printf("%d ", node->keys[i]);
    }
    printf("\n");

    for (int i = 0; i <= node->numKeys; ++i) {
        traverseHelper(node->children[i]);
    }
}

static void splitChild(BTreeNode *parent, int childIndex, int order) {
    BTreeNode *fullChild = parent->children[childIndex];
    BTreeNode *rightChild = createNewNode(order, fullChild->isLeaf);
    int medianIndex = order - 1;

    // Move the keys and children after the median into the new right child.
    rightChild->numKeys = order - 1;
    for (int i = 0; i < order - 1; ++i) {
        rightChild->keys[i] = fullChild->keys[medianIndex + 1 + i];
    }

    if (!fullChild->isLeaf) {
        // Full child gets reused as the left child, new creation is skipped.
        for (int i = 0; i < order; ++i) {
            rightChild->children[i] = fullChild->children[medianIndex + 1 + i];
            fullChild->children[medianIndex + 1 + i] = NULL;
        }
    }

    // Make room for the new child pointer next to the promoted median.
    int oldKeyCount = parent->numKeys;
    for (int i = oldKeyCount; i >= childIndex + 1; --i) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[childIndex + 1] = rightChild;

    // Promote the median and keep both resulting children ordered around it.
    for (int i = oldKeyCount - 1; i >= childIndex; --i) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[childIndex] = fullChild->keys[medianIndex];
    parent->numKeys++;
    fullChild->numKeys = order - 1;
}

static void insertNonFull(BTreeNode *node, int key, int order) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        // Insertion case 1: the target node is a non-full leaf.
        // Shift larger keys right and insert the new key in sorted order.
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
        return;
    }

    // Select the child whose key range contains the new key.
    while (i >= 0 && node->keys[i] > key) {
        --i;
    }
    ++i;

    int maxKeys = 2 * order - 1;
    if (node->children[i]->numKeys == maxKeys) {
        // Insertion case 2: split a full child before descending into it.
        splitChild(node, i, order);
        if (key > node->keys[i]) {
            ++i;
        }
    }
    insertNonFull(node->children[i], key, order);
}

void insertKey(BTree *btree, int key) {
    // Insertion case 0: an empty tree gets a leaf root containing the first key.
    if (!btree->root) {
        btree->root = createNewNode(btree->order, 1);
        btree->root->keys[0] = key;
        btree->root->numKeys = 1;
        return;
    }

    int maxKeys = 2 * btree->order - 1;
    if (btree->root->numKeys == maxKeys) {
        // Insertion case 3: split a full root, increasing the tree height.
        BTreeNode *newRoot = createNewNode(btree->order, 0);
        newRoot->children[0] = btree->root;
        btree->root = newRoot;
        splitChild(newRoot, 0, btree->order);
    }

    insertNonFull(btree->root, key, btree->order);
}

static void freeSingleNode(BTreeNode *node) {
    free(node->keys);
    free(node->children);
    free(node);
}

static int predecessor(BTreeNode *node) {
    while (!node->isLeaf) {
        node = node->children[node->numKeys];
    }
    return node->keys[node->numKeys - 1];
}

static int successor(BTreeNode *node) {
    while (!node->isLeaf) {
        node = node->children[0];
    }
    return node->keys[0];
}

static void borrowFromPrevious(BTreeNode *parent, int childIndex) {
    BTreeNode *child = parent->children[childIndex];
    BTreeNode *sibling = parent->children[childIndex - 1];

    for (int i = child->numKeys - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
        child->children[0] = sibling->children[sibling->numKeys];
        sibling->children[sibling->numKeys] = NULL;
    }

    child->keys[0] = parent->keys[childIndex - 1];
    parent->keys[childIndex - 1] = sibling->keys[sibling->numKeys - 1];
    child->numKeys++;
    sibling->numKeys--;
}

static void borrowFromNext(BTreeNode *parent, int childIndex) {
    BTreeNode *child = parent->children[childIndex];
    BTreeNode *sibling = parent->children[childIndex + 1];

    child->keys[child->numKeys] = parent->keys[childIndex];
    parent->keys[childIndex] = sibling->keys[0];
    if (!child->isLeaf) {
        child->children[child->numKeys + 1] = sibling->children[0];
        for (int i = 0; i < sibling->numKeys; ++i) {
            sibling->children[i] = sibling->children[i + 1];
        }
        sibling->children[sibling->numKeys] = NULL;
    }

    for (int i = 1; i < sibling->numKeys; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    child->numKeys++;
    sibling->numKeys--;
}

static void mergeChildren(BTreeNode *parent, int childIndex, int order) {
    BTreeNode *left = parent->children[childIndex];
    BTreeNode *right = parent->children[childIndex + 1];
    int leftKeyCount = left->numKeys;

    left->keys[leftKeyCount] = parent->keys[childIndex];
    for (int i = 0; i < right->numKeys; ++i) {
        left->keys[leftKeyCount + 1 + i] = right->keys[i];
    }

    if (!left->isLeaf) {
        for (int i = 0; i <= right->numKeys; ++i) {
            left->children[leftKeyCount + 1 + i] = right->children[i];
        }
    }
    left->numKeys += right->numKeys + 1;

    for (int i = childIndex + 1; i < parent->numKeys; ++i) {
        parent->keys[i - 1] = parent->keys[i];
        parent->children[i] = parent->children[i + 1];
    }
    parent->children[parent->numKeys] = NULL;
    parent->numKeys--;
    freeSingleNode(right);
    (void)order;
}

static void deleteFromNode(BTreeNode *node, int key, int order) {
    int i = 0;
    while (i < node->numKeys && node->keys[i] < key) {
        ++i;
    }

    if (i < node->numKeys && node->keys[i] == key) {
        if (node->isLeaf) {
            // Deletion case 1: remove the key directly from a leaf.
            for (int j = i + 1; j < node->numKeys; ++j) {
                node->keys[j - 1] = node->keys[j];
            }
            node->numKeys--;
            return;
        }

        BTreeNode *left = node->children[i];
        BTreeNode *right = node->children[i + 1];
        if (left->numKeys >= order) {
            // Deletion case 2a: replace with the predecessor.
            int replacement = predecessor(left);
            node->keys[i] = replacement;
            deleteFromNode(left, replacement, order);
        } else if (right->numKeys >= order) {
            // Deletion case 2b: replace with the successor.
            int replacement = successor(right);
            node->keys[i] = replacement;
            deleteFromNode(right, replacement, order);
        } else {
            // Deletion case 2c: merge both children with the separating key.
            mergeChildren(node, i, order);
            deleteFromNode(left, key, order);
        }
        return;
    }

    if (node->isLeaf) {
        return;
    }

    BTreeNode *child = node->children[i];
    if (child->numKeys == order - 1) {
        // Deletion case 3: ensure the child has a key available before descent.
        if (i > 0 && node->children[i - 1]->numKeys >= order) {
            borrowFromPrevious(node, i);
        } else if (i < node->numKeys && node->children[i + 1]->numKeys >= order) {
            borrowFromNext(node, i);
        } else if (i < node->numKeys) {
            mergeChildren(node, i, order);
        } else {
            mergeChildren(node, i - 1, order);
            --i;
        }
        child = node->children[i];
    }
    deleteFromNode(child, key, order);
}

void deleteKey(BTree *btree, int key) {
    if (!btree || !btree->root) {
        return;
    }

    deleteFromNode(btree->root, key, btree->order);

    // If the root lost its last key, remove it or promote its only child.
    if (!btree->root->numKeys) {
        BTreeNode *oldRoot = btree->root;
        btree->root = oldRoot->isLeaf ? NULL : oldRoot->children[0];
        if (!oldRoot->isLeaf) {
            oldRoot->children[0] = NULL;
        }
        freeSingleNode(oldRoot);
    }
}

BTreeNode *search(BTree *btree, int key) {
    if (!btree) {
        return NULL;
    }

    BTreeNode *curr = btree->root;
    while (curr) {
        int i = 0;
        while (i < curr->numKeys && curr->keys[i] < key) {
            i++;
        }

        if (i < curr->numKeys && curr->keys[i] == key) {
            return curr;
        }

        if (curr->isLeaf) {
            return NULL;
        }

        curr = curr->children[i];
    }
    return NULL;
}

void traverse(BTree *btree) {
    traverseHelper(btree->root);
}

int main() {
    int order = 2;
    BTree *btree = create(order);
    insertKey(btree, 5);
    insertKey(btree, 1);
    insertKey(btree, 2);
    insertKey(btree, 3);
    insertKey(btree, 10);
    insertKey(btree, 4);
    insertKey(btree, 8);
    insertKey(btree, 6);
    insertKey(btree, 7);

    traverse(btree);
    return 0;
}