#include <stdio.h>
#include <stdlib.h>
#define SIZE 50


typedef struct {

    char fname[16];
    char lname[16];
    char MI;


} nameType;

typedef struct {

    nameType name;
    int ID;
    char course[16];
    int year;


} Student;



typedef struct {

    int count; 
    Student* Elements;

} V3;


void insert (V3 *studList, Student Elements[], Student s){

    Elements[studList->count++] = s;

}


void printList (V3 *studList, Student Elements[]){

    for (int i = 0; i < studList->count; i++){

        printf("%s %c %s\n", Elements[i].name.fname, Elements[i].name.MI, Elements[i].name.lname);
    }

}


int main(){

    Student Elements[SIZE];
    nameType nameArray = {"Help", "Me", 'P'};
    V3 L;
    Student s1 = {nameArray, 0, "CS", 1};
    L.count = 0;

    insert(&L, Elements, s1);
    printList(&L, Elements);
    

}