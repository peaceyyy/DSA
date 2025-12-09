// ### **Story Problem: The Chronos Command Queue**

// In the high-stakes world of temporal engineering, the Chronos Corporation uses a sophisticated command queue to manage tasks for its time-traveling agents. The system, however, has a peculiar but critical operational constraint.

// The command queue processes tasks based on a priority system. Each task is assigned a **priority level** (an integer) and a **timestamp** of when it was submitted. The rule for processing is simple: **the task with the highest priority is always executed next.**

// However, there's a complication. If multiple tasks share the *exact same highest priority level*, the system must preserve the order of submission. That is, the one that was submitted earliest (oldest timestamp) must be executed first.

// An intern, trying to debug the system, logged the following sequence of commands being pushed to the queue. Each command is a pair of `(priority, timestamp)`:

// 1.  `push(10, 1)`
// 2.  `push(20, 2)`
// 3.  `push(15, 3)`
// 4.  `pop()` -> should execute task with priority 20
// 5.  `push(25, 4)`
// 6.  `push(15, 5)` -> Note: same priority as an existing task
// 7.  `pop()` -> should execute task with priority 25
// 8.  `pop()` -> should execute the task `(15, 3)`, not `(15, 5)`

// The intern is struggling to design a data structure that can efficiently handle this "priority-first, timestamp-second" logic. They need to be able to `push` new commands and `pop` the correct one according to the rules.

// Your task is to describe and then implement the data structure and the necessary functions to satisfy the Chronos Corporation's requirements.

#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 100

// Represents a single command in the queue
typedef struct
{
    int priority;
    int timestamp;
} Task;

// The Priority Queue structure, implemented as a max-heap
typedef struct
{
    Task heap[MAX_CAPACITY];
    int size;
} PriorityQueue;

/*
 * Function: createPriorityQueue
 * Description: Initializes a new, empty Priority Queue.
 * Returns: A pointer to the new PriorityQueue.
 */
PriorityQueue *createPriorityQueue()
{

    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->size = 0;
    return pq;
}

/*
 * Function: swap
 * Description: A utility function to swap two Tasks in memory.
 */
void swap(Task *a, Task *b)
{
    Task temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * Function: hasHigherPrecedence
 * Description: The core comparison logic. Determines if Task A has higher
 *              precedence than Task B.
 * Returns: 1 if A is higher, 0 otherwise.
 */
int hasHigherPrecedence(Task a, Task b)
{
    return (a.priority > b.priority) || (a.priority == b.priority && a.timestamp < b.timestamp);
}

/*
 * Function: heapifyUp
 * Description: After insertion, this function ensures the heap property is
 *              maintained by "bubbling up" the last element.
 *
 *
// The command queue processes tasks based on a priority system. Each task is assigned a **priority level** (an integer) and a **timestamp** of when it was submitted. The rule for processing is simple: **the task with the highest priority is always executed next.**

// However, there's a complication. If multiple tasks share the *exact same highest priority level*, the system must preserve the order of submission. That is, the one that was submitted earliest (oldest timestamp) must be executed first.

 */
void heapifyUp(PriorityQueue *pq, int index)
{

    int current = index;
    while (current > 0)
    {
        int parent = (current - 1) / 2;
        if (hasHigherPrecedence(pq->heap[current], pq->heap[parent]))
        {
            swap(&pq->heap[current], &pq->heap[parent]);
            current = parent;
        } else break;
    }
}

/*
 * Function: push
 * Description: Adds a new task to the priority queue.
 */
void push(PriorityQueue *pq, int priority, int timestamp)
{

    if (pq->size < MAX_CAPACITY)
    {
        pq->heap[pq->size].priority = priority;
        pq->heap[pq->size].timestamp = timestamp;
        pq->size++;

        heapifyUp(pq, pq->size - 1);
    }
    else
        printf("\nQueue is full\n");
}

/*
 * Function: heapifyDown
 * Description: After deletion (pop), this function ensures the heap property is
 *              maintained by "sinking down" the root element.
 */
void heapifyDown(PriorityQueue *pq, int index)
{
    int current = index;

    while ((current * 2) + 1 < pq->size)
    {
        int largest = current;
        int LC = (current * 2) + 1;
        int RC = (current * 2) + 2;

        if (LC < pq->size && hasHigherPrecedence(pq->heap[LC], pq->heap[current]))
            largest = LC;
        if (RC < pq->size && hasHigherPrecedence(pq->heap[RC], pq->heap[current]))
            largest = RC;

        if (largest != current)
        {
            swap(&pq->heap[current], &pq->heap[largest]);
            current = largest;
        }
        else
            break;
    }
}

/*
 * Function: pop
 * Description: Removes and returns the task with the highest precedence.
 * Returns: The task with the highest precedence.
 */
Task pop(PriorityQueue *pq)
{

    Task temp = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];

    heapifyDown(pq, 0);

    return temp;
}

/*
 * Function: peek
 * Description: Returns the task with the highest precedence without removing it.
 * Returns: The task with the highest precedence.
 */
Task peek(PriorityQueue *pq)
{
    return pq->heap[0];
}

int main()
{
    printf("Booting Chronos Command System...\n");
    PriorityQueue *commandQueue = createPriorityQueue();

    if (commandQueue == NULL)
    {
        printf("Fatal error: Could not allocate memory for the command queue.\n");
        return 1;
    }

    printf("\n--- Simulating Command Sequence ---\n");

    // 1. push(10, 1)
    push(commandQueue, 10, 1);
    printf("Pushed (10, 1). Top is now: (%d, %d)\n", peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Pushed (10, 1). Top is now: (10, 1)

    // 2. push(20, 2)
    push(commandQueue, 20, 2);
    printf("Pushed (20, 2). Top is now: (%d, %d)\n", peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Pushed (20, 2). Top is now: (20, 2)

    // 3. push(15, 3)
    push(commandQueue, 15, 3);
    printf("Pushed (15, 3). Top is now: (%d, %d)\n", peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Pushed (15, 3). Top is now: (20, 2)

    // 4. pop() -> should be (20, 2)
    Task popped = pop(commandQueue);
    printf("Popped (%d, %d). Top is now: (%d, %d)\n", popped.priority, popped.timestamp, peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Popped (20, 2). Top is now: (15, 3)

    // 5. push(25, 4)
    push(commandQueue, 25, 4);
    printf("Pushed (25, 4). Top is now: (%d, %d)\n", peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Pushed (25, 4). Top is now: (25, 4)

    // 6. push(15, 5)
    push(commandQueue, 15, 5);
    printf("Pushed (15, 5). Top is now: (%d, %d)\n", peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Pushed (15, 5). Top is now: (25, 4)

    // 7. pop() -> should be (25, 4)
    popped = pop(commandQueue);
    printf("Popped (%d, %d). Top is now: (%d, %d)\n", popped.priority, popped.timestamp, peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Popped (25, 4). Top is now: (15, 3)

    // 8. pop() -> should be (15, 3)
    popped = pop(commandQueue);
    printf("Popped (%d, %d). Top is now: (%d, %d)\n", popped.priority, popped.timestamp, peek(commandQueue).priority, peek(commandQueue).timestamp); // Expected: Popped (15, 3). Top is now: (15, 5)

    printf("\n--- Simulation Complete ---\n");

    free(commandQueue);
    printf("System shutdown.\n");

    return 0;
}