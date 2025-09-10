// Purpose: Demonstrate the different ways of working with a structure which contains an array


// Date started: Aug. 26, 2025

#include <stdio.h>
#include <stdlib.h>
#define MAX 50



// Version 1 

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

} V1;


typedef int Position;


void 


void insert (V1 *studList, Student s){

    if (studList->count == MAX){

        printf("Student Array is full!");
    } else
    {
        studList->Elements[studList->count++] = s;
    }

}


void delete (V1* studList, Student s){ //delete by ID number
    int i;
    for (i = 0; i < studList ->count &&  studList ->Elements[i].ID != s.ID; i++){};
    
    if (i > studList->count){
        printf("Student Not Found!");
    } else{

        for (int j = i; j < studList ->count; j++){
            studList->Elements[j] = studList->Elements[j + 1]; 
        }

        studList->count--;
        
    }

}


int locate (V1 studList, Student s){
    int i;
    for (i = 0; studList.count && studList.Elements[i].ID != s.ID; i++){}

    if (studList.count){
        printf("Student not found");
    } else {

        return i;
    } 
}

void printList (V1 *studList){

    for (int i = 0; i < studList->count; i++){

        printf("%s %c %s\n", studList->Elements[i].name.fName, studList->Elements[i].name.MI, studList->Elements[i].name.LName);
    }

}


int main(){

    V1 L;
    L.count = 0;
    Student s1 = {{"Help", "Me", 'P'}, 0, "CS", 1};
    Student s2 = {{"Help", "Me", 'D'}, 0, "CS", 2};

    insert(&L, s1);
    insert(&L, s2);
    Student s3 = {{"Alice", "Smith", 'A'}, 1, "IT", 1};
    Student s4 = {{"Bob", "Brown", 'B'}, 2, "CS", 2};
    Student s5 = {{"Carol", "Jones", 'C'}, 3, "IS", 3};
    Student s6 = {{"David", "Lee", 'D'}, 4, "CS", 4};
    Student s7 = {{"Eve", "Clark", 'E'}, 5, "IT", 2};

    insert(&L, s3);
    insert(&L, s4);
    insert(&L, s5);
    insert(&L, s6);
    insert(&L, s7);

    printList(&L);
    
    
    delete(&L, s1);
    printf("\nDelete S1!\n");
    printList(&L);

    printf("\nStudent ID of %s is %d\n", s7.name, s7.ID);
    printf("Student ID of %d is at index %d", locate(L, s7));
}

