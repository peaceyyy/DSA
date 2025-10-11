#include <stdio.h>
#include <stdlib.h>

typedef struct node {

    char elem;
    struct node* next;

} *SET, node_t;   

void init (SET* A){

    *A = NULL;
}


void insertLast (SET* A, char elem){

    SET* trav; 
    
    SET newNode = (SET) malloc(sizeof(newNode));
    newNode -> elem = elem; 
    newNode -> next = NULL;
    
    if (newNode)
    {
    for (trav = A; *trav != NULL; trav = &(*trav)->next){};
    *trav = newNode;  
    }
}


void display (SET A)
{
    SET trav;
    
    for (trav = A; trav != NULL; trav = trav -> next)
    {
        printf("%c->", trav->elem);
    }
}

// void sortSet (SET* A)
// {   
//     char temp;

//     for (SET* i = A; (*i) != NULL; (i) = &(*i) ->next){

//         int swapped = 0;
//         for (SET* j = &(*A)->next; swapped != 1 && (*j)->next != NULL; j = &(*j)-> next)
//         {
//             if ((*j) -> elem > (*j)->next->elem)
//             {
//                 temp = (*j) -> elem;
//                 (*j)->elem  = (*j)->next->elem;
//                 (*j)->next->elem = temp;
//                 swapped = 1;
//             }
//         }
//     }
// }

void sortSet (SET A)
{   
    char temp;

    for (SET i = A; (i) != NULL; (i) = (i) ->next){

            for (SET j = A; j->next != NULL ; j = (j)-> next)
        {
            if ((j) -> elem > (j)->next->elem)
            {
                temp = (j) -> elem;
                (j)->elem  = (j)->next->elem;
                (j)->next->elem = temp;
            }
        }

    } 
}

SET mergeSet (SET A, SET B)
{
    sortSet(A);
    sortSet(B);

    printf("\n");
    display(A);
    printf("\n");
    display(B);
    printf("\n");

    SET C, aptr, bptr, *cptr; 
    C = NULL; 
    cptr = &C;

    aptr = A; 
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {  
        *cptr = (SET) malloc(sizeof(node_t)); 
        
        if (aptr->elem < bptr->elem)
        {
            // printf("i happened");
            (*cptr)->elem = aptr->elem;
            aptr = aptr->next;
        } else {
            
            // printf("i happened two");
            if (aptr->elem == bptr->elem)
            {
                aptr = aptr->next;
            }
            
            (*cptr)->elem = bptr->elem;
            bptr = bptr -> next;
        }   
        cptr = &(*cptr)->next;
    }
    
    
    aptr = (aptr != NULL) ? aptr : bptr;
    
    while (aptr != NULL){
        
        *cptr = (SET)malloc(sizeof(node_t));
        (*cptr)->elem = aptr->elem;
        aptr = aptr->next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;
    return C;
    
}   


int main(){
    
    SET A; 
    init(&A);
    SET B; 
    init(&B);
    
    insertLast(&B, 'Z');
    insertLast(&A, 'A');
    insertLast(&A, 'E');
    insertLast(&A, 'G');
    insertLast(&B, 'B');
    insertLast(&A, 'C');
    insertLast(&A, 'D');
    
    insertLast(&B, 'F');
    insertLast(&B, 'H');
    insertLast(&B, 'A');
    insertLast(&A, 'Z');
    
    
    display(A);
    printf("\n\n");
    display(B);
    printf("\n\n");
    
    SET C = mergeSet(A, B);    
    display(C);
}