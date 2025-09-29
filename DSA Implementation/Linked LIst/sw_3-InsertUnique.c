// insert unique

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char elem;
    struct Node* link;

} *charList;

void insertUnique (charList* L, char elem){
    charList* trav = L;
    for (; *trav != NULL && (*trav)->elem != elem; trav = &(*trav)->link){}

    if (*trav == NULL){

        charList newNode = (charList) malloc(sizeof(struct Node));
        newNode->elem = elem;
        newNode->link = NULL;
        *trav = newNode;
    }
}


void printList(charList L)
{

    for (charList trav = L; trav != NULL; trav = trav->link)
    {
        printf("%c ", trav->elem);
    };
}




int main(){

    charList L = NULL; 
    insertUnique(&L, 'x');
    // insertUnique(&L, 'x');
    // insertUnique(&L, 'y');
    // insertUnique(&L, 'z');
    // insertUnique(&L, 'z');
    // insertUnique(&L, 'y');
    


    printList(L);

    

}

