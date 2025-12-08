/*
 * DFS (Depth-First Search) for Graphs - Adjacency List Implementation
 * BOILERPLATE for Practice
 * 
 * YOUR TASK:
 * Implement DFS_Recursive_Helper, DFS_Recursive, and DFS_Iterative functions.
 * Use the stack helpers and graph structure provided below.
 * 
 * HINTS:
 * - Recursive: Mark visited, print, then recursively visit all unvisited neighbors
 * - Iterative: Use a stack; pop vertex, mark visited, push unvisited neighbors
 * - Both must use visited[] array to prevent infinite loops
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
    int top;
} Stack;

// =========================================================================
// STACK OPERATIONS (Provided - DO NOT MODIFY)
// =========================================================================

void initStack(Stack *s) {
    s->top = -1;
}

bool isEmptyStack(Stack s) {
    return s.top == -1;
}

void push(Stack *s, int vertex) {
    if (s->top < MAX - 1) {
        s->items[++s->top] = vertex;
    }
}

int pop(Stack *s) {
    if (!isEmptyStack(*s)) {
        return s->items[s->top--];
    }
    return -1;
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
// TODO: IMPLEMENT DFS FUNCTIONS BELOW
// =========================================================================

void DFS_Recursive_Helper(Graph *graph, int vertex, bool visited[]) {
    // TODO: Implement recursive DFS helper
    // 1. Mark current vertex as visited
    // 2. Print the vertex
    // 3. Loop through adjacency list and recursively visit unvisited neighbors
}

void DFS_Recursive(Graph *graph, int startVertex) {
    // TODO: Implement recursive DFS wrapper
    // 1. Create and initialize visited array
    // 2. Print header message
    // 3. Call DFS_Recursive_Helper
    // 4. Print newline
}

void DFS_Iterative(Graph *graph, int startVertex) {
    // TODO: Implement iterative DFS using stack
    // 1. Create and initialize visited array
    // 2. Create and initialize stack
    // 3. Push start vertex
    // 4. While stack not empty:
    //    - Pop vertex
    //    - If already visited, skip
    //    - Mark visited and print
    //    - Push all unvisited neighbors
    // 5. Print newline
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
    
    printf("=== Graph DFS Traversals (Adjacency List) ===\n\n");
    
    DFS_Recursive(graph, 0);
    // Expected: DFS Recursive (starting from vertex 0): 0 1 3 4 5 6 2
    
    DFS_Iterative(graph, 0);
    // Expected: DFS Iterative (starting from vertex 0): 0 2 1 4 6 5 3
    
    printf("\n=== Traversal Complete ===\n");
    
    return 0;
}
