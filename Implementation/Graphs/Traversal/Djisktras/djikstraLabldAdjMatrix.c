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


void main(){
    Graph G;
    printf("\n***** Graph Matrix After Initialization *****\n");
    initGraph(G);
    displayGraph(G);

    printf("\n***** Graph Matrix After Population *****\n");
    populate(G);
    displayGraph(G);
    
    int *dijk = Dijkstra(G, 0);
    displayDijk(dijk);
}

void initGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            G[i][j] = INFINITY;
        }
    }
}
void populate(Graph G){
    G[0][1] = 10;
    G[0][3] = 30;
    G[0][4] = 100;
    G[1][2] = 50;
    G[2][0] = 20;
    G[2][4] = 10;
    G[3][2] = 20;
    G[3][4] = 60;
}

void displayGraph(Graph G){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("\t%d", G[i][j]);
        }
        printf("\n");
    }
}
int *Dijkstra(Graph G, int startV){

    int* shortestDistanceArray = (int*) malloc(sizeof(int) * SIZE);
    int visitedVertices[SIZE] = {0};
    
    
    // initialize everything you know
        // copy the entire row
        // the startV distance to itself is 0

    for (int i = 0; i < SIZE; i++) shortestDistanceArray[i] = G[startV][i];

    shortestDistanceArray[startV] = 0;
    
    for (int x = 0; x < SIZE; x++) // should this be x equal to 1? has to work regardless of start vertex
    {
        int minDistance = INFINITY; 
        int minVertex; 
        int alternatePathDistance = 0;
        // A. Choose a vertex 'minVertex' that is unvisited such that dist[minVertex] is minimum
        for (int currVertex = 0; currVertex < SIZE; currVertex++)
        {
            if (visitedVertices[x] != 1 && shortestDistanceArray[currVertex] < minDistance )
            {
                minDistance = shortestDistanceArray[currVertex];
                minVertex = currVertex ;
                
            }
        }
        // B. Add minVertex to settled
        visitedVertices[x] = 1;

         // C. For each vertex v in visited, relax the edge minVertex -> v
        for (int currentVertex = 0; currentVertex < SIZE; currentVertex++)
        {
            if (visitedVertices[currentVertex] != 1)
            {   
                alternatePathDistance = shortestDistanceArray[currentVertex] + G[minVertex][currentVertex]

                if (shortestDistanceArray[currentVertex]  < alternatePathDistance )
                {
                    shortestDistanceArray = 
                }
            }
        }
    }



    // first for 
        // finding the minimum distance to anything, and check if not in visited
        // if lower, that's your "chosen path to explore"

    // some 'relaxation algo' that looks for alternative pathhs to some other vertex


    
}

void displayDijk(int D[]){
    int i, x;
    printf("Source\tCost\n");
    for(x = 0; x < SIZE; x++){
        printf("%d\t%d\n", x,D[x]);
    }
}