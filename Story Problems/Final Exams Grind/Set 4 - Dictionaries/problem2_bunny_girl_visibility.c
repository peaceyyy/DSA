/*
========================================
PROBLEM 2: Bunny Girl Senpai Visibility Registry
Difficulty: ★★★☆☆ (Medium)
Topic: Dictionary - Closed Hashing (Linear Probing)
StoryFlavor: anime (Rascal Does Not Dream of Bunny Girl Senpai)
========================================

Story:

In Fujisawa, Adolescence Syndrome has struck again. Mai Sakurajima, the famous actress
turned invisible to most students, needs a tracking system to monitor who can still see her.

The **Visibility Registry** uses a closed hash table where:
- **studentID**: Unique 3-digit identifier (e.g., 451 for Sakuta Azusagawa)
- **visibilityStatus**: 1 = can see Mai, 0 = cannot see her, -1 = DELETED

The registry uses **linear probing** to resolve collisions. A key metric is the
**search length** — how many slots you check before finding a student or an empty slot.

Your mission as Sakuta's debugging partner:

**Operations Required:**

1. **initRegistry()**: Initialize all slots to EMPTY (0)

2. **hashStudent(studentID)**: Hash function using modulo 19
   Formula: `studentID % 19`

3. **registerStudent(registry, studentID)**: Add a student who can see Mai
   - Use linear probing if the hashed slot is occupied
   - Mark slot with studentID (positive integer)
   - If studentID already exists, print warning
   - **Important:** Skip DELETED slots (-1) during insertion, but they can be reused

4. **removeStudent(registry, studentID)**: Mark a student as DELETED
   - Find the student using linear probing
   - Set slot to -1 (DELETED sentinel)
   - **Do NOT set to 0 (EMPTY)** — this breaks search chains

5. **canSeeMai(registry, studentID)**: Check if a student is registered
   - Return 1 if found, 0 otherwise
   - Must probe through DELETED slots

6. **calculateSearchLength(registry, studentID)**: Return how many probes it takes
   - Count slots checked from hash position to finding the student or EMPTY
   - If not found, return -1

7. **displayRegistry(registry)**: Show all slots with their states
   - Display: Index | StudentID | Status | SearchLength

8. **getAverageSearchLength(registry)**: Calculate avg search length for all active students

========================================
*/

#include <stdio.h>

#define REGISTRY_SIZE 19
#define EMPTY 0
#define DELETED -1

typedef int VisibilityRegistry[REGISTRY_SIZE];

// TODO: Implement these functions
void initRegistry(VisibilityRegistry registry)
{
    for (int i = 0; i < REGISTRY_SIZE; i++)
    {
        registry[i] = EMPTY;
    }
}

int hashStudent(int studentID)
{   
    // printf("Hash of %d is %d\n", studentID, studentID % 19);
    return studentID % 19;
}

/*
3. **registerStudent(registry, studentID)**: Add a student who can see Mai
   - Use linear probing if the hashed slot is occupied
   - Mark slot with studentID (positive integer)
   - If studentID already exists, print warning
   - **Important:** Skip DELETED slots (-1) during insertion, but they can be reused
*/

void registerStudent(VisibilityRegistry registry, int studentID)
{
    int hashValue = hashStudent(studentID);
    int firstDeletedSlot = 0;
    int foundDeletedSlot = 0;

    if (registry[hashValue] == studentID) return;

    if (registry[hashValue] != EMPTY && registry[hashValue] != DELETED)
    {   


        int i;
        for (i = hashValue + 1; i != hashValue && registry[i] != EMPTY; i = (i + 1) % REGISTRY_SIZE)
        {

            if (registry[i] == studentID) return;
            if (registry[i] == DELETED && foundDeletedSlot != 1)
            {
                firstDeletedSlot = i;
                foundDeletedSlot = 1;
            }

        }

        if (i != hashValue && foundDeletedSlot == 0)
        {
            registry[i] = studentID;
        }
        else
        {
            if (foundDeletedSlot)
            {
                registry[firstDeletedSlot] = studentID;
            }
            else
            {
                printf("Registry full!");
            }
        }
    }

    else
    {
        registry[hashValue] = studentID;
    }
}

/*
4. **removeStudent(registry, studentID)**: Mark a student as DELETED
   - Find the student using linear probing
   - Set slot to -1 (DELETED sentinel)
   - **Do NOT set to 0 (EMPTY)** — this breaks search chains
*/

void removeStudent(VisibilityRegistry registry, int studentID)
{

    int hashValue = hashStudent(studentID);

    if  (registry[hashValue] == studentID){
        registry[hashValue] = DELETED;
    } else {
        int i;
        for (i = hashValue + 1; i != hashValue && registry[i] != EMPTY && registry[i] != studentID; i = (i + 1) % REGISTRY_SIZE){}

        if (i != hashValue && registry[i] != EMPTY){

            registry[i] = DELETED;
        }


    }

}
/*
5. **canSeeMai(registry, studentID)**: Check if a student is registered
   - Return 1 if found, 0 otherwise
   - Must probe through DELETED slots

*/
int canSeeMai(VisibilityRegistry registry, int studentID)
{
    int hashValue = hashStudent(studentID);
    int canSee = 0;

    if  (registry[hashValue] == studentID){
        canSee = 1;
    } else {
        int i;
        for (i = hashValue + 1; i != hashValue && registry[i] != studentID && registry[i] != EMPTY; i = (i + 1) % REGISTRY_SIZE){}

        if (i != hashValue  && registry[i] != EMPTY){

            canSee = 1;
        }


    }

    return canSee;
}
/*
6. **calculateSearchLength(registry, studentID)**: Return how many probes it takes
   - Count slots checked from hash position to finding the student or EMPTY
   - If not found, return -1
*/
int calculateSearchLength(VisibilityRegistry registry, int studentID)
{
    
    
    int hashValue = hashStudent(studentID);
    int count = 0;
    int found = 0;

    if  (registry[hashValue] == studentID){
        count++;
    } else {
        int i;
        for (i = hashValue + 1; registry[i] != studentID && registry[i] != EMPTY; i = (i + 1) % REGISTRY_SIZE){
            count++;
        }

        if (i == hashValue) count = -1;
    }

    return count;
}

void displayRegistry(VisibilityRegistry registry)
{
    printf("\n=== Visibility Registry (Adolescence Syndrome Tracker) ===\n");
    printf("Index | StudentID | Hash | SearchLength | Status\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < REGISTRY_SIZE; i++)
    {
        printf("[%2d]  | ", i);
        if (registry[i] == EMPTY)
        {
            printf("  EMPTY   |  -   |      -       | (no student)\n");
        }
        else if (registry[i] == DELETED)
        {
            printf(" DELETED  |  -   |      -       | (removed)\n");
        }
        else
        {
            int hash = hashStudent(registry[i]);
            int searchLen = calculateSearchLength(registry, registry[i]);
            printf("   %3d    | %2d   |      %d       | Active\n", registry[i], hash, searchLen);
        }
    }
    printf("========================================================\n");
}
/*

8. **getAverageSearchLength(registry)**: Calculate avg search length for all active students
*/

float getAverageSearchLength(VisibilityRegistry registry)
{
    int totalSearchLength = 0;
    int activeCount = 0;

    for (int i = 0; i < REGISTRY_SIZE; i++)
    {
        if (registry[i] > 0)
        { // Active student
            totalSearchLength += calculateSearchLength(registry, registry[i]);
            activeCount++;
        }
    }

    return (activeCount > 0) ? (float)totalSearchLength / activeCount : 0.0f;
}

// --- Main Function (Test Cases) ---
int main()
{
    printf("========================================\n");
    printf("FUJISAWA HIGH - MAI SAKURAJIMA VISIBILITY TRACKER\n");
    printf("Sakuta: 'If you can see her, you're one of the lucky ones.'\n");
    printf("========================================\n");

    VisibilityRegistry registry;
    initRegistry(registry);

    printf("\n--- Test Case 1: Initial State ---\n");
    displayRegistry(registry);
    // Expected: All slots EMPTY

    printf("\n--- Test Case 2: Register Students (No Collisions) ---\n");
    registerStudent(registry, 451); // Sakuta -> Hash 14
    registerStudent(registry, 320); // Rio -> Hash 16
    registerStudent(registry, 108); // Tomoe -> Hash 13
    displayRegistry(registry);
    // Expected:
    // [13]: 108 | Hash 13 | SearchLength 1
    // [14]: 451 | Hash 14 | SearchLength 1
    // [16]: 320 | Hash 16 | SearchLength 1

    printf("\n--- Test Case 3: More Collisions ---\n");
    registerStudent(registry, 32);  // Hash 13 (collision with 108! Probes to 15)
    registerStudent(registry, 127); // Hash 13 (collision! Probes to 17)
    displayRegistry(registry);
    // Expected:
    // [13]: 108 | SearchLength 1
    // [14]: 451 | SearchLength 1
    // [15]: 32  | SearchLength 3 (probed from 13 -> 14 -> 15)
    // [16]: 320 | SearchLength 1
    // [17]: 127 | SearchLength 5 (probed from 13 -> 14 -> 15 -> 16 -> 17)

    printf("\n--- Test Case 4: Check Visibility ---\n");
    printf("Can Sakuta (451) see Mai? %s\n", canSeeMai(registry, 451) ? "Yes" : "No");
    printf("Can Tomoe (108) see Mai? %s\n", canSeeMai(registry, 108) ? "Yes" : "No");
    printf("Can Koga (999) see Mai? %s\n", canSeeMai(registry, 999) ? "Yes" : "No");
    // Expected: Yes, Yes, No

    printf("\n--- Test Case 5: Remove Student (DELETED Sentinel Test) ---\n");
    removeStudent(registry, 108); // Remove from slot 13
    displayRegistry(registry);
    // Expected: Slot 13 now shows DELETED
    // Search for 32 should still work (probes through DELETED at 13)

    printf("\n--- Test Case 6: Verify Search Through DELETED ---\n");
    printf("Can student 32 still be found? %s\n", canSeeMai(registry, 32) ? "Yes" : "No");
    printf("Search length for 32: %d\n", calculateSearchLength(registry, 32));
    // Expected: Yes, SearchLength should account for probing through DELETED

    printf("\n--- Test Case 7: Reuse DELETED Slot ---\n");
    registerStudent(registry, 999); // Should reuse slot 14 (DELETED)
    displayRegistry(registry);
    // Expected: Slot 11 now has 999

    printf("\n--- Test Case 8: Duplicate Prevention ---\n");
    registerStudent(registry, 451); // Duplicate
    displayRegistry(registry);
    // Expected: Warning, no change

    printf("\n--- Test Case 9: Wraparound Collision ---\n");
    registerStudent(registry, 18); // Hash 18
    registerStudent(registry, 37); // Hash 18 (wraps to 0)
    registerStudent(registry, 56); // Hash 18 (wraps to 1)
    displayRegistry(registry);
    // Expected:
    // [18]: 18
    // [0]: 37
    // [1]: 56

    printf("\n--- Test Case 10: Average Search Length ---\n");
    printf("Average search length: %.2f\n", getAverageSearchLength(registry));
    // Expected: Should reflect collision clustering

    printf("\n--- Test Case 11: Mass Deletion and Reinsertion ---\n");
    removeStudent(registry, 451);
    removeStudent(registry, 32);
    removeStudent(registry, 127);
    printf("After deletions:\n");
    displayRegistry(registry);

    registerStudent(registry, 200); // Should reuse DELETED slots
    registerStudent(registry, 201);
    printf("\nAfter reinsertions:\n");
    displayRegistry(registry);
    // Expected: DELETED slots reused efficiently

    printf("\n--- Test Case 12: Edge Case - Full Table Simulation ---\n");
    for (int i = 100; i < 119; i++)
    {
        registerStudent(registry, i);
    }
    displayRegistry(registry);
    printf("Average search length when near-full: %.2f\n", getAverageSearchLength(registry));
    // Expected: High search lengths due to clustering

    printf("\n========================================\n");
    printf("VISIBILITY REGISTRY TEST COMPLETE\n");
    printf("Mai: 'Thank you for seeing me, Sakuta.'\n");
    printf("========================================\n");

    return 0;
}
