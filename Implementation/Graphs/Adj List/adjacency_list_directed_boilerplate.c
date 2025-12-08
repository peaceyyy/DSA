/*
Minimal boilerplate: Adjacency List (Directed Graph)
- Based on Kuya Zeus pattern
- Fill TODO implementations
- Tomorrow: Add DFS/BFS functions
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node
{
    int label; // Destination vertex
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

// Function prototypes
void initAdjList(AdjList L);
void insertEdge(AdjList L, int edge[2]);
void displayAdjList(AdjList L);
void displayEdges(AdjList L);
// Helper functions (exam-essential)
int checkEdge(AdjList L, int u, int v);
void removeEdge(AdjList L, int edge[2]);
int countEdges(AdjList L);
int getNeighbors(AdjList L, int v, int neighbors[]);
int isIsolated(AdjList L, int v);

int main()
{
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);

    AdjList L;
    initAdjList(L);

    printf("=== INSERTING EDGES ===\n");
    for (int i = 0; i < numOfEdges; i++)
    {
        insertEdge(L, edges[i]);
        printf("Inserted edge: %d -> %d\n", edges[i][0], edges[i][1]);
    }

    printf("\n=== ADJACENCY LIST REPRESENTATION ===\n");
    displayAdjList(L);
    // Expected output:
    // Node 0: EMPTY
    // Node 1: 2
    // Node 2: 3
    // Node 3: 0
    // Node 4: EMPTY

    printf("\n=== EDGE LIST ===\n");
    displayEdges(L);
    printf("Expected: Edges: (1, 2) (2, 3) (3, 0)\n");

    printf("\n=== TESTING HELPER FUNCTIONS ===\n");
    
    // Test countEdges
    printf("Total edges: %d (Expected: 3)\n", countEdges(L));

    // Test checkEdge
    printf("Check edge 1->2: %s (Expected: Exists)\n", checkEdge(L, 1, 2) ? "Exists" : "Missing");
    printf("Check edge 1->0: %s (Expected: Missing)\n", checkEdge(L, 1, 0) ? "Exists" : "Missing");

    // Test getNeighbors
    int neighbors[MAX];
    int count = getNeighbors(L, 2, neighbors);
    printf("Neighbors of 2: ");
    for(int i=0; i<count; i++) printf("%d ", neighbors[i]);
    printf("(Expected: 3)\n");

    // Test isIsolated
    printf("Is Node 4 isolated? %s (Expected: Yes)\n", isIsolated(L, 4) ? "Yes" : "No");
    printf("Is Node 1 isolated? %s (Expected: No)\n", isIsolated(L, 1) ? "Yes" : "No");

    // Test removeEdge
    printf("\nRemoving edge 2->3...\n");
    int edgeToRemove[] = {2, 3};
    removeEdge(L, edgeToRemove);
    displayEdges(L);
    printf("Expected: Edges: (1, 2) (3, 0)\n");
    printf("Total edges after removal: %d (Expected: 2)\n", countEdges(L));

    printf("\n");
    return 0;
}

void initAdjList(AdjList L)
{
    for (int i = 0; i < MAX; i++)
    {
        L[i] = NULL;
    }
}

void insertEdge(AdjList L, int edge[2])
{
    // TODO: Insert directed edge edge[0] -> edge[1]
    // Hint: malloc a new node, set label to edge[1], insert at front of L[edge[0]]

    Vertex newEdge = (Vertex)malloc(sizeof(struct node));

    if (newEdge != NULL)
    {
        newEdge->label = edge[1];   // to -> v
        newEdge->next = L[edge[0]]; // setting next to prev head of link
        L[edge[0]] = newEdge;       // setting new head of link of u
    }
}

void displayAdjList(AdjList L)
{
    // TODO: Display each vertex and its neighbors
    // Format: "Node X: neighbor1 neighbor2 ..."
    // If no neighbors, print "EMPTY"

    for (int currVertex = 0; currVertex < MAX; currVertex++)
    {
        Vertex currHead = L[currVertex];
        printf("Node %d: ", currVertex);

        while (currHead != NULL)
        {
            if (currHead->next != NULL)
                printf("%d -> ", currHead->label);
            else
                printf("%d -> NULL", currHead->label);
            currHead = currHead->next;
        }

        printf("\n");
    }
}

void displayEdges(AdjList L)
{
    // TODO: Display all edges in (source, dest) format
    // Format: "Edges: (u, v) (u, w) ..."
    printf("Edges: ");
    for (int currVertex = 0; currVertex < MAX; currVertex++)
    {
        Vertex currHead = L[currVertex];

        while (currHead != NULL)
        {
            printf("(%d, %d) ", currVertex, currHead->label);
            currHead = currHead->next;
        }
    }
}

// ============================================
// HELPER FUNCTIONS (Exam-Essential)
// ============================================

// TODO: Check if edge exists between u and v
// Returns: 1 if edge exists, 0 otherwise
// Hint: Traverse L[u] and search for v in the adjacency list
int checkEdge(AdjList L, int u, int v)
{
    // TODO: Bounds check (u, v must be [0, MAX))
    // TODO: Traverse L[u] linked list
    // TODO: Return 1 if found, 0 if not

    if (u < 0 || u > MAX || v < 0 || v > MAX)
        return 0;

    Vertex trav = L[u];
    while (trav != NULL)
    {

        if (trav->label == v)
            return 1;
        trav = trav->next;
    }

    return 0;
}

// TODO: Remove edge from u to v
// edge[0] = source, edge[1] = destination
// Hint: Use pointer-to-pointer pattern (&L[u] initially)
void removeEdge(AdjList L, int edge[2])
{
    int u = edge[0], v = edge[1];
    if (u < 0 || u > MAX || v < 0 || v > MAX) return;

    if (checkEdge)
    {
        Vertex *trav;

        for (trav = &L[u]; *trav != NULL && (*trav)->label != v; trav = &(*trav)->next)
        {
        }

        if (*trav != NULL)
        {

            Vertex temp = *trav;
            *trav = temp->next;
            free(temp);
        }
    }
    else
    {
        printf("There is no edge from %d to %d", u, v);
    }
}

// TODO: Count total edges in graph
// Returns: Total edge count
// Hint: Loop through all vertices, count nodes in each adjacency list
int countEdges(AdjList L)
{
    int edgeCount = 0;

    for (int currVertex = 0; currVertex < MAX; currVertex++)
    {
        Vertex currHead = L[currVertex];
        while (currHead != NULL)
        {
            edgeCount++;
            currHead = currHead->next;
        }
    }

    return edgeCount;
}

// TODO: Get all neighbors of vertex v
// Fills neighbors[] array, returns count
// neighbors[] must be size MAX
// Hint: Traverse L[v] and copy label values
int getNeighbors(AdjList L, int v, int neighbors[])
{
    if (v < 0 || v > MAX)
        return 0;
    int count = 0;

    Vertex trav = L[v];

    while (trav != NULL)
    {
        neighbors[count++] = trav->label;
        trav = trav->next;
    } 
     
    return count;
}

// TODO: Check if vertex v has no edges
// Returns: 1 if isolated, 0 otherwise
// Hint: Just check if L[v] == NULL
int isIsolated(AdjList L, int v)
{

    if (v < 0 || v > MAX)
        return 0;
    return (L[v] == NULL) ? 1 : 0;
}
