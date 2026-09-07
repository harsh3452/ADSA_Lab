#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *rear = NULL;

void enqueue(int x)
{
    struct Node *p = malloc(sizeof(struct Node));

    if (p == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    p->data = x;

    if (rear == NULL) {
        rear = p;
        p->next = rear;
    }
    else {
        p->next = rear->next;
        rear->next = p;
        rear = p;
    }
}

void dequeue()
{
    if (rear == NULL) {
        printf("Queue Underflow\n");
        return;
    }

    struct Node *front = rear->next;

    printf("Deleted: %d\n", front->data);

    if (front == rear)
        rear = NULL;
    else
        rear->next = front->next;

    free(front);
}

void display()
{
    if (rear == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct Node *p = rear->next;

    do {
        printf("%d ", p->data);
        p = p->next;
    } while (p != rear->next);

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    dequeue();
    dequeue();

    enqueue(50);
    enqueue(60);

    display();

    return 0;
}