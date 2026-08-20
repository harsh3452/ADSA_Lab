#include <stdio.h>
#include <stdbool.h>
void infixToPostfix(char* infix); 
char stack[15];
int top = -1;
bool isEmpty(){
    if(top<=-1){
        return true;
    } else {
        return false;
    }
}
int pop(){
    if(top<=-1){
        return -1;
    } else {
        return stack[top--];
    }
}
void push(int element){
        stack[++top] = element;
}
int peek(){
    if(top<=-1){
        return -1;
    } else { 
        return stack[top];
    }
}
int getPrecedence(char ch){
    if(ch == '*' || ch == '/' ) return 2;
    else if(ch == '+' || ch == '-') return 1;
        
}
int main()
{
    char expression[] = "(23-8)*3+28/4";
    infixToPostfix(expression);
    return 0;
}
void infixToPostfix(char e[]){
    while(*e != '\0'){
        if(*e == '('){
            push(*e);
        }
        else if(*e == ')'){
            while(!isEmpty() && peek() != '('){
                printf("%c",pop());
            }
            if(!isEmpty() && peek() == '('){
                pop();   // remove '('
            }   
        }
        else if(*e == '*' || *e == '/' || *e == '+' || *e == '-'){
            while(isEmpty() == false && getPrecedence(*e) <= getPrecedence(peek())){
                printf("%c",pop());
            }
            push(*e); // push the latest element
        }
        else {
            printf("%c",*e);
        }
        e++;
    }
    while(isEmpty()==false){
        printf("%c",pop());
        e++;
    }
}
