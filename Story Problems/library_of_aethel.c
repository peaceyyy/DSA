
// Cultural flavor applied: Anime - lightly otaku-flavored metaphors used.
// In the ancient Library of Aethel, scrolls are categorized by their mystical 'resonance' (a hash value).
// However, some scrolls are 'Whispering Curses' – their knowledge is too dangerous to store directly.
// When a Whispering Curse scroll is encountered, its ID must be noted in the catalog, but its content is replaced with a 'FORBIDDEN' marker.
// Deleting a Whispering Curse also requires special handling.
// Your task, Lab Member, is to implement the cataloging system.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 10
#define FORBIDDEN_MARKER -999 // Special marker for forbidden scrolls

typedef struct ScrollNode
{
    int scrollID;
    int data; // Stores actual data, or FORBIDDEN_MARKER if cursed
    struct ScrollNode *link;
} *ScrollList;

typedef ScrollList Library[SIZE];

// Function Prototypes
void initLibrary(Library L);
int hash(int scrollID);
void insertScroll(Library L, int scrollID, int data); // TODO: Implement this function
void deleteScroll(Library L, int scrollID);           // TODO: Implement this function
bool findScroll(Library L, int scrollID);             // TODO: Implement this function
void displayLibrary(Library L);

int main()
{
    Library aethelLibrary;
    initLibrary(aethelLibrary);

    printf("=== Library of Aethel: Scroll Cataloging ===\n");

    // Test Case 1: Basic insertions
    printf("\n--- Test Case 1: Basic Insertions ---\n");
    insertScroll(aethelLibrary, 10, 100); // Hash 0
    insertScroll(aethelLibrary, 20, 200); // Hash 0, collision
    insertScroll(aethelLibrary, 3, 30);   // Hash 3
    insertScroll(aethelLibrary, 13, 130); // Hash 3, collision
    displayLibrary(aethelLibrary);
    // Expected:
    // [0]: {ID: 20, Data: 200} -> {ID: 10, Data: 100} -> NULL
    // [1]: NULL
    // [2]: NULL
    // [3]: {ID: 13, Data: 130} -> {ID: 3, Data: 30} -> NULL
    // ... (other empty buckets)

    // Test Case 2: Inserting Forbidden Scrolls (IDs divisible by 7)
    printf("\n--- Test Case 2: Inserting Forbidden Scrolls ---\n");
    insertScroll(aethelLibrary, 7, 70);   // Hash 7, Forbidden
    insertScroll(aethelLibrary, 14, 140); // Hash 4, Forbidden
    insertScroll(aethelLibrary, 21, 210); // Hash 1, Forbidden
    displayLibrary(aethelLibrary);
    // Expected:
    // [0]: {ID: 20, Data: 200} -> {ID: 10, Data: 100} -> NULL
    // [1]: {ID: 21, Data: FORBIDDEN_MARKER} -> NULL
    // [2]: NULL
    // [3]: {ID: 13, Data: 130} -> {ID: 3, Data: 30} -> NULL
    // [4]: {ID: 14, Data: FORBIDDEN_MARKER} -> NULL
    // [7]: {ID: 7, Data: FORBIDDEN_MARKER} -> NULL
    // ... (other empty buckets)

    // Test Case 3: Finding Scrolls
    printf("\n--- Test Case 3: Finding Scrolls ---\n");
    printf("Finding scroll 10: %s\n", findScroll(aethelLibrary, 10) ? "Found (Regular)" : "Not Found");
    // Expected: Found (Regular)
    printf("Finding scroll 7: %s\n", findScroll(aethelLibrary, 7) ? "Found (Forbidden)" : "Not Found");
    // Expected: Found (Forbidden)
    printf("Finding scroll 5: %s\n", findScroll(aethelLibrary, 5) ? "Found" : "Not Found");
    // Expected: Not Found
    printf("Finding scroll 14: %s\n", findScroll(aethelLibrary, 14) ? "Found (Forbidden)" : "Not Found");
    // Expected: Found (Forbidden)

    // Test Case 4: Deleting Scrolls
    printf("\n--- Test Case 4: Deleting Scrolls ---\n");
    deleteScroll(aethelLibrary, 10); // Delete regular scroll
    deleteScroll(aethelLibrary, 7);  // Delete forbidden scroll
    deleteScroll(aethelLibrary, 5);  // Delete non-existent scroll
    displayLibrary(aethelLibrary);
    // Expected:
    // [0]: {ID: 20, Data: 200} -> NULL (10 removed)
    // [1]: {ID: 21, Data: FORBIDDEN_MARKER} -> NULL
    // [2]: NULL
    // [3]: {ID: 13, Data: 130} -> {ID: 3, Data: 30} -> NULL
    // [4]: {ID: 14, Data: FORBIDDEN_MARKER} -> NULL
    // [7]: NULL (7 removed)
    // ... (other empty buckets)

    return 0;
}

void initLibrary(Library L)
{
    for (int i = 0; i < SIZE; i++)
    {
        L[i] = NULL;
    }
}

int hash(int scrollID)
{
    return scrollID % SIZE;
}

void displayLibrary(Library L)
{
    printf("\n--- Current Library State ---\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("[%d]: ", i);
        ScrollList current = L[i];
        while (current != NULL)
        {
            printf("{ID: %d,", current->scrollID);
            if (current->data != FORBIDDEN_MARKER)
            {
                printf(" Data: %d} -> ", current->data);
            }
            else
            {
                printf(" Data: %s -> ", "FORBIDDEN");
            }
            current = current->link;
        }
        printf("NULL\n");
    }
    printf("-----------------------------\n");
}

/*
typedef struct ScrollNode {
    int scrollID;
    int data; // Stores actual data, or FORBIDDEN_MARKER if cursed
    struct ScrollNode* link;
}*ScrollList;

typedef ScrollList Library[SIZE];

*/
// TODO: Implement insertScroll
void insertScroll(Library L, int scrollID, int data)
{

    int hashValue = hash(scrollID);

    ScrollList newScroll = (ScrollList)malloc(sizeof(struct ScrollNode));

    newScroll->data = (scrollID % 7 == 0) ? FORBIDDEN_MARKER : data;
    newScroll->scrollID = scrollID;
    newScroll->link = L[hashValue];
    L[hashValue] = newScroll;
}

// TODO: Implement deleteScroll
void deleteScroll(Library L, int scrollID)
{
    // Your code here
    int hashValue = hash(scrollID);
    ScrollList *trav;
    if (L[hashValue] != NULL)
    {
        for (trav = &L[hashValue]; *trav != NULL && (*trav)->scrollID != scrollID; trav = &(*trav)->link)
        {
        }

        ScrollList temp = *trav;
        *trav = temp->link;
        free(temp);
    }
}

// TODO: Implement findScroll
bool findScroll(Library L, int scrollID)
{
    int hashValue = hash(scrollID);
    ScrollList *trav;
    if (L[hashValue] != NULL)

    {
        for (trav = &L[hashValue]; *trav != NULL; trav = &(*trav)->link)
        {
            if ((*trav)->scrollID == scrollID)
                return true;
        }
        return false;
    }
}