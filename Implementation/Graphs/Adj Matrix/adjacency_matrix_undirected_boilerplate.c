/*
Minimal boilerplate: Adjacency Matrix (Undirected Graph)
- Based on Kuya Zeus pattern
- Fill TODO implementations
- Key: Matrix must be symmetric (M[i][j] = M[j][i])
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
        printf("Inserted edge: %d -- %d\n", edges[i][0], edges[i][1]);
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
    for (int i = 0; i < count; i++)
        printf("%d ", neighbors[i]);
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

void initMatrix(AdjMatrix M)
{
    // Initialize all cells to 0 (no edges)
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            M[i][j] = 0; // no edge from i to j
        }
    }
}

void insertEdge(AdjMatrix M, int edge[2])
{
    int u = edge[0], v = edge[1];
    
    if (u < 0 || v < 0 || u >= MAX || v >= MAX) return;

    M[u][v] = 1;
    M[v][u] = 1;
}

void displayMatrix(AdjMatrix M)
{
    // Display the full adjacency matrix
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%d ", M[i][j]); // print cell (i,j)
        }
        printf("\n");
    }
}

void displayEdges(AdjMatrix M)
{
    // Display all edges in (source, dest) format
    printf("Edges: ");
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (j > i && M[i][j] == 1)
            {
                printf("(%d, %d) ", i, j); // edge from i to j
            }
        }
    }
}
// ============================================
// HELPER FUNCTIONS (Exam-Essential)
// ============================================

// TODO: Check if edge exists between u and v
// Returns: 1 if edge exists, 0 otherwise
// Hint: Return M[u][v] (works both directions for undirected)
int checkEdge(AdjMatrix M, int u, int v)
{
    // TODO: Bounds check (u, v must be [0, MAX))
    // TODO: Return M[u][v]

    return (M[u][v] == 1) ? 1 : 0;
}

// TODO: Remove undirected edge between u and v
// edge[0] = first vertex, edge[1] = second vertex
// CRITICAL: Must remove BOTH M[u][v] = 0 AND M[v][u] = 0 (symmetric)
// Hint: Set both to 0
void removeEdge(AdjMatrix M, int edge[2])
{
    int u = edge[0], v = edge[1];

    if (u < 0 || v < 0 || u >= MAX || v >= MAX) return;

    M[u][v] = 0;
    M[v][u] = 0;
}

// TODO: Count total unique edges in undirected graph
// Returns: Total edge count (avoid double-counting)
// Hint: Only count upper triangle (j > i) to avoid counting each edge twice
int countEdges(AdjMatrix M)
{
    int count = 0;

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (j > i && M[i][j] == 1)
                count++;
        }
    }

    return count;
}

// TODO: Get all neighbors of vertex u
// Fills neighbors[] array, returns count
// neighbors[] must be size MAX
// Hint: Scan row u, collect all j where M[u][j] == 1
int getNeighbors(AdjMatrix M, int u, int neighbors[])
{
    if (u < 0 || u >= MAX) return 0;
    int count = 0;

    for (int i = 0; i < MAX; i++)
    {
        if (M[u][i] == 1)
            neighbors[count++] = i;
    }

    return count;
}

// TODO: Check if vertex v has no edges
// Returns: 1 if isolated, 0 otherwise
// Hint: Scan row v, return 1 if all M[v][j] == 0
int isIsolated(AdjMatrix M, int v)
{
    if (v < 0 || v >= MAX)
        return 0;
    int i = 0;
    for (i = 0; i < MAX && M[v][i] != 1; i++){};

        return (i == MAX) ? 1 : 0;
}
