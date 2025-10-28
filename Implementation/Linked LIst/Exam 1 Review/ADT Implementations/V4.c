// List is a structure with an array & variable count (a variable that keeps track of the number of elements in the array list)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct
{

    char LName[16];
    char FName[24];
    char MI;
} nameType;

typedef struct
{

    nameType name;
    char gender;
    int ID;
    int year;
    char course[8];

} studentType;

typedef struct
{

    studentType *elemPtr;
    int count;

} *LIST;

void initList(LIST *L)
{
    *L = malloc(sizeof(LIST));
    (*L)->elemPtr = malloc(sizeof(studentType) * MAX);
    (*L)->count = 0;
}

void insertSorted(LIST *L, studentType student)
{

    int i;
    for (i = 0; i < (*L)->count && strcmp(student.name.LName, (*L)->elemPtr[i].name.LName) > 0; i++)
    {
    }

    if (i < (*L)->count)
    {
        printf("inserting...");
        for (int j = MAX; j > i; j--)
        {
            (*L)->elemPtr[j] = (*L)->elemPtr[j - 1];
        }

        (*L)->elemPtr[i] = student;
    }
    else
    { // if student goes at the end
        (*L)->elemPtr[(*L)->count] = student;
    }

    (*L)->count++;
}

void insertElemAtPos(LIST *L, int elem, int pos)
{
}

void deleteElem(LIST *L, studentType student) // delete by Last name
{
    int i;

    for (i = 0; i < (*L)->count && strcmp((*L)->elemPtr[i].name.FName, student.name.FName) != 0; i++) {}

        if (i < (*L)->count)
        { // exists

            for (int j = i; j < (*L)->count; j++)
            {
                (*L)->elemPtr[j] = (*L)->elemPtr[j + 1];
            }
        }

    (*L)->count--;
}

void deleteAllOccurrences(LIST *L, studentType student)
{

    int i = 0;


    while (i < (*L)->count){

        if (strcmp((*L)->elemPtr[i].name.LName, student.name.LName) == 0){

            for (int j = i; j < (*L)->count; j++)
            {
                (*L)->elemPtr[j] = (*L)->elemPtr[j + 1];
            }
            (*L)->count--;

        }   else
        {
            i++;
        }
    }


}

void searchElem(LIST* L, int elem)
{
}
void displayList(LIST* L)
{

    for (int i = 0; i < (*L)->count; i++)
        printf("%s %s | ID: %d | %s - %d \n", (*L)->elemPtr[i].name.FName, (*L)->elemPtr[i].name.LName, (*L)->elemPtr[i].ID, (*L)->elemPtr[i].course, (*L)->elemPtr[i].year);
}

int main()
{

    LIST L;
    initList(&L);

    studentType stud2 = {{"Smith", "John", 'B'}, 'M', 2, 2, "BSIT"};
    studentType stud1 = {{"Dorin", "Homer", 'A'}, 'M', 1, 1, "BSCS"};
    studentType stud3 = {{"Dorin", "Anna", 'C'}, 'F', 3, 1, "BSCS"};
    studentType stud4 = {{"Lee", "Sara", 'D'}, 'F', 4, 3, "BSCS"};
    studentType stud5 = {{"Dorin", "Mike", 'E'}, 'M', 5, 2, "BSCS"};

    insertSorted(&L, stud1);
    insertSorted(&L, stud2);
    insertSorted(&L, stud3);
    insertSorted(&L, stud4);
    insertSorted(&L, stud5);

    printf("\nList before deleting all occurrences of 'Dorin':\n");
    displayList(&L);
    printf("\n");
    
    // deleteAllOccurrences(&L, stud1); // Deletes all with LName "Dorin"
    
    // printf("List after deleting all occurrences of 'Dorin':\n");
    // displayList(&L);
    // printf("\n");
    
    deleteElem(&L, stud2); // delete Smith
    deleteElem(&L, stud5); // delete Mike
    displayList(&L);
}
