/*
========================================
KRUSTY KRAB EMPLOYEE HIERARCHY SYSTEM
Story Problem - Binary Search Tree Implementation
========================================

NARRATIVE:

Mr. Krabs has finally decided to modernize the Krusty Krab's employee 
management system! He's asked you to build a hierarchical tracking system 
based on employee ID numbers (because he's too cheap to pay for a proper 
database). Each employee has a unique ID, and the hierarchy is organized 
as a binary search tree where:
- Lower IDs go to the left (junior employees)
- Higher IDs go to the right (senior employees)

Your job is to implement the following operations:

1. HIRE_EMPLOYEE: Add a new employee to the hierarchy by their ID
2. FIRE_EMPLOYEE: Remove an employee from the system
3. FIND_EMPLOYEE: Check if an employee with a given ID exists
4. GET_MOST_JUNIOR: Find the employee with the lowest ID (newest hire)
5. GET_MOST_SENIOR: Find the employee with the highest ID (longest-serving)

6. DISPLAY_BY_SENIORITY: Print all employee IDs in sorted order (ascending)
7. DISPLAY_HIERARCHY_PREORDER: Show the hierarchy structure (root first)
8. DISPLAY_HIERARCHY_POSTORDER: Show the hierarchy from bottom-up

9. COUNT_TOTAL_EMPLOYEES: Return the total number of employees
10. GET_HIERARCHY_DEPTH: Calculate how many levels the hierarchy has
11. IS_HIERARCHY_BALANCED: Check if workload distribution is balanced

12. DISPLAY_BY_SHIFT_LEVEL: Print employees level-by-level (BFS)

--- ADVANCED OPERATIONS (NEW FUNCTIONS YOU HAVEN'T IMPLEMENTED YET) ---

13. FIND_COMMON_MANAGER: Given two employee IDs, find their lowest common 
    ancestor (the closest shared manager in the hierarchy)

14. CHECK_PROMOTION_PATH_SUM: Given a target sum, check if there exists 
    a root-to-leaf path where the sum of employee IDs equals the target
    (Mr. Krabs uses this for bizarre promotion criteria)

15. MIRROR_HIERARCHY: Flip the entire hierarchy (swap left and right 
    subtrees at every node) - Mr. Krabs does this when he's bored

16. KRUSTY_KRAB_SPECIAL: Print all employees at a specific hierarchy level
    (0 = Mr. Krabs, 1 = managers, 2 = shift leaders, etc.)

========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 50

typedef enum {FALSE, TRUE} boolean;

typedef struct employee {
    int employeeID;
    struct employee* junior;   // Left child (lower IDs)
    struct employee* senior;   // Right child (higher IDs)
} EmployeeNode, *Hierarchy;


// ============================================
// FUNCTION PROTOTYPES
// ============================================


void INIT_HIERARCHY(Hierarchy *H);
void HIRE_EMPLOYEE(Hierarchy *H, int id);
void FIRE_EMPLOYEE(Hierarchy *H, int id);
boolean FIND_EMPLOYEE(Hierarchy H, int id);
int GET_MOST_JUNIOR(Hierarchy H);
int GET_MOST_SENIOR(Hierarchy H);

void DISPLAY_BY_SENIORITY(Hierarchy H);        // Inorder
void DISPLAY_HIERARCHY_PREORDER(Hierarchy H);  // Preorder
void DISPLAY_HIERARCHY_POSTORDER(Hierarchy H); // Postorder

int COUNT_TOTAL_EMPLOYEES(Hierarchy H);
int GET_HIERARCHY_DEPTH(Hierarchy H);
boolean IS_HIERARCHY_BALANCED(Hierarchy H);
void DISPLAY_BY_SHIFT_LEVEL(Hierarchy H);      // Level-order BFS

// Advanced Operations (WITH GUIDE COMMENTS - New concepts!)
int FIND_COMMON_MANAGER(Hierarchy H, int id1, int id2);
boolean CHECK_PROMOTION_PATH_SUM(Hierarchy H, int targetSum);
void MIRROR_HIERARCHY(Hierarchy H);
void KRUSTY_KRAB_SPECIAL(Hierarchy H, int level);



// ============================================
// MAIN - TEST HARNESS
// ============================================

int main() {
    printf("========================================\n");
    printf("  KRUSTY KRAB EMPLOYEE HIERARCHY SYSTEM\n");
    printf("========================================\n\n");
    
    Hierarchy krustykrab;
    INIT_HIERARCHY(&krustykrab);
    
    printf(">> Hiring employees: {50, 30, 70, 20, 40, 60, 80, 10, 25, 35}\n");
    HIRE_EMPLOYEE(&krustykrab, 50);  // Mr. Krabs (root)
    HIRE_EMPLOYEE(&krustykrab, 30);  // Squidward
    HIRE_EMPLOYEE(&krustykrab, 70);  // SpongeBob
    HIRE_EMPLOYEE(&krustykrab, 20);  // Patrick
    HIRE_EMPLOYEE(&krustykrab, 40);  // Sandy
    HIRE_EMPLOYEE(&krustykrab, 60);  // Plankton (undercover)
    HIRE_EMPLOYEE(&krustykrab, 80);  // Pearl
    HIRE_EMPLOYEE(&krustykrab, 10);  // Gary
    HIRE_EMPLOYEE(&krustykrab, 25);  // Larry
    HIRE_EMPLOYEE(&krustykrab, 35);  // Karen
    
    printf("\n=== BASIC OPERATIONS ===\n");
    printf("By Seniority (Inorder): ");
    DISPLAY_BY_SENIORITY(krustykrab);  // Expected: 10 20 25 30 35 40 50 60 70 80
    
    printf("\nHierarchy (Preorder): ");
    DISPLAY_HIERARCHY_PREORDER(krustykrab);  // Expected: 50 30 20 10 25 40 35 70 60 80
    
    printf("\nHierarchy (Postorder): ");
    DISPLAY_HIERARCHY_POSTORDER(krustykrab);  // Expected: 10 25 20 35 40 30 60 80 70 50
    
    printf("\n\nTotal Employees: %d\n", COUNT_TOTAL_EMPLOYEES(krustykrab));  // Expected: 10
    printf("Hierarchy Depth: %d\n", GET_HIERARCHY_DEPTH(krustykrab));  // Expected: 3
    printf("Most Junior: %d\n", GET_MOST_JUNIOR(krustykrab));  // Expected: 10
    printf("Most Senior: %d\n", GET_MOST_SENIOR(krustykrab));  // Expected: 80
    printf("Balanced? %s\n", IS_HIERARCHY_BALANCED(krustykrab) ? "YES" : "NO");  // Expected: NO
    
    printf("\nBy Shift Level (Level-order): ");
    DISPLAY_BY_SHIFT_LEVEL(krustykrab);  // Expected: 50 30 70 20 40 60 80 10 25 35
    
    printf("\n\n=== SEARCH OPERATIONS ===\n");
    printf("Is Employee 40 working? %s\n", FIND_EMPLOYEE(krustykrab, 40) ? "YES" : "NO");  // Expected: YES
    printf("Is Employee 99 working? %s\n", FIND_EMPLOYEE(krustykrab, 99) ? "YES" : "NO");  // Expected: NO
    
    printf("\n=== ADVANCED OPERATIONS ===\n");
    printf("Common Manager of 10 and 25: %d\n", FIND_COMMON_MANAGER(krustykrab, 10, 25));  // Expected: 20
    printf("Common Manager of 20 and 60: %d\n", FIND_COMMON_MANAGER(krustykrab, 20, 60));  // Expected: 50
    
    printf("Promotion path sum = 125? %s\n", 
           CHECK_PROMOTION_PATH_SUM(krustykrab, 125) ? "YES" : "NO");  // Expected: YES (50+30+40+5=125 or 50+30+20+25=125)
    printf("Promotion path sum = 999? %s\n", 
           CHECK_PROMOTION_PATH_SUM(krustykrab, 999) ? "YES" : "NO");  // Expected: NO
    

    
    printf("\nEmployees at Level 2: ");
    KRUSTY_KRAB_SPECIAL(krustykrab, 2);  // Expected: 20 40 60 80
    
    printf("\n\n>> Mirroring hierarchy...\n");
    MIRROR_HIERARCHY(krustykrab);
    printf("By Seniority after Mirror: ");
    DISPLAY_BY_SENIORITY(krustykrab);  // Expected: 80 70 60 50 40 35 30 25 20 10 (reversed!)
    
    MIRROR_HIERARCHY(krustykrab);
    printf("\n\n>> Firing employees: 10, 30, 50\n");
    FIRE_EMPLOYEE(&krustykrab, 10);
    FIRE_EMPLOYEE(&krustykrab, 30);
    FIRE_EMPLOYEE(&krustykrab, 50);
    printf("By Seniority after Firings: ");

    DISPLAY_BY_SENIORITY(krustykrab);  // Expected: 20 25 35 40 60 70 80
    
    printf("\n\n========================================\n");
    printf("  KRUSTY KRAB CLOSING TIME!\n");
    printf("========================================\n");
    
    return 0;
}


/*
- Lower IDs go to the left (junior employees)
- Higher IDs go to the right (senior employees)

Your job is to implement the following operations:

1. HIRE_EMPLOYEE: Add a new employee to the hierarchy by their ID
2. FIRE_EMPLOYEE: Remove an employee from the system
3. FIND_EMPLOYEE: Check if an employee with a given ID exists
4. GET_MOST_JUNIOR: Find the employee with the lowest ID (newest hire)
5. GET_MOST_SENIOR: Find the employee with the highest ID (longest-serving)

6. DISPLAY_BY_SENIORITY: Print all employee IDs in sorted order (ascending)
7. DISPLAY_HIERARCHY_PREORDER: Show the hierarchy structure (root first)
8. DISPLAY_HIERARCHY_POSTORDER: Show the hierarchy from bottom-up

9. COUNT_TOTAL_EMPLOYEES: Return the total number of employees
10. GET_HIERARCHY_DEPTH: Calculate how many levels the hierarchy has
11. IS_HIERARCHY_BALANCED: Check if workload distribution is balanced

12. DISPLAY_BY_SHIFT_LEVEL: Print employees level-by-level (BFS)

--- ADVANCED OPERATIONS (NEW FUNCTIONS YOU HAVEN'T IMPLEMENTED YET) ---

13. FIND_COMMON_MANAGER: Given two employee IDs, find their lowest common 
    ancestor (the closest shared manager in the hierarchy)

14. CHECK_PROMOTION_PATH_SUM: Given a target sum, check if there exists 
    a root-to-leaf path where the sum of employee IDs equals the target
    (Mr. Krabs uses this for bizarre promotion criteria)

15. MIRROR_HIERARCHY: Flip the entire hierarchy (swap left and right 
    subtrees at every node) - Mr. Krabs does this when he's bored

16. GET_HIERARCHY_DIAMETER: Find the longest path between any two employees
    in the hierarchy (used to calculate maximum chain-of-command length)

17. KRUSTY_KRAB_SPECIAL: Print all employees at a specific hierarchy level
    (0 = Mr. Krabs, 1 = managers, 2 = shift leaders, etc.)


*/



// ============================================
// UTILITY (if needed)
// ============================================

int max(int a, int b) {
    return (a > b) ? a : b;
}


void INIT_HIERARCHY(Hierarchy *H) {
    *H = NULL;
}

void HIRE_EMPLOYEE(Hierarchy *H, int id) {
    
    Hierarchy* trav; 

    for (trav = H; *trav != NULL && (*trav)->employeeID != id; trav = (id < (*trav)->employeeID) ? &(*trav)->junior : &(*trav)->senior){};

    if (*trav == NULL){

        EmployeeNode* newEmployeeNode = (EmployeeNode*) malloc(sizeof(EmployeeNode));

        newEmployeeNode->employeeID = id;
        newEmployeeNode->junior = NULL;
        newEmployeeNode->senior = NULL;
        *trav = newEmployeeNode;

    } else {
        printf("\nEmployee with ID %d already in the hierarchy\n", id);
    }

}

void FIRE_EMPLOYEE(Hierarchy *H, int id) {

    Hierarchy* trav;

    for (trav = H; *trav != NULL && (*trav)->employeeID != id; trav = (id < (*trav)->employeeID) ? &(*trav)->junior : &(*trav)->senior){};

    if (*trav != NULL){
        
        // Case 1 : No children
        EmployeeNode* temp = *trav;

        if ((*trav)->junior == NULL){
            *trav = (*trav)->senior;
            
        }
        else if ((*trav)->senior == NULL){
            
            *trav = (*trav)->junior;

        } else {

            Hierarchy* successor = &(*trav)->senior; 
            while ((*successor)->junior != NULL) successor = &(*successor)->junior;
            temp->employeeID = (*successor)->employeeID;
            temp = *successor;
            *successor = (*successor)->senior;

        } 

        free(temp);


    } else {
        printf("\nEmployee with ID %d not found in the hierarchy!\n", id);
    }

}

boolean FIND_EMPLOYEE(Hierarchy H, int id) {

    Hierarchy trav = H;

    while (trav != NULL)
    {   
        if (trav->employeeID == id) return TRUE;
        trav = (id < trav->employeeID) ? trav->junior : trav->senior;
    }

    return FALSE;
}

int GET_MOST_JUNIOR(Hierarchy H) {
    
    while (H->junior != NULL) H = H->junior;
    
    return (H != NULL) ? H->employeeID : -1;
}

int GET_MOST_SENIOR(Hierarchy H) {

    while (H->senior != NULL) H = H->senior;    
    return (H != NULL) ? H->employeeID : -1;
}

void DISPLAY_BY_SENIORITY(Hierarchy H) {
    if (H != NULL)
    {
        DISPLAY_BY_SENIORITY(H->junior);
        printf("%d ", H->employeeID);
        DISPLAY_BY_SENIORITY(H->senior);
    }
}

void DISPLAY_HIERARCHY_PREORDER(Hierarchy H) {
    if (H != NULL)
    {
        printf("%d ", H->employeeID);
        DISPLAY_HIERARCHY_PREORDER(H->junior);
        DISPLAY_HIERARCHY_PREORDER(H->senior);
    }
}

void DISPLAY_HIERARCHY_POSTORDER(Hierarchy H) {
    if (H != NULL)
    {
        DISPLAY_HIERARCHY_POSTORDER(H->junior);
        DISPLAY_HIERARCHY_POSTORDER(H->senior);
        printf("%d ", H->employeeID);
    }
}

int COUNT_TOTAL_EMPLOYEES(Hierarchy H) {
    
    if (H == NULL) return 0;
    return 1 + COUNT_TOTAL_EMPLOYEES(H->junior) + COUNT_TOTAL_EMPLOYEES(H->senior);
}

int GET_HIERARCHY_DEPTH(Hierarchy H) {
    // TODO: Height calculation (empty = -1, single node = 0)
    if (H == NULL) return -1; 

    int leftHeight =GET_HIERARCHY_DEPTH(H->junior);
    int rightHeight =GET_HIERARCHY_DEPTH(H->senior);

    return 1 + max(leftHeight, rightHeight);
}

boolean IS_HIERARCHY_BALANCED(Hierarchy H) {
    // TODO: Check height difference <= 1 for all subtrees

    if (H == NULL) return TRUE;
    int leftHeight = GET_HIERARCHY_DEPTH(H->junior);
    int rightHeight = GET_HIERARCHY_DEPTH(H->senior);

    if (abs(leftHeight - rightHeight) > 1) return FALSE;


    return IS_HIERARCHY_BALANCED(H->junior) && IS_HIERARCHY_BALANCED(H->senior);
}

void DISPLAY_BY_SHIFT_LEVEL(Hierarchy H) {

    if (H == NULL) return;

    EmployeeNode* employeeQueue[MAX_QUEUE];
    int front = 0, rear = 0;
    employeeQueue[rear++] = H;


    while (front < rear)
    {
        EmployeeNode* curr = employeeQueue[front++];
        printf("%d ", curr->employeeID);

        if (curr->junior != NULL) employeeQueue[rear++] = curr->junior;
        if (curr->senior != NULL) employeeQueue[rear++] = curr->senior;
    }

}


// ============================================
// TODO: IMPLEMENT ADVANCED FUNCTIONS
// (WITH GUIDE COMMENTS - New concepts!)
// ============================================

/*
 * FIND_COMMON_MANAGER - Lowest Common Ancestor (LCA)
 * 
 * Concept: The LCA of two nodes is the deepest node that has both
 * nodes as descendants (a node can be its own descendant).
 * 
 * BST Property Shortcut:
 * - If both IDs are smaller than current node, LCA is in left subtree
 * - If both IDs are larger than current node, LCA is in right subtree
 * - Otherwise, current node IS the LCA (split point)
 * 
 * Steps:
 * 1. if (H == NULL) return -1
 * 2. If both id1 and id2 < H->employeeID:
 *    - Recurse left: return FIND_COMMON_MANAGER(H->junior, id1, id2)
 * 3. If both id1 and id2 > H->employeeID:
 *    - Recurse right: return FIND_COMMON_MANAGER(H->senior, id1, id2)
 * 4. Else (one is left, one is right, or one equals current):
 *    - return H->employeeID (this is the LCA)
 */
int FIND_COMMON_MANAGER(Hierarchy H, int id1, int id2) {
    if (H == NULL) return -1;
    

    if (id1 < H->employeeID && id2 < H->employeeID) return FIND_COMMON_MANAGER(H->junior, id1, id2);
    if (id1 > H->employeeID && id2 > H->employeeID) return FIND_COMMON_MANAGER(H->senior, id1, id2);
    return  H->employeeID;
}


/*
 * CHECK_PROMOTION_PATH_SUM - Root-to-Leaf Path Sum
 * 
 * Concept: Check if there exists any path from root to a leaf node
 * where the sum of all employee IDs equals targetSum.
 * 
 * Leaf Definition: A node with NO children (junior == NULL && senior == NULL)
 * 
 * Steps:
 * 1. if (H == NULL) return FALSE (no path if tree empty)
 * 2. Subtract current node's ID from targetSum:
 *    newSum = targetSum - H->employeeID
 * 3. If H is a LEAF (no children):
 *    - return (newSum == 0) ? TRUE : FALSE
 * 4. Otherwise, check both subtrees (OR condition):
 *    - return CHECK_PROMOTION_PATH_SUM(H->junior, newSum) ||
 *            CHECK_PROMOTION_PATH_SUM(H->senior, newSum)
 */
boolean CHECK_PROMOTION_PATH_SUM(Hierarchy H, int targetSum) {
    
    if (H == NULL) return FALSE;

    int newSum = targetSum - H->employeeID;

    if (H->junior == NULL && H->senior == NULL) return (newSum == 0) ? TRUE : FALSE;

    return (CHECK_PROMOTION_PATH_SUM(H->junior, newSum) || CHECK_PROMOTION_PATH_SUM(H->senior, newSum));
}


/*
 * MIRROR_HIERARCHY - Invert/Mirror the tree
 * 
 * Concept: Swap left and right children at every node.
 * After mirroring, the tree structure is flipped horizontally.
 * 
 * Steps:
 * 1. if (H == NULL) return (base case)
 * 2. Recursively mirror left subtree: MIRROR_HIERARCHY(H->junior)
 * 3. Recursively mirror right subtree: MIRROR_HIERARCHY(H->senior)
 * 4. Swap the children:
 *    Hierarchy temp = H->junior;
 *    H->junior = H->senior;
 *    H->senior = temp;
 */
void MIRROR_HIERARCHY(Hierarchy H) {
    // TODO: Implement tree mirroring

    if (H == NULL) return;
    MIRROR_HIERARCHY (H->junior);
    MIRROR_HIERARCHY (H->senior);

    Hierarchy temp = H->junior;
    H->junior = H->senior;
    H->senior = temp;
}

/*
 * KRUSTY_KRAB_SPECIAL - Print all nodes at a specific level
 * 
 * Concept: Print employee IDs at a given depth (0 = root, 1 = children of root, etc.)
 * 
 * Approach 1 (Recursive with level tracking):
 * - Create a helper function: _print_level(H, targetLevel, currentLevel)
 * - Base case: if H == NULL, return
 * - If currentLevel == targetLevel, print H->employeeID
 * - Otherwise recurse: _print_level(H->junior, target, current+1)
 *                     _print_level(H->senior, target, current+1)
 * 
 * Approach 2 (BFS with level markers):
 * - Use BFS but track which level you're at
 * - Only print when you reach the target level
 * 
 * Steps (Recursive approach):
 * 1. Define helper: void _print_level(Hierarchy H, int target, int current)
 * 2. In KRUSTY_KRAB_SPECIAL: call _print_level(H, level, 0)
 */
void KRUSTY_KRAB_SPECIAL(Hierarchy H, int level) {
    if (H == NULL || level < 0) return;
    _print_level(H, level, 0);
}

// Helper for KRUSTY_KRAB_SPECIAL (recursive approach)
void _print_level(Hierarchy H, int targetLevel, int currentLevel) {
    if (H == NULL) return;
    if (currentLevel == targetLevel) {
        printf("%d ", H->employeeID);
        return;
    }
    _print_level(H->junior, targetLevel, currentLevel + 1);
    _print_level(H->senior, targetLevel, currentLevel + 1);
}


