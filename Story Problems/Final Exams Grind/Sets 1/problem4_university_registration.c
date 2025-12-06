/*
========================================
PROBLEM 4: The University Course Registration Crisis
Difficulty: ★★★★☆ (Medium-Hard)
Topic: Bit Vector Set Operations (Multi-Set Analysis)
========================================

Story:

At Todai University (Tokyo University), the Computer Science department offers 12 elective courses
(numbered 0-11). Due to budget constraints, the department dean, Professor Tanaka, must analyze 
student registration patterns across three student groups:

- Group A: Third-year students (Junior cohort)
- Group B: Fourth-year students (Senior cohort)  
- Group C: Exchange students

Professor Tanaka needs to determine:
1. Which courses are popular across ALL three groups (Intersection of A, B, C)
2. Which courses are ONLY taken by third-years (A - (B ∪ C))
3. Which courses have NO students at all (Complement of (A ∪ B ∪ C))
4. Whether exchange students' choices are a subset of senior students' choices

This analysis will help decide which courses to offer next semester and which to cancel.

Your Task:
Implement complex multi-set operations using Bit Vectors to handle this three-way analysis.

========================================
Data Structures Provided:
========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_COURSES 12

typedef int SET[TOTAL_COURSES];

// --- Function Prototypes ---
void initSet(SET A);
void enrollCourse(SET A, int courseID);
void displaySet(SET A, const char* name);
void displayCourseNames(SET A);

// TODO: Implement these functions

/*
(numbered 0-11)

Professor Tanaka needs to determine:
1. Which courses are popular across ALL three groups (Intersection of A, B, C)
2. Which courses are ONLY taken by third-years (A - (B ∪ C))
3. Which courses have NO students at all (Complement of (A ∪ B ∪ C))
4. Whether exchange students' choices are a subset of senior students' choices

*/

// Courses in ALL three groups
SET* intersectionThreeWay(SET A, SET B, SET C){

    SET* threeWayIntersection = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < TOTAL_COURSES; i++)
    {   
        (*threeWayIntersection)[i] = A[i] && B[i] && C[i];
    }

    return threeWayIntersection;
    
}
 // Standard union (for intermediate steps)
SET* unionSet(SET A, SET B){
    SET* threeWayUnion = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < TOTAL_COURSES; i++)
    {
        (*threeWayUnion)[i] = A[i] || B[i];
    }

    return threeWayUnion;


}

/*

HINT 2 - Multi-Step Operations:
   For "Juniors only" = Juniors - (Seniors ∪ Exchange)
   
   Break it down:
   Step 1: temp = Seniors ∪ Exchange
   Step 2: result = Juniors - temp
   
   Don't try to do it all in one function!
   Reuse your unionSet and differenceSet.

   / HINT: Need to compute (Juniors - (Seniors ∪ Exchange))


*/                  
SET* differenceSet(SET A, SET B){

    

    SET* setDiff = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < TOTAL_COURSES; i++)
    {
        (*setDiff)[i] = A[i] && !B[i];
    }

    return setDiff;
    
}                
SET* complementSet(SET A){

    
    SET* setComplement = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < TOTAL_COURSES; i++)
    {
        (*setComplement)[i] = !A[i];
    }

    return setComplement;
}  

int isSubset(SET A, SET B){

    SET* setIntersection = (SET*) malloc(sizeof(SET));

    for (int i = 0; i < TOTAL_COURSES; i++)
    {
        (*setIntersection)[i] = A[i] && B[i];
    }

    for (int i = 0; i < TOTAL_COURSES; i++){

        if ((*setIntersection)[i] != B[i]) return 0;
    }
   
    return 1;

}

// --- Helper Functions (Already Implemented) ---
void initSet(SET A) {
    for(int i = 0; i < TOTAL_COURSES; i++) {
        A[i] = 0;
    }
}

void enrollCourse(SET A, int courseID) {
    if(courseID >= 0 && courseID < TOTAL_COURSES) {
        A[courseID] = 1;
    }
}

const char* courseNames[TOTAL_COURSES] = {
    "Algorithms", "Databases", "Networks", "AI", 
    "Graphics", "Security", "Compilers", "OS",
    "ML", "Blockchain", "Quantum", "Cloud"
};

void displaySet(SET A, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < TOTAL_COURSES; i++) {
        if(A[i] == 1) {
            if(!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

void displayCourseNames(SET A) {
    printf("  Course Names: ");
    int count = 0;
    for(int i = 0; i < TOTAL_COURSES; i++) {
        if(A[i] == 1) {
            if(count > 0) printf(", ");
            printf("%s", courseNames[i]);
            count++;
        }
    }
    if(count == 0) printf("(none)");
    printf("\n");
}

// --- Main Function (Test Cases) ---
int main() {
    SET juniors, seniors, exchange;
    
    printf("========================================\n");
    printf("TODAI UNIVERSITY - COURSE REGISTRATION ANALYSIS\n");
    printf("========================================\n\n");
    
    initSet(juniors);
    initSet(seniors);
    initSet(exchange);
    
    printf("--- Test Case 1: Student Enrollments ---\n");
    
    // Juniors (3rd year): Courses 0, 1, 2, 4, 6, 8
    // (Algorithms, Databases, Networks, Graphics, Compilers, ML)
    enrollCourse(juniors, 0);
    enrollCourse(juniors, 1);
    enrollCourse(juniors, 2);
    enrollCourse(juniors, 4);
    enrollCourse(juniors, 6);
    enrollCourse(juniors, 8);
    
    // Seniors (4th year): Courses 1, 2, 5, 6, 9, 10
    // (Databases, Networks, Security, Compilers, Blockchain, Quantum)
    enrollCourse(seniors, 1);
    enrollCourse(seniors, 2);
    enrollCourse(seniors, 5);
    enrollCourse(seniors, 6);
    enrollCourse(seniors, 9);
    enrollCourse(seniors, 10);
    
    // Exchange Students: Courses 1, 2, 6
    // (Databases, Networks, Compilers)
    enrollCourse(exchange, 1);
    enrollCourse(exchange, 2);
    enrollCourse(exchange, 6);
    
    printf("Junior Students:\n");
    displaySet(juniors, "  Course IDs");
    displayCourseNames(juniors);
    // Expected Output:
    //   Course IDs: { 0, 1, 2, 4, 6, 8 }
    //   Course Names: Algorithms, Databases, Networks, Graphics, Compilers, ML
    
    printf("\nSenior Students:\n");
    displaySet(seniors, "  Course IDs");
    displayCourseNames(seniors);
    // Expected Output:
    //   Course IDs: { 1, 2, 5, 6, 9, 10 }
    //   Course Names: Databases, Networks, Security, Compilers, Blockchain, Quantum
    
    printf("\nExchange Students:\n");
    displaySet(exchange, "  Course IDs");
    displayCourseNames(exchange);
    // Expected Output:
    //   Course IDs: { 1, 2, 6 }
    //   Course Names: Databases, Networks, Compilers
    
    printf("\n--- Test Case 2: Three-Way Intersection (Core Courses) ---\n");
    printf("Courses taken by ALL three groups:\n");
    SET* coreCorses = intersectionThreeWay(juniors, seniors, exchange);
    displaySet(*coreCorses, "  Course IDs");
    displayCourseNames(*coreCorses);
    // Expected Output:
    //   Course IDs: { 1, 2, 6 }
    //   Course Names: Databases, Networks, Compilers
    
    printf("\n--- Test Case 3: Junior-Exclusive Courses ---\n");
    printf("Courses taken ONLY by juniors (not seniors or exchange):\n");
    // HINT: Need to compute (Juniors - (Seniors ∪ Exchange))
    SET* seniorOrExchange = unionSet(seniors, exchange);
    SET* juniorExclusive = differenceSet(juniors, *seniorOrExchange);
    displaySet(*juniorExclusive, "  Course IDs");
    displayCourseNames(*juniorExclusive);
    // Expected Output:
    //   Course IDs: { 0, 4, 8 }
    //   Course Names: Algorithms, Graphics, ML
    
    printf("\n--- Test Case 4: Unpopular Courses (No Students) ---\n");
    printf("Courses with ZERO enrollments:\n");
    // HINT: First compute union of all three groups, then take complement
    SET* allEnrolled = unionSet(juniors, seniors);
    SET* temp = unionSet(*allEnrolled, exchange);
    SET* noCourses = complementSet(*temp);
    displaySet(*noCourses, "  Course IDs");
    displayCourseNames(*noCourses);
    // Expected Output:
    //   Course IDs: { 3, 7, 11 }
    //   Course Names: AI, OS, Cloud
    
    printf("\n--- Test Case 5: Subset Analysis ---\n");
    printf("Are exchange students' choices a subset of seniors' choices? ");
    if(isSubset(seniors, exchange)) {
        printf("YES\n");
        printf("  → Exchange students only take courses that seniors also take.\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // YES
    //   → Exchange students only take courses that seniors also take.
    
    printf("\n--- Test Case 6: Edge Case - Empty Group ---\n");
    SET emptyGroup;
    initSet(emptyGroup);
    printf("Is an empty group a subset of Juniors? ");
    if(isSubset(juniors, emptyGroup)) {
        printf("YES (vacuous truth)\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // YES (vacuous truth)
    
    // Cleanup
    free(coreCorses);
    free(seniorOrExchange);
    free(juniorExclusive);
    free(allEnrolled);
    free(temp);
    free(noCourses);
    
    printf("\n========================================\n");
    printf("ANALYSIS COMPLETE\n");
    printf("========================================\n");
    
    return 0;
}

/*
========================================
STRATEGIC HINTS:
========================================

HINT 1 - Three-Way Intersection:
   Problem: Find elements in A AND B AND C
   
   Approach 1 (Nested):
   Step 1: Find A ∩ B
   Step 2: Find (A ∩ B) ∩ C
   
   Approach 2 (Direct):
   For each index i:
       result[i] = (A[i] == 1 && B[i] == 1 && C[i] == 1) ? 1 : 0
   
   Which is simpler? Approach 2!



HINT 3 - Complement Logic:
   Complement means "flip all bits"
   
   For Bit Vector:
   complement[i] = (A[i] == 0) ? 1 : 0
   
   OR simply:
   complement[i] = 1 - A[i]
   
   OR with bitwise NOT:
   complement[i] = !A[i]  // Note: logical NOT, not bitwise ~

HINT 4 - Subset Check Edge Cases:
   Question: Is ∅ (empty set) a subset of any set A?
   Answer: YES! By definition.
   
   Why? Because "for all x in ∅, x is in A" is vacuously true.
   (There are no elements in ∅ to violate the condition)
   
   Implementation:
   for i in range:
       if B[i] == 1 and A[i] == 0:
           return FALSE  // Found element in B not in A
   return TRUE  // No violations found

HINT 5 - Memory Management:
   Remember to:
   1. Allocate result sets with malloc
   2. Initialize the allocated memory
   3. Free intermediate results after use
   
   Example:
   SET* result = (SET*)malloc(sizeof(SET));
   initSet(*result);
   // ... populate result ...
   return result;

========================================
TRICKY PART WARNINGS:
========================================

⚠️ WARNING 1: Multi-Step Operations
   When computing (A - (B ∪ C)), you MUST:
   1. Create a temporary union result
   2. Use that result in the difference operation
   3. Free the temporary result after use
   
   DON'T try to compute everything in one nested call!

⚠️ WARNING 2: Complement Scope
   In this problem, complement means "courses NOT taken"
   out of the TOTAL_COURSES (0-11).
   
   NOT the mathematical universal complement!
   
   So complement of {0, 1, 2} is {3, 4, 5, 6, 7, 8, 9, 10, 11}

⚠️ WARNING 3: Three-Way Intersection
   Don't call intersectionSet three times!
   
   WRONG:
   result = intersectionSet(A, B)
   result = intersectionSet(result, C)  // Memory leak!
   
   RIGHT:
   result = intersectionSet(A, B)
   temp = intersectionSet(result, C)
   free(result)
   return temp
   
   OR BEST:
   Just loop and check all three sets at once!

========================================
RUBRIC (35 points):
========================================
- intersectionThreeWay: 10 points
  * Correct logic for A ∩ B ∩ C (5 pts)
  * Efficient implementation (3 pts)
  * Memory management (2 pts)

- unionSet: 5 points
  * Correct OR logic (3 pts)
  * Proper allocation (2 pts)

- differenceSet: 5 points
  * Correct A - B logic (3 pts)
  * Edge cases handled (2 pts)

- complementSet: 7 points
  * Correct bit flipping (4 pts)
  * Scoped to TOTAL_COURSES (3 pts)

- isSubset: 8 points
  * Correct subset logic (4 pts)
  * Empty set edge case (2 pts)
  * Efficient check (2 pts)

Deductions:
- Memory leaks: -4
- Incorrect multi-step operations: -5
- Wrong complement scope: -3
- Missing edge case handling: -2 per case
========================================
*/
