// Started Sept. 30, 2025
// Completed Sept. 30, 2025

#include <stdio.h>
#include <stdlib.h>


// The Word of Power - represents the magic parchment
typedef struct {
    // TODO: Add your data member(s) here
    unsigned int runeWord;

} WordOfPower;

/**
 * Initialize the Word of Power to its pure empty state
 */
void initializeParchment(WordOfPower* parchment) {
    // TODO: Implement initialization

    parchment->runeWord = 0;
    
}

/**
 * Add a rune mark at the specified position (make it glow)
 * Position range: 0-31
 */
void addRuneMark(WordOfPower* parchment, int position) {
    // TODO: Implement rune marking
    parchment->runeWord = parchment->runeWord | 1 << position;
}

/**
 * Remove a rune mark at the specified position (make it dim)
 * Position range: 0-31  
 */
void removeRuneMark(WordOfPower* parchment, int position) {
    // TODO: Implement rune removal
    parchment->runeWord = parchment->runeWord & ~(1 << position);
}

/**
 * Check if a rune at the given position is glowing
 * Returns: 1 if glowing, 0 if dim
 */
int isRuneGlowing(WordOfPower* parchment, int position) {
    // TODO: Implement rune status check
    return (parchment->runeWord & 1 << position) > 0 ? 1 : 0;
}

/**
 * Count how many runes are currently glowing
 * Returns: number of glowing runes (0-32)
 */
int countGlowingRunes(WordOfPower* parchment) {
    // TODO: Implement counting logic
    int i, glowingRuneCount = 0;

    for (i = 31; i >= 0; i--){

        if ((parchment->runeWord & 1 << i) > 0){
            glowingRuneCount++;
        }

    }

    return glowingRuneCount;
}

/**
 * Reset the parchment to its pure empty state (all runes dim)
 */
void resetParchment(WordOfPower* parchment) {
    // TODO: Implement reset
    parchment->runeWord = 0;

}

/**
 * Display the current state of the parchment (for debugging)
 * Shows positions 31 down to 0
 */
void displayParchment(WordOfPower* parchment) {
    printf("Word of Power state (31->0): ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", isRuneGlowing(parchment, i));
        if (i % 4 == 0 && i != 0) printf(" "); // group by 4 for readability
    }
    printf(" (%d glowing)\n", countGlowingRunes(parchment));
}
void runEdgeCaseTests() {
    WordOfPower parchment;
    int passed = 0, total = 0;
    
    printf("=== COMPREHENSIVE EDGE CASE TESTING ===\n");
    
    // Test 1: Empty parchment operations
    printf("\n--- Test 1: Empty Parchment Operations ---\n");
    initializeParchment(&parchment);
    total++; 
    if (countGlowingRunes(&parchment) == 0) {
        printf("Empty parchment count: PASS\n");
        passed++;
    } else {
        printf("Empty parchment count: FAIL (expected 0, got %d)\n", countGlowingRunes(&parchment));
    }
    
    // Test removing from empty parchment
    removeRuneMark(&parchment, 15);
    total++;
    if (countGlowingRunes(&parchment) == 0) {
        printf("Remove from empty: PASS\n");
        passed++;
    } else {
        printf("Remove from empty: FAIL\n");
    }
    
    // Test 2: Boundary positions (0 and 31)
    printf("\n--- Test 2: Boundary Position Tests ---\n");
    initializeParchment(&parchment);
    
    // Test position 0
    addRuneMark(&parchment, 0);
    printf("   After adding position 0:\n   ");
    displayParchment(&parchment);
    total++;
    if (isRuneGlowing(&parchment, 0) == 1 && countGlowingRunes(&parchment) == 1) {
        printf("Position 0 set: PASS\n");
        passed++;
    } else {
        printf("Position 0 set: FAIL\n");
    }
    
    // Test position 31
    addRuneMark(&parchment, 31);
    printf("   After adding position 31:\n   ");
    displayParchment(&parchment);
    printf("   Expected: 10000000 00000000 10000000 00000001 (2 glowing)\n");
    total++;
    if (isRuneGlowing(&parchment, 31) == 1 && countGlowingRunes(&parchment) == 2) {
        printf("Position 31 set: PASS\n");
        passed++;
    } else {
        printf("Position 31 set: FAIL\n");
    }
    
    // Test 3: All positions set
    printf("\n--- Test 3: All Positions Set ---\n");
    initializeParchment(&parchment);
    for (int i = 0; i < 32; i++) {
        addRuneMark(&parchment, i);
    }
    printf("   After setting all positions:\n   ");
    displayParchment(&parchment);
    printf("   Expected: 11111111 11111111 11111111 11111111 (32 glowing)\n");
    total++;
    if (countGlowingRunes(&parchment) == 32) {
        printf("All 32 positions set: PASS (count = %d)\n", countGlowingRunes(&parchment));
        passed++;
    } else {
        printf("All 32 positions set: FAIL (expected 32, got %d)\n", countGlowingRunes(&parchment));
    }
    
    // Test 4: Duplicate operations
    printf("\n--- Test 4: Duplicate Operations ---\n");
    initializeParchment(&parchment);
    addRuneMark(&parchment, 10);
    addRuneMark(&parchment, 10);  // Duplicate add
    addRuneMark(&parchment, 10);  // Another duplicate
    total++;
    if (countGlowingRunes(&parchment) == 1) {
        printf("Duplicate add operations: PASS\n");
        passed++;
    } else {
        printf("Duplicate add operations: FAIL\n");
    }
    
    removeRuneMark(&parchment, 10);
    removeRuneMark(&parchment, 10);  // Duplicate remove
    total++;
    if (countGlowingRunes(&parchment) == 0) {
        printf("Duplicate remove operations: PASS\n");
        passed++;
    } else {
        printf("Duplicate remove operations: FAIL\n");
    }
    
    // Test 5: Alternating patterns
    printf("\n--- Test 5: Alternating Patterns ---\n");
    initializeParchment(&parchment);
    // Set every even position
    for (int i = 0; i < 32; i += 2) {
        addRuneMark(&parchment, i);
    }
    printf("   After setting even positions (0,2,4,6...):\n   ");
    displayParchment(&parchment);
    printf("   Expected: 01010101 01010101 01010101 01010101 (16 glowing)\n");
    total++;
    if (countGlowingRunes(&parchment) == 16) {
        printf("Even positions pattern: PASS\n");  
        passed++;
    } else {
        printf("Even positions pattern: FAIL (expected 16, got %d)\n", countGlowingRunes(&parchment));
    }
    
    // Test 6: Reset after full population
    printf("\n--- Test 6: Reset Operations ---\n");
    // Parchment should still have even positions set
    resetParchment(&parchment);
    printf("   After reset:\n   ");
    displayParchment(&parchment);
    printf("   Expected: 00000000 00000000 00000000 00000000 (0 glowing)\n");
    total++;
    if (countGlowingRunes(&parchment) == 0) {
        printf("Reset after pattern: PASS\n");
        passed++;
    } else {
        printf("Reset after pattern: FAIL\n");
    }
    
    // Test 7: Single bit operations
    printf("\n--- Test 7: Single Bit Precision ---\n");
    initializeParchment(&parchment);
    addRuneMark(&parchment, 15);
    printf("   After adding only position 15:\n   ");
    displayParchment(&parchment);
    printf("   Expected: 00000000 00000001 00000000 00000000 (1 glowing)\n");
    total++;
    if (isRuneGlowing(&parchment, 15) == 1 && 
        isRuneGlowing(&parchment, 14) == 0 && 
        isRuneGlowing(&parchment, 16) == 0) {
        printf("Single bit precision: PASS\n");
        passed++;
    } else {
        printf("Single bit precision: FAIL\n");
    }
    
    // Test 8: Powers of 2 pattern
    printf("\n--- Test 8: Powers of 2 Pattern ---\n");
    initializeParchment(&parchment);
    // Set positions: 0, 1, 2, 4, 8, 16 (powers of 2 up to 16)
    int powerPositions[] = {0, 1, 2, 4, 8, 16};
    int powerCount = 6;
    for (int i = 0; i < powerCount; i++) {
        addRuneMark(&parchment, powerPositions[i]);
    }
    printf("   After setting positions 0,1,2,4,8,16:\n   ");
    displayParchment(&parchment);
    printf("   Expected: 00000000 00000001 00000000 00010111 (6 glowing)\n");
    total++;
    if (countGlowingRunes(&parchment) == powerCount) {
        printf("Powers of 2 pattern: PASS\n");
        passed++;
    } else {
        printf("Powers of 2 pattern: FAIL (expected %d, got %d)\n", powerCount, countGlowingRunes(&parchment));
    }
    
    // Test 9: Sequential add/remove
    printf("\n--- Test 9: Sequential Add/Remove ---\n");
    initializeParchment(&parchment);
    // Add all, then remove all
    for (int i = 0; i < 32; i++) {
        addRuneMark(&parchment, i);
    }
    for (int i = 0; i < 32; i++) {
        removeRuneMark(&parchment, i);
    }
    total++;
    if (countGlowingRunes(&parchment) == 0) {
        printf("Sequential add/remove all: PASS\n");
        passed++;
    } else {
        printf("Sequential add/remove all: FAIL\n");
    }
    
    // Test 10: Interleaved operations
    printf("\n--- Test 10: Interleaved Operations ---\n");
    initializeParchment(&parchment);
    // Add odd positions, remove even positions (should be no-op for evens)
    for (int i = 0; i < 32; i++) {
        if (i % 2 == 1) {
            addRuneMark(&parchment, i);
        } else {
            removeRuneMark(&parchment, i);  // Remove from empty
        }
    }
    printf("   After adding odd positions (remove even from empty):\n   ");
    displayParchment(&parchment);
    printf("   Expected: 10101010 10101010 10101010 10101010 (16 glowing)\n");
    total++;
    if (countGlowingRunes(&parchment) == 16) {
        printf("Interleaved operations: PASS\n");
        passed++;
    } else {
        printf("Interleaved operations: FAIL (expected 16, got %d)\n", countGlowingRunes(&parchment));
    }
    
    // Test 11: Specific bit patterns
    printf("\n--- Test 11: Specific Bit Patterns ---\n");
    initializeParchment(&parchment);
    // Create pattern: 10101010... (alternating)
    for (int i = 0; i < 32; i += 2) {
        addRuneMark(&parchment, i);
    }
    // Verify specific positions
    total++;
    if (isRuneGlowing(&parchment, 0) == 1 && 
        isRuneGlowing(&parchment, 1) == 0 &&
        isRuneGlowing(&parchment, 2) == 1 &&
        isRuneGlowing(&parchment, 3) == 0) {
        printf("Alternating bit pattern: PASS\n");
        passed++;
    } else {
        printf("Alternating bit pattern: FAIL\n");
    }
    
    // Test 12: Edge case - position boundaries
    printf("\n--- Test 12: Position Boundary Validation ---\n");
    initializeParchment(&parchment);
    addRuneMark(&parchment, 0);   // Minimum valid position
    addRuneMark(&parchment, 31);  // Maximum valid position
    total++;
    if (countGlowingRunes(&parchment) == 2) {
        printf("Boundary positions (0, 31): PASS\n");
        passed++;
    } else {
        printf("Boundary positions (0, 31): FAIL\n");
    }
    
    // Final Results
    printf("\n=== TEST RESULTS ===\n");
    printf("Passed: %d/%d tests\n", passed, total);
    printf("Success Rate: %.1f%%\n", (passed * 100.0) / total);
    
    if (passed == total) {
        printf("🎉 ALL TESTS PASSED! Your Bitlandia implementation is solid!\n");
    } else {
        printf("⚠️  Some tests failed. Review the failing operations.\n");
    }
}

int main() {
    printf("=== Bitlandia Edge Case Test Suite ===\n");

    runEdgeCaseTests();
    

    return 0;
}

