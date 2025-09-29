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
    int front;
    int rear;
} Queue;

// --------- Queue Functions

void initQueue(Queue **Q)
{
    *Q = (Queue *)malloc(sizeof(Queue));
    (*Q)->front = 1;
    (*Q)->rear = 0;
}

bool isQueueEmpty(Queue *Q)
{
    return (Q->rear + 1) % MAX == Q->front;
}

bool isQueueFull(Queue *Q)
{
    return (Q->rear + 2) % MAX == Q->front;
}

void enqueue(Queue *Q, int data)
{
    if (!isQueueFull(Q))
    {
        Q->rear = (Q->rear + 1) % MAX;
        Q->elems[Q->rear] = data;
    }
    else
    {
        printf("Queue has reached max capacity!");
    }
}

int dequeue(Queue *Q)
{
    if (!isQueueEmpty(Q))
    {
        int data = Q->elems[Q->front];
        Q->front = (Q->front + 1) % MAX;
        return data;
    }
    return -1; // sentinel value
}

int frontQueue(Queue *Q)
{
    if (!isQueueEmpty(Q))
    {
        return Q->elems[Q->front];
    }
    return -1; // sentinel value
}

void displayQueue(Queue *Q)
{
    if (isQueueEmpty(Q))
    {
        printf("Queue is empty\n");
        return;
    }

    int i = Q->front;
    while (i != (Q->rear + 1) % MAX)
    {
        printf("%d ", Q->elems[i]);
        i = (i + 1) % MAX;
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
    printf("NULL\n");
}



Queue *LLToQueue(node_t *head)
{

    Queue *Q;
    initQueue(&Q);

    node_t *trav;
    for (trav = head; *trav != NULL; trav = &(*trav)->link)
    {
        enqueue(Q, (*trav)->elem);
    }

    return Q;
}

node_t QueueToLL(Queue* Q)
{  

    node_t head;
    initLL(&head);

    int trav = Q->front;

    while (!isQueueEmpty(Q))
    {

        node_t newNode = createNode(dequeue(Q));
        node_t *travPtr;

        for (travPtr = &head; *travPtr != NULL; travPtr = &(*travPtr)->link)
        {
        }
        *travPtr = newNode;

       
    }

    return head; 
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

    printf("Original Linked List:\n");
    displayLinkedList(&head);

    Queue *LLTurnedQueue = LLToQueue(&head);

        printf("\nLL to Queue:\n");
        displayQueue(LLTurnedQueue);

    Queue *Q;
    initQueue(&Q);
    enqueue(Q, 10);
    enqueue(Q, 20);
    enqueue(Q, 30);
    enqueue(Q, 40);
    enqueue(Q, 50);

    printf("\nTest Queue:\n");
    displayQueue(Q);
    node_t QueueTurnedLL = QueueToLL(Q);

    printf("\nQueue to LL:\n");
    displayLinkedList(&QueueTurnedLL);

    return 0;
}