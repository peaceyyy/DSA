#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{

    char data;
    struct Node *link;

} *node_t;

typedef struct
{
    node_t front;
    node_t rear;
} Queue;

void init(Queue *Q)
{
    Q->front = NULL;
    Q->rear = NULL;
}

node_t createNode(char data)
{

    node_t newNode = (node_t)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->link = NULL;

    return newNode;
}

bool isEmpty(Queue *Q)
{
    return Q->front == NULL;
}

void enqueue(Queue *Q, char data)
{

    node_t newNode = createNode(data);

    if (isEmpty(Q))
    {
        Q->front = newNode;
    }
    else
    {
        Q->rear->link = newNode;
    }

    Q->rear = newNode;
}

void dequeue(Queue *Q)
{
    if (isEmpty(Q))
    {
        printf("Queue is empty!");
    }
    else
    {
        node_t temp = Q->front;
        Q->front = Q->front->link;
        free(temp);
    }

    if (Q->front == NULL)
        Q->rear = NULL;
}

char front(Queue *Q)
{
    if (isEmpty(Q))
    {
        printf("Queue is empty!");
        return '\0';
    }
    return Q->front->data;
}

void emptyQueue(Queue *Q)
{

    while (!isEmpty(Q))
    {
        dequeue(Q);
    }
}

bool findElem(Queue *Q, char elem)
{

    node_t *trav;

    for (trav = &Q->front; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link)
    {
    };
    return (*trav != NULL) ? true : false;
}
void deleteElem(Queue *Q, char elem)
{
    node_t *trav;

    for (trav = &Q->front; *trav != NULL && (*trav)->data != elem; trav = &(*trav)->link)
    {
    };

    if (*trav != NULL)
    {
        node_t temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}

void displayQueue(Queue Q)
{

    if (isEmpty(&Q))
    {
        printf("Queue is empty!");
    }
    else
    {

        node_t trav = Q.front;

        while (trav != NULL)
        {
            printf("%c\n", trav->data);
            trav = trav->link;
        }
    }
}

int main()
{
    Queue Q1;
    init(&Q1);
    enqueue(&Q1, 'A');
    enqueue(&Q1, 'B');
    enqueue(&Q1, 'C');
    enqueue(&Q1, 'D');
    enqueue(&Q1, 'E');
    enqueue(&Q1, 'F');
    deleteElem(&Q1, 'D');

    displayQueue(Q1);
    emptyQueue(&Q1);
    printf("\n");
    displayQueue(Q1);
}