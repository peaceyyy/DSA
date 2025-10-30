// The Great Isekai Quartet Cafeteria Chaos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define a maximum length for magical signatures
#define MAX_SIGNATURE_LEN 50
#define TABLE_SIZE 13 // Prime number recommended for better distribution

// Enumeration to represent the state of each hash table slot
typedef enum
{
    EMPTY,    // Slot has never been used
    OCCUPIED, // Slot currently contains a valid signature
    DELETED   // Slot previously held data but was removed (for probing continuation)
} SlotState;

// Structure to represent a single slot in the hash table
typedef struct
{
    char signature[MAX_SIGNATURE_LEN];
    SlotState state;
} HashSlot;

// The hash table itself (closed hashing = fixed-size array)
HashSlot hashTable[TABLE_SIZE];

// --- Hashing and Dictionary Implementation (TODO: Implement these functions) ---

// Hash function for magical signatures
// This is provided for you, but feel free to experiment with different hash functions
unsigned int hash(const char *signature)
{
    unsigned int hash_val = 0;
    for (int i = 0; signature[i] != '\0'; i++)
    {
        hash_val = hash_val * 31 + signature[i];
    }
    return hash_val % TABLE_SIZE;
}

// TODO: Implement initialization function
// HINT: Set all slots to EMPTY state
void initializeDictionary()
{
    // Initialize all slots in the hash table to EMPTY
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i].state = EMPTY;
    }
}

// TODO: Implement the add function using CLOSED HASHING with probing
// Returns true if the signature was added (i.e., it was unique), false otherwise (duplicate)
//
// REQUIREMENTS:
// 1. Use the hash() function to find the initial index
// 2. If collision occurs, use a probing technique (linear, quadratic, double hashing, etc.)
// 3. Check for duplicates during probing - if signature already exists, return false
// 4. Handle the case where the table is full
// 5. Consider DELETED slots - they should allow probing to continue but can be reused
//
// HINT: You'll need to probe through the table and check:
//       - Is this slot EMPTY? (safe to insert if no duplicate found)
//       - Is this slot OCCUPIED? (check if it's a duplicate)
//       - Is this slot DELETED? (continue probing, but remember this as a potential insert point)
bool addMagicalSignature(const char *signature)
{
    // ...existing code...

    int hashValue = hash(signature);
    int firstDeletedNdx = -1;

    if (hashTable[hashValue].state == EMPTY)
    {
        strcpy(hashTable[hashValue].signature, signature);
        hashTable[hashValue].state = OCCUPIED;
        return true;
    }
    
    else
    {
        if (strcmp(hashTable[hashValue].signature, signature) == 0)
        {
            printf("\n%s already exists in the hash table at %d!\n", signature, hashValue);
            return false;
        } 
        else
        {
            int i;
            for (i = hashValue + 1; i != hashValue && hashTable[i].state != EMPTY; i = (i + 1) % TABLE_SIZE)
            {

                if (hashTable[i].state == DELETED && firstDeletedNdx == -1)
                {
                    firstDeletedNdx = i;
                }

                if (strcmp(hashTable[i].signature, signature) == 0)
                {
                    printf("\n%s already exists in the hash table at %d!\n", signature, i);
                    return false;
                }
            }
            if (firstDeletedNdx != -1)
            {
                printf("\nInserted at DELETED SLOT!\n");
                strcpy(hashTable[firstDeletedNdx].signature, signature);
                hashTable[firstDeletedNdx].state = OCCUPIED;
                return true;
            }

            if (i != hashValue)
            {
                printf("\nInserted at EMPTY SLOT!\n");
                strcpy(hashTable[i].signature, signature);
                hashTable[i].state = OCCUPIED;
                return true;
            }
            else
            {
                printf("\nHash Table is full!\n");
                return false;
            }
        }
    }
}
// TODO: Implement the search/contains function
// Returns true if the signature exists in the hash table, false otherwise
//
// REQUIREMENTS:
// 1. Use the same hash function and probing technique as addMagicalSignature
// 2. Stop probing when you find an EMPTY slot (signature definitely not in table)
// 3. Continue probing through DELETED slots (signature might be further along)
// 4. Return true if you find an OCCUPIED slot with matching signature
bool containsMagicalSignature(const char *signature)
{
    // ...existing code...

    int hashValue = hash(signature);

    if (hashTable[hashValue].state == EMPTY)
    {
        printf("\nSignature not in hash table!\n");
    }

    else
    {
        if (strcmp(hashTable[hashValue].signature, signature) == 0)
        {
            printf("\n%s exists in the hash table at %d!\n", signature, hashValue);
            return true;
        }

        int i;

        for (i = hashValue + 1; i != hashValue && hashTable[i].state != EMPTY; i = (i + 1) % TABLE_SIZE)
        {
            if (hashTable[i].state == OCCUPIED && strcmp(hashTable[i].signature, signature) == 0)
            {
                printf("\n%s exists in the hash table at %d!\n", signature, hashValue);
                return true;
            }
        }
    }

    return false;
}

// BONUS TODO: Implement a delete function (optional, but good practice)
// This is where the DELETED state becomes crucial!
bool deleteMagicalSignature(const char *signature)
{
    int hashValue = hash(signature);

    if (hashTable[hashValue].state == EMPTY)
    {
        printf("\n%s is not in the hash table!\n", signature);
        return false;
    }
    else
    {

        if (strcmp(hashTable[hashValue].signature, signature) == 0)
        {
            hashTable[hashValue].state = DELETED;
            // strcpy(hashTable[hashValue].signature, " ");
            return true;
        }
        int i;

        for (i = hashValue + 1; i != hashValue && hashTable[i].state != EMPTY; i = (i + 1) % TABLE_SIZE)
        {
            if (strcmp(hashTable[i].signature, signature) == 0)
            {
                hashTable[i].state = DELETED;
                // strcpy(hashTable[i].signature, " ");
                return true;
            }
        }
    }

    return false;
}

// Display function to visualize the hash table
void displayDictionary()
{
    printf("\n--- Hash Table State ---\n");
    printf("Index | State      | Signature\n");
    printf("------|------------|------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("%-5d | ", i);

        switch (hashTable[i].state)
        {
        case EMPTY:
            printf("EMPTY      | \n");
            break;
        case OCCUPIED:
            printf("OCCUPIED   | %s\n", hashTable[i].signature);
            break;
        case DELETED:
            printf("DELETED    | (was: %s)\n", hashTable[i].signature);
            break;
        }
    }
    printf("------------------------\n\n");
}

// --- Main function with test cases (DO NOT MODIFY) ---
// Note: The global hashTable array declared above is your dictionary.
// All functions operate on this shared global hash table.
int main()
{
    printf("--- Isekai Quartet Cafeteria Chaos ---\n");
    printf("Using Closed Hashing with TABLE_SIZE = %d\n\n", TABLE_SIZE);

    // Initialize the global hash table
    initializeDictionary();

    // Test Case 1: Adding unique ingredients
    printf("=== Test Case 1: Adding unique ingredients ===\n");
    printf("Adding 'Fireball' (Expected: Added): %s\n", addMagicalSignature("Fireball") ? "Added" : "Discarded");
    printf("Adding 'Heal' (Expected: Added): %s\n", addMagicalSignature("Heal") ? "Added" : "Discarded");
    printf("Adding 'Explosion' (Expected: Added): %s\n", addMagicalSignature("Explosion") ? "Added" : "Discarded");
    displayDictionary();

    // Test Case 2: Adding duplicate ingredients
    printf("\n=== Test Case 2: Adding duplicate ingredients ===\n");
    printf("Adding 'Fireball' (Expected: Discarded): %s\n", addMagicalSignature("Fireball") ? "Added" : "Discarded");
    printf("Adding 'Heal' (Expected: Discarded): %s\n", addMagicalSignature("Heal") ? "Added" : "Discarded");

    // Test Case 3: Adding new unique ingredients after duplicates
    printf("\n=== Test Case 3: Adding new unique ingredients ===\n");
    printf("Adding 'Teleport' (Expected: Added): %s\n", addMagicalSignature("Teleport") ? "Added" : "Discarded");
    printf("Adding 'Darkness' (Expected: Added): %s\n", addMagicalSignature("Darkness") ? "Added" : "Discarded");
    displayDictionary();

    // Test Case 4: Checking for existence
    printf("\n=== Test Case 4: Checking for existence ===\n");
    printf("Contains 'Explosion' (Expected: True): %s\n", containsMagicalSignature("Explosion") ? "True" : "False");
    printf("Contains 'Heal' (Expected: True): %s\n", containsMagicalSignature("Heal") ? "True" : "False");
    printf("Contains 'Summon Golem' (Expected: False): %s\n", containsMagicalSignature("Summon Golem") ? "True" : "False");

    // Test Case 5: Edge case - empty string (if your hash function handles it)
    printf("\n=== Test Case 5: Edge case - empty string ===\n");
    printf("Adding '' (Expected: Added): %s\n", addMagicalSignature("") ? "Added" : "Discarded");
    printf("Contains '' (Expected: True): %s\n", containsMagicalSignature("") ? "True" : "False");

    // Test Case 6: Testing collision handling
    printf("\n=== Test Case 6: Collision handling (if applicable) ===\n");
    printf("Adding 'IceBeam' (Expected: Added): %s\n", addMagicalSignature("IceBeam") ? "Added" : "Discarded");
    printf("Adding 'Lightning' (Expected: Added): %s\n", addMagicalSignature("Lightning") ? "Added" : "Discarded");
    printf("Adding 'Shadow' (Expected: Added): %s\n", addMagicalSignature("Shadow") ? "Added" : "Discarded");

    printf("\n=== Final Verification ===\n");
    printf("Contains 'Teleport' (Expected: True): %s\n", containsMagicalSignature("Teleport") ? "True" : "False");
    printf("Contains 'IceBeam' (Expected: True): %s\n", containsMagicalSignature("IceBeam") ? "True" : "False");
    printf("Contains 'FakeSpell' (Expected: False): %s\n", containsMagicalSignature("FakeSpell") ? "True" : "False");

    // Test Case 7: Testing the delete function
    printf("\n=== Test Case 7: Deleting ingredients ===\n");
    printf("Deleting 'Heal' (Expected: True): %s\n", deleteMagicalSignature("Heal") ? "Deleted" : "Not Found");
    displayDictionary();
    printf("Contains 'Heal' (Expected: False): %s\n", containsMagicalSignature("Heal") ? "True" : "False");

    printf("Deleting 'Summon Golem' (Expected: False): %s\n", deleteMagicalSignature("Summon Golem") ? "Deleted" : "Not Found");
    displayDictionary();

    printf("Deleting 'Fireball' (Expected: True): %s\n", deleteMagicalSignature("Fireball") ? "Deleted" : "Not Found");
    displayDictionary();
    printf("Contains 'Fireball' (Expected: False): %s\n", containsMagicalSignature("Fireball") ? "True" : "False");

    printf("\n--- End of Tests ---\n");

    return 0;
}
