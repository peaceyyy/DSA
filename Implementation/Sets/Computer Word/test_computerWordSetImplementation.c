#include <stdio.h>
#include "computerWordSetImplementation.c"

int main() {
    SET A, B, C;

    // Test initSet
    initSet(&A);
    printf("Test initSet: ");
    displayBitPattern(A); // Expect: 00000000
    printf("\n");

    // Test insertSet
    insertSet(&A, 3);
    printf("Test insertSet (insert 3): ");
    displayBitPattern(A); // Expect: 00001000
    printf("\n");

    insertSet(&A, 7);
    printf("Test insertSet (insert 7): ");
    displayBitPattern(A); // Expect: 10001000
    printf("\n");

    deleteSet(&A, 3);
    printf("Test deleteSet (delete 3): ");
    displayBitPattern(A); // Expect: 10000000
    printf("\n");

    // Test Union
    initSet(&B);
    insertSet(&B, 0);
    insertSet(&B, 1);
    C = Union(A, B);
    printf("Test Union (A | B): ");
    displayBitPattern(C); // Expect: 10000011
    printf("\n");

    // Test Intersection
    C = Intersection(A, B);
    printf("Test Intersection (A & B): ");
    displayBitPattern(C); // Expect: 00000000
    printf("\n");

    insertSet(&A, 1);
    insertSet(&A, 2);
    insertSet(&A, 3);
    insertSet(&A, 4);
    C = Intersection(A, B);
    printf("Test Intersection (A & B) after insert 1 to A: ");
    displayBitPattern(C); // Expect: 00000010
    printf("\n");

    // Test Difference
    C = Difference(A, B);
    printf("Test Difference (A & ~B): ");
    displayBitPattern(C); // Expect: 10000000
    printf("\n");

    // Test isSubset
    initSet(&B);
    insertSet(&B, 1);
    insertSet(&B, 7);
    printf("Test isSubset (B subset of A): %d\n", isSubset(A, B)); // Expect: 1

    insertSet(&B, 2);
    insertSet(&B, 4);
    insertSet(&B, 7);
    printf("\nAfter adding 5\n");
    insertSet(&B, 5);
    printf("Test isSubset (B not subset of A): %d\n", isSubset(A, B)); // Expect: 0
    
    

    displaySetElements(A);
    printf("\n");
    displaySetElements(B);

    return 0;
}