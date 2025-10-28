/*
Story Problem: The Chrono-Cipher Archives
In the dystopian future of Neo-Veridia, the oppressive Chronos Corporation controls all information. You are a rogue archivist, "Cipher," working for the underground resistance. Your mission is to manage fragmented data streams from various rebel cells, each stream representing a "thought-set" of encrypted keywords.

Each thought-set is a collection of up to 32 unique keywords, represented by a single 32-bit unsigned integer. A '1' at a specific bit position means the keyword corresponding to that position is present in the thought-set, and a '0' means it's absent.

The Chronos Corporation's surveillance systems are constantly trying to intercept and combine these thought-sets. Your task is to develop a secure, efficient system to manage these sets, allowing the resistance to:

initializeThoughtSet: Create an empty thought-set.
addKeyword: Add a keyword to a thought-set.
removeKeyword: Remove a keyword from a thought-set.
isKeywordPresent: Check if a specific keyword is in a thought-set.
countKeywords: Count how many keywords are in a thought-set.
unionSets: Combine two thought-sets (keywords present in either).
intersectionSets: Find common keywords between two thought-sets (keywords present in both).
differenceSets: Find keywords present in one set but not the other.
isSubset: Check if one thought-set is a subset of another.
The resistance has intercepted a critical message:

Cell Alpha's thought-set: Keywords at positions 0, 2, 5, 10, 15, 20, 31.
Cell Beta's thought-set: Keywords at positions 2, 5, 8, 15, 25, 31.
You need to demonstrate your system by:

Initializing and populating these two thought-sets.
Finding the union of Alpha and Beta.
Finding the intersection of Alpha and Beta.
Finding the keywords unique to Alpha (Alpha - Beta).
Checking if Beta is a subset of Alpha.
Counting the keywords in each resulting set.
Your system must be robust and handle edge cases, such as empty sets, adding/removing non-existent keywords, and full sets.

*/

#include <stdio.h>
#include <stdlib.h>

// Represents a set of keywords using a 32-bit unsigned integer
typedef struct {
    unsigned int keywords;
} ThoughtSet;

// Function prototypes for managing ThoughtSets

/**
 * @brief Initializes a ThoughtSet to an empty state (no keywords).
 * @param set A pointer to the ThoughtSet to initialize.
 */
void initializeThoughtSet(ThoughtSet* set) {
    set->keywords = 0;
}

/**
 * @brief Adds a keyword to the ThoughtSet at the specified bit position.
 *        Positions range from 0 to 31.
 * @param set A pointer to the ThoughtSet.
 * @param position The bit position (0-31) of the keyword to add.
 */
void addKeyword(ThoughtSet* set, int position) {
    // TODO: Implement adding a keyword

    set->keywords = set->keywords | 1U << position;
}

/**
 * @brief Removes a keyword from the ThoughtSet at the specified bit position.
 *        Positions range from 0 to 31.
 * @param set A pointer to the ThoughtSet.
 * @param position The bit position (0-31) of the keyword to remove.
 */
void removeKeyword(ThoughtSet* set, int position) {
    // TODO: Implement removing a keyword
    set->keywords = set->keywords & ~(1U << position);
}

/**
 * @brief Checks if a keyword is present in the ThoughtSet at the specified bit position.
 * @param set A pointer to the ThoughtSet.
 * @param position The bit position (0-31) of the keyword to check.
 * @return 1 if the keyword is present, 0 otherwise.
 */
int isKeywordPresent(ThoughtSet* set, int position) {
    // TODO: Implement checking for keyword presence
    return (set->keywords & (1U << position)) > 0 ? 1 : 0;
}

/**
 * @brief Counts the number of keywords currently in the ThoughtSet.
 * @param set A pointer to the ThoughtSet.
 * @return The total number of keywords (set bits).
 */
int countKeywords(ThoughtSet* set) {
    int count = 0;
    unsigned int mask = 1u << (8 * sizeof(set->keywords) - 1);
    //  unsigned int w = set->keywords;

    while (mask > 0)
    {
        if ((set->keywords
 & mask) > 0u) count++;
        mask >>= 1;
    }

    return count;
}

/**
 * @brief Computes the union of two ThoughtSets (keywords present in either set).
 * @param setA A pointer to the first ThoughtSet.
 * @param setB A pointer to the second ThoughtSet.
 * @return A new ThoughtSet representing the union.
 */
ThoughtSet unionSets(ThoughtSet* setA, ThoughtSet* setB) {
    ThoughtSet result;
    result.keywords = setA->keywords | setB ->keywords;
    return result; // Placeholder
}

/**
 * @brief Computes the intersection of two ThoughtSets (keywords present in both sets).
 * @param setA A pointer to the first ThoughtSet.
 * @param setB A pointer to the second ThoughtSet.
 * @return A new ThoughtSet representing the intersection.
 */
ThoughtSet intersectionSets(ThoughtSet* setA, ThoughtSet* setB) {
    ThoughtSet result;
    result.keywords = setA->keywords & setB ->keywords;
    return result; // Placeholder
}

/**
 * @brief Computes the difference of two ThoughtSets (keywords present in setA but not in setB).
 * @param setA A pointer to the first ThoughtSet.
 * @param setB A pointer to the second ThoughtSet.
 * @return A new ThoughtSet representing the difference (A - B).
 */
ThoughtSet differenceSets(ThoughtSet* setA, ThoughtSet* setB) {
    ThoughtSet result;
    result.keywords = setA->keywords & ~(setB ->keywords);
    return result; // Placeholder
}

/**
 * @brief Checks if setA is a subset of setB.
 * @param setA A pointer to the potential subset.
 * @param setB A pointer to the potential superset.
 * @return 1 if setA is a subset of setB, 0 otherwise.
 */
int isSubset(ThoughtSet* setA, ThoughtSet* setB) {


    unsigned int mask = 1u << (8 * sizeof(setA->keywords) - 1);
 
    
    int result = 1;

    while (mask > 0 && result)
    {
        if ((setA->keywords & mask) > 0)
        {
            result = (setB->keywords & mask) > 0 ? 1 : 0;  
        } 

        mask >>= 1;
    }

    return result;
}


// int isSubset(ThoughtSet* setA, ThoughtSet* setB) {


//     return (setA->keywords & ~(setB->keywords)) > 0 ? 0 : 1;
// }

/**
 * @brief Displays the keywords in a ThoughtSet in binary format (for debugging).
 * @param set A pointer to the ThoughtSet to display.
 * @param name The name of the set for display purposes.
 */
void displayThoughtSet(ThoughtSet* set, const char* name) {
    printf("%s: ", name);
    for (int i = 31; i >= 0; i--) {
        printf("%d", isKeywordPresent(set, i));
        if (i % 8 == 0 && i != 0) printf(" "); // Group by 8 bits for readability
    }
    printf(" (Total: %d keywords)\n", countKeywords(set));
}


int main() {
    printf("--- Chrono-Cipher Archives: Resistance Data Management ---\n\n");

    ThoughtSet cellAlpha, cellBeta;
    initializeThoughtSet(&cellAlpha);
    initializeThoughtSet(&cellBeta);

    printf("Initializing Cell Alpha and Cell Beta Thought-Sets...\n");

    // Populate Cell Alpha: Keywords at positions 0, 2, 5, 10, 15, 20, 31
    addKeyword(&cellAlpha, 0);
    addKeyword(&cellAlpha, 2);
    addKeyword(&cellAlpha, 5);
    addKeyword(&cellAlpha, 10);
    addKeyword(&cellAlpha, 15);
    addKeyword(&cellAlpha, 20);
    addKeyword(&cellAlpha, 31);
    // Expected output for Cell Alpha (bits set at 31,20,15,10,5,2,0):
    // Cell Alpha: 10000000 00010000 10000100 00100101 (Total: 7 keywords)
    displayThoughtSet(&cellAlpha, "Cell Alpha");

    // Populate Cell Beta: Keywords at positions 2, 5, 8, 15, 25, 31
    addKeyword(&cellBeta, 2);
    addKeyword(&cellBeta, 5);
    addKeyword(&cellBeta, 8);
    addKeyword(&cellBeta, 15);
    addKeyword(&cellBeta, 25);
    addKeyword(&cellBeta, 31);
    // Expected output for Cell Beta (bits set at 31,25,15,8,5,2):
    // Cell Beta : 10000010 00000000 10000001 00100100 (Total: 6 keywords)
    displayThoughtSet(&cellBeta, "Cell Beta");

    printf("\n--- Performing Set Operations ---\n");

    // Union of Alpha and Beta
    ThoughtSet unionAB = unionSets(&cellAlpha, &cellBeta);
    // Expected union (bits 31,25,20,15,10,8,5,2,0):
    // Union (Alpha | Beta): 10000010 00010000 10000101 00100101 (Total: 9 keywords)
    displayThoughtSet(&unionAB, "Union (Alpha | Beta)");

    // Intersection of Alpha and Beta
    ThoughtSet intersectionAB = intersectionSets(&cellAlpha, &cellBeta);
    // Expected intersection (common bits 31,15,5,2):
    // Intersection (Alpha & Beta): 10000000 00000000 10000000 00100100 (Total: 4 keywords)
    displayThoughtSet(&intersectionAB, "Intersection (Alpha & Beta)");

    // Difference (Alpha - Beta)
    ThoughtSet differenceAB = differenceSets(&cellAlpha, &cellBeta);
    // Expected difference (Alpha - Beta) (bits in Alpha not in Beta: 20,10,0):
    // Difference (Alpha - Beta): 00000000 00010000 00000100 00000001 (Total: 3 keywords)
    displayThoughtSet(&differenceAB, "Difference (Alpha - Beta)");

    // Check if Beta is a subset of Alpha.
    // Expected: NO (Beta has bits 25 and 8 that Alpha does not)
    printf("Is Cell Beta a subset of Cell Alpha? %s\n", isSubset(&cellBeta, &cellAlpha) ? "YES" : "NO");

    
        cellBeta.keywords &= cellAlpha.keywords; // now Beta only contains bits also in Alpha
    printf("Removed 25. Is Cell Beta a subset of Cell Alpha? %s\n", isSubset(&cellBeta, &cellAlpha) ? "YES" : "NO");

    // Additional tests (edge cases, etc.)
    printf("\n--- Additional Tests ---\n");

    // Test removing a non-existent keyword
    removeKeyword(&cellAlpha, 1);
    // Removing bit 1 (not set) should leave Alpha unchanged
    // Alpha (after removing non-existent 1): 10000000 00010000 10000100 00100101 (Total: 7 keywords)
    displayThoughtSet(&cellAlpha, "Alpha (after removing non-existent 1)");

    // Test adding an existing keyword (should not change count)
    addKeyword(&cellAlpha, 0);
    // Adding an already-set bit (0) should not change Alpha
    // Alpha (after adding existing 0): 10000000 00010000 10000100 00100101 (Total: 7 keywords)
    displayThoughtSet(&cellAlpha, "Alpha (after adding existing 0)");

    // Test empty set operations
    ThoughtSet emptySet;
    initializeThoughtSet(&emptySet);
    // Empty set expected output:
    // Empty Set: 00000000 00000000 00000000 00000000 (Total: 0 keywords)
    displayThoughtSet(&emptySet, "Empty Set");

    ThoughtSet unionEmptyAlpha = unionSets(&emptySet, &cellAlpha);
    // Union with empty should equal Alpha
    // Union (Empty | Alpha): 10000000 00010000 10000100 00100101 (Total: 7 keywords)
    displayThoughtSet(&unionEmptyAlpha, "Union (Empty | Alpha)");
    // addKeyword(&emptySet, 2);

    ThoughtSet intersectionEmptyAlpha = intersectionSets(&emptySet, &cellAlpha);

    // Intersection with empty should be empty
    // Intersection (Empty & Alpha): 00000000 00000000 00000000 00000000 (Total: 0 keywords)
    displayThoughtSet(&intersectionEmptyAlpha, "Intersection (Empty & Alpha)");

    printf("\n--- Chrono-Cipher Archives: Operations Complete ---\n");

    return 0;
}