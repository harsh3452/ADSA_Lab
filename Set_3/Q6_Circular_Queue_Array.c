#include <stdio.h>

#define SIZE 5

int q[SIZE];
int front = -1, rear = -1;

void enqueue(int x)
{
    if ((rear + 1) % SIZE == front) {
        printf("Queue Overflow\n");
        return;
    }

    if (front == -1)
        front = 0;

    rear = (rear + 1) % SIZE;
    q[rear] = x;
}

void dequeue()
{
    if (front == -1) {
        printf("Queue Underflow\n");
        return;
    }

    printf("Deleted: %d\n", q[front]);

    if (front == rear)
        front = rear = -1;
    else
        front = (front + 1) % SIZE;
}

void display()
{
    if (front == -1) {
        printf("Queue is empty\n");
        return;
    }

    int i = front;

    do {
        printf("%d ", q[i]);
        i = (i + 1) % SIZE;
    } while (i != (rear + 1) % SIZE);

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