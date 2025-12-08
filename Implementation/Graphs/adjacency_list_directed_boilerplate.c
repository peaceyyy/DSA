/*
Minimal boilerplate: Adjacency List (Directed Graph)
- Based on Kuya Zeus pattern
- Fill TODO implementations
- Tomorrow: Add DFS/BFS functions
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct node {
    int label;           // Destination vertex
    struct node *next;
} *Vertex;

typedef Vertex AdjList[MAX];

// Function prototypes
void initAdjList(AdjList L);
void insertEdge(AdjList L, int edge[2]);
void displayAdjList(AdjList L);
void displayEdges(AdjList L);

int main() {
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);

    AdjList L;
    initAdjList(L);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(L, edges[i]);
    }

    displayAdjList(L);
    displayEdges(L);

    return 0;
}

void initAdjList(AdjList L) {
    // TODO: Initialize all vertex lists to NULL
}

void insertEdge(AdjList L, int edge[2]) {
    // TODO: Insert directed edge edge[0] -> edge[1]
    // Hint: malloc a new node, set label to edge[1], insert at front of L[edge[0]]
}

void displayAdjList(AdjList L) {
    // TODO: Display each vertex and its neighbors
    // Format: "Node X: neighbor1 neighbor2 ..."
    // If no neighbors, print "EMPTY"
}

void displayEdges(AdjList L) {
    // TODO: Display all edges in (source, dest) format
    // Format: "Edges: (u, v) (u, w) ..."
}
