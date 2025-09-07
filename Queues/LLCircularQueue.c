#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct { 
    char LName[16];
    char FName[24];
} nameType;


typedef struct {

    nameType studName;
    int age;
    int ID; 

} studType;


typedef struct Node {

    studType stud;
    struct Node* link;

} *nodeType;

typedef struct {

    nodeType front; 
    nodeType rear; 

} CircularQueue;


nodeType createStudNode (studType stud){

    nodeType studNode = malloc(sizeof(studType));
    if (studNode != NULL) {
        studNode->stud = stud;
        studNode->link = NULL;
    }
    return studNode;

}

void init (CircularQueue* CQ){

    CQ->front = CQ->rear = NULL;
}


bool isEmpty (CircularQueue* CQ){
    return CQ->front == NULL ? true : false; 
}

void enqueue (CircularQueue* CQ, nodeType studNode){
    if (isEmpty(CQ)){
        CQ->front = studNode; 
    } else { 
        CQ->rear->link = studNode;
    }
    studNode->link = CQ->front;
    CQ->rear = studNode;
}

studType dequeue (CircularQueue* CQ){
    if(isEmpty(CQ)){
        studType sentinel = {{"", ""}, -1, -1};
        return sentinel; 
    } else { 
        nodeType temp = CQ->front; 
        studType studData = CQ->front->stud;
        CQ->front = CQ->front->link;
        CQ->rear->link = CQ->front; 
        free(temp);
        return studData;
    }
}

void displayStudList (CircularQueue* CQ){
    if (isEmpty(CQ)){
        printf("It is empty!\n");
    } else { 
        nodeType trav;
        for (trav = CQ->front; trav != CQ->rear; trav = trav->link){
            printf("ID: %d, Name: %s %s, Age: %d\n", trav->stud.ID, trav->stud.studName.FName, trav->stud.studName.LName, trav->stud.age);
        }
    }
}


int main(){
    CircularQueue CQ;
    init(&CQ);

    studType s1 = {{"Doe", "John"}, 20, 1001};
    studType s2 = {{"Smith", "Jane"}, 21, 1002};
    studType s3 = {{"Brown", "Alice"}, 22, 1003};

    nodeType n1 = createStudNode(s1);
    nodeType n2 = createStudNode(s2);
    nodeType n3 = createStudNode(s3);

    // Enqueue students
    enqueue(&CQ, n1);
    enqueue(&CQ, n2);
    enqueue(&CQ, n3);

    // Display queue
    displayStudList(&CQ);

    // Dequeue one student
    // dequeue(&CQ);

    // Display queue again
    // displayStudList(&CQ);
}



