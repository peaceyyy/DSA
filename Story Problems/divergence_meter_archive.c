/*
 * THE DIVERGENCE METER ARCHIVE
 * By Professor Okabe, Lab Member 001
 * 
 * STORY:
 * The Future Gadget Lab has discovered a way to track world line shifts using
 * a distributed hash table stored in a "Virtual Heap" — a cursor-based memory
 * system that simulates dynamic allocation without using malloc.
 * 
 * Each world line divergence value (integer) is stored in this hash table,
 * and collisions are resolved using open hashing (separate chaining) with
 * cursor-based linked lists.
 * 
 * Your mission: Implement the archive's core operations to track, query,
 * and manipulate divergence records.
 * 
 * SYSTEM SPECIFICATIONS:
 * 
 * VirtualHeap Structure:
 *   - Fixed-size array of nodes (HEAP_SIZE = 30)
 *   - Each node contains: {divergenceValue, nextIndex}
 *   - avail pointer tracks the head of the free list
 *   - Nodes are "allocated" by removing from avail list
 *   - Nodes are "deallocated" by returning to avail list
 * 
 * Archive Structure:
 *   - Array of TABLE_SIZE (10) head pointers
 *   - Each head points to the start of a collision chain
 *   - -1 indicates NULL/end of chain
 * 
 * Hash Function:
 *   - hash(x) = x % TABLE_SIZE (returns index 0-9)
 * 
 * YOUR TASKS:
 * 
 * 1. PROTOCOL_INIT_MEMORY(VirtualHeap *VH)
 *    "Initialize the virtual heap by linking all nodes into the free list.
 *     The avail pointer should point to the last valid index, and each node
 *     should point backwards (node[i].link = i - 1). node[0].link = -1."
 * 
 * 2. PROTOCOL_INIT_ARCHIVE(Archive A)
 *    "Initialize all hash table heads to -1 (empty chains)."
 * 
 * 3. PROTOCOL_REGISTER_DIVERGENCE(VirtualHeap *VH, Archive A, int value)
 *    "Insert a divergence value into the archive:
 *     - Compute hash index
 *     - Allocate a node from avail (if available)
 *     - Insert at the FRONT of the collision chain (O(1) insertion)
 *     - Update the appropriate head pointer"
 * 
 * 4. PROTOCOL_PURGE_DIVERGENCE(VirtualHeap *VH, Archive A, int value)
 *    "Remove a divergence value from the archive:
 *     - Compute hash index
 *     - Traverse the collision chain to find the node
 *     - Unlink the node from the chain
 *     - Return the node to the avail list (deallocation)"
 * 
 * 5. PROTOCOL_VERIFY_EXISTENCE(VirtualHeap *VH, Archive A, int value)
 *    "Check if a divergence value exists in the archive:
 *     - Compute hash index
 *     - Traverse the collision chain
 *     - Return 1 if found, 0 if not found"
 * 
 * 6. PROTOCOL_DISPLAY_MEMORY(VirtualHeap *VH, Archive A)
 *    "Display the current state of the archive:
 *     - Show avail pointer
 *     - For each hash index, show the collision chain"
 * 
 * CONSTRAINTS:
 * - Use cursor-based indexing (no malloc/free)
 * - Maintain the avail free list correctly
 * - Handle edge cases (full heap, empty chains, duplicate insertions)
 * 
 * EXPECTED BEHAVIOR:
 * For test inputs: 10, 20, 30, 11, 21, 31, 15
 * 
 * Hash index 0: 10 -> 20 -> 30 (values % 10 == 0)
 * Hash index 1: 11 -> 21 -> 31 (values % 10 == 1)
 * Hash index 5: 15 (value % 10 == 5)
 * 
 * After deleting 20 and 31:
 * Hash index 0: 10 -> 30
 * Hash index 1: 11 -> 21
 * Hash index 5: 15
 */

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define HEAP_SIZE 30

typedef struct {
    int divergenceValue;  // The data stored in this node
    int nextIndex;        // Index of next node in chain (-1 = end)
} MemoryNode;

typedef struct {
    MemoryNode nodes[HEAP_SIZE];  // Fixed array of nodes
    int avail;                     // Head of free list
} VirtualHeap;

typedef int Archive[TABLE_SIZE];  // Array of head pointers

// =========================================================================
// FUNCTION PROTOTYPES (YOU MUST IMPLEMENT THESE)
// =========================================================================

void PROTOCOL_INIT_MEMORY(VirtualHeap *VH);
void PROTOCOL_INIT_ARCHIVE(Archive A);
int computeHash(int value);
void PROTOCOL_REGISTER_DIVERGENCE(VirtualHeap *VH, Archive A, int value);
void PROTOCOL_PURGE_DIVERGENCE(VirtualHeap *VH, Archive A, int value);
int PROTOCOL_VERIFY_EXISTENCE(VirtualHeap *VH, Archive A, int value);
void PROTOCOL_DISPLAY_MEMORY(VirtualHeap *VH, Archive A);

// =========================================================================
// TODO: IMPLEMENT ALL PROTOCOLS BELOW
// =========================================================================

void PROTOCOL_INIT_MEMORY(VirtualHeap *VH) {
    

    for (int i = 0; i < HEAP_SIZE; i++){
        VH->nodes[i].nextIndex = i - 1;
    }

    VH->avail = HEAP_SIZE - 1;
}

void PROTOCOL_INIT_ARCHIVE(Archive A) {

    for (int i = 0; i < TABLE_SIZE; i++)
    {
            A[i] = -1; 
    }
}

int computeHash(int value) {


    return value % TABLE_SIZE;
}

void PROTOCOL_REGISTER_DIVERGENCE(VirtualHeap *VH, Archive A, int value) {
    
    int hashValue = computeHash(value);

    int* trav;

    for (trav = &A[hashValue]; *trav != -1 && VH->nodes[*trav].divergenceValue != value; trav = &VH->nodes[*trav].nextIndex){}

    if (*trav == -1)
    {
        printf("INSERTED");
        int temp = VH->avail;
        if (temp != -1)
        {
            VH->avail = VH->nodes[temp].nextIndex;

        }

        VH->nodes[temp].divergenceValue = value;
        VH->nodes[temp].nextIndex = *trav;
        *trav = temp;
    }

    
}

void PROTOCOL_PURGE_DIVERGENCE(VirtualHeap *VH, Archive A, int value) {
    // TODO: Delete value from hash table
    // 1. Compute hash index
    // 2. Traverse chain to find node (use pointer to pointer or index tracking)
    // 3. Unlink node from chain
    // 4. Deallocate: nodes[temp].nextIndex = avail; avail = temp

    int hashValue = computeHash(value);

    

    *trav = VH->nodes[temp].nextIndex; 

    VH->nodes[temp].nextIndex = VH->avail;
    VH->avail = temp;
        
        
    

}

int PROTOCOL_VERIFY_EXISTENCE(VirtualHeap *VH, Archive A, int value) {
    int hashValue = computeHash(value);

    int* trav;

    for (trav = &A[hashValue]; *trav != -1; trav = &VH->nodes[*trav].nextIndex){


        if (VH->nodes[*trav].divergenceValue == value) return 1;
    }
    
    return 0;
}

void PROTOCOL_DISPLAY_MEMORY(VirtualHeap *VH, Archive A) {
    // TODO: Display archive state
    // Print avail pointer
    // For each hash index, print the collision chain
    printf("\n[ARCHIVE STATUS]\n");
    printf("Avail: %d\n", VH->avail);
    printf("\nDivergence Chains:\n");
    // Loop through each hash index and traverse chains
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (A[i] == -1) {
            printf("(empty)\n");
        } else {
            int current = A[i];
            while (current != -1) {
                printf("%d", VH->nodes[current].divergenceValue);
                current = VH->nodes[current].nextIndex;
                if (current != -1) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }
}

// =========================================================================
// MAIN - TEST HARNESS (DO NOT MODIFY)
// =========================================================================

int main(void) {
    VirtualHeap VH;
    Archive A;
    
    printf("=== DIVERGENCE METER ARCHIVE INITIALIZATION ===\n");
    PROTOCOL_INIT_MEMORY(&VH);
    PROTOCOL_INIT_ARCHIVE(A);
    
    printf("\nInitial State:\n");
    PROTOCOL_DISPLAY_MEMORY(&VH, A);
    
    printf("\n\n=== REGISTERING DIVERGENCE VALUES ===\n");
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 10);
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 20);
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 30);
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 11);
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 21);
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 31);
    PROTOCOL_REGISTER_DIVERGENCE(&VH, A, 15);
    
    printf("\nAfter Registration:\n");
    PROTOCOL_DISPLAY_MEMORY(&VH, A);
    // Expected:
    // Index 0: 30 -> 20 -> 10
    // Index 1: 31 -> 21 -> 11
    // Index 5: 15
    
    printf("\n\n=== VERIFYING EXISTENCE ===\n");
    printf("Divergence 20 exists: %s\n", PROTOCOL_VERIFY_EXISTENCE(&VH, A, 20) ? "YES" : "NO");
    printf("Divergence 99 exists: %s\n", PROTOCOL_VERIFY_EXISTENCE(&VH, A, 99) ? "YES" : "NO");
    // Expected: 20 = YES, 99 = NO
    
    printf("\n\n=== PURGING DIVERGENCE VALUES ===\n");
    PROTOCOL_PURGE_DIVERGENCE(&VH, A, 20);
    PROTOCOL_PURGE_DIVERGENCE(&VH, A, 31);
    
    printf("\nAfter Purge:\n");
    PROTOCOL_DISPLAY_MEMORY(&VH, A);
    // Expected:
    // Index 0: 30 -> 10
    // Index 1: 21 -> 11
    // Index 5: 15
    
    printf("\n\n=== FINAL VERIFICATION ===\n");
    printf("Divergence 20 exists: %s\n", PROTOCOL_VERIFY_EXISTENCE(&VH, A, 20) ? "YES" : "NO");
    printf("Divergence 30 exists: %s\n", PROTOCOL_VERIFY_EXISTENCE(&VH, A, 30) ? "YES" : "NO");
    // Expected: 20 = NO, 30 = YES
    
    printf("\n=== PROTOCOL EXECUTION COMPLETE ===\n");
    printf("El. Psy. Kongroo.\n");
    
    return 0;
}
