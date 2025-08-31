#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{

    char *charArray;
    int size;
    int top;

} charStack;

charStack *initStack(int size);
bool isFull(charStack *S);
bool isEmpty(charStack *S);
void push(charStack *S, char elem);
char pop(charStack *S);
char peek(charStack *S);
void printStack(charStack S);

int main()
{

    charStack* C = initStack(5);
    push(C, 'a');
    push(C, 'b');
    push(C, 'c');
    push(C, 'd');
    push(C, 'e');
    push(C, 'f'); // This will print "Stack is full!"
    printStack(*C);
    printf("\n");
    printf("%c\n", pop(C));
    printf("%c\n", pop(C));
    printf("%c\n", pop(C));
    printf("%c\n", pop(C));
    printf("%c\n", pop(C));

        return 0;
}

charStack *initStack(int size)
{

    charStack *S = malloc(sizeof(charStack));
    S->size = size;
    S->charArray = (char *)malloc(sizeof(char) * S->size);
    S->top = 0;

    return S;
}

bool isFull(charStack *S)
{

    return S->size == S->top;
}

bool isEmpty(charStack *S){
    return S -> top == 0;

}

void push(charStack *S, char elem)
{

    if (isFull(S))
    {
        printf("Stack is full!\n");
    }
    else
    {

        S->charArray[S->top++] = elem;
    }
}

char pop(charStack *S)
{

    if (isEmpty(S))
    {
        printf("Stack is empty!\n");
    }
    else
    {

        return S->charArray[--S->top];
    }
}
char peek(charStack *S)
{

    if (isEmpty(S))
    {
        printf("Stack is empty!");
    }
    else
    {

        return S->charArray[S->top];
    }
}

void printStack(charStack S)
{

    if (isEmpty(&S))
    {
        printf("Stack is empty!");
    }
    else
    {

        for (int ndx = 0; ndx < S.top; ndx++)
            printf("%c ", S.charArray[ndx]);
    }
}
