/*
 * DIJKSTRA'S ALGORITHM - BOILERPLATE
 * 
 * Find the shortest path from a source vertex to all other vertices
 * in a weighted, directed graph (non-negative weights only).
 * 
 * Input: Graph with adjacency list, source vertex
 * Output: dist[] array (shortest distances), parent[] array (for path reconstruction)
 * 
 * Complexity: O((V + E) log V) with min-heap
 * 
 * DO NOT implement the utility functions (MinHeap, Graph ops, etc.)
 * Focus on the core Dijkstra logic and integration.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// =========================================================================
// GRAPH STRUCTURES (Provided - DO NOT MODIFY)
// =========================================================================

typedef struct {
    int dest;
    int weight;
} Edge;

typedef struct {
    Edge *edges;
    int numEdges;
} AdjacencyListNode;

typedef struct {
    AdjacencyListNode *adjList[MAX_VERTICES];
    int numVertices;
} Graph;

typedef struct {
    int vertex;
    int key;
} HeapNode;

typedef struct {
    HeapNode *array;
    int capacity;
    int size;
    int position[MAX_VERTICES];
} MinHeap;

// =========================================================================
// UTILITY FUNCTIONS (Provided - DO NOT MODIFY)
// =========================================================================

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    for (int i = 0; i < MAX_VERTICES; i++) heap->position[i] = -1;
    return heap;
}

void swapHeapNodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->array[left].key < heap->array[smallest].key)
        smallest = left;
    if (right < heap->size && heap->array[right].key < heap->array[smallest].key)
        smallest = right;
    
    if (smallest != index) {
        HeapNode smallNode = heap->array[smallest];
        HeapNode indexNode = heap->array[index];
        
        heap->position[smallNode.vertex] = index;
        heap->position[indexNode.vertex] = smallest;
        
        swapHeapNodes(&heap->array[index], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}

void decreaseKey(MinHeap *heap, int vertex, int newKey) {
    int index = heap->position[vertex];
    heap->array[index].key = newKey;
    
    while (index > 0 && heap->array[(index - 1) / 2].key > heap->array[index].key) {
        int parentIndex = (index - 1) / 2;
        
        heap->position[heap->array[index].vertex] = parentIndex;
        heap->position[heap->array[parentIndex].vertex] = index;
        
        swapHeapNodes(&heap->array[index], &heap->array[parentIndex]);
        index = parentIndex;
    }
}

HeapNode extractMin(MinHeap *heap) {
    HeapNode root = heap->array[0];
    HeapNode lastNode = heap->array[heap->size - 1];
    
    heap->array[0] = lastNode;
    heap->position[lastNode.vertex] = 0;
    heap->position[root.vertex] = -1;
    
    heap->size--;
    minHeapify(heap, 0);
    
    return root;
}

void insertHeap(MinHeap *heap, int vertex, int key) {
    heap->size++;
    int index = heap->size - 1;
    heap->array[index].vertex = vertex;
    heap->array[index].key = key;
    heap->position[vertex] = index;
    
    while (index > 0 && heap->array[(index - 1) / 2].key > heap->array[index].key) {
        int parentIndex = (index - 1) / 2;
        
        heap->position[heap->array[index].vertex] = parentIndex;
        heap->position[heap->array[parentIndex].vertex] = index;
        
        swapHeapNodes(&heap->array[index], &heap->array[parentIndex]);
        index = parentIndex;
    }
}

int isInHeap(MinHeap *heap, int vertex) {
    return heap->position[vertex] != -1;
}

Graph* createGraph(int numVertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i] = (AdjacencyListNode*)malloc(sizeof(AdjacencyListNode));
        graph->adjList[i]->edges = NULL;
        graph->adjList[i]->numEdges = 0;
    }
    return graph;
}

void addEdge(Graph *graph, int src, int dest, int weight) {
    graph->adjList[src]->edges = (Edge*)realloc(graph->adjList[src]->edges,
                                                  sizeof(Edge) * (graph->adjList[src]->numEdges + 1));
    graph->adjList[src]->edges[graph->adjList[src]->numEdges].dest = dest;
    graph->adjList[src]->edges[graph->adjList[src]->numEdges].weight = weight;
    graph->adjList[src]->numEdges++;
}

// =========================================================================
// TODO: IMPLEMENT DIJKSTRA'S ALGORITHM
// =========================================================================

/*
 * Function: dijkstra
 * 
 * Purpose: Compute shortest paths from source vertex to all other vertices
 * 
 * Parameters:
 *   - graph: the input graph (adjacency list)
 *   - src: source vertex
 *   - dist[]: output array; dist[i] = shortest distance from src to i
 *   - parent[]: output array; parent[i] = previous vertex on shortest path to i
 * 
 * Algorithm outline (you must implement):
 *   1. Initialize distances: src = 0, all others = INF
 *   2. Insert src into min-heap with key 0
 *   3. While heap not empty:
 *      a. Extract minimum (smallest distance) vertex u from heap
 *      b. For each neighbor v of u:
 *         - Calculate new distance via u: newDist = dist[u] + weight(u, v)
 *         - If newDist < dist[v]:
 *           * Update dist[v] = newDist
 *           * Update parent[v] = u
 *           * If v not in heap: insert v with key newDist
 *           * If v in heap: decrease key of v to newDist
 *   4. Return (dist[] and parent[] are updated by reference)
 * 
 * Time Complexity: O((V + E) log V)
 * Space Complexity: O(V) for dist[], parent[], position[] arrays
 */
void dijkstra(Graph *graph, int src, int dist[], int parent[]) {
    // TODO: Implement Dijkstra's algorithm
    // Use the min-heap and graph structure provided above
}

// =========================================================================
// HELPER FUNCTIONS (Provided - DO NOT MODIFY)
// =========================================================================

void printShortestPaths(int dist[], int numVertices, int src) {
    printf("\nShortest distances from vertex %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (dist[i] == INF)
            printf("Vertex %d: INF (unreachable)\n", i);
        else
            printf("Vertex %d: %d\n", i, dist[i]);
    }
}

void printPath(int dest, int parent[]) {
    if (dest == -1) {
        return;
    }
    printPath(parent[dest], parent);
    printf("%d ", dest);
}

void printShortestPathsDetailed(int dist[], int parent[], int numVertices, int src) {
    printf("\nShortest paths from vertex %d:\n", src);
    for (int i = 0; i < numVertices; i++) {
        if (i == src) {
            printf("Vertex %d to %d: 0 (source)\n", src, i);
        } else if (dist[i] == INF) {
            printf("Vertex %d to %d: INF (unreachable)\n", src, i);
        } else {
            printf("Vertex %d to %d: %d (path: ", src, i, dist[i]);
            int temp = i;
            int tempParent[MAX_VERTICES];
            for (int j = 0; j < numVertices; j++) tempParent[j] = parent[j];
            printPath(i, tempParent);
            printf(")\n");
        }
    }
}

// =========================================================================
// MAIN - TEST HARNESS (DO NOT MODIFY)
// =========================================================================

int main(void) {
    Graph *graph = createGraph(6);
    
    // Build a test graph:
    //     0
    //    / \
    //   1   2
    //  / \ /
    // 3   4
    //      \
    //       5
    
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 3, 8);
    addEdge(graph, 2, 4, 10);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 4, 5, 3);
    
    int dist[MAX_VERTICES];
    int parent[MAX_VERTICES];
    
    // Initialize arrays
    for (int i = 0; i < 6; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    
    printf("=== DIJKSTRA'S ALGORITHM ===\n");
    dijkstra(graph, 0, dist, parent);
    printShortestPathsDetailed(dist, parent, 6, 0);
    
    printf("\n=== TEST COMPLETE ===\n");
    
    return 0;
}
