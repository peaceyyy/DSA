#include <stdio.h>
#include <stdint.h>

// The Word of Power - represents the magic parchment
typedef struct {
    // TODO: Add your data member(s) here
} WordOfPower;

/**
 * Initialize the Word of Power to its pure empty state
 */
void initializeParchment(WordOfPower* parchment) {
    // TODO: Implement initialization
}

/**
 * Add a rune mark at the specified position (make it glow)
 * Position range: 0-31
 */
void addRuneMark(WordOfPower* parchment, int position) {
    // TODO: Implement rune marking
}

/**
 * Remove a rune mark at the specified position (make it dim)
 * Position range: 0-31  
 */
void removeRuneMark(WordOfPower* parchment, int position) {
    // TODO: Implement rune removal
}

/**
 * Check if a rune at the given position is glowing
 * Returns: 1 if glowing, 0 if dim
 */
int isRuneGlowing(WordOfPower* parchment, int position) {
    // TODO: Implement rune status check
    return 0; // placeholder
}

/**
 * Count how many runes are currently glowing
 * Returns: number of glowing runes (0-32)
 */
int countGlowingRunes(WordOfPower* parchment) {
    // TODO: Implement counting logic
    return 0; // placeholder
}

/**
 * Reset the parchment to its pure empty state (all runes dim)
 */
void resetParchment(WordOfPower* parchment) {
    // TODO: Implement reset
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

int main() {
    WordOfPower parchment;
    
    printf("=== Bitlandia Royal Archive Ritual Simulator ===\n\n");
    
    // Initialize the parchment
    initializeParchment(&parchment);
    printf("1. Initialized parchment:\n");
    displayParchment(&parchment);
    
    // Test adding some rune marks
    printf("\n2. Adding rune marks at positions 0, 7, 15, 31:\n");
    addRuneMark(&parchment, 0);
    addRuneMark(&parchment, 7);  
    addRuneMark(&parchment, 15);
    addRuneMark(&parchment, 31);
    displayParchment(&parchment);
    
    // Test checking specific runes
    printf("\n3. Checking rune status:\n");
    printf("   Position 0: %s\n", isRuneGlowing(&parchment, 0) ? "Glowing" : "Dim");
    printf("   Position 5: %s\n", isRuneGlowing(&parchment, 5) ? "Glowing" : "Dim");
    printf("   Position 15: %s\n", isRuneGlowing(&parchment, 15) ? "Glowing" : "Dim");
    
    // Test removing a rune mark
    printf("\n4. Removing rune mark at position 7:\n");
    removeRuneMark(&parchment, 7);
    displayParchment(&parchment);
    
    // Test adding more marks
    printf("\n5. Adding marks at positions 3, 8, 16:\n");
    addRuneMark(&parchment, 3);
    addRuneMark(&parchment, 8);
    addRuneMark(&parchment, 16);
    displayParchment(&parchment);
    
    // Test count
    printf("\n6. Current glowing runes count: %d\n", countGlowingRunes(&parchment));
    
    // Test reset
    printf("\n7. Resetting parchment to pure state:\n");
    resetParchment(&parchment);
    displayParchment(&parchment);
    
    // Edge case tests
    printf("\n8. Testing edge positions (0 and 31):\n");
    addRuneMark(&parchment, 0);
    addRuneMark(&parchment, 31);
    displayParchment(&parchment);
    
    printf("\n=== Ritual simulation complete! ===\n");
    
    return 0;
}