/*
Anime Flavor Story: "The Shrine of Forgotten Sets"

In the bustling city of Akihabara, a secret club of high-school hackers (the Data Shrine Alliance) is challenged by the mysterious transfer student, Kurisu Makise. She brings a legendary artifact: the Quantum Dictionary, said to hold the power to instantly check membership and uniqueness among any set of student IDs. But the artifact is incomplete! The club must implement its core functions before the next school festival, or risk losing their clubroom to the rival Arcade Otaku Society.


*/

#include <stdio.h>
#include <string.h>

#define MAX_SIZE 32
#define DICT_SIZE 49

// --- SET STRUCTURE ---
typedef struct
{
    int elements[MAX_SIZE];
    int count;
} AnimeSet;

// --- DICTIONARY STRUCTURE ---
typedef struct
{
    char keys[DICT_SIZE][16];
    int values[DICT_SIZE];
    int used[DICT_SIZE]; // 0 = empty, 1 = used
} QuantumDictionary;

// --- Helper Functions (provided) ---
// Simple hash for dictionary keys
int superHasher(const char *key)
{
    int sum = 0, i = 0;
    while (key[i] != '\0')
    {
        sum += key[i];
        i++;
    }
    return sum % DICT_SIZE;
}

// --- TODO: Implement these functions ---

// Adds an element to the set if not present
void addToSet(AnimeSet *set, int elem)
{
    if (set->count < MAX_SIZE)
    {
        int found = 0;
        for (int i = 0; found != 1 && i < set->count; i++)
        {
            if (set->elements[i] == elem)
                found = 1;
        }

        if (!found)
        {
            set->elements[set->count++] = elem;
        }
    }
}
// Checks if an element is in the set
int isInSet(AnimeSet *set, int elem)
{
    for (int i = 0; i < set->count; i++)
    {
        if (set->elements[i] == elem)
            return 1;
    }

    return 0;
}

// Inserts a key-value pair into the dictionary
void insertToDictionary(QuantumDictionary *dict, const char *key, int value)
{
    if (value > DICT_SIZE) return;

    int hashValue = superHasher(key);

    if (dict->used[hashValue] != 0 )
    {

        if (strcmp(dict->keys[hashValue], key) != 0)
        {
            int i;
            for (i = hashValue + 1; dict->used[i] == 1 && strcmp(dict->keys[i], key) != 0; i = (i + 1) % DICT_SIZE)
            {
                if (i == hashValue)
                    return; // table full
            }
            if (dict->used[i] == 1 && strcmp(dict->keys[i], key) == 0)
            {
                dict->values[i] = value; // update
            }
            else
            {
                strcpy(dict->keys[i], key);
                dict->values[i] = value;
                dict->used[i] = 1;
            }
        }
        else
        {
            dict->values[hashValue] = value;
        }
    }
    else
    {
        dict->values[hashValue] = value;
        strcpy(dict->keys[hashValue], key);
        dict->used[hashValue] = 1;
    }
}





// Looks up a value by key in the dictionary
int lookupDictionary(QuantumDictionary *dict, const char *key)
{
    int hashValue = superHasher(key);
    if (dict->used[hashValue] == 1)
    {
        if (dict->used[hashValue] == 1 && strcmp(dict->keys[hashValue], key) == 0)
        {
            return dict->values[hashValue];
        }
        else
        {

                int i;
                for (i = hashValue + 1; i != hashValue && dict->used[i] != 0; i = (i + 1) % DICT_SIZE)
                {
                    if (dict->used[i] == 1 && strcmp(dict->keys[i], key) == 0) {
                        // printf("i fired\n");
                        return dict->values[i];
                }
            }

                return -1;

            // int i = hashValue;
            // do
            // {
            //     if (dict->used[i] == 1 && strcmp(dict->keys[i], key) == 0)
            //         return dict->values[i];
            //     if (dict->used[i] == 0)
            //         return -1; // not found
            //     i = (i + 1) % DICT_SIZE;
            // } while (i != hashValue);
            // return -1; // not found after full loop
        }
    }
    else
    {

        return -1;
    }
}



void displaySet (AnimeSet a)
{
    for (int i = 0; i < a.count; i++) printf("%d ", a.elements[i]);
}
// --- MAIN: Test Cases ---
int main()
{
    AnimeSet clubSet = {.count = 0};
    QuantumDictionary quantumDict = {0};

    // Test 1: Add student IDs to set
    addToSet(&clubSet, 101);
    addToSet(&clubSet, 102);
    addToSet(&clubSet, 101); // duplicate
    printf("Set contains 101? %d (expected 1)\n", isInSet(&clubSet, 101));
    printf("Set contains 103? %d (expected 0)\n", isInSet(&clubSet, 103));

    // Test 1b: Add more IDs, check for edge cases
    addToSet(&clubSet, 104);
    addToSet(&clubSet, 105);
    addToSet(&clubSet, 104);                                               // duplicate
    printf("Set contains 104? %d (expected 1)\n", isInSet(&clubSet, 104)); // Expected: 1
    printf("Set contains 999? %d (expected 0)\n", isInSet(&clubSet, 999)); // Expected: 0
    
    
    // Reset and fill up the set
    clubSet.count = 0;
    for (int i = 0; i < MAX_SIZE; i++)
        addToSet(&clubSet, i);
    printf("Set contains 0? %d (expected 1)\n", isInSet(&clubSet, 0));            // Expected: 1
    printf("Set contains 31? %d (expected 1)\n", isInSet(&clubSet, 31));          // Expected: 1
    addToSet(&clubSet,32);                                                       // Should not add if out of bounds
    printf("Set contains 32? %d (expected 0 or crash)\n", isInSet(&clubSet, 32)); // Expected: 0 or crash

    displaySet(clubSet);

    printf("\n\n");

    // Test 2: Insert key-value pairs to dictionary
    insertToDictionary(&quantumDict, "Kurisu", 18);
    insertToDictionary(&quantumDict, "Daru", 19);
    insertToDictionary(&quantumDict, "Mayuri", 17);
    printf("Kurisu's age: %d (expected 18)\n", lookupDictionary(&quantumDict, "Kurisu"));
    printf("Okabe's age: %d (expected -1)\n", lookupDictionary(&quantumDict, "Okabe"));

    // Test 2b: Overwrite value
    insertToDictionary(&quantumDict, "Kurisu", 21);
    printf("Kurisu's age after update: %d (expected 21)\n", lookupDictionary(&quantumDict, "Kurisu")); // Expected: 21

    // Test 2c: Insert more keys, check collisions
    insertToDictionary(&quantumDict, "Suzuha", 20);
    insertToDictionary(&quantumDict, "Feyris", 18);
    insertToDictionary(&quantumDict, "Ruka", 17);
    printf("Suzuha's age: %d (expected 20)\n", lookupDictionary(&quantumDict, "Suzuha")); // Expected: 20
    printf("Feyris's age: %d (expected 18)\n", lookupDictionary(&quantumDict, "Feyris")); // Expected: 18
    printf("Ruka's age: %d (expected 17)\n", lookupDictionary(&quantumDict, "Ruka"));     // Expected: 17
    
    // Test 2d: Lookup non-existent key after many inserts
    printf("Moeka's age: %d (expected -1)\n", lookupDictionary(&quantumDict, "Moeka")); // Expected: -1

    // Test 2e: More check
        insertToDictionary(&quantumDict, "Key0", 0);
    printf("Key0's value: %d (expected 0)\n", lookupDictionary(&quantumDict, "Key0"));    // Expected: 0
    insertToDictionary(&quantumDict, "Key48", 48);
    printf("Key48's value: %d (expected 48)\n", lookupDictionary(&quantumDict, "Key48")); // Expected: 48
    insertToDictionary(&quantumDict, "Overflow", 999);
    printf("Overflow's value: %d (expected -1 or collision value)\n", lookupDictionary(&quantumDict, "Overflow")); // Expected: -1 or collision value

    return 0;
}
