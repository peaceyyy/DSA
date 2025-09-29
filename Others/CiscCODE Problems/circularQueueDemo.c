#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX 7

typedef struct {
    int elems[MAX];
    int front, rear;
} CQueue;

void initQueue(CQueue *q) {
    q->front = 0;
    q->rear = MAX - 1;
}

bool isEmpty(CQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

bool isFull(CQueue *q) {
    return (q->rear + 2) % MAX == q->front;
}

bool enqueue(CQueue *q, int x) {
    if (!isFull(q)) {
        q->rear = (q->rear + 1) % MAX;
        q->elems[q->rear] = x;
        return true;
    } 
    return false;
}

bool dequeue(CQueue *q) {
    if (!isEmpty(q)) {
        q->front = (q->front + 1) % MAX;
        return true;
    }
    return false;
}

void display(CQueue *q) {
    int i = q->front;
    printf("Queue: ");
    while (i != (q->rear + 1) % MAX) {
        printf("%d ", q->elems[i]);
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int count(CQueue *q) {
    return (q->rear - q->front + MAX + 1) % MAX;
}

int search(CQueue *q, int val) {
    int i = q->front;
    while (i != (q->rear + 1) % MAX) {
        if (q->elems[i] == val) return i;
        i = (i + 1) % MAX;
    }
    return -1;
}

void rotate(CQueue *q, int k) {
    for (int i = 0; i < k; i++) {
        if (!isEmpty(q)) {
            int temp = q->elems[q->front];
            dequeue(q);
            enqueue(q, temp);
        }
    }
}

void reverse(CQueue *q) {
    int n = count(q);
    int temp[MAX];
    int i = q->front;
    for (int j = 0; j < n; j++) {
        temp[j] = q->elems[i];
        i = (i + 1) % MAX;
    }
    for (int j = 0; j < n; j++) {
        q->elems[(q->front + j) % MAX] = temp[n - j - 1];
    }
}

void bulkRemove(CQueue *q, int val) {
    int n = count(q);
    int i = q->front, newRear = q->front - 1;
    int temp[MAX];
    int idx = 0;
    while (i != (q->rear + 1) % MAX) {
        if (q->elems[i] != val) {
            temp[idx++] = q->elems[i];
        }
        i = (i + 1) % MAX;
    }
    for (int j = 0; j < idx; j++) {
        q->elems[(q->front + j) % MAX] = temp[j];
    }
    q->rear = (q->front + idx - 1 + MAX) % MAX;
}

void bulkInsertSorted(CQueue *q, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        // Insert in sorted order
        if (isFull(q)) break;
        int x = arr[i];
        int pos = q->front;
        while (pos != (q->rear + 1) % MAX && q->elems[pos] < x) {
            pos = (pos + 1) % MAX;
        }
        // Shift right
        for (int y = (q->rear + 1) % MAX; y != pos; y = (y - 1 + MAX) % MAX) {
            q->elems[y] = q->elems[(y - 1 + MAX) % MAX];
        }
        q->elems[pos] = x;
        q->rear = (q->rear + 1) % MAX;
    }
}

int main() {
    CQueue q;
    initQueue(&q);
    enqueue(&q, 5);
    enqueue(&q, 2);
    enqueue(&q, 7);
    enqueue(&q, 2);
    enqueue(&q, 9);
    display(&q);
    printf("Count: %d\n", count(&q));
    printf("Search 7: %d\n", search(&q, 7));
    rotate(&q, 2);
    printf("After rotate 2:\n");
    display(&q);
    reverse(&q);
    printf("After reverse:\n");
    display(&q);
    bulkRemove(&q, 2);
    printf("After bulk remove 2:\n");
    display(&q);
    int arr[] = {3, 8, 1};
    bulkInsertSorted(&q, arr, 3);
    printf("After bulk insert sorted 3,8,1:\n");
    display(&q);
    return 0;
}
