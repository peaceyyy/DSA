/*
========================================
UNDIRECTED GRAPH - ADJACENCY MATRIX
Implementation Mode - Complete Reference
========================================

Based on Kuya Zeus's implementation pattern.
Undirected graph: matrix is symmetric (M[i][j] = M[j][i]).

KEY DIFFERENCE FROM DIRECTED:
- insertEdge() sets BOTH M[u][v] and M[v][u] to 1
- Matrix is symmetric along diagonal

STRUCTURE:
- M[i][j] = 1 if edge i—j exists, 0 otherwise
- M[i][j] always equals M[j][i]
- Space: O(V²) but only upper triangle needed conceptually

WHY UNDIRECTED MATRIX:
- O(1) edge lookup (check M[u][v])
- Simple symmetric update
- Good for dense undirected graphs

========================================
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int AdjMatrix[MAX][MAX];

// Core functions
void initMatrix(AdjMatrix M);
void insertEdge(AdjMatrix M, int edge[2]);
void displayMatrix(AdjMatrix M);
void displayEdges(AdjMatrix M);
// Helper functions (exam-essential)
int checkEdge(AdjMatrix M, int u, int v);
void removeEdge(AdjMatrix M, int edge[2]);
int countEdges(AdjMatrix M);
int getNeighbors(AdjMatrix M, int u, int neighbors[]);
int isIsolated(AdjMatrix M, int v);

int main() {
    // Sample undirected graph: 1—2, 2—3, 3—0
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;
    initMatrix(M);              // set all cells to 0

    printf("Inserting edges into undirected graph...\n");
    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
        printf("Inserted edge: %d -- %d\n", edges[i][0], edges[i][1]); // Expected: prints each edge
    }

    printf("\n=== ADJACENCY MATRIX REPRESENTATION ===\n");
    displayMatrix(M);
    // Expected output (5x5 symmetric matrix):
    // 0 0 0 1 0
    // 0 0 1 0 0
    // 0 1 0 1 0
    // 1 0 1 0 0
    // 0 0 0 0 0

    printf("\n=== EDGE LIST ===\n");
    displayEdges(M);
    printf("Expected: Edges: (0, 3) (1, 2) (2, 3)\n");

    printf("\n=== TESTING HELPER FUNCTIONS ===\n");
    
    // Test countEdges
    printf("Total unique edges: %d (Expected: 3)\n", countEdges(M));

    // Test checkEdge (both directions should work)
    printf("Check edge 1-2: %s (Expected: Exists)\n", checkEdge(M, 1, 2) ? "Exists" : "Missing");
    printf("Check edge 2-1: %s (Expected: Exists)\n", checkEdge(M, 2, 1) ? "Exists" : "Missing");
    printf("Check edge 1-0: %s (Expected: Missing)\n", checkEdge(M, 1, 0) ? "Exists" : "Missing");

    // Test getNeighbors
    int neighbors[MAX];
    int count = getNeighbors(M, 2, neighbors);
    printf("Neighbors of 2: ");
    for(int i=0; i<count; i++) printf("%d ", neighbors[i]);
    printf("(Expected: 1 3 or 3 1)\n");

    // Test isIsolated
    printf("Is Node 4 isolated? %s (Expected: Yes)\n", isIsolated(M, 4) ? "Yes" : "No");
    printf("Is Node 1 isolated? %s (Expected: No)\n", isIsolated(M, 1) ? "Yes" : "No");

    // Test removeEdge
    printf("\nRemoving edge 2-3...\n");
    int edgeToRemove[] = {2, 3};
    removeEdge(M, edgeToRemove);
    displayEdges(M);
    printf("Expected: Edges: (0, 3) (1, 2)\n");
    printf("Total edges after removal: %d (Expected: 2)\n", countEdges(M));
    printf("Check edge 3-2 after removal: %s (Expected: Missing)\n", checkEdge(M, 3, 2) ? "Exists" : "Missing");

    printf("\n");
    return 0;
}

void initMatrix(AdjMatrix M) {
    // Initialize all cells to 0 (no edges)
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            M[i][j] = 0;   // no edge between i and j
        }
    }
}

void insertEdge(AdjMatrix M, int edge[2]) {
    // Insert undirected edge: edge[0] -- edge[1]
    // MUST set BOTH M[u][v] and M[v][u] to 1 (symmetric)
    M[edge[0]][edge[1]] = 1;    // mark edge u→v
    M[edge[1]][edge[0]] = 1;    // mark edge v→u (undirected)
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
    // Display all edges avoiding duplicates
    // Only print upper triangle: if i < j and M[i][j] == 1
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(int j = i + 1; j < MAX; j++) {  // j > i ensures upper triangle only
            if(M[i][j] == 1) {
                printf("(%d, %d) ", i, j); // edge between i and j
            }
        }
    }
}

// ============================================
// HELPER FUNCTIONS (Exam-Essential)
// ============================================

// Check if edge exists between two vertices
// Returns: 1 if edge exists, 0 otherwise
// Note: For undirected, M[u][v] == M[v][u]
int checkEdge(AdjMatrix M, int u, int v) {
    if (u < 0 || u >= MAX || v < 0 || v >= MAX)        // bounds check
        return 0;                                       // invalid vertices
    return M[u][v];                                     // return 1 if edge exists, 0 otherwise
}

// Remove undirected edge between two vertices
// edge[0] = first vertex, edge[1] = second vertex
// CRITICAL: Must remove BOTH M[u][v] and M[v][u] (symmetric)
void removeEdge(AdjMatrix M, int edge[2]) {
    int u = edge[0], v = edge[1];                       // extract vertices
    if (u < 0 || u >= MAX || v < 0 || v >= MAX)        // bounds check
        return;                                         // invalid vertices
    M[u][v] = 0;                                        // remove edge u-v
    M[v][u] = 0;                                        // remove edge v-u (symmetric)
}

// Count total number of unique edges in undirected graph
// Returns: Total unique edge count (avoid double-counting)
// Note: Only count upper triangle to avoid counting each edge twice
int countEdges(AdjMatrix M) {
    int count = 0;                                      // initialize counter
    for (int i = 0; i < MAX; i++) {                     // for each row
        for (int j = i + 1; j < MAX; j++) {             // only count upper triangle (j > i)
            if (M[i][j] == 1)                           // if edge exists
                count++;                                // increment counter
        }
    }
    return count;                                       // return unique edge count
}

// Get all neighbors of a vertex
// Fills neighbors[] array and returns count
// neighbors[] must be pre-allocated with size MAX
int getNeighbors(AdjMatrix M, int u, int neighbors[]) {
    if (u < 0 || u >= MAX)                              // bounds check
        return 0;                                       // invalid vertex
    
    int count = 0;                                      // initialize neighbor count
    for (int v = 0; v < MAX; v++) {                     // scan row u
        if (M[u][v] == 1) {                             // if edge u-v exists
            neighbors[count++] = v;                     // store neighbor and increment
        }
    }
    return count;                                       // return number of neighbors found
}

// Check if vertex has no edges
// Returns: 1 if isolated, 0 otherwise
int isIsolated(AdjMatrix M, int v) {
    if (v < 0 || v >= MAX)                              // bounds check
        return 0;                                       // invalid vertex
    
    for (int j = 0; j < MAX; j++) {                     // scan row v
        if (M[v][j] == 1)                               // if any edge exists
            return 0;                                   // not isolated
    }
    return 1;                                           // no edges = isolated
}


/*
========================================
KEY CONCEPTS (for tomorrow's DFS/BFS)
========================================

1. ITERATING OVER NEIGHBORS (same as directed):
   for (int v = 0; v < MAX; v++) {
       if (M[u][v] == 1) {
           // v is a neighbor of u
           // Process neighbor...
       }
   }

2. VISITED ARRAY (prevents cycles):
   int visited[MAX] = {0};
   visited[v] = 1;  // Mark before processing

   Critical for undirected: without visited, you'd bounce
   back and forth on every edge (u→v→u→v...).

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
UNDIRECTED MATRIX vs LIST
========================================

Adjacency Matrix (Undirected):
+ O(1) edge lookup
+ Symmetric structure (M[i][j] = M[j][i])
+ Simple double-assignment insert
- O(V²) space (wastes half since symmetric)
- O(V) to find all neighbors (scan full row)

Adjacency List (Undirected):
+ O(V + 2E) space (each edge stored twice)
+ O(degree) to iterate neighbors
- Two malloc calls per edge insert
- Pointer traversal required

For exams: Matrix is faster to code.
For real graphs: List more common (social networks, etc.).

========================================
*/
