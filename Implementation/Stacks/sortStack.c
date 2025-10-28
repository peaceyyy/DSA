#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct
{
    int elems[MAX];
    int top;

} Stack;


void initStack(Stack** S)
{

    *S = (Stack*) malloc(sizeof(Stack));
    (*S)->top = 0;
}

bool isFull(Stack *S)
{

    return S->top == MAX;
}

bool isEmpty(Stack *S){
    return S -> top == 0;

}

void push(Stack *S, int elem)
{

    if (isFull(S))
    {
        printf("Stack is full!\n");
    }
    else
    {

        S->elems[S->top++] = elem;
    }
}

int pop(Stack *S)
{

    if (isEmpty(S))
    {
        printf("Stack is empty!\n");
    }
    else
    {

        return S->elems[--S->top];
    }
}
int peek(Stack *S)
{

    if (isEmpty(S))
    {
        printf("Stack is empty!");
    }
    else
    {

        return S->elems[S->top];
    }
}

void printStack(Stack S)
{

    if (isEmpty(&S))
    {
        printf("Stack is empty!");
    }
    else
    {

        for (int ndx = S.top - 1; ndx >= 0; ndx--)
            printf("%d ", S.elems[ndx]);
    }
}


void sortStack(Stack* S){

    // 1    ->    9     
    // 9          5            
    // 3          4
    // 5          3
    // 4          1
    
    Stack* tempStack;
    initStack(&tempStack);
    int temp = pop(S);

    while (!isEmpty(S) && peek(S) > temp){
        push(S, pop(tempStack));
    }  
} 

int main(){

    Stack* S;
    initStack(&S);

    // Push some test values
    push(S, 5);
    push(S, 1);
    push(S, 9);
    push(S, 3);
    push(S, 4);

    printf("Original stack: ");
    printf("\nTop: %d\n", S->top);
    printStack(*S);
    printf("\n");

    sortStack(S);

    printf("Sorted stack: ");
    printStack(*S);
    printf("\n");

    return 0;
}