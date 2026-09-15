#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode *child[2 * T];

    int n;       // number of keys
    int leaf;    // 1 = leaf, 0 = internal node
} BTreeNode;

BTreeNode *root = NULL;


/* ---------- CREATE TREE ---------- */

void createTree()
{
    root = NULL;
}


/* ---------- CREATE NODE ---------- */

BTreeNode* createNode(int leaf)
{
    BTreeNode *node;

    node = (BTreeNode*)malloc(sizeof(BTreeNode));

    node->n = 0;
    node->leaf = leaf;

    for (int i = 0; i < 2 * T; i++)
        node->child[i] = NULL;

    return node;
}


/* ---------- SEARCH ---------- */

int searchItem(BTreeNode *node, int key)
{
    int i = 0;

    if (node == NULL)
        return 0;

    while (i < node->n && key > node->keys[i])
        i++;

    if (i < node->n && key == node->keys[i])
        return 1;

    if (node->leaf)
        return 0;

    return searchItem(node->child[i], key);
}


/* ---------- SPLIT CHILD ---------- */

void splitChild(BTreeNode *parent, int i)
{
    BTreeNode *full = parent->child[i];
    BTreeNode *newNode = createNode(full->leaf);

    newNode->n = T - 1;

    /* Move last T-1 keys */
    for (int j = 0; j < T - 1; j++)
        newNode->keys[j] = full->keys[j + T];

    /* Move children if not leaf */
    if (!full->leaf)
    {
        for (int j = 0; j < T; j++)
            newNode->child[j] = full->child[j + T];
    }

    full->n = T - 1;

    /* Shift parent's children */
    for (int j = parent->n; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[i + 1] = newNode;

    /* Shift parent's keys */
    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = full->keys[T - 1];

    parent->n++;
}


/* ---------- INSERT INTO NON-FULL NODE ---------- */

void insertNonFull(BTreeNode *node, int key)
{
    int i = node->n - 1;

    if (node->leaf)
    {
        /* Shift keys to make space */
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->n++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        /* Child is full */
        if (node->child[i]->n == 2 * T - 1)
        {
            splitChild(node, i);

            if (key > node->keys[i])
                i++;
        }

        insertNonFull(node->child[i], key);
    }
}


/* ---------- INSERT ITEM ---------- */

void insertItem(int key)
{
    /* Empty tree */
    if (root == NULL)
    {
        root = createNode(1);

        root->keys[0] = key;
        root->n = 1;

        return;
    }

    /* Root is full */
    if (root->n == 2 * T - 1)
    {
        BTreeNode *newRoot = createNode(0);

        newRoot->child[0] = root;

        root = newRoot;

        splitChild(root, 0);

        int i = 0;

        if (key > root->keys[0])
            i++;

        insertNonFull(root->child[i], key);
    }
    else
    {
        insertNonFull(root, key);
    }
}


/* ---------- FIND PREDECESSOR ---------- */

int getPredecessor(BTreeNode *node)
{
    while (!node->leaf)
        node = node->child[node->n];

    return node->keys[node->n - 1];
}


/* ---------- FIND SUCCESSOR ---------- */

int getSuccessor(BTreeNode *node)
{
    while (!node->leaf)
        node = node->child[0];

    return node->keys[0];
}


/* ---------- MERGE CHILDREN ---------- */

void merge(BTreeNode *node, int index)
{
    BTreeNode *child1 = node->child[index];
    BTreeNode *child2 = node->child[index + 1];

    /* Bring parent key down */
    child1->keys[T - 1] = node->keys[index];

    /* Copy keys from child2 */
    for (int i = 0; i < child2->n; i++)
        child1->keys[i + T] = child2->keys[i];

    /* Copy children */
    if (!child1->leaf)
    {
        for (int i = 0; i <= child2->n; i++)
            child1->child[i + T] = child2->child[i];
    }

    child1->n += child2->n + 1;

    /* Shift parent keys */
    for (int i = index + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];

    /* Shift parent children */
    for (int i = index + 2; i <= node->n; i++)
        node->child[i - 1] = node->child[i];

    node->n--;

    free(child2);
}


/* ---------- BORROW FROM PREVIOUS ---------- */

void borrowFromPrevious(BTreeNode *node, int index)
{
    BTreeNode *child = node->child[index];
    BTreeNode *sibling = node->child[index - 1];

    /* Shift child keys */
    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    /* Shift children */
    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];

        child->child[0] = sibling->child[sibling->n];
    }

    child->keys[0] = node->keys[index - 1];

    node->keys[index - 1] =
        sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}


/* ---------- BORROW FROM NEXT ---------- */

void borrowFromNext(BTreeNode *node, int index)
{
    BTreeNode *child = node->child[index];
    BTreeNode *sibling = node->child[index + 1];

    child->keys[child->n] = node->keys[index];

    if (!child->leaf)
        child->child[child->n + 1] =
            sibling->child[0];

    node->keys[index] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] =
                sibling->child[i];
    }

    child->n++;
    sibling->n--;
}


/* ---------- FILL CHILD ---------- */

void fill(BTreeNode *node, int index)
{
    if (index != 0 &&
        node->child[index - 1]->n >= T)
    {
        borrowFromPrevious(node, index);
    }
    else if (index != node->n &&
             node->child[index + 1]->n >= T)
    {
        borrowFromNext(node, index);
    }
    else
    {
        if (index != node->n)
            merge(node, index);
        else
            merge(node, index - 1);
    }
}


/* ---------- DELETE FROM NODE ---------- */

void deleteFromNode(BTreeNode *node, int key)
{
    int index = 0;

    while (index < node->n &&
           node->keys[index] < key)
    {
        index++;
    }

    /* Key found */
    if (index < node->n &&
        node->keys[index] == key)
    {
        /* Case 1: Leaf */
        if (node->leaf)
        {
            for (int i = index + 1; i < node->n; i++)
                node->keys[i - 1] = node->keys[i];

            node->n--;
        }

        /* Case 2: Internal node */
        else
        {
            /*
             * Left child has enough keys
             */
            if (node->child[index]->n >= T)
            {
                int pred =
                    getPredecessor(node->child[index]);

                node->keys[index] = pred;

                deleteFromNode(
                    node->child[index],
                    pred
                );
            }

            /*
             * Right child has enough keys
             */
            else if (node->child[index + 1]->n >= T)
            {
                int succ =
                    getSuccessor(node->child[index + 1]);

                node->keys[index] = succ;

                deleteFromNode(
                    node->child[index + 1],
                    succ
                );
            }

            /*
             * Both children have T-1 keys
             */
            else
            {
                merge(node, index);

                deleteFromNode(
                    node->child[index],
                    key
                );
            }
        }
    }

    /* Key not found in this node */
    else
    {
        if (node->leaf)
            return;

        int lastChild = (index == node->n);

        /*
         * Child has minimum number of keys.
         * Fix it before going down.
         */
        if (node->child[index]->n < T)
            fill(node, index);

        if (lastChild && index > node->n)
            deleteFromNode(
                node->child[index - 1],
                key
            );
        else
            deleteFromNode(
                node->child[index],
                key
            );
    }
}


/* ---------- DELETE ITEM ---------- */

void deleteItem(int key)
{
    if (root == NULL)
        return;

    deleteFromNode(root, key);

    /*
     * Root has become empty.
     * Make its child the new root.
     */
    if (root->n == 0)
    {
        BTreeNode *oldRoot = root;

        if (root->leaf)
        {
            root = NULL;
        }
        else
        {
            root = root->child[0];
        }

        free(oldRoot);
    }
}


/* ---------- DELETE TREE ---------- */

void freeTree(BTreeNode *node)
{
    if (node == NULL)
        return;

    if (!node->leaf)
    {
        for (int i = 0; i <= node->n; i++)
            freeTree(node->child[i]);
    }

    free(node);
}


void deleteTree()
{
    freeTree(root);
    root = NULL;
}


/* ---------- TRAVERSAL ---------- */

void traverse(BTreeNode *node)
{
    if (node == NULL)
        return;

    int i;

    for (i = 0; i < node->n; i++)
    {
        if (!node->leaf)
            traverse(node->child[i]);

        printf("%d ", node->keys[i]);
    }

    if (!node->leaf)
        traverse(node->child[i]);
}


/* ---------- MAIN ---------- */

int main()
{
    createTree();

    insertItem(10);
    insertItem(20);
    insertItem(5);
    insertItem(6);
    insertItem(12);
    insertItem(30);
    insertItem(7);
    insertItem(17);

    printf("B-Tree after insertion:\n");
    traverse(root);

    printf("\n\n");

    if (searchItem(root, 12))
        printf("12 found\n");
    else
        printf("12 not found\n");

    deleteItem(12);

    printf("\nB-Tree after deleting 12:\n");
    traverse(root);

    deleteTree(root);
    root = NULL;

    printf("\nTree deleted successfully\n");

    return 0;
}