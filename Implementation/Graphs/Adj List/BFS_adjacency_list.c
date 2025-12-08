/*
 * BFS (Breadth-First Search) for Graphs - Adjacency List Implementation
 * Complete Reference with Line-by-Line Annotations
 * 
 * PURPOSE:
 * Demonstrates BFS on a directed graph using adjacency lists.
 * BFS explores all neighbors at the current depth before moving to next depth level.
 * 
 * KEY CONCEPTS:
 * - BFS uses a QUEUE (FIFO) - first vertex in is first processed
 * - Explores layer-by-layer (like ripples in water)
 * - MUST track visited[] to avoid infinite loops
 * - Time Complexity: O(V + E) where V = vertices, E = edges
 * - Space Complexity: O(V) for visited array and queue
 * - BFS finds SHORTEST PATH in unweighted graphs
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Adjacency List Node
typedef struct EdgeNode {
    int vertex;              // Neighbor vertex ID
    struct EdgeNode *next;   // Pointer to next neighbor
} EdgeNode;

// Graph structure
typedef struct {
    EdgeNode *adjList[MAX];  // Array of adjacency lists
    int numVertices;         // Total number of vertices
} Graph;

// Queue for BFS
typedef struct {
    int items[MAX];          // Array to store vertex IDs
    int front;               // Index of front element
    int rear;                // Index of rear element
} Queue;

// =========================================================================
// QUEUE OPERATIONS (for BFS)
// =========================================================================

void initQueue(Queue *q) {
    q->front = -1;           // Empty queue: front is -1
    q->rear = -1;            // Empty queue: rear is -1
}

bool isEmptyQueue(Queue q) {
    return q.front == -1;    // Queue is empty when front is -1
}

void enqueue(Queue *q, int vertex) {
    if (q->rear == MAX - 1) {  // Queue full check
        return;
    }
    
    if (q->front == -1) {      // First element being added
        q->front = 0;          // Set front to 0
    }
    
    q->items[++q->rear] = vertex;  // Increment rear and add vertex
}

int dequeue(Queue *q) {
    if (isEmptyQueue(*q)) {    // Check if queue is empty
        return -1;
    }
    
    int vertex = q->items[q->front];  // Get front element
    
    if (q->front == q->rear) {        // Last element being removed
        q->front = q->rear = -1;      // Reset queue to empty state
    } else {
        q->front++;                    // Move front forward
    }
    
    return vertex;
}

// =========================================================================
// GRAPH OPERATIONS
// =========================================================================

Graph* createGraph(int vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    
    // Initialize all adjacency lists to NULL
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    // Create new edge node for destination
    EdgeNode *newNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    newNode->vertex = dest;              // Store destination vertex
    newNode->next = graph->adjList[src]; // Link to existing list
    graph->adjList[src] = newNode;       // Update head of list
    
    // For undirected graph, add reverse edge:
    // EdgeNode *revNode = (EdgeNode*)malloc(sizeof(EdgeNode));
    // revNode->vertex = src;
    // revNode->next = graph->adjList[dest];
    // graph->adjList[dest] = revNode;
}

// =========================================================================
// BFS IMPLEMENTATION
// =========================================================================

void BFS(Graph *graph, int startVertex) {
    // Initialize visited array (all vertices start unvisited)
    bool visited[MAX] = {false};
    
    // Create and initialize queue
    Queue queue;
    initQueue(&queue);
    
    // Mark start vertex as visited and enqueue it
    visited[startVertex] = true;         // Mark as visited BEFORE enqueuing
    enqueue(&queue, startVertex);        // Add to queue for processing
    
    printf("BFS (starting from vertex %d): ", startVertex);
    
    // Main BFS loop: continues until queue is empty
    while (!isEmptyQueue(queue)) {
        int currentVertex = dequeue(&queue);  // Remove vertex from front of queue
        printf("%d ", currentVertex);         // Process/visit the vertex (print it)
        
        // Explore all neighbors of current vertex
        EdgeNode *temp = graph->adjList[currentVertex];  // Start at head of adjacency list
        
        while (temp != NULL) {               // Traverse entire adjacency list
            int neighbor = temp->vertex;     // Get neighbor vertex ID
            
            if (!visited[neighbor]) {        // If neighbor not yet visited
                visited[neighbor] = true;    // Mark as visited (CRITICAL: do this BEFORE enqueue)
                enqueue(&queue, neighbor);   // Add to queue for future processing
            }
            
            temp = temp->next;               // Move to next neighbor in list
        }
    }
    
    printf("\n");
}

// =========================================================================
// BFS WITH LEVEL TRACKING (Shows depth/distance from start)
// =========================================================================

void BFS_WithLevels(Graph *graph, int startVertex) {
    bool visited[MAX] = {false};
    int level[MAX] = {0};                // Track depth/distance from start
    
    Queue queue;
    initQueue(&queue);
    
    visited[startVertex] = true;
    level[startVertex] = 0;              // Start vertex is at level 0
    enqueue(&queue, startVertex);
    
    printf("BFS with Levels (starting from vertex %d):\n", startVertex);
    
    while (!isEmptyQueue(queue)) {
        int currentVertex = dequeue(&queue);
        printf("  Vertex %d at level %d\n", currentVertex, level[currentVertex]);
        
        EdgeNode *temp = graph->adjList[currentVertex];
        
        while (temp != NULL) {
            int neighbor = temp->vertex;
            
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                level[neighbor] = level[currentVertex] + 1;  // Child is one level deeper
                enqueue(&queue, neighbor);
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
    //         6
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 5);
    addEdge(graph, 4, 6);
    
    printf("=== Graph BFS Traversals (Adjacency List) ===\n\n");
    
    // Test standard BFS
    BFS(graph, 0);
    // Expected: 0 1 2 3 4 5 6 (or 0 2 1 4 3 6 5 depending on insertion order)
    // Key: All depth-1 nodes before depth-2 nodes
    
    printf("\n");
    
    // Test BFS with level tracking
    BFS_WithLevels(graph, 0);
    // Shows which vertices are at each depth level
    
    printf("=== Traversal Complete ===\n");
    
    return 0;
}
