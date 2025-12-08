/*
========================================
UNDIRECTED GRAPH - ADJACENCY LIST
Implementation Mode - Complete Reference
========================================

Based on Kuya Zeus's implementation pattern.
Undirected graph: if edge (u,v) exists, then edge (v,u) also exists.

KEY DIFFERENCE FROM DIRECTED:
- insertEdge() adds BOTH u→v and v→u
- Each edge appears in TWO adjacency lists

STRUCTURE:
- Array of vertex pointers (L[0] to L[MAX-1])
- Each vertex has a linked list of neighbors
- Space: O(V + 2E) where E = number of edges

========================================
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node {
    int label;           // Neighbor vertex
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

// Core functions
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

int main() {
    // Sample undirected graph: 1—2, 2—3, 3—0
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);

    AdjList L;
    initAdjList(L);                // set all heads to NULL

    printf("Inserting edges into undirected graph...\n");
    for(int i = 0; i < numOfEdges; i++) {
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
    for(int i=0; i<count; i++) printf("%d ", neighbors[i]);
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

void initAdjList(AdjList L) {
    // Initialize each adjacency list head to NULL
    for(int i = 0; i < MAX; i++) {
        L[i] = NULL;              // no neighbors yet for vertex i
    }
}

void insertEdge(AdjList L, int edge[2]) {
    // Insert undirected edge: edge[0] -- edge[1]
    // MUST insert BOTH directions (u→v and v→u)
    
    // First direction: edge[0] → edge[1]
    Vertex temp = (Vertex) malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->label = edge[1];      // neighbor is edge[1]
        temp->next = L[edge[0]];    // link to previous head
        L[edge[0]] = temp;          // update head for edge[0]
    }

    // Second direction: edge[1] → edge[0]
    temp = (Vertex) malloc(sizeof(struct node));
    if(temp != NULL) {
        temp->label = edge[0];      // neighbor is edge[0]
        temp->next = L[edge[1]];    // link to previous head
        L[edge[1]] = temp;          // update head for edge[1]
    }
}

void displayAdjList(AdjList L) {
    // Display adjacency list: each vertex and its neighbors
    for(int i = 0; i < MAX; i++) {
        printf("Node %d: ", i);

        Vertex trav = L[i];            // start at head of list for vertex i

        if(trav == NULL) {
            printf("EMPTY");         // no neighbors
        }

        for(; trav != NULL; trav = trav->next) { // traverse neighbors
            printf("%d ", trav->label);       // print neighbor label
        }

        printf("\n");
    }
}

void displayEdges(AdjList L) {
    // Display all edges in (source, dest) format
    // Note: undirected edges appear twice (once per direction)
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(Vertex trav = L[i]; trav != NULL; trav = trav->next) {
            // Filter to avoid duplicates: only print if i < neighbor
            if(trav->label > i) {
                printf("(%d, %d) ", i, trav->label); // print edge i -- neighbor
            }
        }
    }
}

// ============================================
// HELPER FUNCTIONS (Exam-Essential)
// ============================================

// Check if edge exists between two vertices
// Returns: 1 if edge exists, 0 otherwise
int checkEdge(AdjList L, int u, int v) {
    if (u < 0 || u >= MAX || v < 0 || v >= MAX)        // bounds check
        return 0;                                       // invalid vertices
    
    for (Vertex curr = L[u]; curr != NULL; curr = curr->next) {
        if (curr->label == v)                           // found neighbor
            return 1;                                   // edge exists
    }
    return 0;                                           // edge not found
}

// Remove undirected edge between two vertices
// Removes BOTH directions: u-v and v-u
// edge[0] = first vertex, edge[1] = second vertex
void removeEdge(AdjList L, int edge[2]) {
    int u = edge[0], v = edge[1];                       // extract vertices
    if (u < 0 || u >= MAX || v < 0 || v >= MAX)        // bounds check
        return;                                         // invalid vertices
    
    // Remove u -> v direction
    Vertex *trav = &L[u];                               // pointer-to-pointer
    while (*trav != NULL) {                             // traverse list
        if ((*trav)->label == v) {                      // found target
            Vertex temp = *trav;                        // save node
            *trav = (*trav)->next;                      // bypass node
            free(temp);                                 // free memory
            break;                                      // exit loop
        }
        trav = &(*trav)->next;                          // move to next pointer
    }
    
    // Remove v -> u direction (symmetric removal)
    trav = &L[v];                                       // reset to v's list
    while (*trav != NULL) {                             // traverse list
        if ((*trav)->label == u) {                      // found reverse edge
            Vertex temp = *trav;                        // save node
            *trav = (*trav)->next;                      // bypass node
            free(temp);                                 // free memory
            return;                                     // both directions removed
        }
        trav = &(*trav)->next;                          // move to next pointer
    }
}

// Count total number of undirected edges
// Note: Each edge counted twice (once per direction), so divide by 2
// Returns: Total unique edge count
int countEdges(AdjList L) {
    int count = 0;                                      // initialize counter
    for (int i = 0; i < MAX; i++) {                     // for each vertex
        for (Vertex curr = L[i]; curr != NULL; curr = curr->next) {
            if (curr->label > i)                        // only count if neighbor > i (avoid double-counting)
                count++;                                // increment for each edge
        }
    }
    return count;                                       // return total unique edges
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


/*
========================================
KEY CONCEPTS (for tomorrow's DFS/BFS)
========================================

1. ITERATING OVER NEIGHBORS (same as directed):
   for (Vertex trav = L[start]; trav != NULL; trav = trav->next) {
       int neighbor = trav->label;
       // Process neighbor...
   }

2. VISITED ARRAY (prevents cycles - CRITICAL for undirected):
   int visited[MAX] = {0};
   visited[v] = 1;  // Mark before processing

   Why more important here: undirected edges go both ways,
   so without visited[], you'd ping-pong forever (u→v→u→v...).

3. DFS PATTERN (recursive):
   void DFS(AdjList L, int v, int visited[]) {
       visited[v] = 1;
       printf("%d ", v);
       for (Vertex trav = L[v]; trav != NULL; trav = trav->next) {
           if (!visited[trav->label]) {
               DFS(L, trav->label, visited);
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
       for (Vertex trav = L[u]; trav != NULL; trav = trav->next) {
           if (!visited[trav->label]) {
               visited[trav->label] = 1;
               enqueue(&Q, trav->label);
           }
       }
   }

========================================
UNDIRECTED vs DIRECTED
========================================

Directed Graph:
- insertEdge(u, v) → add u→v only
- Can have one-way edges
- displayEdges prints each edge once

Undirected Graph:
- insertEdge(u, v) → add BOTH u↔v (two inserts)
- Symmetric relationships
- displayEdges must filter duplicates (print only if u < v)

========================================
*/
