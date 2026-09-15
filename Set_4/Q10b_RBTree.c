#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct Node
{
    int key;
    int color;

    struct Node *left;
    struct Node *right;
    struct Node *parent;

} Node;

Node *root = NULL;


/* Create a new node */
Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->key = key;
    newNode->color = RED;

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}


/* Create an empty tree */
void createTree()
{
    root = NULL;
}


/* Left Rotation */
void leftRotate(Node *x)
{
    Node *y = x->right;

    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;

    else if (x == x->parent->left)
        x->parent->left = y;

    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}


/* Right Rotation */
void rightRotate(Node *x)
{
    Node *y = x->left;

    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;

    else if (x == x->parent->left)
        x->parent->left = y;

    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}


/* Fix Red-Black violations after insertion */
void fixInsertion(Node *z)
{
    while (z != root && z->parent->color == RED)
    {
        Node *parent = z->parent;
        Node *grandparent = parent->parent;

        /* Parent is left child */
        if (parent == grandparent->left)
        {
            Node *uncle = grandparent->right;

            /* Case 1: Uncle is RED */
            if (uncle != NULL && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                z = grandparent;
            }

            else
            {
                /* Case 2: LR */
                if (z == parent->right)
                {
                    z = parent;
                    leftRotate(z);

                    parent = z->parent;
                    grandparent = parent->parent;
                }

                /* Case 3: LL */
                parent->color = BLACK;
                grandparent->color = RED;

                rightRotate(grandparent);
            }
        }

        /* Parent is right child */
        else
        {
            Node *uncle = grandparent->left;

            /* Case 1: Uncle is RED */
            if (uncle != NULL && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                z = grandparent;
            }

            else
            {
                /* Case 2: RL */
                if (z == parent->left)
                {
                    z = parent;
                    rightRotate(z);

                    parent = z->parent;
                    grandparent = parent->parent;
                }

                /* Case 3: RR */
                parent->color = BLACK;
                grandparent->color = RED;

                leftRotate(grandparent);
            }
        }
    }

    root->color = BLACK;
}


/* Insert an item */
void insertItem(int key)
{
    Node *newNode = createNode(key);
    Node *parent = NULL;
    Node *current = root;

    /* Normal BST insertion */
    while (current != NULL)
    {
        parent = current;

        if (key < current->key)
            current = current->left;

        else
            current = current->right;
    }

    newNode->parent = parent;

    if (parent == NULL)
        root = newNode;

    else if (key < parent->key)
        parent->left = newNode;

    else
        parent->right = newNode;

    /* Fix Red-Black Tree */
    fixInsertion(newNode);
}


/* Search for an item */
int searchItem(int key)
{
    Node *current = root;

    while (current != NULL)
    {
        if (key == current->key)
            return 1;

        if (key < current->key)
            current = current->left;

        else
            current = current->right;
    }

    return 0;
}


/* Replace subtree u with subtree v */
void transplant(Node *u, Node *v)
{
    if (u->parent == NULL)
        root = v;

    else if (u == u->parent->left)
        u->parent->left = v;

    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}


/* Find minimum node */
Node *minimum(Node *node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}


/* Fix Red-Black violations after deletion */
void fixDeletion(Node *x, Node *parent)
{
    while (x != root &&
           (x == NULL || x->color == BLACK))
    {
        if (x == parent->left)
        {
            Node *sibling = parent->right;

            /* Sibling is RED */
            if (sibling != NULL &&
                sibling->color == RED)
            {
                sibling->color = BLACK;
                parent->color = RED;

                leftRotate(parent);

                sibling = parent->right;
            }

            /* Both sibling children are BLACK */
            if (sibling == NULL ||
                ((sibling->left == NULL ||
                  sibling->left->color == BLACK) &&
                 (sibling->right == NULL ||
                  sibling->right->color == BLACK)))
            {
                if (sibling != NULL)
                    sibling->color = RED;

                x = parent;
                parent = x->parent;
            }

            else
            {
                /* Sibling's right child is BLACK */
                if (sibling->right == NULL ||
                    sibling->right->color == BLACK)
                {
                    if (sibling->left != NULL)
                        sibling->left->color = BLACK;

                    sibling->color = RED;

                    rightRotate(sibling);

                    sibling = parent->right;
                }

                /* Final case */
                sibling->color = parent->color;
                parent->color = BLACK;

                if (sibling->right != NULL)
                    sibling->right->color = BLACK;

                leftRotate(parent);

                x = root;
                parent = NULL;
            }
        }

        else
        {
            Node *sibling = parent->left;

            /* Sibling is RED */
            if (sibling != NULL &&
                sibling->color == RED)
            {
                sibling->color = BLACK;
                parent->color = RED;

                rightRotate(parent);

                sibling = parent->left;
            }

            /* Both sibling children are BLACK */
            if (sibling == NULL ||
                ((sibling->left == NULL ||
                  sibling->left->color == BLACK) &&
                 (sibling->right == NULL ||
                  sibling->right->color == BLACK)))
            {
                if (sibling != NULL)
                    sibling->color = RED;

                x = parent;
                parent = x->parent;
            }

            else
            {
                /* Sibling's left child is BLACK */
                if (sibling->left == NULL ||
                    sibling->left->color == BLACK)
                {
                    if (sibling->right != NULL)
                        sibling->right->color = BLACK;

                    sibling->color = RED;

                    leftRotate(sibling);

                    sibling = parent->left;
                }

                /* Final case */
                sibling->color = parent->color;
                parent->color = BLACK;

                if (sibling->left != NULL)
                    sibling->left->color = BLACK;

                rightRotate(parent);

                x = root;
                parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = BLACK;
}


/* Delete an item */
void deleteItem(int key)
{
    Node *z = root;

    /* Search for node */
    while (z != NULL)
    {
        if (key == z->key)
            break;

        if (key < z->key)
            z = z->left;

        else
            z = z->right;
    }

    if (z == NULL)
        return;

    Node *y = z;
    Node *x;
    Node *parent;
    int originalColor = y->color;

    /* No left child */
    if (z->left == NULL)
    {
        x = z->right;
        parent = z->parent;

        transplant(z, z->right);
    }

    /* No right child */
    else if (z->right == NULL)
    {
        x = z->left;
        parent = z->parent;

        transplant(z, z->left);
    }

    /* Two children */
    else
    {
        y = minimum(z->right);

        originalColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            parent = y;

            if (x != NULL)
                x->parent = y;
        }

        else
        {
            parent = y->parent;

            transplant(y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    /* Fix if a BLACK node was removed */
    if (originalColor == BLACK)
        fixDeletion(x, parent);
}


/* Inorder traversal */
void inorder(Node *node)
{
    if (node == NULL)
        return;

    inorder(node->left);

    printf("%d(%c) ", node->key,
           node->color == RED ? 'R' : 'B');

    inorder(node->right);
}


/* Delete complete tree */
void freeTree(Node *node)
{
    if (node == NULL)
        return;

    freeTree(node->left);
    freeTree(node->right);

    free(node);
}


void deleteTree()
{
    freeTree(root);
    root = NULL;
}


/* Main function */
int main()
{
    int choice, key;

    createTree();

    while (1)
    {
        printf("\n\n--- RED BLACK TREE ---\n");
        printf("1. Insert\n");
        printf("2. Delete Item\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Delete Tree\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);

                insertItem(key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);

                deleteItem(key);
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);

                if (searchItem(key))
                    printf("Key found\n");
                else
                    printf("Key not found\n");

                break;

            case 4:
                printf("Inorder traversal:\n");
                inorder(root);
                printf("\n");
                break;

            case 5:
                deleteTree();
                printf("Tree deleted\n");
                break;

            case 6:
                deleteTree();
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}