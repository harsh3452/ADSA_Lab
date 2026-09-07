#include <stdio.h>

#define SIZE 100

int s1[SIZE], s2[SIZE];
int top1 = -1, top2 = -1;

void push1(int x)
{
    s1[++top1] = x;
}

int pop1()
{
    return s1[top1--];
}

void push2(int x)
{
    s2[++top2] = x;
}

int pop2()
{
    return s2[top2--];
}

void enqueue(int x)
{
    push1(x);
}

void dequeue()
{
    if (top1 == -1) {
        printf("Queue Underflow\n");
        return;
    }

    while (top1 != 0)
        push2(pop1());

    printf("Deleted: %d\n", pop1());

    while (top2 != -1)
        push1(pop2());
}

void display()
{
    if (top1 == -1) {
        printf("Queue is empty\n");
        return;
    }

    for (int i = top1; i >= 0; i--)
        printf("%d ", s1[i]);

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    dequeue();

    display();

    return 0;
}