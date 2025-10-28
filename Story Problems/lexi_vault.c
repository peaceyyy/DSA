// The LexiVault Incident

// In the central database of LexiVault Industries, every device prototype is registered under a unique serial code.
// Each serial code is paired with a prototype name and current development stage (e.g., “Testing,” “Production,” “Scrapped”).

// To streamline development, the R&D team built a lightweight lookup system with the following rules:

// Each prototype’s serial code is used to index directly into a storage table using a hashing function that converts the serial code into an integer key.

// If two prototypes map to the same table index, the new entry must be placed in the next available position within the table.

// When a prototype is scrapped, its record is marked but not removed, to ensure future insertions still function properly.

// Engineers must be able to:

// Insert a new prototype record

// Search for an existing prototype by its serial code

// Delete (mark as scrapped) a prototype record

// Display all active prototypes with their details in order of their stored positions

// During testing, one engineer inserted the following sequence of serial codes:
// 57, 100, 23, 92, 58
// and used a hash function of h(x) = x mod 10.

// They later deleted serial code 100 and inserted 70.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define MAX_NAME_LEN 50

// Enum to represent the state of each slot in the hash table
typedef enum
{
    EMPTY,
    OCCUPIED,
    DELETED
} Status;

// Represents a single prototype record
typedef struct
{
    int serialCode;
    char prototypeName[MAX_NAME_LEN];
    char developmentStage[MAX_NAME_LEN];
} Prototype;

// Represents a single slot in our hash table
typedef struct
{
    Prototype item;
    Status status;
} HashTableSlot;

// The main hash table structure
typedef struct
{
    HashTableSlot table[TABLE_SIZE];
    int count; // Number of active items
} Dictionary;

/*
 * Function: createDictionary
 * Description: Initializes a new Dictionary (hash table).
 * Returns: A pointer to the newly created Dictionary.
 */
Dictionary *createDictionary()
{

    Dictionary *D = (Dictionary *)malloc(sizeof(Dictionary));
    D->count = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        D->table[i].status = EMPTY;
    }
    return D;
}

/*
 * Function: hash
 * Description: Computes the hash value for a given serial code.
 * Arguments:
 *   key - The serial code (int) to hash.
 * Returns: The calculated hash index (int).
 */
int hash(int key)
{
    return key % TABLE_SIZE;
}

/*
 * Function: insert
 * Description: Inserts a new prototype into the dictionary using linear probing.
 * Arguments:
 *   dict - A pointer to the Dictionary.
 *   item - The Prototype to insert.
 */
void insert(Dictionary *dict, Prototype item)
{
    // Your code here: Find an appropriate slot (EMPTY or DELETED) and insert.
    // Remember to handle table full scenarios.

    if (dict->count < TABLE_SIZE)
    {
        int hashVal = hash(item.serialCode);
        if (strcmp(item.prototypeName, dict->table[hashVal].item.prototypeName) != 0)
        {
            if (dict->table[hashVal].status == EMPTY || dict->table[hashVal].status == DELETED)
            {
                dict->table[hashVal].item = item;
            }
            else // occupied (in prod)
            {
                int i;
                // we know there will be space because we check for table size already
                for (i = hashVal; dict->table[i].item.serialCode != item.serialCode && dict->table[i].status == OCCUPIED; i = (i + 1) % TABLE_SIZE)
                {
                }

                dict->table[i].item = item;
                hashVal = i;
            }
        }

        dict->table[hashVal].status = OCCUPIED;
        dict->count++;
    }
    else
    {
        printf("Table is full!");
    }
}

/*
 * Function: search
 * Description: Searches for a prototype by its serial code.
 * Arguments:
 *   dict - A pointer to the Dictionary.
 *   serialCode - The serial code to search for.
 * Returns: The index of the found item, or -1 if not found.
 */
int search(Dictionary *dict, int serialCode)
{
    // Your code here: Probe through the table until you find the item or an EMPTY slot.
    // Remember to skip over DELETED slots.

    int hashVal = hash(serialCode);

    if (dict->table[hashVal].status != EMPTY)
    {
        if (dict->table[hashVal].item.serialCode != serialCode)
        {
            int i;
            for (i = hashVal + 1; i != hashVal && dict->table[i].status != EMPTY; i = (i + 1) % TABLE_SIZE)
            {
                if (dict->table[hashVal].item.serialCode == serialCode)
                {
                    return i;
                }
            }
        }
        else
        {
            return hashVal;
        }
    }
    return -1;
}

/*
 * Function: deleteItem
 * Description: Marks a prototype as "scrapped" (lazy deletion).
 * Arguments:
 *   dict - A pointer to the Dictionary.
 *   serialCode - The serial code of the prototype to delete.
 */
void deleteItem(Dictionary *dict, int serialCode)
{

    int hashVal = hash(serialCode);

    if (dict->table[hashVal].status != EMPTY)
    {

        if (dict->table[hashVal].item.serialCode != serialCode)
        {
            int i;
            for (i = hashVal + 1; i != hashVal && dict->table[i].status != EMPTY; i = (i + 1) % TABLE_SIZE)
            {
                if (dict->table[hashVal].item.serialCode == serialCode)
                {
                    dict->table[hashVal].status = DELETED;
                }
            }
        }
        else
        {
            dict->table[hashVal].status = DELETED;
        }
    }
}

/*
 * Function: display
 * Description: Prints all active (OCCUPIED) prototypes in the dictionary.
 * Arguments:
 *   dict - A pointer to the Dictionary.
 */
void display(Dictionary *dict)
{
    printf("LexiVault Prototype Registry:\n");
    printf("-------------------------------------------------\n");
    printf("Index | Serial | Name         | Stage\n");
    printf("-------------------------------------------------\n");
    // Your code here: Iterate through the table and print details for OCCUPIED slots.

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (dict->table[i].status != EMPTY && dict->table[i].status != DELETED) printf("%d | %d | %s         | %d\n", i, dict->table[i].item.serialCode, dict->table[i].item.prototypeName, dict->table[i].status);
        else if (dict->table[i].status == DELETED )printf("DELETED | DELETED | DELETED       | DELETED\n");
        else printf("--- | --- | ---       | ---\n");
    }
    printf("-------------------------------------------------\n");
}

int main()
{
    printf("Initializing LexiVault Database...\n");
    Dictionary *vault = createDictionary();

    // --- Engineer's Test Sequence ---
    printf("\nPhase 1: Initial insertions...\n");
    insert(vault, (Prototype){57, "Alpha-1", "Testing"});
    insert(vault, (Prototype){100, "Beta-2", "Production"});
    insert(vault, (Prototype){23, "Gamma-3", "Testing"});
    insert(vault, (Prototype){92, "Delta-4", "Scrapped"});
    insert(vault, (Prototype){58, "Epsilon-5", "Production"});

    printf("Current state after initial insertions:\n");
    display(vault);

    printf("\nPhase 2: Deleting prototype 100...\n");
    deleteItem(vault, 100);

    printf("Current state after deletion:\n");
    display(vault);

    printf("\nPhase 3: Inserting prototype 70...\n");
    insert(vault, (Prototype){70, "Zeta-6", "Testing"});

    printf("Final state of the vault:\n");
    display(vault);

    // --- Verification ---
    printf("\nVerifying search for 92...\n");
    int index = search(vault, 92);
    if (index != -1)
    {
        printf("Found prototype 92 at index %d.\n", index);
    }
    else
    {
        printf("Could not find prototype 92.\n");
    }

    printf("\nVerifying search for 100 (deleted)...\n");
    index = search(vault, 100);
    if (index != -1)
    {
        printf("Error: Found deleted prototype 100 at index %d.\n", index);
    }
    else
    {
        printf("Correctly did not find active prototype 100.\n");
    }

    // Clean up
    free(vault);
    printf("\nSystem shutdown.\n");

    return 0;
}