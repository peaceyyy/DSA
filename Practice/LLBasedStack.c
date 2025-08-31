#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{

    char data; 
    struct Node* link;

} *node_t;

typedef struct {

    node_t head; 
    int top;
    int size; 

} Stack;


node_t createNode (int x){

    node_t newNode = malloc(sizeof(struct Node));

    if (!newNode){
        fprintf(stderr, "Memory alloc failed!");
    } else { 
        newNode->data = x;
        newNode->link = NULL;
    } 
}

void initStack(Stack** S,int size){
    
    S = malloc(sizeof(Stack));
    (*S)->head = NULL;
    (*S)->size = size;
    (*S)->top = -1;

}

void push(Stack** S, int x){
    if (isFull(**S)){
    
        printf("Stack is full!");


    } else {

    node_t newNode = createNode(1);

    if ((*S)->head == NULL){
        (*S)->head = newNode; 
    } else {
        (*S)->head->link = newNode;
    }   

    (*S)->top++;

    }
}

bool isFull (Stack S){
    return S.top == S.size;
}


bool isEmpty (Stack S){
    return S.top == -1;
}

int pop(Stack* S){

    if (isEmpty(*S)){

        printf("Stack is empty");

    } else {

        return S->to
    }


}

int peek (Stack S){


}



int main(){

    L 

}

