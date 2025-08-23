#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10

typedef struct node
{
    char elem;
    struct node *link;
} *charList;

charList initializeCharList()
{

    return NULL;
}

void insert(charList *L, char elem)
{

    charList newNode = malloc(sizeof(struct node));
    newNode->elem = elem;
    newNode->link = NULL;

    if (*L == NULL)
    {
        *L = newNode;
    }
    else
    {

        charList trav = *L;
        for (; trav->link != NULL; trav = trav->link)
        {
        };
        trav->link = newNode;
    }
}

void printList(charList L)
{

    for (charList trav = L; trav != NULL; trav = trav->link)
    {
        printf("%c ", trav->elem);
    };
}

bool findElem(charList L, char elem)
{

    charList trav = L;
    for (; trav != NULL && trav->elem != elem; trav = trav->link)
    {
    }
    return trav != NULL ? true : false;
}

void deleteElem(charList *L, char elem)
{
    if (*L == NULL)
    {
        printf("List is empty");
        // return;
    }

    else
    {
        // Special case: head node
        if ((*L)->elem == elem)
        {
            charList temp = *L;
            *L = (*L)->link;
            free(temp);
            
        } else {

        charList trav;
        for (trav = *L; trav->link != NULL && trav->link->elem != elem; trav = trav->link)
        {
        }

        if (trav->link == NULL)
        {
            printf("Element is not in list");
            
        } else {

  // Delete the node
        charList temp = trav->link;
        trav->link = trav -> link -> link;
        free(temp);

        }

      
    }

}

}


void deleteAllOccurrences (charList* L, char elem)
{

    if (*L == NULL) printf("List is empty");
    else if ((*L)->elem == elem) {
        *L = (*L)->link;
    }
    else { 
        charList trav = *L; 
        while (trav->link != NULL){

            if (trav->link->elem == elem){

                charList temp = trav->link;
                trav -> link = trav->link->link;
                free(temp);
               
            } else trav = trav -> link;
            

        }

        if (trav->link == NULL) printf("Element is not in list\n");

    }


}
int main()
{

    charList L1 = initializeCharList();
    insert(&L1, 'u');
    insert(&L1, 's');
    insert(&L1, 's');
    insert(&L1, 'c');

    printList(L1);
    printf("\n\n");
    deleteAllOccurrences(&L1, 'c');
    printList(L1);

    return 0;
}