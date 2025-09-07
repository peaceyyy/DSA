#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{

    char data; 
    struct Node* link;

} *node_t;


node_t createNode (int x){

    node_t newNode = malloc(sizeof(struct Node));

    if (!newNode){
        fprintf(stderr, "Memory alloc failed!");
    } else { 
        newNode->data = x;
        newNode->link = NULL;
    } 
}

void init (node_t* S){
    *S = NULL;
}

void push(node_t* S, int x){

    node_t newNode = createNode(x);

    if ((*S) == NULL){
        (*S) = newNode; 
    } else {
        newNode ->link = *S;
        (*S) = newNode; 
    }   
    
}

bool isEmpty (node_t S){
    return S == NULL;
}

int pop(node_t* S){

    if (isEmpty(*S)){

        printf("Stack is empty");

    } else {

        node_t temp = (*S);
        int data = (*S)->data;
        *(S) = (*S)->link;
        free(temp);
        return data;       
    }


}

int peek (node_t S){

 if (isEmpty(S)){

        printf("node_t is empty");

    } else {
        return (S)->data;       
    }

}

void displayStack (node_t S){

    node_t trav = S; 

    for (; trav != NULL; trav = trav->link) printf("%d \n" , trav->data);

}



int main(){

    node_t StackHead;
    init(&StackHead);

    push(&StackHead, 1);
    push(&StackHead, 2);
    push(&StackHead, 3);
    push(&StackHead, 3);
    displayStack (StackHead);

    printf("Popped: %d", pop(&StackHead));

}

