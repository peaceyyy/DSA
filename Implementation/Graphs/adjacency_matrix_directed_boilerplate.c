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

int main() {
    int edges[][2] = {{1, 2}, {2, 3}, {3, 0}};
    int numOfEdges = sizeof(edges) / sizeof(edges[0]);
    
    AdjMatrix M;
    initMatrix(M);

    for(int i = 0; i < numOfEdges; i++) {
        insertEdge(M, edges[i]);
    }

    displayMatrix(M);
    displayEdges(M);

    return 0;
}

void initMatrix(AdjMatrix M) {
    // TODO: Initialize all cells to 0 (no edges)
}

void insertEdge(AdjMatrix M, int edge[2]) {
    // TODO: Insert directed edge edge[0] -> edge[1]
    // Hint: Set M[edge[0]][edge[1]] = 1
}

void displayMatrix(AdjMatrix M) {
    // TODO: Display the full MAX x MAX matrix
    // Format: print each row on separate line with spaces between elements
}

void displayEdges(AdjMatrix M) {
    // TODO: Display all edges in (source, dest) format
    // Format: "Edges: (i, j) (i, k) ..." for all M[i][j] == 1
}
