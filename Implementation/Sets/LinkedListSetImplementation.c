#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{

    int elem;
    struct Node *next;

} ctype, *SET;

void initializeSet(SET *A)
{

    *A = NULL;
}

void insert(SET *A, int x)
{

    if (*A == NULL)
    {
        ctype *newNode = (ctype *)malloc(sizeof(ctype));
        newNode->elem = x;
        newNode->next = NULL;

        *A = newNode;
    }
    else
    {

        SET *trav;

        for (trav = A; *trav != NULL && (*trav)->elem != x; trav = &(*trav)->next)
        {
        };

        if (*trav == NULL)
        {

            ctype *newNode = (ctype *)malloc(sizeof(ctype));
            newNode->elem = x;
            newNode->next = NULL;

            *trav = newNode;
        }
    }
}

void delete(SET *A, int x)
{

    if (*A != NULL)
    {

        SET *trav;

        for (trav = A; *trav != NULL && (*trav)->elem != x; trav = &(*trav)->next)
        {
        };

        if (*trav != NULL)
        {
            ctype *temp = *trav;
            *trav = temp->next;
            free(temp);
        }
    }
}

SET setUnion(SET A, SET B)
{

    SET aptr, bptr, *cptr, dptr;
    SET C;
    cptr = &C;
    C = NULL;

    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        *cptr = (SET)malloc(sizeof(ctype));

        if (aptr->elem < bptr->elem)
        {

            (*cptr)->elem = aptr->elem;
            aptr = aptr->next;
        }
        else
        {

            if (aptr->elem == bptr->elem)
            {
                aptr = aptr->next;
            }

            (*cptr)->elem = bptr->elem;
            bptr = bptr->next;
        }

        cptr = &(*cptr)->next;
    }

    dptr = (aptr != NULL) ? aptr : bptr;

    while (dptr != NULL)
    {

        *cptr = (SET)malloc(sizeof(ctype));
        (*cptr)->elem = dptr->elem;
        dptr = dptr->next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;
    return C;
}

SET setIntersection(SET A, SET B)
{

    SET aptr, bptr, *cptr;
    SET C;
    C = NULL;
    cptr = &C;

    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        *cptr = (ctype *)malloc(sizeof(ctype));

        if (aptr->elem > bptr->elem) // if the element is greater then we can hope and assume that it might be found later down the list in the second set
        {

            bptr = bptr->next; // just move second set pointer
        }

        else if (aptr->elem == bptr->elem)
        {
            (*cptr)->elem = aptr->elem;
            cptr = &(*cptr)->next;
            bptr = bptr->next;
        }

        aptr = aptr->next;
    }

    *cptr = NULL;
    return C;
}

// SET setDifference(SET A, SET B)
// {
//     SET aptr, bptr, *cptr;
//     SET C;
//     C = NULL;
//     cptr = &C;

//     while (aptr != NULL && bptr != NULL)
//     {
//         *cptr = (ctype *)malloc(sizeof(ctype));

//         if (aptr->elem < bptr->elem)
//         {
//             printf("fore");
//             (*cptr)->elem = aptr->elem;
//             (cptr) = &(*cptr)->next;
//             aptr = aptr->next;
//         }
//         else
//         {

//             printf("fore loop");
//             bptr = bptr->next;
//         }
//     }

//     while (aptr != NULL)
//     {

//         *cptr = (ctype *)malloc(sizeof(ctype));
//         (*cptr)->elem = aptr->elem;
//         (cptr) = &(*cptr)->next;
//         aptr = aptr->next;
//     }

//     *cptr = NULL;
//     return C;
// }

SET setDifference(SET A, SET B)
{
    SET aptr, bptr, *cptr;
    SET C;
    C = NULL;
    cptr = &C;

    aptr = A;
    bptr = B;

    while (aptr != NULL)
    {
        *cptr = (SET)malloc(sizeof(ctype));

        while (bptr != NULL)
        {
            if (aptr->elem == bptr->elem) // if they're the same jsut move both
            {
                aptr = aptr->next;
                bptr = bptr->next;
            }

            else if (aptr->elem < bptr->elem) // no hope in that the element in A will be further down in B
            {
                // printf("fire");
                (*cptr)->elem = aptr->elem;
                (cptr) = &(*cptr)->next;
                aptr = aptr->next;
            }
            else
            {
                // printf("move B");

                bptr = bptr->next; // just move B until we fulfill one ot the two conditions above
            }
        }

    
        (*cptr)->elem = aptr->elem;
        (cptr) = &(*cptr)->next;
        aptr = aptr->next;
    }

    
    *cptr = NULL;
    return C;
}


int isSubset (SET A, SET B)
{
    SET aptr, bptr;
     
    bptr = B; 

    while (bptr != NULL)
    {
        for (aptr = A; aptr != NULL; aptr = aptr->next)
        {
            if (aptr->elem == bptr->elem) // if it's a proper subset then b would reach NULL before a does because every element in b is in a
            {
                bptr = bptr->next;
            }
        }
    }

    return (bptr == NULL) ? 1 : 0;

}

void displaySet(SET A)
{
    if (A == NULL)
    {
        printf("Set is empty!");
    }
    else
    {

        for (SET trav = A; trav != NULL; trav = trav->next)
            printf("%d -> ", trav->elem);
    }
}



int main()
{

    SET A;
    SET B;
    initializeSet(&A);
    initializeSet(&B);
    // insert(&A, 0);
    // insert(&A, 1);
    // insert(&A, 2);
    // insert(&A, 3);
    // insert(&A, 4);
    // insert(&A, 5);
    // insert(&A, 7);
    // insert(&A, 8);
    // insert(&A, 9);
    // insert(&A, 10);
    // displaySet(A);

    printf("\n\n");

    // insert(&B, 0);
    // insert(&B, 1);
    // insert(&B, 2);
    // insert(&B, 3);
    // insert(&B, 4);
    // insert(&B, 6);
    // insert(&B, 8);
    // insert(&B, 10);

    // displaySet(B);

    // printf("\n\n");
    
    // SET C;
    // C = setUnion(A, B);
    // displaySet(C);
    
    // printf("\n\nSet Intersection:\n");
    
    // SET D;
    // D = setIntersection(A, B);
    // displaySet(D);
    
    // printf("\n\nSet Difference:\n");
    
    // SET E;
    // E = setDifference(A, B);
    // displaySet(E);
    
    // printf("\n\nSet Difference:\n");
    
    SET X;
    SET Y;

    initializeSet(&X);
    initializeSet(&Y);
    
    insert(&X, 1);
    insert(&X, 2);
    insert(&X, 3);
    insert(&X, 4);
    insert(&X, 5);
    insert(&X, 6);
    insert(&X, 7);
    insert(&X, 8);
    insert(&X, 9);
    insert(&X, 10);
    
    
    insert(&Y, 1);
    insert(&Y, 2);
    insert(&Y, 3);
    insert(&Y, 4);
    insert(&Y, 5);
    insert(&Y, 6);
    
    displaySet(X);
    printf("\n\n");
    displaySet(Y);
    
    
    printf("\n\n");
    if (isSubset(X, Y))
    {
        printf("it's a subset");
    } else {
        
        printf("it's not a subset");
    }
  
    
    
}