/*
Minimal boilerplate: Adjacency Matrix (Directed Graph)
- Based on Kuya Zeus pattern
- Fill TODO implementations
- Tomorrow: Add DFS/BFS functions
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int AdjMatrix[MAX][MAX];

// Function prototypes
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

int main()
{
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);

    AdjMatrix M;
    initMatrix(M);

    printf("=== INSERTING EDGES ===\n");
    for (int i = 0; i < numOfEdges; i++)
    {
        insertEdge(M, edges[i]);
        printf("Inserted edge: %d -> %d\n", edges[i][0], edges[i][1]);
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
    printf("Expected: Edges: (1, 2) (2, 3) (3, 0)\n");

    printf("\n=== TESTING HELPER FUNCTIONS ===\n");
    
    // Test countEdges
    printf("Total edges: %d (Expected: 3)\n", countEdges(M));

    // Test checkEdge
    printf("Check edge 1->2: %s (Expected: Exists)\n", checkEdge(M, 1, 2) ? "Exists" : "Missing");
    printf("Check edge 1->0: %s (Expected: Missing)\n", checkEdge(M, 1, 0) ? "Exists" : "Missing");

    // Test getNeighbors
    int neighbors[MAX];
    int count = getNeighbors(M, 2, neighbors);
    printf("Neighbors of 2: ");
    for(int i=0; i<count; i++) printf("%d ", neighbors[i]);
    printf("(Expected: 3)\n");

    // Test isIsolated
    printf("Is Node 4 isolated? %s (Expected: Yes)\n", isIsolated(M, 4) ? "Yes" : "No");
    printf("Is Node 1 isolated? %s (Expected: No)\n", isIsolated(M, 1) ? "Yes" : "No");

    // Test removeEdge
    printf("\nRemoving edge 2->3...\n");
    int edgeToRemove[] = {2, 3};
    removeEdge(M, edgeToRemove);
    displayEdges(M);
    printf("Expected: Edges: (1, 2) (3, 0)\n");
    printf("Total edges after removal: %d (Expected: 2)\n", countEdges(M));

    printf("\n");
    return 0;
}

void initMatrix(AdjMatrix M)
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            M[i][j] = 0;
        }
    }
}

void insertEdge(AdjMatrix M, int edge[2])
{
    // TODO: Insert directed edge edge[0] -> edge[1]
    int u = edge[0], v = edge[1];
    M[u][v] = 1;
}

void displayMatrix(AdjMatrix M)
{
    // TODO: Display the full MAX x MAX matrix
    // Format: print each row on separate line with spaces between elements
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", M[i][j]);
        }

        printf("\n");
    }
}

void displayEdges(AdjMatrix M)
{
    // TODO: Display all edges in (source, dest) format
    // Format: "Edges: (i, j) (i, k) ..." for all M[i][j] == 1
    printf("Edges: ");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (M[i][j] == 1) printf("(%d, %d) ", i, j);
        }
    }
}

// ============================================
// HELPER FUNCTIONS (Exam-Essential)
// ============================================

// TODO: Check if edge exists between u and v
// Returns: 1 if edge exists, 0 otherwise
// Hint: Just return M[u][v] (after bounds check)
int checkEdge(AdjMatrix M, int u, int v) {
    // TODO: Bounds check (u, v must be [0, MAX))
    // TODO: Return M[u][v]

    return (M[u][v] == 1) ? 1 : 0;

}

// TODO: Remove directed edge from u to v
// edge[0] = source, edge[1] = destination
// Hint: Set M[u][v] = 0
void removeEdge(AdjMatrix M, int edge[2]) {
    // TODO: Extract u = edge[0], v = edge[1]
    // TODO: Bounds check
    // TODO: Set M[u][v] = 0
    M[edge[0]][edge[1]] = 0;
}

// TODO: Count total edges in graph
// Returns: Total edge count
// Hint: Nested loop, count all M[i][j] == 1
int countEdges(AdjMatrix M) {
    int count = 0;

     for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (M[i][j] == 1) count++;
        }
    }

    return count;
}

// TODO: Get all neighbors of vertex u (outgoing edges)
// Fills neighbors[] array, returns count
// neighbors[] must be size MAX
// Hint: Scan row u, collect all j where M[u][j] == 1
int getNeighbors(AdjMatrix M, int u, int neighbors[]) {
    // TODO: Bounds check
    // TODO: int count = 0
    // TODO: For each column j, if M[u][j] == 1, neighbors[count++] = j
    // TODO: Return count
    if (u < 0 || u > MAX) return -1;
    int count = 0;

     for (int i = 0; i < MAX; i++)
    {
            if (M[u][i] == 1) neighbors[count++] = i;  
        
    }

    return count;

}

// TODO: Check if vertex v has no outgoing edges
// Returns: 1 if isolated, 0 otherwise
// Hint: Scan row v, return 1 if all M[v][j] == 0
int isIsolated(AdjMatrix M, int v) {
    // TODO: Bounds check
    // TODO: For each j, if M[v][j] == 1, return 0 (not isolated)
    // TODO: Return 1 (isolated)

    if (v < 0 || v > MAX) return 0;

    for (int i = 0; i < MAX; i++) if (M[v][i] == 1) return 0;

    return 1;
}
