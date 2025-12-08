/*
========================================
PROBLEM 5: The Cryptographer's Bit Vault Challenge
Difficulty: ★★★★★ (Hard)
Topic: Computer Word Set Operations (Advanced Bitwise Manipulation)
========================================

Story:

In the underground labs of Neo-Kyoto's Cipher Division, Dr. Kurisu Makise has developed 
a quantum-resistant encryption system called "BitVault-256". The system uses multiple 
8-bit registers to encode secret agent permissions across different security domains.

Agent codenames are represented as bit positions (0-7), and four security clearance 
registers track different operational zones:

Register ALPHA: Cyber-warfare operations (positions 0-7)
Register BRAVO: Intelligence gathering (positions 0-7)
Register CHARLIE: Covert infiltration (positions 0-7)
Register DELTA: Emergency protocols (positions 0-7)

A critical security audit requires analyzing agent overlap, exclusivity, and cascading 
permissions across these registers. The system must handle:

1. Multi-register intersections (agents cleared for ALL zones)
2. Symmetric differences (agents in EITHER A or B, but NOT both)
3. Cascading unions with complement checks
4. Complex subset chain verification

Your Mission:
Implement advanced Computer Word operations that Dr. Makise needs for her audit.

========================================
Data Structures Provided:
========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char REGISTER;

// --- Function Prototypes ---
void initRegister(REGISTER *R);
void grantAccess(REGISTER *R, int agentID);
void revokeAccess(REGISTER *R, int agentID);
int hasAccess(REGISTER R, int agentID);
void displayRegister(REGISTER R, const char* name);
void displayBitPattern(REGISTER R);
int countAgents(REGISTER R);

// TODO: Implement these functions


/*
Register ALPHA: Cyber-warfare operations (positions 0-7)
Register BRAVO: Intelligence gathering (positions 0-7)
Register CHARLIE: Covert infiltration (positions 0-7)
Register DELTA: Emergency protocols (positions 0-7)

A critical security audit requires analyzing agent overlap, exclusivity, and cascading 
permissions across these registers. The system must handle:

1. Multi-register intersections (agents cleared for ALL zones)
2. Symmetric differences (agents in EITHER A or B, but NOT both)
3. Cascading unions with complement checks
4. Complex subset chain verification
*/

// Agents in ALL registers
/*
HINT 1 - IntersectAll (Multi-Register AND):
   Problem: Find agents in ALL registers in an array
   
   Naive approach:
   result = registers[0]
   for i = 1 to count-1:
       result = result & registers[i]
   
   Optimized approach:
   result = 0xFF  // Start with all bits set
   for i = 0 to count-1:
       result &= registers[i]
   
   Why start with 0xFF? 
   Because 0xFF & anything = anything
   This handles variable array sizes elegantly!
*/
REGISTER intersectAll(REGISTER *registers, int count){

           
    REGISTER intersectRegister = registers[0];
    for (int i = 1; i < count; i++){
        intersectRegister = intersectRegister & registers[i];
    }

    return intersectRegister;
}

/*
HINT 2 - Symmetric Difference (XOR):
   Problem: Elements in A OR B, but NOT both
   
   Mathematical definition: (A ∪ B) - (A ∩ B)
   
   But there's a MUCH simpler bitwise solution!
   
   XOR operator (^) does EXACTLY this:
   - Returns 1 if bits differ
   - Returns 0 if bits match
   
   So: A ^ B gives you symmetric difference directly!
   
   Example:
   A = 01010101
   B = 01001110
   A ^ B = 00011011  ← Elements in one but not both

*/
REGISTER symmetricDifference(REGISTER A, REGISTER B){
    return A ^ B;
    
}

// Agents in ANY register
REGISTER unionAll(REGISTER *registers, int count){

            
    REGISTER unionRegister = registers[0];
    for (int i = 1; i < count; i++){
        unionRegister = unionRegister | registers[i];
    }

    return unionRegister;
}

// Agents NOT in R
REGISTER complement(REGISTER R){
    return ~R;
}         

// Is B ⊆ A?
int isSubset(REGISTER A, REGISTER B){

    REGISTER intersection = A & B;

    return (intersection == B) ? 1 : 0;

}

// No common agents?
int areDisjoint(REGISTER A, REGISTER B){

    return ((A & B) == 0) ? 1 : 0;

}                

/*

HINT 6 - Relative Supplement (U - A):
   "Elements in U but not in A"
   
   This is just set difference: U & ~A
   
   Example:
   U = 11011111 (Master list)
   A = 01010101 (Alpha)
   ~A = 10101010
   U & ~A = 10001010 (Elements in U but not A)
*/


 // U - A (within universal set U)

REGISTER relativeSupplement(REGISTER U, REGISTER A){

    return U & ~A;
}   

// --- Helper Functions (Already Implemented) ---
void initRegister(REGISTER *R) {
    *R = 0;
}

void grantAccess(REGISTER *R, int agentID) {
    if(agentID >= 0 && agentID < 8) {
        *R |= (1 << agentID);
    }
}

void revokeAccess(REGISTER *R, int agentID) {
    if(agentID >= 0 && agentID < 8) {
        *R &= ~(1 << agentID);
    }
}

int hasAccess(REGISTER R, int agentID) {
    return (R & (1 << agentID)) != 0;
}

void displayRegister(REGISTER R, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < 8; i++) {
        if(hasAccess(R, i)) {
            if(!first) printf(", ");
            printf("Agent%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

void displayBitPattern(REGISTER R) {
    printf("  Binary: ");
    for(int i = 7; i >= 0; i--) {
        printf("%d", hasAccess(R, i) ? 1 : 0);
        if(i == 4) printf(" ");
    }
    printf(" (Decimal: %d)\n", R);
}

int countAgents(REGISTER R) {
    int count = 0;
    for(int i = 0; i < 8; i++) {
        if(hasAccess(R, i)) count++;
    }
    return count;
}

const char* agentNames[8] = {
    "Falcon", "Shadow", "Viper", "Ghost", 
    "Raven", "Phoenix", "Cipher", "Spectre"
};

void displayAgentNames(REGISTER R) {
    printf("  Agents: ");
    int count = 0;
    for(int i = 0; i < 8; i++) {
        if(hasAccess(R, i)) {
            if(count > 0) printf(", ");
            printf("%s", agentNames[i]);
            count++;
        }
    }
    if(count == 0) printf("(none)");
    printf("\n");
}

// --- Main Function (Test Cases) ---
int main() {
    REGISTER alpha, bravo, charlie, delta;
    
    printf("========================================\n");
    printf("BITVAULT-256 SECURITY AUDIT - NEO-KYOTO CIPHER DIVISION\n");
    printf("========================================\n\n");
    
    initRegister(&alpha);
    initRegister(&bravo);
    initRegister(&charlie);
    initRegister(&delta);
    
    printf("--- Test Case 1: Security Register Setup ---\n");
    
    // ALPHA (Cyber-warfare): Agents 0, 2, 4, 6
    grantAccess(&alpha, 0);
    grantAccess(&alpha, 2);
    grantAccess(&alpha, 4);
    grantAccess(&alpha, 6);
    
    // BRAVO (Intelligence): Agents 1, 2, 3, 6
    grantAccess(&bravo, 1);
    grantAccess(&bravo, 2);
    grantAccess(&bravo, 3);
    grantAccess(&bravo, 6);
    
    // CHARLIE (Infiltration): Agents 2, 4, 6, 7
    grantAccess(&charlie, 2);
    grantAccess(&charlie, 4);
    grantAccess(&charlie, 6);
    grantAccess(&charlie, 7);
    
    // DELTA (Emergency): Agents 2, 6
    grantAccess(&delta, 2);
    grantAccess(&delta, 6);
    
    printf("ALPHA Register (Cyber-warfare):\n");
    displayRegister(alpha, "  ");
    displayBitPattern(alpha);
    displayAgentNames(alpha);
    // Expected Output:
    //   : { Agent0, Agent2, Agent4, Agent6 }
    //   Binary: 0101 0101 (Decimal: 85)
    //   Agents: Falcon, Viper, Raven, Cipher
    
    printf("\nBRAVO Register (Intelligence):\n");
    displayRegister(bravo, "  ");
    displayBitPattern(bravo);
    displayAgentNames(bravo);
    // Expected Output:
    //   : { Agent1, Agent2, Agent3, Agent6 }
    //   Binary: 0100 1110 (Decimal: 78)
    //   Agents: Shadow, Viper, Ghost, Cipher
    
    printf("\nCHARLIE Register (Infiltration):\n");
    displayRegister(charlie, "  ");
    displayBitPattern(charlie);
    displayAgentNames(charlie);
    // Expected Output:
    //   : { Agent2, Agent4, Agent6, Agent7 }
    //   Binary: 1101 0100 (Decimal: 212)
    //   Agents: Viper, Raven, Cipher, Spectre
    
    printf("\nDELTA Register (Emergency):\n");
    displayRegister(delta, "  ");
    displayBitPattern(delta);
    displayAgentNames(delta);
    // Expected Output:
    //   : { Agent2, Agent6 }
    //   Binary: 0100 0100 (Decimal: 68)
    //   Agents: Viper, Cipher
    
    printf("\n--- Test Case 2: Universal Clearance (All Zones) ---\n");
    printf("Agents cleared for ALL four zones:\n");
    REGISTER registers[4] = {alpha, bravo, charlie, delta};
    REGISTER universal = intersectAll(registers, 4);
    displayRegister(universal, "  Universal");
    displayAgentNames(universal);
    // Expected Output:
    //   Universal: { Agent2, Agent6 }
    //   Agents: Viper, Cipher
    
    printf("\n--- Test Case 3: Symmetric Difference (Exclusive Access) ---\n");
    printf("Agents in EITHER Alpha OR Bravo, but NOT both:\n");
    REGISTER exclusive = symmetricDifference(alpha, bravo);
    displayRegister(exclusive, "  Exclusive");
    displayBitPattern(exclusive);
    displayAgentNames(exclusive);
    // Expected Output:
    //   Exclusive: { Agent0, Agent1, Agent3, Agent4 }
    //   Binary: 0001 1011 (Decimal: 27)
    //   Agents: Falcon, Shadow, Ghost, Raven
    
    printf("\n--- Test Case 4: Master Access List (Any Zone) ---\n");
    printf("All agents with at least one zone clearance:\n");
    REGISTER masterList = unionAll(registers, 4);
    displayRegister(masterList, "  Master");
    displayBitPattern(masterList);
    displayAgentNames(masterList);
    printf("  Total agents: %d\n", countAgents(masterList));
    // Expected Output:
    //   Master: { Agent0, Agent1, Agent2, Agent3, Agent4, Agent6, Agent7 }
    //   Binary: 1101 1111 (Decimal: 223)
    //   Agents: Falcon, Shadow, Viper, Ghost, Raven, Cipher, Spectre
    //   Total agents: 7
    
    printf("\n--- Test Case 5: Blacklisted Agents (Complement) ---\n");
    printf("Agents NOT in the master list:\n");
    REGISTER blacklist = complement(masterList);
    displayRegister(blacklist, "  Blacklist");
    displayBitPattern(blacklist);
    displayAgentNames(blacklist);
    // Expected Output:
    //   Blacklist: { Agent5 }
    //   Binary: 0010 0000 (Decimal: 32)
    //   Agents: Phoenix
    
    printf("\n--- Test Case 6: Subset Verification ---\n");
    printf("Is DELTA a subset of ALPHA? ");
    printf("%s\n", isSubset(alpha, delta) ? "YES" : "NO");
    printf("Is DELTA a subset of CHARLIE? ");
    printf("%s\n", isSubset(charlie, delta) ? "YES" : "NO");
    // Expected Output:
    // Is DELTA a subset of ALPHA? YES
    // Is DELTA a subset of CHARLIE? YES
    
    printf("\n--- Test Case 7: Disjoint Check ---\n");
    REGISTER newRegister;
    initRegister(&newRegister);
    grantAccess(&newRegister, 1);
    grantAccess(&newRegister, 3);
    grantAccess(&newRegister, 5);
    
    printf("New register: {Agent1, Agent3, Agent5}\n");
    printf("Are ALPHA and new register disjoint? ");
    printf("%s\n", areDisjoint(alpha, newRegister) ? "YES" : "NO");
    // Expected Output:
    // Are ALPHA and new register disjoint? YES
    
    printf("\n--- Test Case 8: Relative Supplement (Advanced) ---\n");
    printf("Agents in Master List but NOT in ALPHA:\n");
    REGISTER supplement = relativeSupplement(masterList, alpha);
    displayRegister(supplement, "  Supplement");
    displayAgentNames(supplement);
    // Expected Output:
    //   Supplement: { Agent1, Agent3, Agent7 }
    //   Agents: Shadow, Ghost, Spectre
    
    printf("\n========================================\n");
    printf("SECURITY AUDIT COMPLETE\n");
    printf("========================================\n");
    
    return 0;
}

/*
========================================
ADVANCED IMPLEMENTATION HINTS:
========================================





HINT 3 - UnionAll (Multi-Register OR):
   Similar to intersectAll, but use OR instead of AND:
   
   result = 0  // Start with empty set
   for i = 0 to count-1:
       result |= registers[i]
   
   Each OR adds new bits to the result.

HINT 4 - Complement (NOT):
   Simple: ~R
   
   BUT WATCH OUT for unsigned char behavior!
   ~R flips ALL 8 bits correctly for unsigned char.
   
   If you were using a larger type (like int), you'd need:
   ~R & 0xFF  // Mask to keep only lower 8 bits
   
   For this problem, unsigned char is perfect.

HINT 5 - Are Disjoint (No Common Elements):
   Sets A and B are disjoint if A ∩ B = ∅
   
   In bit terms: A & B == 0
   
   Implementation:
   return (A & B) == 0;
   
   That's it! One line.


========================================
TRICKY EDGE CASES:
========================================

⚠️ EDGE CASE 1: Empty Array for IntersectAll
   What if count = 0?
   Convention: Return 0 (empty set) or handle error
   
   if(count == 0) return 0;

⚠️ EDGE CASE 2: Single Register for IntersectAll
   What if count = 1?
   Answer: Just return that register
   
   if(count == 1) return registers[0];

⚠️ EDGE CASE 3: Symmetric Difference with Self
   A ^ A = 0 (empty set)
   This is correct! No element is in "one but not both"

⚠️ EDGE CASE 4: Disjoint with Empty Set
   Are A and ∅ disjoint? YES (vacuously true)
   A & 0 == 0 ✓

⚠️ EDGE CASE 5: Complement of Complement
   ~(~A) = A
   But be careful with type sizes! Might need masking.

========================================
BITWISE OPERATOR CHEAT SHEET:
========================================

| Operation          | Operator | Example       | Result |
|--------------------|----------|---------------|--------|
| Union              | \|       | 0101 \| 0011  | 0111   |
| Intersection       | &        | 0101 & 0011   | 0001   |
| Difference A-B     | & ~      | 0101 & ~0011  | 0100   |
| Complement         | ~        | ~0101         | 1010   |
| Symmetric Diff     | ^        | 0101 ^ 0011   | 0110   |
| Subset check B⊆A   | &, ==    | (A & B) == B  | bool   |
| Disjoint check     | &, ==    | (A & B) == 0  | bool   |
| Set bit i          | \|       | A \| (1<<i)   | A+{i}  |
| Clear bit i        | & ~      | A & ~(1<<i)   | A-{i}  |
| Test bit i         | &        | A & (1<<i)    | bool   |
| Toggle bit i       | ^        | A ^ (1<<i)    | flip   |

========================================
PERFORMANCE NOTES:
========================================

Time Complexity (all operations):
- Single register ops: O(1)
- Multi-register ops: O(n) where n = number of registers
- Bit counting: O(8) = O(1) for unsigned char

Space Complexity:
- All operations: O(1) (no dynamic allocation needed!)

Why Computer Word Sets are FAST:
- Bitwise operations are single CPU instructions
- No memory allocation/deallocation
- Cache-friendly (fits in registers)
- Parallel bit processing

========================================
RUBRIC (40 points):
========================================
- intersectAll: 8 points
  * Loop logic (3 pts)
  * Initialization (2 pts)
  * Edge cases (3 pts)

- symmetricDifference: 6 points
  * XOR usage (4 pts)
  * Understanding of concept (2 pts)

- unionAll: 6 points
  * OR accumulation (4 pts)
  * Initialization (2 pts)

- complement: 4 points
  * NOT operator (3 pts)
  * Type awareness (1 pt)

- isSubset: 6 points
  * Correct logic (4 pts)
  * Edge cases (2 pts)

- areDisjoint: 5 points
  * AND check (3 pts)
  * Zero comparison (2 pts)

- relativeSupplement: 5 points
  * Difference logic (3 pts)
  * Correct operand order (2 pts)

Deductions:
- Wrong bitwise operator: -3 per function
- Missing edge case handling: -2
- Type casting errors: -2
- Incorrect test output: -2 per test case
========================================

FINAL NOTE:
This problem tests your DEEP understanding of:
1. Bitwise operations beyond basic AND/OR
2. Set theory translated to bit manipulation
3. Multi-set operations
4. Edge case reasoning
5. Performance optimization via bit tricks

Master this, and you'll handle any bit-based problem thrown at you!
========================================
*/
