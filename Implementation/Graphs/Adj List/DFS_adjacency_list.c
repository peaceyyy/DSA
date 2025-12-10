/*
 * DFS (Depth-First Search) for Graphs - Adjacency List Implementation
 * Complete Reference with Line-by-Line Annotations
 * 
 * PURPOSE:
 * Demonstrates iterative and recursive DFS on a directed graph using adjacency lists.
 * DFS explores as far as possible along each branch before backtracking.
 * 
 * KEY CONCEPTS:
 * - DFS uses a STACK (LIFO) - either explicit (iterative) or call stack (recursive)
 * - MUST track visited[] to avoid infinite loops (graphs can have cycles)
 * - Time Complexity: O(V + E) where V = vertices, E = edges
 * - Space Complexity: O(V) for visited array and stack
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Adjacency List Node (stores a neighbor vertex)
typedef struct EdgeNode {
    int vertex;              // The neighbor vertex ID
    struct EdgeNode *next;   // Pointer to next neighbor in the list
} EdgeNode;

// Graph structure
typedef struct {
    EdgeNode *adjList[MAX];  // Array of adjacency lists (one per vertex)
    int numVertices;         // Total number of vertices in the graph
} Graph;

// Stack for iterative DFS
typedef struct {
    int items[MAX];          // Array to store vertex IDs
    int top;                 // Index of top element (-1 means empty)
} Stack;

// =========================================================================
// STACK OPERATIONS (for iterative DFS)
// =========================================================================

void initStack(Stack *s) {
    s->top = -1;             // Empty stack: top index is -1
}

bool isEmptyStack(Stack s) {
    return s.top == -1;      // Stack is empty when top is -1
}

void push(Stack *s, int vertex) {
    if (s->top < MAX - 1) {  // Check if stack is not full
        s->items[++s->top] = vertex;  // Pre-increment top, then assign
    }
}

int pop(Stack *s) {
    if (!isEmptyStack(*s)) { // Check if stack has elements
        return s->items[s->top--];  // Return top, then post-decrement
    }
    return -1;               // Return -1 if stack is empty
}

// =========================================================================
// GRAPH OPERATIONS
// =========================================================================

Graph* createGraph(int vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));  // Allocate graph structure
    graph->numVertices = vertices;                 // Set vertex count
    
    // Initialize all adjacency lists to NULL (no edges yet)
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    // Create a new edge node for destination vertex
    EdgeNode *newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = dest;                  // Store destination vertex
    newNode->next = graph->adjList[src];     // Link to existing list (insert at head)
    graph->adjList[src] = newNode;           // Update head of adjacency list
    
    // For undirected graph, uncomment below to add reverse edge:
    // EdgeNode *revNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    // revNode->vertex = src;
    // revNode->next = graph->adjList[dest];
    // graph->adjList[dest] = revNode;
}

// =========================================================================
// DFS - RECURSIVE IMPLEMENTATION
// =========================================================================

void DFS_Recursive_Helper(Graph *graph, int vertex, bool visited[]) {
    // Mark current vertex as visited
    visited[vertex] = true;
    printf("%d ", vertex);                   // Process/visit the vertex (print it)
    
    // Explore all neighbors of current vertex
    EdgeNode *temp = graph->adjList[vertex]; // Start at head of adjacency list
    while (temp != NULL) {                   // Traverse the entire list
        int neighbor = temp->vertex;         // Get neighbor vertex ID
        
        if (!visited[neighbor]) {            // If neighbor not yet visited
            DFS_Recursive_Helper(graph, neighbor, visited);  // Recursive call (go deeper)
        }
        
        temp = temp->next;                   // Move to next neighbor in list
    }
    // Implicit backtracking happens when function returns
}

void DFS_Recursive(Graph *graph, int startVertex) {
    // Initialize visited array (all vertices start as unvisited)
    bool visited[MAX] = {false};
    
    printf("DFS Recursive (starting from vertex %d): ", startVertex);
    DFS_Recursive_Helper(graph, startVertex, visited);  // Start DFS from given vertex
    printf("\n");
}

// =========================================================================
// DFS - ITERATIVE IMPLEMENTATION (Using Explicit Stack)
// =========================================================================

void DFS_Iterative(Graph *graph, int startVertex) {
    // Initialize visited array (all vertices start as unvisited)
    bool visited[MAX] = {false};
    
    // Create and initialize stack
    Stack stack;
    initStack(&stack);
    
    // Push starting vertex onto stack
    push(&stack, startVertex);
    
    printf("DFS Iterative (starting from vertex %d): ", startVertex);
    
    // Main DFS loop: continues until stack is empty
    while (!isEmptyStack(stack)) {
        int currentVertex = pop(&stack);     // Pop vertex from stack        

                // Mark as visited and process
        printf("%d ", currentVertex);        // Process/visit the vertex (print it)
        
        // Push all unvisited neighbors onto stack
        // Note: We traverse the adjacency list, and since we're using a stack,
        // the last neighbor pushed will be processed first (LIFO)
        EdgeNode *temp = graph->adjList[currentVertex];

        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {        // Only push unvisited neighbors
                visited[neighbor] = true;
                push(&stack, neighbor);      // Push onto stack for later processing
            }
            temp = temp->next;
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
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 6);
    
    printf("=== Graph DFS Traversals (Adjacency List) ===\n\n");
    
    // Test recursive DFS
    DFS_Recursive(graph, 0);
    // Expected output: 0 1 3 4 5 6 2 (or similar, order depends on adjacency list order)
    
    // Test iterative DFS
    DFS_Iterative(graph, 0);
    // Expected output: 0 2 1 4 6 5 3 (or similar, reverse of recursive due to stack nature)
    
    printf("\n=== Traversal Complete ===\n");
    
    return 0;
}
