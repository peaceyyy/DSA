/*
========================================
PROBLEM 3: The Alien Invasion Defense Protocol
Difficulty: ★★★☆☆ (Medium)
Topic: Linked List Set Operations (Sorted)
========================================

Story:

Year 2157. Humanity has made contact with three alien species: The Zephyrians (peaceful traders),
The Krell (scientific researchers), and The Vortigaunts (neutral observers). Earth's Defense Council
maintains authorization lists for each species using sorted linked list databases.

However, a rogue AI has corrupted the authorization system. Commander Reeves needs your help to:
1. Identify which aliens are authorized by BOTH the Military and Science divisions (Intersection)
2. Find aliens authorized ONLY by Military (Difference: Military - Science)
3. Create a MASTER authorization list combining both divisions (Union)

Each alien is identified by a unique ID number (sorted in ascending order in the lists).
The lists MUST remain sorted after operations to maintain database integrity.

Your Task:
Implement Linked List Set operations that preserve sorted order and handle duplicates correctly.

========================================
Data Structures Provided:
========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int alienID;
    struct Node* next;
} Node, *SET;

// --- Function Prototypes ---
void initSet(SET *S);
void insertSorted(SET *S, int alienID);  // Insert in ascending order, no duplicates
void displaySet(SET S, const char* name);
void freeSet(SET *S);

// TODO: Implement these functions
// IDs in BOTH lists
SET intersectionSet(SET A, SET B){

    SET aptr, bptr, *cptr, C; 
    C = NULL;
    cptr = &C;
    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        *cptr = (Node*) malloc(sizeof(Node));

        if (aptr->alienID > bptr->alienID){
            
            bptr = bptr->next;
        } else if (aptr->alienID < bptr->alienID){
            
            aptr = aptr->next;
        } else  {
            
            (*cptr)->alienID = aptr->alienID;
            cptr = &(*cptr)->next;
            aptr = aptr->next;
            bptr = bptr->next;
        }

    }
    
    *cptr = NULL;

    return C;
}

// IDs in A but NOT in B
SET differenceSet(SET A, SET B){

    SET aptr, bptr, *cptr, C; 
    C = NULL;
    cptr = &C;
     aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        *cptr = (Node*) malloc(sizeof(Node));

        if (aptr->alienID > bptr->alienID){
            
            bptr = bptr->next;

        } else if (aptr->alienID < bptr->alienID){
            (*cptr)->alienID = aptr->alienID;
            cptr = &(*cptr)->next;
            aptr = aptr->next;
        } else  {
            
            aptr = aptr->next;
            bptr = bptr->next;
        }

    }
    
    *cptr = NULL;

    return C;

}

// IDs in EITHER list (combined, sorted, no duplicates)
SET unionSet(SET A, SET B){
   
    SET aptr, bptr, *cptr, C; 
    C = NULL;
    cptr = &C;
     aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        *cptr = (Node*) malloc(sizeof(Node));

        if (aptr->alienID < bptr->alienID){
            
            (*cptr)->alienID = aptr->alienID;
            aptr = aptr->next;

        } else  {
            
            if (aptr->alienID == bptr->alienID){
                aptr = aptr->next;
            }

            (*cptr)->alienID = bptr->alienID;
            bptr = bptr->next;
        }

        cptr = &(*cptr)->next;
    }
    
    SET dptr = (aptr != NULL) ? aptr : bptr;
    
    while (dptr != NULL){
        
        *cptr = (Node*) malloc(sizeof(Node));
        (*cptr)->alienID = dptr->alienID;    
        dptr = dptr->next;    
        cptr = &(*cptr)->next;
    }


    *cptr = NULL;
    return C;
}           

// --- Helper Functions (Already Implemented) ---
void initSet(SET *S) {
    *S = NULL;
}

void insertSorted(SET *S, int alienID) {
    Node **trav = S;
    
    // Find insertion point (maintain ascending order)
    while(*trav != NULL && (*trav)->alienID < alienID) {
        trav = &(*trav)->next;
    }
    
    // Check for duplicate
    if(*trav != NULL && (*trav)->alienID == alienID) {
        return;  // Already exists, ignore
    }
    
    // Insert new node
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode != NULL) {
        newNode->alienID = alienID;
        newNode->next = *trav;
        *trav = newNode;
    }
}

void displaySet(SET S, const char* name) {
    printf("%s: [ ", name);
    Node *trav = S;
    while(trav != NULL) {
        printf("%d", trav->alienID);
        if(trav->next != NULL) printf(", ");
        trav = trav->next;
    }
    printf(" ]\n");
}

void freeSet(SET *S) {
    Node *current = *S;
    while(current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    *S = NULL;
}

// --- Main Function (Test Cases) ---
int main() {
    SET military, science;
    
    printf("========================================\n");
    printf("EARTH DEFENSE COUNCIL - AUTHORIZATION DB\n");
    printf("========================================\n\n");
    
    initSet(&military);
    initSet(&science);
    
    printf("--- Test Case 1: Loading Authorization Lists ---\n");
    // Military Division authorizes: 101, 105, 110, 115, 120, 130
    insertSorted(&military, 101);
    insertSorted(&military, 105);
    insertSorted(&military, 110);
    insertSorted(&military, 115);
    insertSorted(&military, 120);
    insertSorted(&military, 130);
    
    // Science Division authorizes: 105, 108, 110, 125, 130, 135
    insertSorted(&science, 105);
    insertSorted(&science, 108);
    insertSorted(&science, 110);
    insertSorted(&science, 125);
    insertSorted(&science, 130);
    insertSorted(&science, 135);
    
    displaySet(military, "Military Clearance");
    displaySet(science, "Science Clearance");
    // Expected Output:
    // Military Clearance: [ 101, 105, 110, 115, 120, 130 ]
    // Science Clearance: [ 105, 108, 110, 125, 130, 135 ]
    
    printf("\n--- Test Case 2: Intersection (Dual Authorization) ---\n");
    printf("Aliens authorized by BOTH divisions:\n");
    SET dualAuth = intersectionSet(military, science);
    displaySet(dualAuth, "  Dual Authorization");
    // Expected Output:
    //   Dual Authorization: [ 105, 110, 130 ]
    
    printf("\n--- Test Case 3: Difference (Military-Only Access) ---\n");
    printf("Aliens authorized ONLY by Military (not Science):\n");
    SET militaryOnly = differenceSet(military, science);
    displaySet(militaryOnly, "  Military-Only");
    // Expected Output:
    //   Military-Only: [ 101, 115, 120 ]
    
    printf("\n--- Test Case 4: Union (Master Authorization) ---\n");
    printf("All authorized aliens (combined list):\n");
    SET masterList = unionSet(military, science);
    displaySet(masterList, "  Master Authorization");
    // Expected Output:
    //   Master Authorization: [ 101, 105, 108, 110, 115, 120, 125, 130, 135 ]
    
    printf("\n--- Test Case 5: Edge Case - Empty Intersection ---\n");
    SET listA, listB;
    initSet(&listA);
    initSet(&listB);
    
    insertSorted(&listA, 10);
    insertSorted(&listA, 20);
    insertSorted(&listB, 30);
    insertSorted(&listB, 40);
    
    displaySet(listA, "List A");
    displaySet(listB, "List B");
    SET emptyIntersect = intersectionSet(listA, listB);
    displaySet(emptyIntersect, "  Intersection");
    // Expected Output:
    // List A: [ 10, 20 ]
    // List B: [ 30, 40 ]
    //   Intersection: [  ]
    
    printf("\n--- Test Case 6: Edge Case - One Empty List ---\n");
    SET empty;
    initSet(&empty);
    SET result = unionSet(listA, empty);
    displaySet(result, "  Union with Empty");
    // Expected Output:
    //   Union with Empty: [ 10, 20 ]
    
    // Cleanup
    freeSet(&military);
    freeSet(&science);
    freeSet(&dualAuth);
    freeSet(&militaryOnly);
    freeSet(&masterList);
    freeSet(&listA);
    freeSet(&listB);
    freeSet(&emptyIntersect);
    freeSet(&empty);
    freeSet(&result);
    
    printf("\n========================================\n");
    printf("TESTS COMPLETE - Memory Freed\n");
    printf("========================================\n");
    
    return 0;
}

/*
========================================
IMPLEMENTATION NOTES:
========================================

1. Sorted Linked List Properties:
   - Elements stored in ASCENDING order
   - No duplicate elements allowed
   - Traversal is linear O(n)

2. Two-Pointer Technique for Set Operations:
   - Use two traversal pointers (one for each list)
   - Compare current nodes
   - Advance pointers based on comparison result
   
   Example for Intersection:
   ```
   Military: 101 -> 105 -> 110 -> ...
             ^
   Science:  105 -> 108 -> 110 -> ...
             ^
   
   If military->ID < science->ID: advance military
   If military->ID > science->ID: advance science
   If military->ID == science->ID: MATCH! Add to result, advance both
   ```

3. Union Strategy:
   - Start with both list heads
   - Always take the SMALLER current node
   - If both equal, take one and skip duplicate
   - Continue until both lists exhausted

4. Difference Strategy (A - B):
   - Traverse A
   - For each element in A, check if it exists in B
   - If NOT in B, add to result
   - Alternative: Use two-pointer merge-like approach

5. Memory Management:
   - All operations return NEW lists (don't modify originals)
   - Must allocate new nodes for results
   - Caller responsible for freeing returned lists

6. Edge Cases to Handle:
   - One or both lists empty
   - No common elements (empty intersection)
   - Identical lists
   - One list is subset of other

========================================
RUBRIC (30 points):
========================================
- intersectionSet: 10 points
  * Correct two-pointer logic (5 pts)
  * Maintains sorted order (3 pts)
  * No duplicates (2 pts)
  
- differenceSet: 10 points
  * Correct element selection (5 pts)
  * Sorted output (3 pts)
  * Edge cases handled (2 pts)
  
- unionSet: 10 points
  * Merges both lists (4 pts)
  * No duplicates (3 pts)
  * Maintains sorted order (3 pts)

Deductions:
- Memory leaks: -3 per function
- Unsorted output: -4 per function
- Incorrect traversal logic: -5 per function
- Duplicate elements in output: -3
========================================

ALGORITHM PSEUDOCODE:

intersectionSet(A, B):
    result = NULL
    travA = A, travB = B
    
    while travA != NULL AND travB != NULL:
        if travA->ID < travB->ID:
            travA = travA->next
        else if travA->ID > travB->ID:
            travB = travB->next
        else:  // Equal - found match
            insertSorted(&result, travA->ID)
            travA = travA->next
            travB = travB->next
    
    return result

unionSet(A, B):
    result = NULL
    travA = A, travB = B
    
    while travA != NULL AND travB != NULL:
        if travA->ID < travB->ID:
            insertSorted(&result, travA->ID)
            travA = travA->next
        else if travA->ID > travB->ID:
            insertSorted(&result, travB->ID)
            travB = travB->next
        else:  // Equal - add once
            insertSorted(&result, travA->ID)
            travA = travA->next
            travB = travB->next
    
    // Append remaining elements
    while travA != NULL:
        insertSorted(&result, travA->ID)
        travA = travA->next
    
    while travB != NULL:
        insertSorted(&result, travB->ID)
        travB = travB->next
    
    return result

========================================
*/
