/*
 * DFS (Depth-First Search) for Graphs - Adjacency Matrix Implementation
 * Complete Reference with Line-by-Line Annotations
 * 
 * PURPOSE:
 * Demonstrates iterative and recursive DFS on a directed graph using adjacency matrix.
 * Adjacency Matrix is better for dense graphs where edge lookups need to be O(1).
 * 
 * KEY CONCEPTS:
 * - DFS uses a STACK (LIFO) - either explicit (iterative) or call stack (recursive)
 * - Adjacency matrix: matrix[i][j] = 1 means edge from i to j exists
 * - MUST track visited[] to avoid infinite loops
 * - Time Complexity: O(V²) due to matrix traversal
 * - Space Complexity: O(V²) for matrix + O(V) for visited/stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Graph structure using adjacency matrix
typedef struct {
    int adjMatrix[MAX][MAX];  // 2D array: adjMatrix[i][j] = 1 if edge i→j exists
    int numVertices;          // Total number of vertices
} Graph;

// Stack for iterative DFS
typedef struct {
    int items[MAX];
    int top;
} Stack;

// =========================================================================
// STACK OPERATIONS (for iterative DFS)
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
// GRAPH OPERATIONS
// =========================================================================

Graph* createGraph(int vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    // Initialize all matrix entries to 0 (no edges)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;  // 0 means no edge from i to j
        }
    }
    
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    // For directed graph: set matrix[src][dest] = 1
    graph->adjMatrix[src][dest] = 1;  // Edge from src to dest
    
    // For undirected graph, uncomment below to add reverse edge:
    // graph->adjMatrix[dest][src] = 1;
}

// =========================================================================
// DFS - RECURSIVE IMPLEMENTATION
// =========================================================================

void DFS_Recursive_Helper(Graph *graph, int vertex, bool visited[]) {
    // Mark current vertex as visited
    visited[vertex] = true;
    printf("%d ", vertex);            // Process/visit the vertex (print it)
    
    // Explore all vertices (check entire row in adjacency matrix)
    for (int neighbor = 0; neighbor < graph->numVertices; neighbor++) {
        // Check if edge exists AND neighbor not visited
        if (graph->adjMatrix[vertex][neighbor] == 1 && !visited[neighbor]) {
            DFS_Recursive_Helper(graph, neighbor, visited);  // Recursive call
        }
    }
    // Implicit backtracking when function returns
}

void DFS_Recursive(Graph *graph, int startVertex) {
    // Initialize visited array
    bool visited[MAX] = {false};
    
    printf("DFS Recursive (starting from vertex %d): ", startVertex);
    DFS_Recursive_Helper(graph, startVertex, visited);
    printf("\n");
}

// =========================================================================
// DFS - ITERATIVE IMPLEMENTATION (Using Explicit Stack)
// =========================================================================

void DFS_Iterative(Graph *graph, int startVertex) {
    // Initialize visited array
    bool visited[MAX] = {false};
    
    // Create and initialize stack
    Stack stack;
    initStack(&stack);
    
    // Push starting vertex onto stack
    push(&stack, startVertex);
    
    printf("DFS Iterative (starting from vertex %d): ", startVertex);
    
    // Main DFS loop
    while (!isEmptyStack(stack)) {
        int currentVertex = pop(&stack);  // Pop vertex from stack
        
        // Skip if already visited
        if (visited[currentVertex]) {
            continue;
        }
        
        // Mark as visited and process
        visited[currentVertex] = true;
        printf("%d ", currentVertex);
        
        // Push all unvisited neighbors onto stack
        // Traverse the row in adjacency matrix for current vertex
        for (int neighbor = 0; neighbor < graph->numVertices; neighbor++) {
            // If edge exists and neighbor not visited
            if (graph->adjMatrix[currentVertex][neighbor] == 1 && !visited[neighbor]) {
                push(&stack, neighbor);   // Push neighbor onto stack
            }
        }
    }
    
    printf("\n");
}

// =========================================================================
// MAIN - TEST HARNESS
// =========================================================================

int main(void) {
    // Create a directed graph with 7 vertices (0-6)
    Graph *graph = createGraph(7);
    
    // Add edges to form this graph structure:
    //     0 → 1 → 3
    //     ↓   ↓
    //     2   4 → 5
    //         ↓
    //         6
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 6);
    
    printf("=== Graph DFS Traversals (Adjacency Matrix) ===\n\n");
    
    // Test recursive DFS
    DFS_Recursive(graph, 0);
    // Expected: 0 1 3 4 5 6 2
    
    // Test iterative DFS
    DFS_Iterative(graph, 0);
    // Expected: 0 2 1 4 6 5 3 (order may vary based on matrix traversal)
    
    printf("\n=== Traversal Complete ===\n");
    
    return 0;
}
