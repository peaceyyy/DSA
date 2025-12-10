/*
 * DFS (Depth-First Search) for Graphs - Adjacency Matrix Implementation
 * BOILERPLATE for Practice
 * 
 * YOUR TASK:
 * Implement DFS_Recursive_Helper, DFS_Recursive, and DFS_Iterative functions.
 * Use the matrix representation: graph->adjMatrix[i][j] = 1 means edge i→j exists.
 * 
 * HINTS:
 * - Loop through matrix row to find neighbors: check if adjMatrix[vertex][j] == 1
 * - Don't forget visited[] array to prevent infinite loops
 * - Matrix version: iterate 0 to numVertices-1 to check all potential neighbors
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int adjMatrix[MAX][MAX];
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
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
}

// =========================================================================
// TODO: IMPLEMENT DFS FUNCTIONS BELOW
// =========================================================================

void DFS_Recursive_Helper(Graph *graph, int vertex, bool visited[]) {
        
    visited[vertex] = true;
    printf("%d ", vertex);
    
    for (int neighbor = 0; neighbor < graph->numVertices; neighbor++)
    {
        if (graph->adjMatrix[vertex][neighbor] == 1 && visited[neighbor] == false)
        {
            DFS_Recursive_Helper(graph, neighbor, visited);
            visited[neighbor] = true;
        }
    }
    
    
}

void DFS_Recursive(Graph *graph, int startVertex) {
     printf("DFS Recursive (starting from vertex %d): ", startVertex);
     bool visited[MAX] = {false};
     
     DFS_Recursive_Helper(graph, startVertex, visited);

    printf("\n");
}

void DFS_Iterative(Graph *graph, int startVertex) {
     printf("DFS Iterative (starting from vertex %d): ", startVertex);
    int visited[MAX] = {0};
    Stack s;
    initStack(&s);
    
    push(&s, startVertex);
    visited[startVertex] = 1;
    
    while (!isEmptyStack(s))
    {
        int curr = pop(&s);
        printf("%d ", curr);
        
        
        for (int j = 0; j < graph->numVertices; j++)
        {
            if (graph->adjMatrix[curr][j] == 1 && visited[j] == 0)
            {
                push(&s, j);
                visited[j] = 1;
            }
        }
    }
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
    
    printf("=== Graph DFS Traversals (Adjacency Matrix) ===\n\n");
    
    DFS_Recursive(graph, 0);
    // Expected: DFS Recursive (starting from vertex 0): 0 1 3 4 5 6 2
    
    DFS_Iterative(graph, 0);
    // Expected: DFS Iterative (starting from vertex 0): 0 2 1 4 6 5 3
    
    printf("\n=== Traversal Complete ===\n");
    
    return 0;
}
