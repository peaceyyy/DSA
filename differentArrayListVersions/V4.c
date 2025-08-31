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

} V4;


void initList (V4* studList){

    studList->count = 0;
    studList->Elements = malloc(sizeof(V4));
    
}


void insert (V4 *studList, Student s){

    stud

}


void printList (V4 *studList){

    for (int i = 0; i < studList->count; i++){

        printf("%s %c %s\n", );
    }

}


int main(){

    V4* L;
    initList(&L);
    L->Elements = malloc(sizeof(Student) * SIZE);

    Student s1 = {{"Help", "Me", 'P'}, 0, "CS", 1};



    printList(L);
    

}