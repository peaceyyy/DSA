// 📜 Story Problem: The Quantum Access Panel

// The research facility at NovaDyne Labs controls entry to seven experimental chambers, each requiring a unique access bit within a 16-bit control word.

// Each scientist has a 16-bit clearance key representing which chambers they can access.
// A bit value of 1 indicates access granted, while 0 indicates restricted.

// The system must support the following operations:

// GrantAccess(id, chamber) – Turns ON the corresponding bit in a scientist’s key.

// RevokeAccess(id, chamber) – Turns OFF the bit.

// CheckAccess(id, chamber) – Returns whether the scientist currently has clearance.

// MergeAccess(idA, idB) – Creates a new clearance key that combines both scientists’ access rights.

// ExclusiveAccess(idA, idB) – Produces a clearance key containing only the chambers unique to either scientist (not both).

// At any time, the system should be able to print all scientists’ clearance keys in binary form, padded to 16 bits.

// Example Session:
// Suppose there are three scientists, initially with all bits off.
// After the following commands:

// GrantAccess(1, 5)
// GrantAccess(2, 5)
// GrantAccess(2, 6)
// GrantAccess(3, 1)
// ExclusiveAccess(1, 2)


// the resulting exclusive clearance between scientist 1 and 2 should reflect access to chamber 6 only.

#include <stdio.h>
#include <stdlib.h>

#define MAX_SCIENTISTS 10
#define WORD_SIZE 16  // 16-bit control word

typedef unsigned int Word;  // each scientist’s clearance key

// FUNCTION PROTOTYPES
void initClearances(Word keys[], int n);
void grantAccess(Word keys[], int id, int chamber);
void revokeAccess(Word keys[], int id, int chamber);
int checkAccess(Word keys[], int id, int chamber);
Word mergeAccess(Word keys[], int idA, int idB);
Word exclusiveAccess(Word keys[], int idA, int idB);
void printClearances(Word keys[], int n);

// MAIN FUNCTION
int main() {
    Word clearances[MAX_SCIENTISTS];
    int n = 3; // number of scientists

    initClearances(clearances, n);

    printf("=== Quantum Access Panel Simulation ===\n");

    grantAccess(clearances, 1, 5);
    grantAccess(clearances, 2, 5);
    grantAccess(clearances, 2, 6);
    grantAccess(clearances, 3, 1);

    printf("\n-- Current Clearances --\n");
    printClearances(clearances, n);

    printf("\nChecking access:\n");
    printf("Scientist 1 -> Chamber 5: %s\n", checkAccess(clearances, 1, 5) ? "YES" : "NO");
    
    printf("Scientist 2 -> Chamber 6: %s\n", checkAccess(clearances, 2, 6) ? "YES" : "NO");
    printf("Scientist 3 -> Chamber 7: %s\n", checkAccess(clearances, 3, 7) ? "YES" : "NO");

    printf("\nMerging Scientist 1 and 2:\n");
    Word merged = mergeAccess(clearances, 1, 2);
    printf("Merged Access (S1 + S2): ");
    for (int i = WORD_SIZE - 1; i >= 0; i--)
        printf("%d", (merged >> i) & 1);
    printf("\n");

    printf("\nExclusive Access between Scientist 1 and 2:\n");
    Word exclusive = exclusiveAccess(clearances, 1, 2);
    printf("Exclusive Access (S1 XOR S2): ");
    for (int i = WORD_SIZE - 1; i >= 0; i--)
        printf("%d", (exclusive >> i) & 1);
    printf("\n");

    printf("\n=== Expected Output Summary ===\n");
    printf("Scientist 1 -> 0000000000100000\n");
    printf("Scientist 2 -> 0000000001100000\n");
    printf("Scientist 3 -> 0000000000000010\n");
    printf("Merged (1 + 2) -> 0000000001100000\n");
    printf("Exclusive (1 XOR 2) -> 0000000001000000\n");

    return 0;
}

void printClearances(Word keys[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Scientist %d: ", i + 1);
        for (int j = WORD_SIZE - 1; j >= 0; j--) {
            printf("%d", (keys[i] >> j) & 1);
        }
        printf("\n");
    }
}

// FUNCTION DEFINITIONS (You fill these in)

void initClearances(Word keys[], int n) {
    for (int i = 0; i < n; i++) keys[i] = 0u;
}

void grantAccess(Word keys[], int id, int chamber) {
    // Set bit to 1 (grant access)
    keys[id - 1] |= (1u << chamber);
}

void revokeAccess(Word keys[], int id, int chamber) {
    // Set bit to 0 (revoke access)
    keys[id - 1] &= ~(1u << chamber);
}

int checkAccess(Word keys[], int id, int chamber) {
    // Return 1 if bit is set, else 0
    return (keys[id - 1] & (1u << chamber)) != 0 ? 1 : 0;
}

Word mergeAccess(Word keys[], int idA, int idB) {
    // Creates a new clearance key that combines BOTH scientists’ access rights
    return (keys[idA - 1] | keys[idB - 1]); 
}

Word exclusiveAccess(Word keys[], int idA, int idB) {
    // Produces a clearance key containing only the chambers UNIQUE to either scientist.
    return (keys[idA - 1] ^ keys[idB - 1]); 
}

