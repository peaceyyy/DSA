/*
========================================
PROBLEM 3: Toradora! Palmtop Tiger's Secret Santa
Difficulty: ★★★☆☆ (Medium)
Topic: Dictionary - Open Hashing (Cursor-Based / Virtual Heap)
StoryFlavor: anime (Toradora!)
========================================

Story:

It's Christmas Eve at Ohashi High School, and Taiga Aisaka (the "Palmtop Tiger") is
organizing the class Secret Santa gift exchange. However, her temper flares when she
realizes students keep swapping gift assignments behind her back!

To maintain order, she implements a **Gift Assignment Dictionary** using:
- **Virtual Heap**: Fixed-size array of 30 nodes with an availability list
- **Hash Table**: 13 buckets for fast lookup
- **GiftPair**: (giverID, receiverID) stored in cursor-based linked lists

The system uses **open hashing with cursor-based lists** to handle collisions.

Your mission as Ryuuji's cleanup crew:

**Operations Required:**

1. **initVirtualHeap(vh)**: Initialize the virtual heap
   - Set all nodes' `next` pointers to form an availability chain
   - Set `avail` to the last index (29)

2. **allocSpace(vh)**: Allocate a node from the virtual heap
   - Return the index of the available node
   - Update `avail` to the next available node
   - Return -1 if heap is full

3. **deallocSpace(vh, index)**: Return a node to the virtual heap
   - Add the node back to the availability list

4. **initDictionary(dict)**: Initialize all hash buckets to -1 (empty)

5. **hashGiver(giverID)**: Hash function using modulo 13
   Formula: `giverID % 13`

6. **assignGift(vh, dict, giverID, receiverID)**: Add a gift assignment
   - Hash the giverID
   - Allocate a node from the virtual heap
   - Insert at the **front** of the chain
   - If giverID already has an assignment, print warning and reject

7. **removeAssignment(vh, dict, giverID)**: Remove a gift assignment
   - Find the node and deallocate it

8. **findReceiver(vh, dict, giverID)**: Find who the giver is assigned to
   - Return receiverID if found, -1 otherwise

9. **swapAssignments(vh, dict, giverID1, giverID2)**: Swap receiver assignments
   - Find both assignments
   - Swap their receiverID values
   - Print "Taiga is angry!" if either giver not found

10. **displayDictionary(vh, dict)**: Show all gift assignments by hash bucket

11. **countAssignments(vh, dict)**: Count total active assignments

========================================
*/

#include <stdio.h>

#define HEAP_SIZE 30
#define BUCKET_COUNT 13

typedef struct
{
    int giverID;
    int receiverID;
    int next; // Index of next node in chain (-1 if end)
} GiftNode;

typedef struct
{
    GiftNode nodes[HEAP_SIZE];
    int avail; // Index of first available node
} VirtualHeap;

typedef int GiftDictionary[BUCKET_COUNT];

// TODO: Implement these functions
void initVirtualHeap(VirtualHeap *vh)
{
    for (int i = HEAP_SIZE; i >= 0; i--){

        vh->nodes[i].next = i - 1;
    }

    vh->avail = HEAP_SIZE - 1;
}

int allocSpace(VirtualHeap *vh)
{
    int temp = vh->avail;
    
    if (temp != -1){
        vh->avail = vh->nodes[temp].next;
    }

    return temp;
}

void deallocSpace(VirtualHeap *vh, int index)
{
    vh->nodes[index].next = vh->avail;
    vh->avail = index;
}

void initDictionary(GiftDictionary dict)
{
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        dict[i] = -1;
    }
}

int hashGiver(int giverID)
{
    return giverID % 13;
}


/*
6. **assignGift(vh, dict, giverID, receiverID)**: Add a gift assignment
   - Hash the giverID
   - Allocate a node from the virtual heap
   - Insert at the **front** of the chain
   - If giverID already has an assignment, print warning and reject

7. **removeAssignment(vh, dict, giverID)**: Remove a gift assignment
   - Find the node and deallocate it

8. **findReceiver(vh, dict, giverID)**: Find who the giver is assigned to
   - Return receiverID if found, -1 otherwise

9. **swapAssignments(vh, dict, giverID1, giverID2)**: Swap receiver assignments
   - Find both assignments
   - Swap their receiverID values
   - Print "Taiga is angry!" if either giver not found

10. **displayDictionary(vh, dict)**: Show all gift assignments by hash bucket

11. **countAssignments(vh, dict)**: Count total active assignments

*/

void assignGift(VirtualHeap *vh, GiftDictionary dict, int giverID, int receiverID)
{
    int hashValue = hashGiver(giverID);

    // look for duplicate first
    int* trav;

    for (trav = &dict[hashValue]; *trav != -1; trav = &vh->nodes[*trav].next){
        if (vh->nodes[*trav].giverID == giverID){
            printf("\nGiver %d already has an assignment!\n", giverID);
            return;
        }
    }

    
        int newAvail = allocSpace(vh);

        if (newAvail != -1){

        vh->nodes[newAvail].giverID = giverID;
        vh->nodes[newAvail].receiverID = receiverID;
        vh->nodes[newAvail].next = dict[hashValue];
        dict[hashValue] = newAvail;
        }
        
    

    

}

void removeAssignment(VirtualHeap *vh, GiftDictionary dict, int giverID)
{
    int hashValue = hashGiver(giverID);

    
    int* trav;

    for (trav = &dict[hashValue]; *trav != -1 && vh->nodes[*trav].giverID != giverID; trav = &vh->nodes[*trav].next){}

    if (*trav != -1){
        int temp = *trav;
        *trav = vh->nodes[temp].next;

        deallocSpace(vh, temp);

    }

    

}

int findReceiver(VirtualHeap vh, GiftDictionary dict, int giverID)
{
     int hashValue = hashGiver(giverID);

    // look for duplicate first
    int trav;

    for (trav = dict[hashValue]; trav != -1; trav = vh.nodes[trav].next){
        if (vh.nodes[trav].giverID == giverID){
            return vh.nodes[trav].receiverID;
        }
    }

    return -1;
}

/*

9. **swapAssignments(vh, dict, giverID1, giverID2)**: Swap receiver assignments
   - Find both assignments
   - Swap their receiverID values
   - Print "Taiga is angry!" if either giver not found

*/
void swapAssignments(VirtualHeap *vh, GiftDictionary dict, int giverID1, int giverID2)
{
    int A = findReceiver(*vh, dict, giverID1);
    int B = findReceiver(*vh, dict, giverID2);

    if (A != -1 && B != -1){

        int a = hashGiver(giverID1);
        int b = hashGiver(giverID2);


        int travA;
        for (travA = dict[a]; travA != -1; travA = vh->nodes[travA].next){
            if (vh->nodes[travA].giverID == giverID1){
                break;
            }
        }

        int travB;
        for (travB = dict[b]; travB != -1; travB = vh->nodes[travB].next){
            if (vh->nodes[travB].giverID == giverID2){
                break;
            }
        }

        int temp = vh->nodes[travA].giverID;
        vh->nodes[travA].giverID = vh->nodes[travB].giverID;
        vh->nodes[travB].giverID = temp;


    } else {
        printf("Taiga is angry!" );
    }
}

void displayDictionary(VirtualHeap vh, GiftDictionary dict)
{
    printf("\n=== Taiga's Secret Santa Gift Assignments ===\n");
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        printf("Bucket [%2d]: ", i);
        int current = dict[i];
        if (current == -1)
        {
            printf("(no assignments)\n");
        }
        else
        {
            while (current != -1)
            {
                printf("{Giver:%d -> Receiver:%d} -> ", vh.nodes[current].giverID, vh.nodes[current].receiverID);
                current = vh.nodes[current].next;
            }
            printf("END\n");
        }
    }
    printf("=============================================\n");
}

int countAssignments(VirtualHeap vh, GiftDictionary dict)
{
    int count = 0;
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        int current = dict[i];
        while (current != -1)
        {
            count++;
            current = vh.nodes[current].next;
        }
    }
    return count;
}

// --- Main Function (Test Cases) ---
int main()
{
    printf("========================================\n");
    printf("OHASHI HIGH - TAIGA'S SECRET SANTA ORGANIZER\n");
    printf("Taiga: 'No swapping gifts without my permission!'\n");
    printf("========================================\n");

    VirtualHeap vh;
    GiftDictionary dict;

    initVirtualHeap(&vh);
    initDictionary(dict);

    printf("\n--- Test Case 1: Initial State ---\n");
    printf("Available nodes in heap: %d\n", vh.avail);
    displayDictionary(vh, dict);
    // Expected: avail = 29, all buckets empty

    printf("\n--- Test Case 2: Assign Gifts (No Collisions) ---\n");
    assignGift(&vh, dict, 101, 202); // Taiga -> Ryuuji
    assignGift(&vh, dict, 114, 303); // Minori -> Yusaku
    assignGift(&vh, dict, 5, 404);   // Ami -> Kitamura
    displayDictionary(vh, dict);
    // Expected: Assignments in respective hash buckets

    printf("\n--- Test Case 3: Assign with Collisions ---\n");
    assignGift(&vh, dict, 127, 505); // Hash = 10 (collides with 114)
    assignGift(&vh, dict, 140, 606); // Hash = 10 (another collision)
    displayDictionary(vh, dict);
    // Expected: Bucket 10 has chain: 140 -> 127 -> 114 -> END

    printf("\n--- Test Case 4: Find Receivers ---\n");
    printf("Giver 101 is assigned to: %d\n", findReceiver(vh, dict, 101));
    printf("Giver 114 is assigned to: %d\n", findReceiver(vh, dict, 114));
    printf("Giver 999 is assigned to: %d\n", findReceiver(vh, dict, 999));
    // Expected: 202, 303, -1

    printf("\n--- Test Case 5: Duplicate Prevention ---\n");
    assignGift(&vh, dict, 101, 999); // Duplicate giverID
    displayDictionary(vh, dict);
    // Expected: Warning, no change

    printf("\n--- Test Case 6: Swap Assignments ---\n");
    printf("Before swap:\n");
    printf("  Giver 101 -> Receiver %d\n", findReceiver(vh, dict, 101));
    printf("  Giver 114 -> Receiver %d\n", findReceiver(vh, dict, 114));

    swapAssignments(&vh, dict, 101, 114);

    printf("After swap:\n");
    printf("  Giver 101 -> Receiver %d\n", findReceiver(vh, dict, 101));
    printf("  Giver 114 -> Receiver %d\n", findReceiver(vh, dict, 114));
    // Expected: 101->303, 114->202 (swapped)

    printf("\n--- Test Case 7: Remove Assignment ---\n");
    removeAssignment(&vh, dict, 127);
    displayDictionary(vh, dict);
    printf("Available nodes after removal: %d\n", vh.avail);
    // Expected: 127 removed, node returned to avail list

    printf("\n--- Test Case 8: Reuse Deallocated Node ---\n");
    assignGift(&vh, dict, 999, 777); // Should reuse deallocated node
    displayDictionary(vh, dict);
    printf("Total assignments: %d\n", countAssignments(vh, dict));
    // Expected: New assignment uses recycled node

    printf("\n--- Test Case 9: Edge Case - Invalid Swap ---\n");
    swapAssignments(&vh, dict, 101, 9999); // 9999 doesn't exist
    // Expected: "Taiga is angry!" message

    printf("\n--- Test Case 10: Fill Heap ---\n");
    printf("Assigning mass gifts to test heap capacity...\n");
    for (int i = 200; i < 230; i++)
    {
        assignGift(&vh, dict, i, i + 1000);
    }
    printf("Total assignments: %d\n", countAssignments(vh, dict));
    printf("Available nodes remaining: %d\n", vh.avail);
    // Expected: Should approach heap capacity (30 nodes)

    printf("\n--- Test Case 11: Heap Full Test ---\n");
    assignGift(&vh, dict, 999, 888); // Should fail if heap full
    displayDictionary(vh, dict);
    // Expected: Error message if heap exhausted

    printf("\n--- Test Case 12: Remove Multiple and Recheck ---\n");
    removeAssignment(&vh, dict, 200);
    removeAssignment(&vh, dict, 201);
    removeAssignment(&vh, dict, 202);
    printf("Total assignments after removals: %d\n", countAssignments(vh, dict));
    printf("Available nodes: %d\n", vh.avail);
    // Expected: Count reduced, avail increased

    printf("\n========================================\n");
    printf("SECRET SANTA ORGANIZER TEST COMPLETE\n");
    printf("Ryuuji: 'Taiga, everyone got their gifts safely!'\n");
    printf("========================================\n");

    return 0;
}
