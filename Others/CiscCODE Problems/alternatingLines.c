#include <stdio.h>
#include <stdbool.h>
#define MAX 100

typedef struct {
    char students[MAX];
    int front, rear;
} Queue;

// HELPER FUNCTIONS
/* -------------- */
void initQueue(Queue *q);
bool isEmpty(Queue q);
bool isFull(Queue q);
void enqueue(Queue *q, char x);
void dequeue(Queue *q);
char peek(Queue q);
void display(Queue q);
/* --------------- */

void mergeStudents(Queue *q); // TODO

/*------------------------------------*/
int main() {
    Queue q;
    initQueue(&q);

    int boys, girls;

    printf("How many boys?: ");
    scanf("%d", &boys);

    printf("How many girls?: ");
    scanf("%d", &girls);

    for (int i = 0; i < boys; i++) {
        enqueue(&q, 'b');
    }
    for (int i = 0; i < girls; i++) {
        enqueue(&q, 'g');
    }

    printf("Original queue of students: ");
    display(q);

    mergeStudents(&q);
    printf("Merged queue of students: ");
    display(q);

    return 0;
}

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(Queue q) {
    return (q.rear + 1) % MAX == q.front;
}

bool isFull(Queue q) {
    return (q.rear + 2) % MAX == q.front;
}

void enqueue(Queue *q, char x) {
    if (!isFull(*q)) {
        q->rear = (q->rear + 1) % MAX;
        q->students[q->rear] = x;
    }
}

void dequeue(Queue *q) {
    if (!isEmpty(*q)) {
        q->front = (q->front + 1) % MAX;
    }
}

char peek(Queue q) {
    return (!isEmpty(q)) ? q.students[q.front] : -1;
}

void display(Queue q) {
    for (int i = q.front; i <= q.rear; i++) {
        printf("%c ", q.students[i]);
    }
    printf("\n");
}
/*------------------------------------*/

void mergeStudents(Queue *q) {
    Queue girlQ;
    Queue boyQ;

    initQueue(&girlQ);
    initQueue(&boyQ);

    int ndx; 

    for (ndx = q->front; ndx != (q->rear + 1) % MAX; ndx = (ndx + 1)  % MAX){
        if (q->students[ndx] == 'b'){
            enqueue(&boyQ, peek(*q));
        }

        if (q->students[ndx] == 'g'){
            enqueue(&girlQ, peek(*q));
        }

        dequeue(q);
    }

    while (!isEmpty(girlQ) && !isEmpty(boyQ)){
        enqueue(q, peek(boyQ));
        dequeue(&boyQ);
        enqueue(q, peek(girlQ));
        dequeue(&girlQ);
    }

    while (!isEmpty(boyQ)){
         enqueue(q, peek(boyQ));
        dequeue(&boyQ);
    } 
    while (!isEmpty(girlQ)){
         enqueue(q, peek(girlQ));
        dequeue(&girlQ);
    }
}
