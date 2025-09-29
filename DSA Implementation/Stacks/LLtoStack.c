#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct Node
{

    int elem;
    struct Node *link;
} *node_t;

typedef struct
{
    int elems[MAX];
    int top;
} Stack;

void initStack(Stack **S)
{
    *S = (Stack *)malloc(sizeof(Stack));
    (*S)->top = -1;
}

bool isEmpty(Stack *S)
{
    return S->top == -1;
}

bool isFull(Stack *S)
{
    return S->top == MAX - 1;
}

void push(Stack *S, int data)
{
    if (!isFull(S))
    {
        S->elems[++S->top] = data;
    }
}

int pop(Stack *S)
{
    if (!isEmpty(S))
    {
        return S->elems[S->top--];
    }
    return -1; // sentinel value
}

int peek(Stack *S)
{
    if (!isEmpty(S))
    {
        return S->elems[S->top];
    }
    return -1; // sentinel value
}

void displayStack(Stack *S)
{
    for (int i = S->top; i >= 0; i--)
    {
        printf("%d ", S->elems[i]);
    }
    printf("\n");
}

// --------- LL Functions

void initLL(node_t *head)
{
    *head = NULL;
}

node_t createNode(int elem)
{
    node_t newNode = (node_t)malloc(sizeof(struct Node));
    newNode->elem = elem;
    newNode->link = NULL;

    return newNode;
}

void insertFirst(node_t *head, int elem)
{
    node_t newNode = createNode(elem);

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {

        newNode->link = *head;
        *head = newNode;
    }
}
void insertLast(node_t *head, int elem)
{
    node_t newNode = createNode(elem);

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {

        node_t *trav;

        for (trav = head; *trav != NULL; trav = &(*trav)->link)
        {
        }
        *trav = newNode;
    }
}
void displayLinkedList(node_t *head)
{

    node_t *trav;

    for (trav = head; *trav != NULL; trav = &(*trav)->link)
    {
        printf("%d -> ", (*trav)->elem);
    }
}


Stack* LLToStack (node_t *head){

    Stack* S;
    initStack(&S);

    //traverse the linked list
    node_t* trav;
    for (trav = head; *trav != NULL; trav = &(*trav)->link){
        push(S, (*trav)->elem);
    }

    return S; 
}

int main()
{
    node_t head;
    initLL(&head);
    insertFirst(&head, 5);
    insertFirst(&head, 2);
    insertFirst(&head, 8);
    insertLast(&head, 38);
    insertFirst(&head, 1);
    insertFirst(&head, 9);
    displayLinkedList(&head);

    Stack* LLTurnedStack = LLToStack(&head); 
    
    printf("\n\n");
    displayStack(LLTurnedStack);

    return 0;
}