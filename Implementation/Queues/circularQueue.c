#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct
{
    char data[MAX];
    int front;
    int rear;

} *CircularQueue;

void initCQ(CircularQueue *CQ)
{
    *CQ = (CircularQueue)malloc(sizeof(CircularQueue));
    (*CQ)->front = 1;
    (*CQ)->rear = 0;
}

bool isEmpty(CircularQueue CQ)
{
    return (CQ->front == (CQ->rear + 1) % MAX);
}

bool isFull(CircularQueue CQ)
{

    return (CQ->front == (CQ->rear + 2) % MAX);
}

void enqueue(CircularQueue CQ, char elem)
{

    if (isFull(CQ))
    {
        printf("Queue is full!");
    }
    else
    {
        CQ->rear = (CQ->rear + 1) % MAX;
        CQ->data[CQ->rear] = elem;
    }
}

void dequeue(CircularQueue CQ)
{
    if (isEmpty(CQ))
    {
        printf("Queue is empty!");
    }
    else
    {
        CQ->front = (CQ->front + 1) % MAX;
    }
}

char front(CircularQueue CQ)
{
    return (!isEmpty(CQ)) ? CQ->data[CQ->front] : '\0';
}

void displayQueue(CircularQueue CQ)
{
    printf("\n");
    if (isEmpty(CQ))
    {
        printf("Queue is empty!");
    }
    else
    {
        for (int ndx = CQ->front; ndx != (CQ->rear + 1) % MAX; ndx = (ndx + 1) % MAX)
        {
            printf("%c", CQ->data[ndx]);
        }
    }
}

int main()
{

    CircularQueue CQ1;
    initCQ(&CQ1);
    enqueue(CQ1, 'A');
    enqueue(CQ1, 'B');
    enqueue(CQ1, 'C');
    enqueue(CQ1, 'D');
    displayQueue(CQ1);
    dequeue(CQ1);
    printf("\nThe front character is %c", front(CQ1));
    displayQueue(CQ1);
}
