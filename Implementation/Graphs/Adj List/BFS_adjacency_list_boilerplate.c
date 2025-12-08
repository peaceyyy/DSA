/*
 * BFS (Breadth-First Search) for Graphs - Adjacency List Implementation
 * BOILERPLATE for Practice
 * 
 * YOUR TASK:
 * Implement BFS and BFS_WithLevels functions.
 * Use the queue helpers provided below.
 * 
 * HINTS:
 * - BFS uses a QUEUE (FIFO), not a stack
 * - Mark visited BEFORE enqueuing (important!)
 * - Process vertex when you dequeue it
 * - Enqueue all unvisited neighbors
 * - For level tracking: child_level = parent_level + 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct EdgeNode {
    int vertex;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    EdgeNode *adjList[MAX];
    int numVertices;
} Graph;

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

// =========================================================================
// QUEUE OPERATIONS (Provided - DO NOT MODIFY)
// =========================================================================

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmptyQueue(Queue q) {
    return q.front == -1;
}

void enqueue(Queue *q, int vertex) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = vertex;
}

int dequeue(Queue *q) {
    if (isEmptyQueue(*q)) return -1;
    int vertex = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return vertex;
}

// =========================================================================
// GRAPH OPERATIONS (Provided - DO NOT MODIFY)
// =========================================================================

Graph* createGraph(int vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    EdgeNode *newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// =========================================================================
// TODO: IMPLEMENT BFS FUNCTIONS BELOW
// =========================================================================

void BFS(Graph *graph, int startVertex) {
    // TODO: Implement BFS
    // 1. Initialize visited array to false
    // 2. Create and initialize queue
    // 3. Mark start vertex as visited and enqueue it
    // 4. Print header message
    // 5. While queue not empty:
    //    - Dequeue vertex and print it
    //    - Loop through its adjacency list
    //    - For each unvisited neighbor: mark visited and enqueue
    // 6. Print newline
}

void BFS_WithLevels(Graph *graph, int startVertex) {
    // TODO: Implement BFS with level tracking
    // 1. Initialize visited[] and level[] arrays
    // 2. Create and init queue
    // 3. Mark start visited, set level[start] = 0, enqueue start
    // 4. Print header
    // 5. While queue not empty:
    //    - Dequeue vertex
    //    - Print "Vertex X at level Y"
    //    - For each unvisited neighbor:
    //      - Mark visited
    //      - Set level[neighbor] = level[current] + 1
    //      - Enqueue neighbor
    // 6. Print newline
}

// =========================================================================
// MAIN - TEST HARNESS (DO NOT MODIFY)
// =========================================================================

int main(void) {
    Graph *graph = createGraph(7);
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 6);
    
    printf("=== Graph BFS Traversals (Adjacency List) ===\n\n");
    
    BFS(graph, 0);
    // Expected: BFS (starting from vertex 0): 0 1 2 3 4 5 6
    
    printf("\n");
    
    BFS_WithLevels(graph, 0);
    // Expected output showing vertices at each depth level
    
    printf("=== Traversal Complete ===\n");
    
    return 0;
}
