#include <stdio.h>
#include <stdlib.h>

#define INFINITY 999
#define SIZE 5

typedef int Graph[SIZE][SIZE];

void initGraph(Graph G);
void populate(Graph G);
void displayGraph(Graph G);
void displayDijk(int D[]);
int *Dijkstra(Graph G, int startV);

void main()
{
    Graph G;
    printf("\n***** Graph Matrix After Initialization *****\n"); // Expected: "\n***** Graph Matrix After Initialization *****\n"
    initGraph(G);
    displayGraph(G);
    // Expected matrix after initialization (each entry = 999):
    //	999	999	999	999	999
    //	999	999	999	999	999
    //	999	999	999	999	999
    //	999	999	999	999	999
    //	999	999	999	999	999

    printf("\n***** Graph Matrix After Population *****\n"); // Expected: "\n***** Graph Matrix After Population *****\n"
    populate(G);
    displayGraph(G);
    // Expected matrix after population:
    // Row 0: \t999\t10\t999\t30\t100
    // Row 1: \t999\t999\t50\t999\t999
    // Row 2: \t20\t999\t999\t999\t10
    // Row 3: \t999\t999\t20\t999\t60
    // Row 4: \t999\t999\t999\t999\t999

    // Expected outputs for different `startV` values on this graph:
    // When startV = 0:
    // 0\t0
    // 1\t10
    // 2\t50
    // 3\t30
    // 4\t60
    //
    // When startV = 1:
    // 0\t70
    // 1\t0
    // 2\t50
    // 3\t100
    // 4\t60
    //
    // When startV = 2:
    // 0\t20
    // 1\t30
    // 2\t0
    // 3\t50
    // 4\t10
    //
    // When startV = 3:
    // 0\t40
    // 1\t50
    // 2\t20
    // 3\t0
    // 4\t30
    //
    // When startV = 4:
    // 0\t999
    // 1\t999
    // 2\t999
    // 3\t999
    // 4\t0
    int *dijk = Dijkstra(G, 0);
    displayDijk(dijk);
}

void initGraph(Graph G)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            G[i][j] = INFINITY;
        }
    }
}
void populate(Graph G)
{
    G[0][1] = 10;
    G[0][3] = 30;
    G[0][4] = 100;
    G[1][2] = 50;
    G[2][0] = 20;
    G[2][4] = 10;
    G[3][2] = 20;
    G[3][4] = 60;
}

void displayGraph(Graph G)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("\t%d", G[i][j]); // Expected: prints one matrix element preceded by a tab (e.g. "\t999" or "\t10")
        }
        printf("\n");
    }
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int *Dijkstra(Graph G, int startV)
{

    int *shortestDistanceArray = (int *)malloc(sizeof(int) * SIZE);
    int visitedVertices[SIZE] = {0};

    // initialize everything you know
    // copy the entire row
    // the startV distance to itself is 0

    for (int i = 0; i < SIZE; i++) shortestDistanceArray[i] = G[startV][i];

    shortestDistanceArray[startV] = 0;

    for (int x = 1; x < SIZE; x++)
    {
        int minDistance = INFINITY;
        int minVertex;
        // A. Choose a vertex 'minVertex' that is unvisited such that dist[minVertex] is minimum
        for (int currVertex = 0; currVertex < SIZE; currVertex++)
        {
            if (visitedVertices[currVertex] != 1 && shortestDistanceArray[currVertex] < minDistance)
            {                
                minDistance = shortestDistanceArray[currVertex];
                minVertex = currVertex;
            }
        }
        // B. Add minVertex to settled
        visitedVertices[minVertex] = 1;

        // C. For each vertex v in visited, relax the edge minVertex -> v
        for (int j = 0; j < SIZE; j++)
        {
            if (visitedVertices[j] != 1 && G[minVertex][j] != INFINITY && shortestDistanceArray[minVertex] != INFINITY)
            {

                shortestDistanceArray[j] = min(shortestDistanceArray[j], shortestDistanceArray[minVertex] + G[minVertex][j]);
                }
        }
    }

    return shortestDistanceArray;
}

void displayDijk(int D[])
{
    int i, x;
    printf("Source\tCost\n"); // Expected: "Source\tCost\n"
    for (x = 0; x < SIZE; x++)
    {
        // Expected outputs for the current program (startV = 0):
        // 0\t0
        // 1\t10
        // 2\t999
        // 3\t30
        // 4\t100
        printf("%d\t%d\n", x, D[x]); // Expected: prints the source index and its cost (see lines above)
    }
}