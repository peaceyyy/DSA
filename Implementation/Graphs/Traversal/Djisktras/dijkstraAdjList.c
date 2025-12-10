#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#define INF INT_MAX 
#define MAX 6

typedef struct cell{
 int vertex;
 int length;
 struct cell *link;
}node, *list;

typedef list adj_list[MAX];

int** Dijkstra(adj_list L, int start){

   int** shortestDistanceArr = (int **)malloc(MAX * sizeof(int *));
   
   int visited[MAX] = {0};
   int minDistance = INT_MAX, minVertex;

   // fill distance for immediate neighbors
   node* trav = L[start];
   int count = 0;

   while (trav != NULL)
   {
      shortestDistanceArr[count++] = trav->length;
      trav = trav->link;
   }

   shortestDistanceArr[start] = 0;

   for (int x = 1; x < MAX; x++)
   {
      for (int i = 0; i < MAX; i++)
      {
         node* currentVertex = L[i];

         while (trav != NULL)
         {
            if (visited[trav->vertex] != 1 && shortestDistanceArr[< minDistance)
            {
               minDistance = trav->vertex;
               minVertex = currentVertex;
            }
         }
      }





   }

   

}

void displayLengthAndPath(int **D, int start){
   printf("\n\nDijkstra's algorithm - Starting from vertex %d\n",start);
   printf("Vertex  Dist   Path", start);
   int x,y;
   for(x=0;x<MAX;x++){
     printf("\n%d\t%d\t%d",x,D[x][0],x);
     for(y=D[x][1]; y!=-1; y=D[y][1]){
        printf("<-%d",y);
     }
   }

   
}

void populate(adj_list L){
   int A[][3] = {{0,2,2},{2,0,2},{0,1,4},{1,0,4},{4,1,3},{1,4,3},{2,3,2},{3,2,2},{3,4,3},{4,3,3},{2,5,4},{5,2,4},{3,5,1},{5,3,1},{5,4,1},{4,5,1}};
   int numPaths = 16;
   int x;
   list temp;
   for(x=0;x<numPaths;x++){
   		temp = (list)malloc(sizeof(node));
   		temp->vertex = A[x][1];
   		temp->length = A[x][2];
   		temp->link = L[A[x][0]];
	   	L[A[x][0]] = temp;
   }
}

void main(){
   adj_list L = {NULL,NULL,NULL,NULL,NULL,NULL};
   populate(L);
   int start,x;
   for(x=0;x<MAX;x++){
   	  start = x;
    	  // Expected outputs for each `start` on this undirected graph:
    	  // start = 0:
    	  // Vertex  Dist   Path
    	  // 0	0	0
    	  // 1	4	1<-0
    	  // 2	2	2<-0
    	  // 3	4	3<-2<-0
    	  // 4	6	4<-5<-3<-2<-0
    	  // 5	5	5<-3<-2<-0
    	  //
    	  // start = 1:
    	  // Vertex  Dist   Path
    	  // 0	4	0<-1
    	  // 1	0	1
    	  // 2	6	2<-0<-1
    	  // 3	5	3<-5<-4<-1
    	  // 4	3	4<-1
    	  // 5	4	5<-4<-1
    	  //
    	  // start = 2:
    	  // Vertex  Dist   Path
    	  // 0	2	0<-2
    	  // 1	6	1<-0<-2
    	  // 2	0	2
    	  // 3	2	3<-2
    	  // 4	4	4<-5<-3<-2
    	  // 5	3	5<-3<-2
    	  //
    	  // start = 3:
    	  // Vertex  Dist   Path
    	  // 0	4	0<-2<-3
    	  // 1	5	1<-4<-5<-3
    	  // 2	2	2<-3
    	  // 3	0	3
    	  // 4	2	4<-5<-3
    	  // 5	1	5<-3
    	  //
    	  // start = 4:
    	  // Vertex  Dist   Path
    	  // 0	6	0<-2<-3<-5<-4
    	  // 1	3	1<-4
    	  // 2	4	2<-3<-5<-4
    	  // 3	2	3<-5<-4
    	  // 4	0	4
    	  // 5	1	5<-4
    	  //
    	  // start = 5:
    	  // Vertex  Dist   Path
    	  // 0	5	0<-2<-3<-5
    	  // 1	4	1<-4<-5
    	  // 2	3	2<-3<-5
    	  // 3	1	3<-5
    	  // 4	1	4<-5
    	  // 5	0	5
    
    	  int **D = Dijkstra(L,start);
   	  displayLengthAndPath(D, start);
   }
   
}


