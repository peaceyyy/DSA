#include <stdio.h>
#include <stdlib.h>


typedef struct Node {

   char data; 
   struct Node* link; 

} *L;


void initializeList (L* ListHead) 
{
    *ListHead = NULL;
}

void insertFirst(L* ListHead, char elem) {
    L newNode = (L)malloc(sizeof(struct Node));
    if (newNode == NULL) return;
    newNode->data = elem;
    newNode->link = *ListHead;
    *ListHead = newNode;
}

void insertLast(L* ListHead, char elem) {
    L newNode = (L)malloc(sizeof(struct Node));
    if (newNode == NULL) return;
    newNode->data = elem;
    newNode->link = NULL;
    if (*ListHead == NULL) {
        *ListHead = newNode;
    } else {
        L trav = *ListHead;
        while (trav->link != NULL) {
            trav = trav->link;
        }
        trav->link = newNode;
    }
}


void insertLastV2(L* ListHead, char elem) {
    L newNode = (L)malloc(sizeof(struct Node));
    
    
    newNode->data = elem;
    newNode->link = NULL;

    if (*ListHead == NULL) {
        *ListHead = newNode;
    } else {
        L* trav = ListHead;
        for (; *trav != NULL; trav = &(*trav)->link){}
        *trav = newNode; 

    }
}

void printList(L ListHead) {

    if (ListHead == NULL){
        printf("List is empty!");
    }
    else{
         for (L trav = ListHead; trav != NULL; trav = trav->link) {
        printf("%c ", trav->data);
    }
    printf("\n");

    }
   
}



void delete (L* ListHead, char elem)
{
    if ((*ListHead)->data == elem){
        L temp = *ListHead;
        *ListHead = (*ListHead)->link;
        free(temp);
    } else {

        L* trav = ListHead;

        for (; (*trav) != NULL && (*trav)->data != elem; trav = &(*trav)->link){} //1

        if (*trav != NULL){
            L* temp = trav; //2
            *trav= *temp;   //3
            free(temp); //4

        } else {
            printf("Element not found!\n");
        }
    
    }
    
}






int main() {
    L ListHead;
    initializeList(&ListHead);

    insertLastV2(&ListHead, 'a');
    printList(ListHead);
    // insertLastV2(&ListHead, 'b');
    // insertLastV2(&ListHead, 'c');
    insertFirst(&ListHead, 'x');
    insertLastV2(&ListHead, 'y');
    printList(ListHead);

    printf("\n");

    delete(&ListHead, 'x');
    printList(ListHead);

    delete(&ListHead, 'a');
    printList(ListHead);

    return 0;
}