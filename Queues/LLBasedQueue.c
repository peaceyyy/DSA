#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {

    char data; 
    struct Node* link;

} *node_t;


typedef struct {
    node_t front;
    node_t rear; 
} Queue; 


void init (Queue* Q){
    Q->front = NULL; 
    Q->rear = NULL;
}

node_t createNode (char data){

    node_t newNode = (node_t) malloc(sizeof(struct Node));
    newNode ->data = data; 
    newNode ->link = NULL;
}

bool isEmpty (Queue* Q){
    return Q == NULL;
}

void enqueue (Queue* Q, char data){}
void dequeue (Queue* Q){}
char front (Queue* Q){}
void emptyQueue (Queue* Q){}
void makeNULL (Queue* Q){}

bool findElem (Queue* Q){}
void deleteElem (Queue* Q){}



int main(){

}