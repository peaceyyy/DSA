/*
 * GRAPH UTILITY FUNCTIONS SCAFFOLD
 * For use in MST (Prim's, Kruskal's) and Shortest Path (Dijkstra's) Algorithms
 * 
 * Contains:
 * 1. Union-Find (Disjoint Set Union) for cycle detection
 * 2. Min-Heap for priority queue operations
 * 3. Graph structure and edge representation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

// =========================================================================
// 1. UNION-FIND (DISJOINT SET UNION) - For Kruskal's Cycle Detection
// =========================================================================

typedef struct {
    int parent[MAX_VERTICES];  // parent[i] stores the parent/representative of set containing i
    int rank[MAX_VERTICES];    // rank[i] stores the approximate height of subtree rooted at i
} UnionFind;

UnionFind* initUnionFind(int numVertices) {
    // Initialize each vertex as its own parent (own set)
    // Set rank of each vertex to 0 initially
}

int find(UnionFind *uf, int vertex) {
    // Find the representative (root) of the set containing vertex
    // Implement path compression: point vertex directly to root
}

void unionSets(UnionFind *uf, int vertex1, int vertex2) {
    // Union two sets by linking their roots
    // Use union by rank: attach smaller tree under larger tree
}

// =========================================================================
// 2. MIN-HEAP (PRIORITY QUEUE) - For Prim's and Dijkstra's
// =========================================================================

// Heap node structure (context depends on algorithm)
typedef struct {
    int vertex;           // Vertex ID
    int key;              // Key value (distance/weight)
} HeapNode;

typedef struct {
    HeapNode *array;      // Array of heap nodes
    int capacity;         // Maximum capacity
    int size;             // Current number of elements
    int position[MAX_VERTICES];  // position[i] = index of vertex i in heap array
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    // Allocate and initialize min-heap
    // Set size to 0, position[] to -1 (not in heap)
}

void swapHeapNodes(HeapNode *a, HeapNode *b) {
    // Swap two heap nodes by exchanging their data
}

void minHeapify(MinHeap *heap, int index) {
    // Restore min-heap property by sinking down from index
    // Find smallest among node, left child, right child
    // Swap if necessary and recurse
}

void decreaseKey(MinHeap *heap, int vertex, int newKey) {
    // Decrease the key of a vertex in the heap
    // Update heap array and float up to restore property
}

HeapNode extractMin(MinHeap *heap) {
    // Extract and return the minimum element (root)
    // Replace root with last element, shrink, and heapify down
}

void insertHeap(MinHeap *heap, int vertex, int key) {
    // Insert a new vertex with given key into heap
    // Add at end, float up to restore min-heap property
}

int isInHeap(MinHeap *heap, int vertex) {
    // Check if vertex is currently in the heap
}

// =========================================================================
// 3. GRAPH STRUCTURES
// =========================================================================

// For adjacency list representation
typedef struct {
    int dest;           // Destination vertex
    int weight;         // Edge weight
} Edge;

typedef struct {
    Edge *edges;        // Array of edges from this vertex
    int numEdges;       // Number of outgoing edges
} AdjacencyListNode;

typedef struct {
    AdjacencyListNode *adjList[MAX_VERTICES];
    int numVertices;
    int numEdges;
} Graph;

// For edge list representation (useful for Kruskal's)
typedef struct {
    int src;            // Source vertex
    int dest;           // Destination vertex
    int weight;         // Edge weight
} EdgeList;

// =========================================================================
// 4. GRAPH OPERATIONS
// =========================================================================

Graph* createGraph(int numVertices) {
    // Allocate graph structure
    // Initialize adjacency list for each vertex (no edges yet)
}

void addEdge(Graph *graph, int src, int dest, int weight) {
    // Add an edge from src to dest with given weight
    // For undirected: also add reverse edge (dest to src)
    // For directed: only add forward edge
}

EdgeList* getAllEdges(Graph *graph, int *edgeCount) {
    // Create an array of all edges in the graph
    // Useful for Kruskal's algorithm (sorts this array by weight)
}

void sortEdgesByWeight(EdgeList *edges, int numEdges) {
    // Sort edges in ascending order by weight
    // Use qsort or manual sort
}

// =========================================================================
// 5. UTILITY FUNCTIONS
// =========================================================================

void printMST(int parent[], int numVertices) {
    // Print the Minimum Spanning Tree
    // parent[i] = parent of vertex i in MST
}

void printShortestPaths(int dist[], int numVertices) {
    // Print shortest distances from source to all vertices
}

int getMSTWeight(int parent[], Graph *graph, int numVertices) {
    // Calculate total weight of the MST given parent[] array
    // Sum weights of all edges in the tree
}
