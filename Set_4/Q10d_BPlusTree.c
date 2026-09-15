#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

typedef struct Node
{
    int key[ORDER];
    struct Node *child[ORDER + 1];

    int n;
    int leaf;

    struct Node *next;
} Node;

Node *root = NULL;


/* Create a new node */
Node *createNode(int leaf)
{
    Node *p = (Node *)malloc(sizeof(Node));

    p->n = 0;
    p->leaf = leaf;
    p->next = NULL;

    for (int i = 0; i <= ORDER; i++)
        p->child[i] = NULL;

    return p;
}


/* Create an empty B+ Tree */
void createTree()
{
    root = NULL;
}


/* Return first key of a subtree */
int firstKey(Node *p)
{
    while (!p->leaf)
        p = p->child[0];

    return p->key[0];
}


/* Update separator keys */
void updateKeys(Node *p)
{
    if (p == NULL || p->leaf)
        return;

    for (int i = 0; i <= p->n; i++)
        updateKeys(p->child[i]);

    for (int i = 0; i < p->n; i++)
        p->key[i] = firstKey(p->child[i + 1]);
}


/* Search */
int searchItem(int key)
{
    Node *p = root;
    int i;

    if (p == NULL)
        return 0;

    while (!p->leaf)
    {
        i = 0;

        while (i < p->n && key >= p->key[i])
            i++;

        p = p->child[i];
    }

    for (i = 0; i < p->n; i++)
    {
        if (p->key[i] == key)
            return 1;
    }

    return 0;
}


/* Insert key into leaf */
void insertLeaf(Node *p, int key)
{
    int i = p->n - 1;

    while (i >= 0 && key < p->key[i])
    {
        p->key[i + 1] = p->key[i];
        i--;
    }

    p->key[i + 1] = key;
    p->n++;
}


/*
    Insert recursively.

    Returns 1 if the node was split.
    promoted = separator key
    newChild = newly created right node
*/
int insertRecursive(Node *p, int key,
                    int *promoted,
                    Node **newChild)
{
    int i, j;

    /* Leaf */
    if (p->leaf)
    {
        insertLeaf(p, key);

        if (p->n < ORDER)
            return 0;

        /* Split leaf */
        Node *right = createNode(1);

        int mid = ORDER / 2;

        right->n = p->n - mid;

        for (i = 0; i < right->n; i++)
            right->key[i] = p->key[mid + i];

        p->n = mid;

        right->next = p->next;
        p->next = right;

        *promoted = right->key[0];
        *newChild = right;

        return 1;
    }


    /* Find child */
    i = 0;

    while (i < p->n && key >= p->key[i])
        i++;


    /* Insert into child */
    int promo;
    Node *rightChild = NULL;

    if (!insertRecursive(p->child[i],
                         key,
                         &promo,
                         &rightChild))
    {
        return 0;
    }


    /* Insert promoted key */
    for (j = p->n; j > i; j--)
    {
        p->key[j] = p->key[j - 1];
        p->child[j + 1] = p->child[j];
    }

    p->key[i] = promo;
    p->child[i + 1] = rightChild;

    p->n++;


    /* Internal node overflow */
    if (p->n < ORDER)
        return 0;

    Node *right = createNode(0);

    int mid = ORDER / 2;

    *promoted = p->key[mid];

    right->n = p->n - mid - 1;

    for (j = 0; j < right->n; j++)
        right->key[j] = p->key[mid + 1 + j];

    for (j = 0; j <= right->n; j++)
        right->child[j] = p->child[mid + 1 + j];

    p->n = mid;

    *newChild = right;

    return 1;
}


/* Insert item */
void insertItem(int key)
{
    if (root == NULL)
    {
        root = createNode(1);
        root->key[0] = key;
        root->n = 1;
        return;
    }

    int promoted;
    Node *newChild = NULL;

    if (insertRecursive(root, key,
                        &promoted,
                        &newChild))
    {
        Node *newRoot = createNode(0);

        newRoot->key[0] = promoted;
        newRoot->child[0] = root;
        newRoot->child[1] = newChild;
        newRoot->n = 1;

        root = newRoot;
    }

    updateKeys(root);
}


/* Collect all keys from leaves */
void collectKeys(Node *p, int keys[], int *count)
{
    if (p == NULL)
        return;

    if (p->leaf)
    {
        for (int i = 0; i < p->n; i++)
            keys[(*count)++] = p->key[i];

        return;
    }

    for (int i = 0; i <= p->n; i++)
        collectKeys(p->child[i], keys, count);
}


/*
    Delete item.

    For a compact implementation, collect all keys,
    remove the required key, and rebuild the B+ Tree.
*/
void deleteItem(int key)
{
    if (!searchItem(key))
        return;

    int keys[100];
    int count = 0;

    collectKeys(root, keys, &count);

    /* Delete entire tree */
    void deleteTree();

    deleteTree();

    /* Rebuild without deleted key */
    for (int i = 0; i < count; i++)
    {
        if (keys[i] != key)
            insertItem(keys[i]);
    }
}


/* Free entire tree */
void freeTree(Node *p)
{
    if (p == NULL)
        return;

    if (!p->leaf)
    {
        for (int i = 0; i <= p->n; i++)
            freeTree(p->child[i]);
    }

    free(p);
}


/* Delete entire tree */
void deleteTree()
{
    freeTree(root);
    root = NULL;
}


/* Display leaf nodes */
void display()
{
    Node *p = root;

    if (p == NULL)
    {
        printf("Tree is empty\n");
        return;
    }

    while (!p->leaf)
        p = p->child[0];

    printf("B+ Tree: ");

    while (p != NULL)
    {
        for (int i = 0; i < p->n; i++)
            printf("%d ", p->key[i]);

        p = p->next;
    }

    printf("\n");
}


/* Main */
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

    printf("B+ Tree after insertion:\n");
    display();

    if (searchItem(12))
        printf("12 found\n");
    else
        printf("12 not found\n");

    deleteItem(12);

    printf("\nB+ Tree after deleting 12:\n");
    display();

    deleteTree();

    printf("\nTree deleted successfully\n");

    return 0;
}