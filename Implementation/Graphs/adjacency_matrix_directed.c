/*
========================================
DIRECTED GRAPH - ADJACENCY MATRIX
Implementation Mode - Complete Reference
========================================

Based on Kuya Zeus's implementation pattern.
Adjacency matrix uses 2D array to represent edges.

STRUCTURE:
- M[i][j] = 1 if edge i→j exists, 0 otherwise
- Space: O(V²) where V = vertices

WHY ADJACENCY MATRIX:
- O(1) edge lookup: check M[u][v] directly
- Simple to implement (no pointers)
- Good for dense graphs (many edges)
- Fast for "is there an edge?" queries

TRADE-OFFS:
- Wastes space for sparse graphs
- Iterating neighbors requires full row scan

TOMORROW: You'll add DFS/BFS functions to this structure.
========================================
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int AdjMatrix[MAX][MAX];

void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[2]);
void displayMatrix(AdjMatrix M);
void displayEdges(AdjMatrix M);

int main() {
    // Sample directed graph: 1→2, 2→3, 3→0
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;                // declare adjacency matrix
    initMatrix(M);              // set all cells to 0 (no edges)

    printf("Inserting edges into directed graph...\n");
    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
        printf("Inserted edge: %d -> %d\n", edges[i][0], edges[i][1]); // Expected: prints each edge
    }

    printf("\n=== ADJACENCY MATRIX REPRESENTATION ===\n");
    displayMatrix(M);
    // Expected output (5x5 matrix):
    // 0 0 0 0 0
    // 0 0 1 0 0
    // 0 0 0 1 0
    // 1 0 0 0 0
    // 0 0 0 0 0

    printf("\n=== EDGE LIST ===\n");
    displayEdges(M);
    // Expected: Edges: (1, 2) (2, 3) (3, 0)

    printf("\n");
    return 0;
}

void initMatrix(AdjMatrix M) {
    // Initialize all cells to 0 (no edges)
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = 0;   // no edge from i to j
        }
    }
}

void insertEdge(AdjMatrix M, int edge[2]) {
    // Insert directed edge: edge[0] -> edge[1]
    // Set M[source][dest] = 1
    M[edge[0]][edge[1]] = 1;    // mark presence of directed edge
}

void displayMatrix(AdjMatrix M) {
    // Display the full adjacency matrix
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            printf("%d ", M[i][j]); // print cell (i,j)
        }
        printf("\n");
    }
}

void displayEdges(AdjMatrix M) {
    // Display all edges in (source, dest) format
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            if(M[i][j] == 1) {
                printf("(%d, %d) ", i, j); // edge from i to j
            }
        }
    }
}


/*
========================================
KEY CONCEPTS (for tomorrow's DFS/BFS)
========================================

1. ITERATING OVER NEIGHBORS:
   for (int v = 0; v < MAX; v++) {
       if (M[u][v] == 1) {
           // v is a neighbor of u
           // Process neighbor...
       }
   }

2. VISITED ARRAY (same as adjacency list):
   int visited[MAX] = {0};
   visited[v] = 1;  // Mark as visited

3. DFS PATTERN (recursive):
   void DFS(AdjMatrix M, int v, int visited[]) {
       visited[v] = 1;
       printf("%d ", v);
       for (int neighbor = 0; neighbor < MAX; neighbor++) {
           if (M[v][neighbor] == 1 && !visited[neighbor]) {
               DFS(M, neighbor, visited);
           }
       }
   }

4. BFS PATTERN (queue):
   Queue Q;
   enqueue(&Q, start);
   visited[start] = 1;
   while (!isEmpty(Q)) {
       int u = dequeue(&Q);
       printf("%d ", u);
       for (int v = 0; v < MAX; v++) {
           if (M[u][v] == 1 && !visited[v]) {
               visited[v] = 1;
               enqueue(&Q, v);
           }
       }
   }

========================================
MATRIX vs LIST COMPARISON
========================================

Adjacency Matrix:
+ O(1) edge lookup
+ Simple nested loops for neighbors
- O(V²) space (wastes for sparse graphs)
- O(V) to find all neighbors (scan full row)

Adjacency List:
+ O(V + E) space (efficient for sparse)
+ O(degree) to iterate neighbors
- O(degree) edge lookup
- Pointer traversal required

For exams: Matrix is faster to code under time pressure.
For real graphs: List is more common (social networks, etc.).

========================================
*/
