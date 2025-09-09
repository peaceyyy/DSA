// linkedListStack.h

#ifndef LINKEDLISTSTACK_H
#define ARRAYSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    char data;
    struct Node *link;

} *node_t, *Stack;

void init(Stack *top)
{
    printf("USING LINKED LIST IMPLEMENTATION!\n");
       printf("============================\n");
    *top = NULL;
}

struct Node *createNode(char data)
{

    node_t newNode = (node_t)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory Allocation failed for node!");
    }
    else
    {
        newNode->data = data;
        newNode->link = NULL;
        return newNode;
    }
}

bool isEmpty(Stack* S)
{
    return *S == NULL;
}

void push(Stack *S, char data) {
    node_t newNode = createNode(data);
    newNode->link = *S;
    *S = newNode;
}

void pop(Stack *S) {
    if (isEmpty(S)) {
        printf("Stack is empty!");
   
    } else {
        node_t temp = *S;
        *S = (*S)->link;
        free(temp);
    }
}

char top (Stack* S){
    if (isEmpty(S)){
        printf("Stack is empty!");
        return '\0';
    } else {
        return (*S)->data;
    }
}

void printStack(Stack *S)
{
    for (node_t* trav = S; *trav != NULL; trav = &(*trav)->link){
        printf("%c", (*trav)->data);
    }
}

bool findElem (Stack* S){}


void deleteElem(Stack *S, char elem)
{
    node_t *trav;
    for (trav = S; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link){}
    if (*trav != NULL)
    {
        node_t temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}


void emptyQueue (Stack* S){}
void makeNULL (Stack* S){}





#endif