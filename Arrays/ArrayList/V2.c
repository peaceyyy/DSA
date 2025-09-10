// Purpose: Demonstrate the different ways of working with a structure which contains an array


// Date started: Aug. 26, 2025

#include <stdio.h>
#include <stdlib.h>
#define MAX 50


// Version 2

typedef struct {

    char fName[16];
    char LName[16];
    char MI;

} nameType;

typedef struct {

    nameType name;
    int ID;
    char course[4];
    int year; 
    

} Student;


typedef struct {

    Student Elements[MAX];
    int count;

} *V2;


void insert (V2 studList, Student s){

    
    if (studList->count == MAX){

        printf("Student Array is full!");
    } else
    {
        studList->Elements[studList->count++] = s;
    }

}

void printList (V2 studList){

    if (studList -> count == 0){
        
        printf("List is empty!");

    } else {

        for (int i = 0; i < studList->count; i++){

        printf("%s %c %s\n", studList->Elements[i].name.fName, studList->Elements[i].name.MI, studList->Elements[i].name.LName);
    }
       
    }
}

int main(){

    V2 L = (V2)malloc(sizeof(struct { Student Elements[MAX]; int count; }));
    L->count = 0;
    Student s1 = {{"Help", "Me", 'P'}, 0, "CS", 1};

    insert(L, s1);
    printList(L);
}

