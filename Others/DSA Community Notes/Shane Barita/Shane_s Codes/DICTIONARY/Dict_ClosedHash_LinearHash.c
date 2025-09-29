/*
Dictionary Closed Hashing Linear Hashing Implementation
*/
//A. Include files and macro definition
#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define EMPTY 0
#define DELETED -1

//B. Data Structure definition
typedef int Dictionary[MAX];

//C. Function prototypes
void initDict(Dictionary D);
void displayDict(Dictionary D);
int hash(int elem);
void insertDict(Dictionary D, int elem);
void deleteDict(Dictionary D, int elem);
int isMember(Dictionary D, int elem);

//D. Function main
void main(){
    Dictionary D;
    printf("\n***** INITIALIZATION *****\n");
    initDict(D);
    displayDict(D);

    printf("***** INSERT ELEMENTS *****\n");
    insertDict(D, 33);
    insertDict(D, 69);
    insertDict(D, 73);
    insertDict(D, 14);
    insertDict(D, 19);
    displayDict(D);
    printf("***** DELETE ELEMENTS *****\n");
    deleteDict(D, 33);
    displayDict(D);
    printf("\n**** CHECK MEMBERSHIP ****\n");
    printf("is 69 a part of Dictionary D?: %d\n", isMember(D,69));
    printf("is 45 a part of Dictionary D?: %d\n", isMember(D,45));
    
}
//E. Function definitions of the prototypes
void initDict(Dictionary D){
    int index;
    for(index = 0; index < MAX; index++){
        D[index] = EMPTY;
    }
}
void displayDict(Dictionary D){
    int index;
    printf("\n INDEX     ELEMENT  HASH VALUE ");
    for(index = 0; index < MAX; index++){
        printf("\n[%d] ", index);
        if(D[index] == EMPTY){
            printf("%12s ", "EMPTY");
        } else if (D[index] == DELETED){
            printf("%12s ", "DELETED");
        }
        else{
            printf("%9d ", D[index]);
        }
        if(D[index] == EMPTY || D[index] == DELETED){
            printf("%9d ", 0);
        }else{
            printf("%9d", hash(D[index]));
        }
    }
}
int hash(int elem){
    return(elem % MAX);
}
void insertDict(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp;
    // Only insert if not already at home position
    if(D[hashVal] != elem){
        // Find first available slot (EMPTY or DELETED) - this is CORRECT
        // Loop stops when we find: the element already exists, empty slot, or deleted slot
        for(temp = hashVal; D[temp] != elem && D[temp] != EMPTY && D[temp] != DELETED; temp = (temp+1)%MAX){}
        D[temp] = elem;  // Place element in available slot
    }
}
void deleteDict(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp = hashVal;
    // MAJOR BUG: This will infinite loop if element doesn't exist!
    // Check home position first
    if(D[temp] != elem){
        // BUG HERE: No termination condition to prevent infinite wraparound
        // Should stop when we've checked all positions or hit EMPTY
        for(temp = hashVal+1; D[temp] != elem && D[temp] != EMPTY && D[temp] != DELETED; temp = (temp+1)%MAX){
            // MISSING: check if temp == hashVal (full circle)
        }
    }
    // DANGER: If element not found, this deletes random slot!
    // Should check if we actually found the element before deleting
    if(D[temp] == elem) {  // This check is MISSING in original
        D[temp] = DELETED;
    }
}
int isMember(Dictionary D, int elem){
    int hashVal = hash(elem);
    int temp, counter;
        for(temp = hashVal, counter = 1; counter < MAX && D[temp] != EMPTY && D[temp] != elem; counter++, temp = (temp+1) % MAX){}
        return (D[temp] != EMPTY && counter < MAX)? 1 : 0;
    
}
