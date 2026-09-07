#include <stdio.h>

#define SIZE 100

int q1[SIZE], q2[SIZE];
int f1 = 0, r1 = -1;
int f2 = 0, r2 = -1;

void enqueue1(int x)
{
    q1[++r1] = x;
}

int dequeue1()
{
    return q1[f1++];
}

void enqueue2(int x)
{
    q2[++r2] = x;
}

int dequeue2()
{
    return q2[f2++];
}

void push(int x)
{
    enqueue1(x);
}

void pop()
{
    if (f1 > r1) {
        printf("Stack Underflow\n");
        return;
    }

    while (f1 < r1)
        enqueue2(dequeue1());

    printf("Popped: %d\n", dequeue1());

    while (f2 <= r2)
        enqueue1(dequeue2());

    f2 = 0;
    r2 = -1;
}

void display()
{
    if (f1 > r1) {
        printf("Stack is empty\n");
        return;
    }

    for (int i = r1; i >= f1; i--)
        printf("%d ", q1[i]);

    printf("\n");
}

int main()
{
    push(10);
    push(20);
    push(30);

    display();

    pop();

    display();

    return 0;
}