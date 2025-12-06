/*
========================================
PROBLEM 1: The Kendo Club Roster
Difficulty: ★☆☆☆☆ (Easy - Warmup)
Topic: Bit Vector Set Operations
========================================

Story:

At Karasuno High School, the Kendo Club is preparing for the upcoming inter-school tournament. 
The club captain, Takeru, maintains two rosters using a traditional attendance board with 
numbered slots (0-9 for 10 members).

Each slot can be marked with a wooden peg (1 = present, 0 = absent). Takeru needs your help 
to analyze attendance patterns for this week's practices.

Your Task:
Implement a Bit Vector Set to track which members attended Monday's practice vs. Friday's practice.
Then perform the following operations:

1. Find members who attended BOTH days (Intersection)
2. Find members who attended ONLY Monday (Difference: Monday - Friday)
3. Find members who attended AT LEAST ONE day (Union)
4. Check if Friday's attendance is a subset of Monday's attendance

========================================
Data Structures Provided:
========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef int SET[MAX];

// --- Function Prototypes ---
void initSet(SET A);
void insertSet(SET A, int memberID);
void displaySet(SET A, const char* name);

// TODO: Implement these functions

// Members in both Monday AND Friday
SET* intersectionSet(SET A, SET B){

    SET* intersection = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < MAX; i++){

        (*intersection)[i] = A[i] && B[i];
    }
}

// Members in Monday but NOT Friday
SET* differenceSet(SET A, SET B){

    SET* difference = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < MAX; i++){

        (*difference)[i] = A[i] && !B[i];
    }
    
    return difference;

}   

// Members in Monday OR Friday
SET* unionSet(SET A, SET B){

    SET* setUnion = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < MAX; i++){

        (*setUnion)[i] = A[i] || B[i];
    }

    return setUnion;
}   

// Is B a subset of A?
int isSubset(SET A, SET B){


    SET* intersectionOfAandB = intersectionSet(A, B);

    for (int i = 0; i < MAX; i++){
        if ((*intersectionOfAandB)[i] != B[i]) return 0;
    }

    return 1;
}       

// --- Helper Functions (Already Implemented) ---
void initSet(SET A) {
    for(int i = 0; i < MAX; i++) {
        A[i] = 0;
    }
}

void insertSet(SET A, int memberID) {
    if(memberID >= 0 && memberID < MAX) {
        A[memberID] = 1;
    }
}

void displaySet(SET A, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < MAX; i++) {
        if(A[i] == 1) {
            if(!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

// --- Main Function (Test Cases) ---
int main() {
    SET monday, friday;
    
    // Initialize both sets
    initSet(monday);
    initSet(friday);
    
    printf("========================================\n");
    printf("KARASUNO KENDO CLUB - ATTENDANCE TRACKER\n");
    printf("========================================\n\n");
    
    // Monday's attendance: Members 0, 2, 4, 5, 7, 9
    printf("--- Test Case 1: Recording Attendance ---\n");
    insertSet(monday, 0);
    insertSet(monday, 2);
    insertSet(monday, 4);
    insertSet(monday, 5);
    insertSet(monday, 7);
    insertSet(monday, 9);
    
    // Friday's attendance: Members 2, 4, 5, 8
    insertSet(friday, 2);
    insertSet(friday, 4);
    insertSet(friday, 5);
    insertSet(friday, 8);
    
    displaySet(monday, "Monday Practice");
    displaySet(friday, "Friday Practice");
    // Expected Output:
    // Monday Practice: { 0, 2, 4, 5, 7, 9 }
    // Friday Practice: { 2, 4, 5, 8 }
    
    printf("\n--- Test Case 2: Intersection (Both Days) ---\n");
    SET* both = intersectionSet(monday, friday);
    displaySet(*both, "Attended Both Days");
    // Expected Output:
    // Attended Both Days: { 2, 4, 5 }
    
    printf("\n--- Test Case 3: Difference (Monday Only) ---\n");
    SET* mondayOnly = differenceSet(monday, friday);
    displaySet(*mondayOnly, "Monday Only");
    // Expected Output:
    // Monday Only: { 0, 7, 9 }
    
    printf("\n--- Test Case 4: Union (At Least One Day) ---\n");
    SET* atLeastOne = unionSet(monday, friday);
    displaySet(*atLeastOne, "At Least One Day");
    // Expected Output:
    // At Least One Day: { 0, 2, 4, 5, 7, 8, 9 }
    
    printf("\n--- Test Case 5: Subset Check ---\n");
    printf("Is Friday a subset of Monday? ");
    if(isSubset(monday, friday)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // Is Friday a subset of Monday? NO
    // (Because member 8 attended Friday but not Monday)
    
    printf("\n--- Test Case 6: Edge Case - Friday Becomes Subset ---\n");
    // Remove member 8 from Friday's set to make it a true subset
    friday[8] = 0;
    displaySet(friday, "Updated Friday Practice");
    printf("Is Friday a subset of Monday now? ");
    if(isSubset(monday, friday)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // Updated Friday Practice: { 2, 4, 5 }
    // Is Friday a subset of Monday now? YES
    
    printf("\n========================================\n");
    printf("TESTS COMPLETE\n");
    printf("========================================\n");
    
    return 0;
}

/*
========================================
IMPLEMENTATION NOTES:
========================================

1. Bit Vector Representation:
   - Array of integers where index = element value
   - A[i] = 1 means element i is in the set
   - A[i] = 0 means element i is NOT in the set

2. Set Operations Logic:
   - UNION: A[i] = 1 OR B[i] = 1
   - INTERSECTION: A[i] = 1 AND B[i] = 1
   - DIFFERENCE (A - B): A[i] = 1 AND B[i] = 0
   - SUBSET (B ⊆ A): For all i, if B[i] = 1 then A[i] must = 1

3. Return Type Note:
   - Functions return SET* (pointer to dynamically allocated array)
   - Remember to malloc the result set before returning

4. Edge Cases to Handle:
   - Empty sets (all zeros)
   - Full sets (all ones)
   - Identical sets
   - Disjoint sets (no common elements)

========================================
RUBRIC (20 points):
========================================
- intersectionSet: 5 points (correct AND logic)
- differenceSet: 5 points (correct AND-NOT logic)
- unionSet: 5 points (correct OR logic)
- isSubset: 5 points (correct implication check)

Deductions:
- Missing malloc: -2 per function
- Off-by-one errors: -1 per occurrence
- Incorrect output: -3 per test case
========================================
*/
