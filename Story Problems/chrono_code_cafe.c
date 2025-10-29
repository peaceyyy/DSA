/*

 Chrono-Code Cafe: Cipher Key Registry - Temporal Anomaly Management
by Daru 

Background
In the year 2077, the bustling digital metropolis of Neo-Akihabara thrives on information. You, Lab Member, are a data archivist for the renowned "Chrono-Code Cafe," a nexus for time-traveling hackers, retro-gamers, and data enthusiasts. Your critical mission is to manage the cafe's "Cipher Key Registry," a vi tal database of unique alphanumeric keys used to access various temporal archives and digital realms.

Each cipher key is a unique set of uppercase alphanumeric characters (A-Z), represented as a "computer word" for ultra-fast, bitwise processing. This allows for incredibly efficient storage and manipulation of character sets.

However, the cafe's ancient, temperamental server, "The Chronos Engine," has a peculiar and dangerous bug. Whenever a cipher key contains the character 'X' (which, in the Chronos Engine's lexicon, signifies a "temporal anomaly"), the system automatically "quarantines" it.

The Chronos Engine's Quirks (The Twist)
IMPORTANT: Your implementation must adhere to these exact specifications:

Cipher Key Representation: Each key is an unsigned int (ComputerWord). Each uppercase letter 'A' through 'Z' corresponds to a specific bit position (A=0, B=1, ..., Z=25).
Temporal Anomaly ('X'): The character 'X' is specifically mapped to bit position 23.
Quarantine Protocol: A cipher key is considered "quarantined" if and only if the bit corresponding to 'X' (bit 23) is set within its ComputerWord representation.
Quarantined Key Restrictions: Quarantined keys are highly unstable. They cannot be directly modified (i.e., registerKey should not alter the registry if the newKey is quarantined) and cannot be merged with any other key (i.e., mergeKeys must fail if either input key is quarantined).
Your Mission: Implement the Registry Functions

As the Guild's apprentice programmer, you must implement the following core functions for the Chrono-Code Cafe's Cipher Key Registry:

1) ComputerWord registerKey(ComputerWord *registry, ComputerWord newKey)

Purpose: Adds a newKey to the overall registry.
Behavior:
If newKey is quarantined, the registry remains unchanged, and the function returns the current value of *registry.
If newKey is NOT quarantined, it is combined with the *registry using a bitwise OR operation, updating *registry. The function then returns the newly updated *registry.
Return Value: The updated (or unchanged) registry value.


2) bool isQuarantined(ComputerWord key)

Purpose: Checks if a given key contains the 'X' character (is a temporal anomaly).
Behavior: Returns true if the bit corresponding to 'X' (bit 23) is set in key, false otherwise.
Return Value: true if quarantined, false if not.


3) ComputerWord mergeKeys(ComputerWord key1, ComputerWord key2)

Purpose: Attempts to combine two cipher keys into a single new key.
Behavior:
If key1 OR key2 (or both) are quarantined, the merge operation fails. The function returns 0 (an empty ComputerWord) to indicate failure.
If neither key1 nor key2 is quarantined, the keys are merged using a bitwise OR operation, and the resulting ComputerWord is returned.
Return Value: The merged ComputerWord on success, or 0 on failure.
Given Helper Functions

The following functions are already implemented and available for use:

int charToBitPos(char c): Converts an uppercase character to its corresponding bit position (0-25).
ComputerWord createKey(char *chars): Creates a ComputerWord from a string of characters.
void printKey(ComputerWord key): Prints the characters represented by a ComputerWord in a human-readable format (e.g., {A, B, C}).

*/

#include <stdio.h>
#include <stdbool.h>

// Assuming a 32-bit integer for the computer word, supporting 'A'-'Z', 'a'-'z', '0'-'9'
// For simplicity, let's map characters to bit positions.
// '0'-'9' -> 0-9
// 'A'-'Z' -> 10-35
// 'a'-'z' -> 36-61 (We'll need a larger word size or a different mapping for full alphanumeric)
// For this problem, let's simplify to uppercase letters A-Z for a 32-bit int.
// 'A' = 0, 'B' = 1, ..., 'Z' = 25
// 'X' will be at bit position 23.

typedef unsigned int ComputerWord;

// Function Prototypes
ComputerWord createKey(char *chars); // Helper to create a computer word from a string
void printKey(ComputerWord key);     // Helper to print the characters in a computer word

// TODO: Implement these functions
ComputerWord registerKey(ComputerWord *registry, ComputerWord newKey); // Registers a key, marks if quarantined
bool isQuarantined(ComputerWord key);                                 // Checks if a key is quarantined
ComputerWord mergeKeys(ComputerWord key1, ComputerWord key2);         // Merges two keys, fails if either is quarantined

int main() {
    ComputerWord registry = 0; // Our simple registry (can be expanded to an array for multiple keys)

    printf("=== Chrono-Code Cafe: Cipher Key Registry ===\n");

    // Test Case 1: Registering normal keys
    printf("\n--- Test Case 1: Basic Registering ---\n");
    ComputerWord key1 = createKey("ABC");
    ComputerWord key2 = createKey("DEF");
    printf("Registering key1 (ABC): ");
    registry = registerKey(&registry, key1);
    printKey(key1);
    printf(" Quarantined: %s\n", isQuarantined(key1) ? "YES" : "NO");

    printf("Registering key2 (DEF): ");
    registry = registerKey(&registry, key2);
    printKey(key2);
    printf(" Quarantined: %s\n", isQuarantined(key2) ? "YES" : "NO");
    // Expected:
    // Registering key1 (ABC): {A, B, C} Quarantined: NO
    // Registering key2 (DEF): {D, E, F} Quarantined: NO

    // Test Case 2: Registering a Quarantined Key (contains 'X')
    printf("\n--- Test Case 2: Registering a Quarantined Key ---\n");
    ComputerWord key3 = createKey("XYZ");
    printf("Registering key3 (XYZ): ");
    registry = registerKey(&registry, key3);
    printKey(key3);
    printf(" Quarantined: %s\n", isQuarantined(key3) ? "YES" : "NO");
    // Expected:
    // Registering key3 (XYZ): {X, Y, Z} Quarantined: YES

    // Test Case 3: Merging Keys
    printf("\n--- Test Case 3: Merging Keys ---\n");
    ComputerWord mergedKey;

    printf("Merging key1 (ABC) and key2 (DEF): ");
    mergedKey = mergeKeys(key1, key2);
    if (mergedKey != 0) {
        printKey(mergedKey);
        printf(" Quarantined: %s\n", isQuarantined(mergedKey) ? "YES" : "NO");
    } else {
        printf("Merge failed (quarantined key involved or other error).\n");
    }
    // Expected: Merging key1 (ABC) and key2 (DEF): {A, B, C, D, E, F} Quarantined: NO

    printf("Merging key1 (ABC) and key3 (XYZ): ");
    mergedKey = mergeKeys(key1, key3);
    if (mergedKey != 0) {
        printKey(mergedKey);
        printf(" Quarantined: %s\n", isQuarantined(mergedKey) ? "YES" : "NO");
    } else {
        printf("Merge failed (quarantined key involved or other error).\n");
    }
    // Expected: Merging key1 (ABC) and key3 (XYZ): Merge failed (quarantined key involved or other error).

    return 0;
}

// Helper function to convert a character to its bit position (0-25 for A-Z)
int charToBitPos(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return -1; // Invalid character
}

// Helper function to create a computer word from a string of characters
ComputerWord createKey(char *chars) {
    ComputerWord key = 0;
    for (int i = 0; chars[i] != '\0'; i++) {
        int bitPos = charToBitPos(chars[i]);
        if (bitPos != -1) {
            key |= (1 << bitPos);
        }
    }
    return key;
}

// Helper function to print the characters represented by a computer word
void printKey(ComputerWord key) {
    printf("{");
    bool first = true;
    for (int i = 0; i < 26; i++) { // Iterate through A-Z
        if ((key >> i) & 1) {
            if (!first) {
                printf(", ");
            }
            printf("%c", (char)('A' + i));
            first = false;
        }
    }
    printf("}");
}



// TODO: Implement registerKey
ComputerWord registerKey(ComputerWord *registry, ComputerWord newKey) {
    
        if (isQuarantined(newKey))
        {
            return *registry;
        } else {
            
            return *registry |= newKey;
        }
}

// TODO: Implement isQuarantined
bool isQuarantined(ComputerWord key) {
    return ((key & (1U << 23)) != 0); // Check if 'X' bit (position 23) is set
}

// TODO: Implement mergeKeys
ComputerWord mergeKeys(ComputerWord key1, ComputerWord key2) {
    return (isQuarantined(key1) || isQuarantined(key2)) ? 0 : key1 | key2; 
}   