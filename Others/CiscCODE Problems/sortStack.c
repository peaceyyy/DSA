#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct {
    int elems[MAX];
    int top;
} Stack;

void init (Stack** S){
    *S = (Stack*) malloc(sizeof(Stack));
    (*S)->top = 0; 
}














int main(){


    // while 

    //pop first the top and store in temp 
    // compare temp with pop(Stack) until
    //  - temp < pop
    //  - isEmpty(Stack)
    
    // once pop < temp
    // push(temp, S1)
    // while (!isEmpty(tempStack)) push (S1, pop(tempStack))
}

