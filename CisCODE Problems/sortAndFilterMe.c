/*



Sort and Filter me!!!
By Zeus Elderfield

DSA
You are tasked with completing a circular queue program that stores people’s names (first name and last name). The queue has limited capacity and supports basic operations like enqueue, dequeue, and display.

Your mission is to implement the following two functions:

1. filterNames(NQueue *nq, char *filterString)
- Removes all names from the queue that match the given last name (filterString).
- Returns the removed names in an array, ending with a sentinel element (both fname and lname as empty strings " ").
- If no names match, return only the sentinel.


2. insertSorted(NQueue *nq, Name n)
- Inserts a new name into the queue in sorted order by last name.
- Must directly manipulate the queue’s array structure (i.e., do not use enqueue, dequeue, or front).
- Should return false if the queue is already full.


When completed, the program should allow users to:
1. Enter names which are automatically sorted into the queue.
2. Display the queue.
3. Enter a last name to filter out matching entries, which are then listed separately.


Started September 18, 2025
Finished September 19, 2025 (1:10 AM)

*/

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
        }
    }

    printf("QUEUE:\n");
    displayQueue(Q);


        char remove[100];
    printf("\nEnter last name to filter from queue: ");
    scanf(" %[^\n]", remove);

    Name *f = filterNames(&Q, remove);

    printf("\nQUEUE:\n");
    displayQueue(Q);

    printf("\nFILTERED NAMES:\n");
    for(int i = 0; strcmp(f[i].lname, "END") != 0; i++) {
        printf("%s %s\n", f[i].fname, f[i].lname);
    }

    return 0;

}

/*Removes the names that matches the filterString to the lastname.
  Returns the removed names. Use the concept of adding a sentinel
  at the end indicating the last item in list as empty strings for
  fname and lname. If there are no names that will match then the
  function should return the sentinel.*/
Name *filterNames(NQueue *nq, char *filterString)
{

    Name sentinelName = {"END", "END"};
    Name* filteredNameArray = malloc(sizeof(Name) * MAX);
  
    

    int x = nq->front;
    int filteredNameCount = 0;
    while (x != (nq->rear + 1) % MAX)
    {

        if (strcmp(nq->elems[x].lname, filterString) == 0)
        {
            filteredNameArray [filteredNameCount++] = nq->elems[x];

            for (int y = x; y != (nq->rear + 1) % MAX; y = (y + 1) % MAX)
            {
                nq->elems[(y)] = nq->elems[(y + 1) % MAX];
            }

            nq->rear = (nq->rear - 1 + MAX) % MAX;

            
        }

        else
        {
            x = (x + 1) % MAX;
        }
    }

     filteredNameArray[filteredNameCount] = sentinelName;


    return filteredNameArray;
}

bool insertSorted(NQueue *nq, Name n)
{
    if (isFull(*nq))
        return false;

    int x;

    for (x = nq->front; x != (nq->rear + 1) % MAX && strcmp(n.lname, nq->elems[x].lname) > 0; x = (x + 1) % MAX)
    {
    }

    for (int y = (nq->rear + 1) % MAX; y != x; y = (y - 1 + MAX) % MAX)
    {
        nq->elems[(y)] = nq->elems[y - 1];
    }

    nq->elems[x] = n;
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