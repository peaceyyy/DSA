/*
 * BFS (Breadth-First Search) for Graphs - Adjacency Matrix Implementation
 * Complete Reference with Line-by-Line Annotations
 * 
 * PURPOSE:
 * Demonstrates BFS on a directed graph using adjacency matrix.
 * BFS explores all neighbors at the current depth before moving to next depth level.
 * 
 * KEY CONCEPTS:
 * - BFS uses a QUEUE (FIFO) - first vertex in is first processed
 * - Explores layer-by-layer (like ripples in water)
 * - MUST track visited[] to avoid infinite loops
 * - Time Complexity: O(V²) where V = vertices (must scan entire row for neighbors)
 * - Space Complexity: O(V²) for matrix + O(V) for visited array and queue
 * - BFS finds SHORTEST PATH in unweighted graphs
 * 
 * DIFFERENCE FROM ADJACENCY LIST:
 * - List: Traverse linked list of neighbors → O(degree) per vertex
 * - Matrix: Scan entire row for edges → O(V) per vertex
 * - Matrix is simpler to code but slower for sparse graphs
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// Graph structure (Adjacency Matrix)
typedef struct {
    int adjMatrix[MAX][MAX];  // 2D array: adjMatrix[i][j] = 1 if edge i→j exists
    int numVertices;          // Total number of vertices
} Graph;

// Queue for BFS
typedef struct {
    int items[MAX];           // Array to store vertex IDs
    int front;                // Index of front element
    int rear;                 // Index of rear element
} Queue;

// =========================================================================
// QUEUE OPERATIONS (for BFS)
// =========================================================================

void initQueue(Queue *q) {
    q->front = -1;            // Empty queue: front is -1
    q->rear = -1;             // Empty queue: rear is -1
}

bool isEmptyQueue(Queue q) {
    return q.front == -1;     // Queue is empty when front is -1
}

void enqueue(Queue *q, int vertex) {
    if (q->rear == MAX - 1) {   // Queue full check
        return;
    }
    
    if (q->front == -1) {       // First element being added
        q->front = 0;           // Set front to 0
    }
    
    q->items[++q->rear] = vertex;  // Increment rear and add vertex
}

int dequeue(Queue *q) {
    if (isEmptyQueue(*q)) {     // Check if queue is empty
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
    
    // Initialize all edges to 0 (no edge)
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }
    
    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;  // Mark edge as existing (1 = edge exists)
    
    // For undirected graph, add reverse edge:
    // graph->adjMatrix[dest][src] = 1;
}

// =========================================================================
// BFS IMPLEMENTATION (ADJACENCY MATRIX VERSION)
// =========================================================================

void BFS(Graph *graph, int startVertex) {
    // Initialize visited array (all vertices start unvisited)
    int visited[MAX] = {0};
    
    Queue qt;
    initQueue(&qt);
    enqueue(&qt, startVertex);
    visited[startVertex] = 1;

      printf("BFS (starting from vertex %d): ", startVertex);
    while (!isEmptyQueue(qt))
    {
        int curr = dequeue(&qt);
        printf("%d ", curr);

        for (int neighbor = 0; neighbor < graph->numVertices; neighbor++)
        {
            if(graph->adjMatrix[curr][neighbor] == 1 && visited[neighbor] == 0)
            {
                visited[neighbor] = 1;
                enqueue(&qt, neighbor);
            }
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
        
        // Scan entire row for neighbors (O(V) per vertex)
        for (int neighbor = 0; neighbor < graph->numVertices; neighbor++) {
            if (graph->adjMatrix[currentVertex][neighbor] == 1) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    level[neighbor] = level[currentVertex] + 1;  // Child is one level deeper
                    enqueue(&queue, neighbor);
                }
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
    
    printf("=== Graph BFS Traversals (Adjacency Matrix) ===\n\n");
    
    // Test standard BFS
    BFS(graph, 0);
    // Expected: 0 1 2 3 4 5 6
    // Note: Matrix order is deterministic (scans 0→V-1), so output is stable
    
    printf("\n");
    
    // Test BFS with level tracking
    BFS_WithLevels(graph, 0);
    // Shows which vertices are at each depth level
    
    printf("=== Traversal Complete ===\n");
    
    return 0;
}
