#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

int values[MAX];
char operators[MAX];

int vtop = -1;
int top = -1;

void pushValue(int value)
{
    values[++vtop] = value;
}

int popValue()
{
    return values[vtop--];
}

void pushOp(char op)
{
    operators[++top] = op;
}

char popOp()
{
    return operators[top--];
}

char peekOp()
{
    return operators[top];
}

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

int applyOp()
{
    int first, second;
    char operation;

    operation = popOp();

    second = popValue();
    first = popValue();

    switch (operation) {
    case '+':
        return first + second;

    case '-':
        return first - second;

    case '*':
        return first * second;

    case '/':
        return first / second;
    }

    return 0;
}

int evaluate(char *expression)
{
    int i = 0;
    int number;

    while (expression[i] != '\0') {
        if (expression[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(expression[i])) {
            number = 0;

            while (isdigit(expression[i])) {
                number = number * 10 + expression[i] - '0';
                i++;
            }

            pushValue(number);
            continue;
        }

        if (expression[i] == '(') {
            pushOp(expression[i]);
        } else if (expression[i] == ')') {
            while (peekOp() != '(') {
                pushValue(applyOp());
            }

            popOp();
        } else {
            while (top != -1 && peekOp() != '(' &&
                   precedence(peekOp()) >= precedence(expression[i])) {
                pushValue(applyOp());
            }

            pushOp(expression[i]);
        }

        i++;
    }

    while (top != -1) {
        pushValue(applyOp());
    }

    return popValue();
}

int main(int argc, char *argv[])
{
    char expression[MAX] = "";

    if (argc < 2) {
        printf("Wrong Input\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        strcat(expression, argv[i]);
    }

    printf("%d\n", evaluate(expression));

    return 0;
}