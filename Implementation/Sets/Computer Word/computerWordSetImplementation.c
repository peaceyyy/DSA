#include <stdio.h>


typedef char SET        ;
void displayBitPattern (SET A)
{
    unsigned int mask = 1 << sizeof(char) * 7;

    while (mask > 0)
    {
        printf("%d", (A & mask) != 0 ? 1 : 0);
        mask >>= 1;
    }
}

void displaySetElements (SET A){

    int size = sizeof(char) * 7;

    for (int i = 0; i <= size; i++){
        // printf("hi\n");
        if ((A & 1 << i) > 0) printf("%d,", i);
    }
}


void initSet (SET* A)
{
    *A = 0;
}


void insertSet (SET* A, int x){

    *A = *A | 1 << x;
}

void deleteSet (SET* A, int x){

    *A = *A & ~(1 << x);
}

SET Union (SET A, SET B)
{
    return A | B;
}

SET Intersection (SET A, SET B)
{
    return A & B;
}

SET Difference (SET A, SET B)
{
    return A & ~B;
}

int isSubset (SET A, SET B)
{
    return (A & B) == B;
}


int main(){
    SET A; 
    initSet(&A);


    // insertSet(&A, 7);
    // insertSet(&A, 6);
    // insertSet(&A, 5);
    // insertSet(&A, 4);
    // insertSet(&A, 3);
    // insertSet(&A, 2);
    // insertSet(&A, 1);
    insertSet(&A, 0);
    // deleteSet(&A, 7);
    displayBitPattern(A);
    printf("\n");
    displaySetElements(A);
}


