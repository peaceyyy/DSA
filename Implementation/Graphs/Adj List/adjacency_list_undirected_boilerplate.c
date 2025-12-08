/*
Minimal boilerplate: Adjacency List (Undirected Graph)
- Based on Kuya Zeus pattern
- Fill TODO implementations
- Key: Insert edges in BOTH directions
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node
{
    int label; // Neighbor vertex
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
        printf("Inserted edge: %d -- %d\n", edges[i][0], edges[i][1]);
    }

    printf("\n=== ADJACENCY LIST REPRESENTATION ===\n");
    displayAdjList(L);
    // Expected output (order may vary due to insert-at-front):
    // Node 0: 3
    // Node 1: 2
    // Node 2: 3 1
    // Node 3: 0 2
    // Node 4: EMPTY

    printf("\n=== EDGE LIST ===\n");
    displayEdges(L);
    printf("Expected: Edges: (0, 3) (1, 2) (2, 3)\n");

    printf("\n=== TESTING HELPER FUNCTIONS ===\n");

    // Test countEdges
    printf("Total unique edges: %d (Expected: 3)\n", countEdges(L));

    // Test checkEdge
    printf("Check edge 1-2: %s (Expected: Exists)\n", checkEdge(L, 1, 2) ? "Exists" : "Missing");
    printf("Check edge 2-1: %s (Expected: Exists)\n", checkEdge(L, 2, 1) ? "Exists" : "Missing");
    printf("Check edge 1-0: %s (Expected: Missing)\n", checkEdge(L, 1, 0) ? "Exists" : "Missing");

    // Test getNeighbors
    int neighbors[MAX];
    int count = getNeighbors(L, 2, neighbors);
    printf("Neighbors of 2: ");
    for (int i = 0; i < count; i++)
        printf("%d ", neighbors[i]);
    printf("(Expected: 3 1 or 1 3)\n");

    // Test isIsolated
    printf("Is Node 4 isolated? %s (Expected: Yes)\n", isIsolated(L, 4) ? "Yes" : "No");
    printf("Is Node 1 isolated? %s (Expected: No)\n", isIsolated(L, 1) ? "Yes" : "No");

    // Test removeEdge
    printf("\nRemoving edge 2-3...\n");
    int edgeToRemove[] = {2, 3};
    removeEdge(L, edgeToRemove);
    displayEdges(L);
    printf("Expected: Edges: (0, 3) (1, 2)\n");
    printf("Total edges after removal: %d (Expected: 2)\n", countEdges(L));
    printf("Check edge 3-2 after removal: %s (Expected: Missing)\n", checkEdge(L, 3, 2) ? "Exists" : "Missing");

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

    int u = edge[0], v = edge[1];

    Vertex newEdge1 = (Vertex)malloc(sizeof(struct node));

    if (newEdge1 != NULL)
    {
        newEdge1->label = v;          // to
        newEdge1->next = L[u]; // from
        L[u] = newEdge1;
    }

    Vertex newEdge2 = (Vertex)malloc(sizeof(struct node));

    if (newEdge2 != NULL)
    {
        newEdge2->label = u;          // to
        newEdge2->next = L[v]; // from
        L[v] = newEdge2;
    }
}

void displayAdjList(AdjList L)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("Node %d: ", i);

        Vertex trav = L[i]; // start at head of list for vertex i

        if (trav == NULL)
        {
            printf("EMPTY"); // no neighbors
        }

        for (; trav != NULL; trav = trav->next)
        {                               // traverse neighbors
            printf("%d ", trav->label); // print neighbor label
        }

        printf("\n");
    }
}

void displayEdges(AdjList L)
{
    // TODO: Display all edges avoiding duplicates
    // Format: "Edges: (u, v) (u, w) ..."
    // Hint: Only print edge (i, neighbor) if i < neighbor
    //       (prevents printing both (1,2) and (2,1))

    printf("Edges: ");
    for (int i = 0; i < MAX; i++)
    {
        for (Vertex trav = L[i]; trav != NULL; trav = trav->next)
        {
            // avoid duplicates: only print if i < neighbor
            if (trav->label > i)
            {
                printf("(%d, %d) ", i, trav->label); // print edge i -- neighbor
            }
        }
    }
}

// ============================================
// HELPER FUNCTIONS (Exam-Essential)
// ============================================

// TODO: Check if edge exists between u and v
// Returns: 1 if edge exists, 0 otherwise
// Hint: Traverse L[u] and search for v (or traverse L[v] for u - symmetric)
int checkEdge(AdjList L, int u, int v)
{
    // TODO: Bounds check (u, v must be [0, MAX))
    // TODO: Traverse L[u] linked list
    // TODO: Return 1 if found, 0 if not

    if (u < 0 || v < 0 || u > MAX || v > MAX)
        return 0;

    Vertex trav;
    for (trav = L[u]; trav != NULL && (trav)->label != v; trav = trav->next){};

    return (trav != NULL) ? 1: 0; 

}

// TODO: Remove undirected edge between u and v
// edge[0] = first vertex, edge[1] = second vertex
// CRITICAL: Must remove BOTH directions (u-v AND v-u)
// Hint: Use pointer-to-pointer twice (once for each direction)
void removeEdge(AdjList L, int edge[2])
{
    // TODO: Extract u = edge[0], v = edge[1]
    // TODO: Bounds check
    // TODO: Remove u->v: Vertex *trav = &L[u], find v, bypass, free
    // TODO: Remove v->u: Vertex *trav = &L[v], find u, bypass, free


    int u = edge[0], v = edge[1];

    
    if (u < 0 || v < 0 || u > MAX || v > MAX)
        return; 

    if (checkEdge(L,u,v))
    {
        Vertex* trav,  temp;
        for (trav = &L[u]; *trav != NULL && (*trav)->label != v; trav = &(*trav)->next){};

        if (*trav != NULL)
        {
            temp = *trav;
            *trav = temp->next;
            free(temp);
        }   

        for (trav = &L[v]; *trav != NULL && (*trav)->label != u; trav = &(*trav)->next){};

        if (*trav != NULL)
        {
            temp = *trav;
            *trav = temp->next;
            free(temp);
        }        

    } else {
        printf("\nEdge between %d and %d does not exist\n", u, v);
    }


}

// TODO: Count total unique edges in undirected graph
// Returns: Total edge count (avoid double-counting)
// Hint: Only count edge (i, neighbor) if neighbor > i
int countEdges(AdjList L)
{
    int count = 0;

    for (int i = 0; i < MAX; i++){
        Vertex trav;
        for (trav = L[i]; trav != NULL; trav = trav->next){
            if (trav->label > i) count++;
        }
    } 

    return count;
}
// Get all neighbors of a vertex
// Fills neighbors[] array and returns count
// neighbors[] must be pre-allocated with size MAX
int getNeighbors(AdjList L, int v, int neighbors[]) {
    if (v < 0 || v >= MAX)                              // bounds check
        return 0;                                       // invalid vertex
    
    int count = 0;                                      // initialize neighbor count
    for (Vertex curr = L[v]; curr != NULL; curr = curr->next) {
        neighbors[count++] = curr->label;               // store neighbor and increment
    }
    return count;                                       // return number of neighbors found
}

// Check if vertex has no edges
// Returns: 1 if isolated, 0 otherwise
int isIsolated(AdjList L, int v) {
    if (v < 0 || v >= MAX)                              // bounds check
        return 0;                                       // invalid vertex
    return L[v] == NULL ? 1 : 0;                        // NULL list = isolated
}

