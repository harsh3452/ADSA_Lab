#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key, height;
    struct Node *left, *right;
};

int height(struct Node *p)
{
    return p ? p->height : 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

struct Node *newNode(int key)
{
    struct Node *p = malloc(sizeof(struct Node));

    if (p == NULL)
        return NULL;

    p->key = key;
    p->height = 1;
    p->left = p->right = NULL;

    return p;
}

int balance(struct Node *p)
{
    return p ? height(p->left) - height(p->right) : 0;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node *insertItem(struct Node *root, int key)
{
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
        root->left = insertItem(root->left, key);
    else if (key > root->key)
        root->right = insertItem(root->right, key);
    else
        return root;

    root->height = 1 + max(height(root->left),
                            height(root->right));

    int b = balance(root);

    if (b > 1 && key < root->left->key)
        return rightRotate(root);              /* LL */

    if (b < -1 && key > root->right->key)
        return leftRotate(root);               /* RR */

    if (b > 1 && key > root->left->key) {      /* LR */
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && key < root->right->key) {    /* RL */
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node *minNode(struct Node *root)
{
    struct Node *p = root;

    while (p->left != NULL)
        p = p->left;

    return p;
}

struct Node *deleteItem(struct Node *root, int key)
{
    if (root == NULL)
        return NULL;

    if (key < root->key)
        root->left = deleteItem(root->left, key);

    else if (key > root->key)
        root->right = deleteItem(root->right, key);

    else {
        if (root->left == NULL || root->right == NULL) {
            struct Node *child;

            child = root->left ? root->left : root->right;

            if (child == NULL) {
                free(root);
                return NULL;
            }

            *root = *child;
            free(child);
        }
        else {
            struct Node *p = minNode(root->right);

            root->key = p->key;
            root->right = deleteItem(root->right, p->key);
        }
    }

    root->height = 1 + max(height(root->left),
                            height(root->right));

    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0)
        return rightRotate(root);              /* LL */

    if (b > 1 && balance(root->left) < 0) {    /* LR */
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && balance(root->right) <= 0)
        return leftRotate(root);               /* RR */

    if (b < -1 && balance(root->right) > 0) {  /* RL */
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node *searchItem(struct Node *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchItem(root->left, key);

    return searchItem(root->right, key);
}

void deleteTree(struct Node *root)
{
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

struct Node *createTree()
{
    return NULL;
}

void inorder(struct Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

int main()
{
    struct Node *root = createTree();
    int n, x;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Invalid input\n");
        return 0;
    }

    printf("Enter elements: ");

    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insertItem(root, x);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Enter element to search: ");
    scanf("%d", &x);

    if (searchItem(root, x))
        printf("Element found\n");
    else
        printf("Element not found\n");

    printf("Enter element to delete: ");
    scanf("%d", &x);

    root = deleteItem(root, x);

    printf("After deletion: ");
    inorder(root);
    printf("\n");

    deleteTree(root);

    return 0;
}