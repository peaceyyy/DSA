#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 5

typedef struct
{
    char fname[30];
    char lname[30];
} Name;

typedef struct
{
    Name elems[MAX];
    int front;
    int rear;
} NQueue;

/**************************************/

/**************************************/
Name *filterNames(NQueue *nq, char *filterString);
bool insertSorted(NQueue *nq, Name n);

/**************************************/

/**************************************/
void initNQueue(NQueue *nq);
bool isEmpty(NQueue nq);
bool isFull(NQueue nq);
void displayQueue(NQueue nq);
bool enqueue(NQueue *nq, Name n);
bool dequeue(NQueue *nq);
Name front(NQueue nq);

int main()
{
    NQueue Q;
    int size;

    initNQueue(&Q);

    printf("Enter size: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        Name temp;
        printf("Enter first name: ");
        scanf(" %[^\n]", temp.fname);

        printf("Enter last name: ");
        scanf(" %[^\n]", temp.lname);
        printf("\n");

        if (!insertSorted(&Q, temp))
        {
            printf("Queue is FULL!\n\n");
        }+
    }

    printf("QUEUE:\n");
    displayQueue(Q);

    
    
    

    

    
    

    
    
    
    
    

    return 0;
}


Name *filterNames(NQueue *nq, char *filterString)
{
    Name *filteredNames[MAX];
}


bool insertSorted(NQueue *nq, Name n) {
    if (isFull(*nq)) return false;

    
    int count = (nq->rear - nq->front + MAX) % MAX;  
    int pos = 0;

    
    while (pos < count &&
           strcmp(n.lname, nq->elems[(nq->front + 1 + pos) % MAX].lname) > 0) {
        pos++;
    }

    
    for (int i = count; i > pos; i--) {
        nq->elems[(nq->front + 1 + i) % MAX] =
            nq->elems[(nq->front + i) % MAX];
    }

    
    nq->elems[(nq->front + 1 + pos) % MAX] = n;

    
    nq->rear = (nq->rear + 1) % MAX;

    return true;
}



void initNQueue(NQueue *nq)
{
    nq->front = 1;
    nq->rear = 0;
}

bool isEmpty(NQueue nq)
{
    return (nq.rear + 1) % MAX == nq.front ? true : false;
}

bool isFull(NQueue nq)
{
    return (nq.rear + 2) % MAX == nq.front ? true : false;
}

void displayQueue(NQueue nq)
{
    int stop = (nq.rear + 1) % MAX;

    while (nq.front != stop)
    {
        Name data = front(nq);
        printf("%s %s\n", data.fname, data.lname);

        dequeue(&nq);
                enqueue(&nq, data);
    }
}

bool enqueue(NQueue *nq, Name n)
{
    bool status = false;

    if (!isFull(*nq))
    {
        nq->rear = (nq->rear + 1) % MAX;
        nq->elems[nq->rear] = n;
        status = true;
    }

    return status;
}

bool dequeue(NQueue *nq)
{
    bool status = false;

    if (!isEmpty(*nq))
    {
        nq->front = (nq->front + 1) % MAX;
        status = true;
    }

    return status;
}

Name front(NQueue nq)
{
    Name def = {"XXXX", "XXXXX"};

    return (isEmpty(nq)) ? def : nq.elems[nq.front];
}