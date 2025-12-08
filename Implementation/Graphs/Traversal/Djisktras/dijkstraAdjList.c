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

   int x, i, w, min=999;
   list trav;
   int visited[MAX] = {0};
   int **D = (int**)calloc(MAX, sizeof(int*));

   for (int i )
   
   
   return D;
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
   	  int **D = Dijkstra(L,start);
   	  displayLengthAndPath(D, start);
   }
   
}


