#include "arrayStack.h"
// #include "linkedListStack.h"


int main(){
    Stack S1;
    Stack S2;
    init(&S1);
    init(&S2);

    printf("First Stack\n");
    printf("=============\n");
    push(&S1, 'A');
    push(&S1, 'B');
    push(&S1, 'C');
    push(&S1, 'D');

    printStack(&S1);

    // while (!isEmpty(&S1)){
    //     push(&S2, top(&S1));
    //     pop(&S1);
    // }

    // printf("\n\nSecond Stack\n");
    // printf("=============\n");
    // printStack(&S2);

    // push(&S1, 'W');

    // while (!isEmpty(&S2)){
    //     push(&S1, top(&S2));
    //     pop(&S2);
    // }
    // printf("\n\nInserted letter W at bottom of Stack 1\n");
    // printf("=============\n");
    

    char elemToDel = 'A';
    printf("\n\nDeleting letter %c\n", elemToDel);
    printf("=============\n");

    deleteElem(&S1, elemToDel);
    printStack(&S1);
}   