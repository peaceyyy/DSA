/*
========================================
PROBLEM 2: The Izakaya Access Panel
Difficulty: ★★★☆☆ (Medium)
Topic: Computer Word Set Operations
========================================

Story:

In the neon-lit streets of Shibuya, there's a hidden izakaya (Japanese pub) called "The Binary Byte" 
that only allows entry to members with special access codes. The bouncer, Hiroshi-san, uses a compact 
8-bit electronic panel to track VIP permissions.

Each of the 8 bits represents a different privilege:
- Bit 0: Free appetizers
- Bit 1: Premium sake access
- Bit 2: Private booth reservation
- Bit 3: Karaoke room access
- Bit 4: Chef's special menu
- Bit 5: Late-night entry (after 11 PM)
- Bit 6: Bring guests privilege
- Bit 7: VIP lounge access

Two regular customers, Kenji and Yuki, each have their own access codes stored as single bytes. 
Hiroshi-san needs to analyze their combined privileges for a special event.

Your Task:
Implement Computer Word Set operations to manage these 8-bit privilege codes efficiently.

========================================
Data Structures Provided:
========================================
*/

#include <stdio.h>

typedef unsigned char SET;

// --- Function Prototypes ---
void initSet(SET *A);
void insertPrivilege(SET *A, int bitPosition);
void removePrivilege(SET *A, int bitPosition);
int hasPrivilege(SET A, int bitPosition);
void displaySet(SET A, const char* name);
void displayBitPattern(SET A);

// TODO: Implement these functions

    // Privileges either person has
SET unionSet(SET A, SET B){
    
    return A | B;

}    

// Privileges BOTH people have
SET intersectionSet(SET A, SET B){
    return A & B;

}

// Privileges only A has (A - B)
SET differenceSet(SET A, SET B){

    return A & ~B;

}      
SET complementSet(SET A){
    return ~A;
}

int isSubset(SET A, SET B){

    return (intersectionSet(A, B) == B) ? 1 : 0;
}          

// --- Helper Functions (Already Implemented) ---
void initSet(SET *A) {
    *A = 0;
}

void insertPrivilege(SET *A, int bitPosition) {
    if(bitPosition >= 0 && bitPosition < 8) {
        *A |= (1 << bitPosition);
    }
}

void removePrivilege(SET *A, int bitPosition) {
    if(bitPosition >= 0 && bitPosition < 8) {
        *A &= ~(1 << bitPosition);
    }
}

int hasPrivilege(SET A, int bitPosition) {
    return (A & (1 << bitPosition)) != 0;
}

void displaySet(SET A, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < 8; i++) {
        if(hasPrivilege(A, i)) {
            if(!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

void displayBitPattern(SET A) {
    printf("Bit Pattern: ");
    for(int i = 7; i >= 0; i--) {
        printf("%d", hasPrivilege(A, i) ? 1 : 0);
        if(i == 4) printf(" ");  // Visual separator
    }
    printf("\n");
}

// --- Main Function (Test Cases) ---
int main() {
    SET kenji, yuki;
    
    printf("========================================\n");
    printf("THE BINARY BYTE IZAKAYA - ACCESS CONTROL\n");
    printf("========================================\n\n");
    
    // Initialize
    initSet(&kenji);
    initSet(&yuki);
    
    printf("--- Test Case 1: Setting Up Access Codes ---\n");
    // Kenji's privileges: 0, 2, 4, 6 (Free appetizers, Private booth, Chef's menu, Bring guests)
    insertPrivilege(&kenji, 0);
    insertPrivilege(&kenji, 2);
    insertPrivilege(&kenji, 4);
    insertPrivilege(&kenji, 6);
    
    // Yuki's privileges: 1, 2, 5, 7 (Premium sake, Private booth, Late-night, VIP lounge)
    insertPrivilege(&yuki, 1);
    insertPrivilege(&yuki, 2);
    insertPrivilege(&yuki, 5);
    insertPrivilege(&yuki, 7);
    
    printf("Kenji's Access Code:\n");
    displaySet(kenji, "  Privileges");
    displayBitPattern(kenji);
    // Expected Output:
    //   Privileges: { 0, 2, 4, 6 }
    //   Bit Pattern: 0101 0101
    
    printf("\nYuki's Access Code:\n");
    displaySet(yuki, "  Privileges");
    displayBitPattern(yuki);
    // Expected Output:
    //   Privileges: { 1, 2, 5, 7 }
    //   Bit Pattern: 1010 0110
    
    printf("\n--- Test Case 2: Union (Combined Event Pass) ---\n");
    printf("For a joint event, combine both access codes:\n");
    SET combined = unionSet(kenji, yuki);
    displaySet(combined, "  Combined Privileges");
    displayBitPattern(combined);
    // Expected Output:
    //   Combined Privileges: { 0, 1, 2, 4, 5, 6, 7 }
    //   Bit Pattern: 1111 0111
    
    printf("\n--- Test Case 3: Intersection (Shared Privileges) ---\n");
    printf("Privileges both Kenji AND Yuki have:\n");
    SET shared = intersectionSet(kenji, yuki);
    displaySet(shared, "  Shared Privileges");
    displayBitPattern(shared);
    // Expected Output:
    //   Shared Privileges: { 2 }
    //   Bit Pattern: 0000 0100
    
    printf("\n--- Test Case 4: Difference (Kenji's Exclusive) ---\n");
    printf("Privileges only Kenji has (not Yuki):\n");
    SET kenjiOnly = differenceSet(kenji, yuki);
    displaySet(kenjiOnly, "  Kenji-Exclusive");
    displayBitPattern(kenjiOnly);
    // Expected Output:
    //   Kenji-Exclusive: { 0, 4, 6 }
    //   Bit Pattern: 0101 0001
    
    printf("\n--- Test Case 5: Complement (Forbidden Privileges) ---\n");
    printf("Privileges Kenji does NOT have:\n");
    SET kenjiForbidden = complementSet(kenji);
    displaySet(kenjiForbidden, "  Forbidden");
    displayBitPattern(kenjiForbidden);
    // Expected Output:
    //   Forbidden: { 1, 3, 5, 7 }
    //   Bit Pattern: 1010 1010
    
    printf("\n--- Test Case 6: Subset Check ---\n");
    SET basicPass;
    initSet(&basicPass);
    insertPrivilege(&basicPass, 0);
    insertPrivilege(&basicPass, 2);
    
    printf("Basic Pass (privileges 0, 2):\n");
    displaySet(basicPass, "  ");
    printf("Is Basic Pass a subset of Kenji's privileges? ");
    if(isSubset(kenji, basicPass)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // Is Basic Pass a subset of Kenji's privileges? YES
    
    printf("\nIs Yuki's pass a subset of Kenji's privileges? ");
    if(isSubset(kenji, yuki)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // Is Yuki's pass a subset of Kenji's privileges? NO
    
    printf("\n========================================\n");
    printf("TESTS COMPLETE\n");
    printf("========================================\n");
    
    return 0;
}

/*
========================================
IMPLEMENTATION HINTS:
========================================

HINT 1 - Bitwise Operations Refresher:
   - OR (|):  Combines bits (1 if either is 1)
   - AND (&): Intersection (1 if both are 1)
   - XOR (^): Exclusive or (1 if different)
   - NOT (~): Flips all bits
   - Left shift (<<): Multiplies by 2^n
   - Right shift (>>): Divides by 2^n

HINT 2 - Union Operation:
   Think: "Give me a 1 if EITHER Kenji OR Yuki has that bit set"
   Which bitwise operator does that?
   Answer: A | B

HINT 3 - Intersection Operation:
   Think: "Give me a 1 if BOTH Kenji AND Yuki have that bit set"
   Which bitwise operator does that?
   Answer: A & B

HINT 4 - Difference Operation (A - B):
   Think: "Give me bits that are in A but NOT in B"
   Step 1: Flip B using NOT (~B)
   Step 2: AND that with A
   Answer: A & ~B

HINT 5 - Complement Operation:
   Think: "Flip all bits in the set"
   Answer: ~A
   
   CAUTION: Be aware that ~A flips ALL bits, including those beyond bit 7!
   If you're using unsigned char (8 bits), this is fine.
   If using larger types, you might need to mask: ~A & 0xFF

HINT 6 - Subset Check (Is B ⊆ A?):
   Think: "For B to be a subset of A, every bit in B must also be in A"
   Method 1: (A & B) == B
   Method 2: (A | B) == A
   
   Why does Method 1 work?
   - If we AND A with B, we keep only bits that are in BOTH
   - If that result equals B, it means all of B's bits were in A
   
   Example:
   A = 01010101 (Kenji)
   B = 00000101 (BasicPass: bits 0,2)
   A & B = 00000101 == B ✓ (subset confirmed)

========================================
RUBRIC (25 points):
========================================
- unionSet: 5 points (correct OR operation)
- intersectionSet: 5 points (correct AND operation)
- differenceSet: 5 points (correct AND-NOT operation)
- complementSet: 3 points (correct NOT operation)
- isSubset: 7 points (correct subset logic)

Deductions:
- Using wrong bitwise operator: -3 per function
- Missing return statement: -2 per function
- Incorrect bit masking in complement: -2
- Incorrect output: -2 per test case
========================================
*/
