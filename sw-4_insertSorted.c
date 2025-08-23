#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{

    char elem;
    struct Node *link;

} *charList;

void insertSorted(charList *L, char elem)
{

     charList newNode = (charList)malloc(sizeof(struct Node));
     newNode->elem = elem;

    if (*L == NULL || elem < (*L)->elem)
    {
        newNode->link = (*L);
        *L = newNode;
    }

    else
    {

        charList *trav = L;

        for (; (*trav) != NULL && elem > (*trav)->elem; trav = &(*trav)->link)
        {
        }

        if (trav != NULL)
        {

            newNode->link = (*trav);
            (*trav)= newNode;
        }
    }
}

void printList(charList L)
{

    for (charList trav = L; trav != NULL; trav = trav->link)
    {
        printf("%c ", trav->elem);
    };
}

int main()
{

    charList L = NULL;
    insertSorted(&L, 'a');
    insertSorted(&L, 'a');
    insertSorted(&L, 'a');
    insertSorted(&L, 'a');
    insertSorted(&L, 'a');
    insertSorted(&L, 'c');
    insertSorted(&L, 'b');


    printList(L);
}