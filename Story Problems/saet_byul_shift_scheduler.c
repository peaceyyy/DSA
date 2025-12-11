/*
 * SAET-BYUL'S SHIFT SCHEDULER
 * Inspired by: Backstreet Rookie (편의점 샛별이)
 * 
 * STORY:
 * Choi Dae-Hyun runs a 24-hour convenience store in Seoul, and his part-timer
 * Jung Saet-byul has taken it upon herself to organize the chaotic employee
 * shift system. The store has multiple staff members, and Saet-byul needs to
 * track who's available for different shift types: morning, afternoon, and night.
 * 
 * The problem? Some employees can work multiple shifts, and Saet-byul needs to
 * perform SET OPERATIONS to optimize scheduling:
 * - Find employees who can work BOTH morning AND afternoon (INTERSECTION)
 * - Combine all available employees across shifts (UNION)
 * - Find employees exclusive to certain shifts (DIFFERENCE)
 * - Check if one shift's roster is a subset of another (SUBSET)
 * 
 * Each employee is represented by their ID number (1-99), and the shift rosters
 * are maintained as SORTED LINKED LIST SETS (no duplicates, ascending order).
 * 
 * TECHNICAL SPECIFICATIONS:
 * 
 * Node Structure:
 *   - employeeID: Integer (1-99)
 *   - next: Pointer to next node
 * 
 * Set Representation:
 *   - Singly linked list
 *   - Always sorted in ASCENDING order by employeeID
 *   - NO DUPLICATES allowed
 *   - Empty set represented as NULL
 * 
 * YOUR TASKS:
 * 
 * 1. initializeShift(Set *S)
 *    "Initialize an empty shift roster (set to NULL)."
 *    Level 1 Hint: Just assign NULL to the set pointer - simple as that.
 * 
 * 2. insertEmployee(Set *S, int empID)
 *    "Add an employee to a shift roster IF they're not already present.
 *     Maintain sorted order (ascending). Do NOT insert duplicates."
 *    Level 1 Hint: Use a traversal pattern with pointer-to-pointer (&current) to find
 *    insertion point. Check if empID already exists BEFORE creating new node.
 * 
 * 3. unionShifts(Set A, Set B)
 *    "Combine two shift rosters into one set containing all unique employees.
 *     Result must be sorted, no duplicates."
 *    Level 1 Hint: Merge like sorted arrays - compare heads, take smaller, advance that pointer.
 *    Build result list by inserting each unique ID once.
 * 
 * 4. intersectionShifts(Set A, Set B)
 *    "Find employees who are available in BOTH shift rosters.
 *     Return new set containing only common employees."
 *    Level 1 Hint: Two-pointer traverse both lists simultaneously. Only add to result when
 *    both current nodes have the SAME employeeID.
 * 
 * 5. differenceShifts(Set A, Set B)
 *    "Find employees in shift A who are NOT in shift B (A - B).
 *     Return new set containing exclusive employees from A."
 *    Level 1 Hint: Traverse A, and for each element check if it exists in B. Only add to
 *    result if NOT found in B. You can use two-pointer technique for efficiency.
 * 
 * 6. isSubset(Set A, Set B)
 *    "Check if shift roster A is completely contained within shift roster B.
 *     Return 1 if A ⊆ B, otherwise 0."
 *    Level 1 Hint: Every element in A must exist in B. Traverse A and for each node,
 *    scan B to find match. If any element of A missing in B, return 0.
 * 
 * 7. displayShift(Set S, const char* shiftName)
 *    "Display all employees in a shift roster in sorted order."
 *    Level 1 Hint: Simple linked list traversal. Print employeeID of each node.
 *    Handle empty set case (print "No employees scheduled").
 * 
 * CONSTRAINTS:
 * - Employee IDs range from 1 to 99
 * - All sets must remain SORTED after operations
 * - NO DUPLICATES allowed in any set
 * - Use malloc for dynamic allocation
 * - Remember to handle memory properly (though main doesn't test cleanup here)
 * 
 * WORLD-BUILDING FLAVOR (Backstreet Rookie):
 * - Employee IDs represent: Saet-byul (10), Dae-Hyun (15), Yeon-joo (20),
 *   Eun-byul (25), Seung-joon (30), Dal-shik (35), Geum-bi (40)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int employeeID;
    struct node *next;
} NodeType, *Set;

// =========================================================================
// FUNCTION PROTOTYPES
// =========================================================================

void initializeShift(Set *S);
void insertEmployee(Set *S, int empID);
Set unionShifts(Set A, Set B);
Set intersectionShifts(Set A, Set B);
Set differenceShifts(Set A, Set B);
int isSubset(Set A, Set B);
void displayShift(Set S, const char* shiftName);

// =========================================================================
// TODO: IMPLEMENT ALL FUNCTIONS BELOW
// =========================================================================

void initializeShift(Set *S) {
    // TODO: Initialize empty set
    // Level 1 Hint: Just assign NULL to the set pointer - simple as that.
}

void insertEmployee(Set *S, int empID) {
    // TODO: Insert employee maintaining sorted order, no duplicates
    // Level 1 Hint: Use a traversal pattern with pointer-to-pointer (&current) to find
    // insertion point. Check if empID already exists BEFORE creating new node.
}

Set unionShifts(Set A, Set B) {
    // TODO: Return union of two sets (A ∪ B)
    // Level 1 Hint: Merge like sorted arrays - compare heads, take smaller, advance that pointer.
    // Build result list by inserting each unique ID once.
    return NULL;
}

Set intersectionShifts(Set A, Set B) {
    // TODO: Return intersection of two sets (A ∩ B)
    // Level 1 Hint: Two-pointer traverse both lists simultaneously. Only add to result when
    // both current nodes have the SAME employeeID.
    return NULL;
}

Set differenceShifts(Set A, Set B) {
    // TODO: Return difference of two sets (A - B)
    // Level 1 Hint: Traverse A, and for each element check if it exists in B. Only add to
    // result if NOT found in B. You can use two-pointer technique for efficiency.
    return NULL;
}

int isSubset(Set A, Set B) {
    // TODO: Check if A is subset of B (A ⊆ B)
    // Level 1 Hint: Every element in A must exist in B. Traverse A and for each node,
    // scan B to find match. If any element of A missing in B, return 0.
    return 0;
}

void displayShift(Set S, const char* shiftName) {
    // TODO: Display all employees in the shift
    // Level 1 Hint: Simple linked list traversal. Print employeeID of each node.
    // Handle empty set case (print "No employees scheduled").
}

// =========================================================================
// MAIN - TEST HARNESS
// =========================================================================

int main(void) {
    Set morningShift, afternoonShift, nightShift;
    Set combined, overlap, exclusive;
    
    printf("========================================\n");
    printf("  SAET-BYUL'S SHIFT SCHEDULER v1.0\n");
    printf("  Backstreet Rookie Store Management\n");
    printf("========================================\n\n");
    
    // Initialize all shifts
    initializeShift(&morningShift);
    initializeShift(&afternoonShift);
    initializeShift(&nightShift);
    
    printf("=== SCHEDULING MORNING SHIFT ===\n");
    printf("Adding: Dae-Hyun (15), Saet-byul (10), Geum-bi (40), Eun-byul (25)\n");
    insertEmployee(&morningShift, 15);
    insertEmployee(&morningShift, 10);
    insertEmployee(&morningShift, 40);
    insertEmployee(&morningShift, 25);
    displayShift(morningShift, "Morning Shift");
    // Expected: Morning Shift: 10 -> 15 -> 25 -> 40
    
    printf("\n=== SCHEDULING AFTERNOON SHIFT ===\n");
    printf("Adding: Yeon-joo (20), Dae-Hyun (15), Dal-shik (35), Saet-byul (10)\n");
    insertEmployee(&afternoonShift, 20);
    insertEmployee(&afternoonShift, 15);
    insertEmployee(&afternoonShift, 35);
    insertEmployee(&afternoonShift, 10);
    displayShift(afternoonShift, "Afternoon Shift");
    // Expected: Afternoon Shift: 10 -> 15 -> 20 -> 35
    
    printf("\n=== SCHEDULING NIGHT SHIFT ===\n");
    printf("Adding: Seung-joon (30), Eun-byul (25)\n");
    insertEmployee(&nightShift, 30);
    insertEmployee(&nightShift, 25);
    displayShift(nightShift, "Night Shift");
    // Expected: Night Shift: 25 -> 30
    
    printf("\n=== TESTING DUPLICATE PREVENTION ===\n");
    printf("Attempting to add Saet-byul (10) again to morning shift...\n");
    insertEmployee(&morningShift, 10);
    displayShift(morningShift, "Morning Shift");
    // Expected: Morning Shift: 10 -> 15 -> 25 -> 40 (no change)
    
    printf("\n=== UNION: ALL AVAILABLE EMPLOYEES ===\n");
    printf("Combining morning and afternoon shifts...\n");
    combined = unionShifts(morningShift, afternoonShift);
    displayShift(combined, "Combined (Morning ∪ Afternoon)");
    // Expected: Combined: 10 -> 15 -> 20 -> 25 -> 35 -> 40
    
    printf("\n=== INTERSECTION: FLEXIBLE EMPLOYEES ===\n");
    printf("Finding employees who can work BOTH morning and afternoon...\n");
    overlap = intersectionShifts(morningShift, afternoonShift);
    displayShift(overlap, "Flexible Workers (Morning ∩ Afternoon)");
    // Expected: Flexible Workers: 10 -> 15
    
    printf("\n=== DIFFERENCE: MORNING-ONLY EMPLOYEES ===\n");
    printf("Finding employees exclusive to morning shift...\n");
    exclusive = differenceShifts(morningShift, afternoonShift);
    displayShift(exclusive, "Morning-Only (Morning - Afternoon)");
    // Expected: Morning-Only: 25 -> 40
    
    printf("\n=== DIFFERENCE: AFTERNOON-ONLY EMPLOYEES ===\n");
    printf("Finding employees exclusive to afternoon shift...\n");
    exclusive = differenceShifts(afternoonShift, morningShift);
    displayShift(exclusive, "Afternoon-Only (Afternoon - Morning)");
    // Expected: Afternoon-Only: 20 -> 35
    
    printf("\n=== SUBSET CHECK: NIGHT ⊆ MORNING? ===\n");
    printf("Is night shift roster a subset of morning shift?\n");
    int result1 = isSubset(nightShift, morningShift);
    printf("Result: %s\n", result1 ? "YES (Night ⊆ Morning)" : "NO");
    // Expected: NO (30 is in night but not in morning)
    
    printf("\n=== SUBSET CHECK: NIGHT ⊆ COMBINED? ===\n");
    printf("Is night shift roster a subset of combined shift?\n");
    int result2 = isSubset(nightShift, combined);
    printf("Result: %s\n", result2 ? "YES (Night ⊆ Combined)" : "NO");
    // Expected: NO (30 is not in combined)
    
    printf("\n=== CREATING TEST SUBSET ===\n");
    Set testSubset;
    initializeShift(&testSubset);
    insertEmployee(&testSubset, 10);
    insertEmployee(&testSubset, 15);
    displayShift(testSubset, "Test Subset");
    // Expected: Test Subset: 10 -> 15
    
    printf("\n=== SUBSET CHECK: TEST ⊆ MORNING? ===\n");
    int result3 = isSubset(testSubset, morningShift);
    printf("Result: %s\n", result3 ? "YES (Test ⊆ Morning)" : "NO");
    // Expected: YES (both 10 and 15 are in morning)
    
    printf("\n=== SUBSET CHECK: TEST ⊆ AFTERNOON? ===\n");
    int result4 = isSubset(testSubset, afternoonShift);
    printf("Result: %s\n", result4 ? "YES (Test ⊆ Afternoon)" : "NO");
    // Expected: YES (both 10 and 15 are in afternoon)
    
    printf("\n========================================\n");
    printf("  Shift scheduling complete!\n");
    printf("  Dae-Hyun approves this roster. 👍\n");
    printf("========================================\n");
    
    return 0;
}
