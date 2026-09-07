#include <stdbool.h>
#include <stdio.h>

void infixToPostfix(char *infix);

char stack[15];
int top = -1;

bool isEmpty()
{
    if (top <= -1)
        return true;
    else
        return false;
}

char pop()
{
    if (top <= -1)
        return -1;
    else
        return stack[top--];
}

void push(char element)
{
    stack[++top] = element;
}

char peek()
{
    if (top <= -1)
        return -1;
    else
        return stack[top];
}

int getPrecedence(char ch)
{
    if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

void infixToPostfix(char *e)
{
    while (*e != '\0') {
        if (*e == '(') {
            push(*e);
        } else if (*e == ')') {
            while (!isEmpty() && peek() != '(') {
                printf("%c", pop());
            }

            if (!isEmpty() && peek() == '(') {
                pop();
            }
        } else if (*e == '*' || *e == '/' || *e == '+' || *e == '-') {
            while (!isEmpty() && peek() != '(' &&
                   getPrecedence(*e) <= getPrecedence(peek())) {
                printf("%c", pop());
            }

            push(*e);
        } else {
            printf("%c", *e);
        }

        e++;
    }

    while (!isEmpty()) {
        printf("%c", pop());
    }
    printf("\n");
}

int main()
{
    char expression[100];

    printf("Enter infix expression: ");
    scanf(" %[^\n]", expression);
    printf("Postfix expression: ");
    infixToPostfix(expression);

    return 0;
}