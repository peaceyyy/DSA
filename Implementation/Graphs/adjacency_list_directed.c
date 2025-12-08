/*
========================================
DIRECTED GRAPH - ADJACENCY LIST
Implementation Mode - Complete Reference
========================================

Based on Kuya Zeus's implementation pattern.
Adjacency list uses linked lists to store neighbors for each vertex.

STRUCTURE:
- Array of vertex pointers (L[0] to L[MAX-1])
- Each vertex has a linked list of outgoing edges
- Space: O(V + E) where V = vertices, E = edges

========================================
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node {
    int label;           // Destination vertex
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

void initAdjList(AdjList L);
void insertEdge(AdjList L, int edge[2]);
void displayAdjList(AdjList L);
void displayEdges(AdjList L);

int main() {
    // Sample directed graph: 1→2, 2→3, 3→0
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);

    AdjList L;                     // declare array of adjacency heads
    initAdjList(L);                // set each list head to NULL

    printf("Inserting edges into directed graph...\n");
    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(L, edges[i]);                          // add edge edges[i][0] -> edges[i][1]
        printf("Inserted edge: %d -> %d\n", edges[i][0], edges[i][1]); // Expected: prints each edge
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
    // Expected: Edges: (1, 2) (2, 3) (3, 0)

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
    // Insert directed edge: edge[0] -> edge[1]
    // Uses insert-at-front (O(1) operation)
    // allocate new adjacency node
    Vertex temp = (Vertex) malloc(sizeof(struct node));

    if(temp != NULL) {
        temp->label = edge[1];      // set neighbor label (destination)
        temp->next = L[edge[0]];    // link to previous head (may be NULL)
        L[edge[0]] = temp;          // make new node the new head for source
    }
}

void displayAdjList(AdjList L) {
    // Display adjacency list: each vertex and its neighbors
    for(int i = 0; i < MAX; i++) {
        printf("Node %d: ", i);

        Vertex trav = L[i];            // start at head of list for vertex i

        if(trav == NULL) {
            printf("EMPTY");         // no outgoing edges
        }

        for(; trav != NULL; trav = trav->next) { // traverse neighbors
            printf("%d ", trav->label);       // print neighbor label
        }

        printf("\n");
    }
}

void displayEdges(AdjList L) {
    // Display all edges in (source, dest) format
    printf("Edges: ");
    for(int i = 0; i < MAX; i++) {
        for(Vertex trav = L[i]; trav != NULL; trav = trav->next) {
            printf("(%d, %d) ", i, trav->label); // print edge from i to trav->label
        }
    }
}


/*
========================================
KEY CONCEPTS (for tomorrow's DFS/BFS)
========================================

1. ITERATING OVER NEIGHBORS:
   for (Vertex trav = L[start]; trav != NULL; trav = trav->next) {
       int neighbor = trav->label;
       // Process neighbor...
   }

2. VISITED ARRAY (prevents cycles):
   int visited[MAX] = {0};
   visited[v] = 1;  // Mark as visited before processing

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
*/
