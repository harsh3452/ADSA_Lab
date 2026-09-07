#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int x)
{
    struct Node *p = malloc(sizeof(struct Node));

    if (p == NULL)
        return NULL;

    p->data = x;
    p->left = p->right = NULL;

    return p;
}

void preorder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Node *stack[100];
    int top = -1;

    stack[++top] = root;

    while (top != -1)
    {
        struct Node *p = stack[top--];

        printf("%d ", p->data);

        // Push right first
        if (p->right != NULL)
            stack[++top] = p->right;

        // Push left second
        if (p->left != NULL)
            stack[++top] = p->left;
    }
}

int main()
{
    struct Node *root = newNode(1);

    root->left = newNode(2);
    root->right = newNode(3);

    root->left->left = newNode(4);
    root->left->right = newNode(5);

    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Preorder: ");
    preorder(root);

    return 0;
}