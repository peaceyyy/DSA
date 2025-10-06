#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 18

typedef struct
{

    char LName[16];
    char FName[24];
    char MI;
} nameType;

typedef struct node
{

    nameType name;
    struct node *link;

} *LIST, node_t;

typedef LIST Dictionary[MAX];

void initDictionary(Dictionary D);
int goldenHashBrown(nameType name);
void insertElem(Dictionary D, char *FName, char MI, char *LName);
void deleteElem(Dictionary D, nameType name);
bool isMember(Dictionary D, nameType name);
void display(Dictionary D);

int main()
{

    Dictionary D;
    initDictionary(D);

    insertElem(D, "Homer", 'A', "Dorin");
    insertElem(D, "Marge", 'B', "Simpson");
    insertElem(D, "Bart", 'C', "Simpson");
    insertElem(D, "Lisa", 'D', "Simpson");
    insertElem(D, "Maggie", 'E', "Simpson");

    printf("Before deletion:\n");
    display(D);

    nameType toDelete;
    strcpy(toDelete.FName, "Maggie");
    strcpy(toDelete.LName, "Simpson");
    toDelete.MI = 'E';
    deleteElem(D, toDelete);

    insertElem(D, "Homer", 'A', "Simpson"); // Likely to collide with Bart, Lisa, Maggie (same LName)
    insertElem(D, "Bart", 'C', "Dorin");    // Likely to collide with Homer (same FName)

    printf("\nAfter deleting Maggie:\n");
    display(D);
}

int goldenHashBrown(nameType name)
{
    int LNameSum = 0, FNameSum = 0;

    for (int i = 0; name.LName[i] != '\0'; i++)
    {
        LNameSum += name.LName[i];
    }
    for (int i = 0; name.FName[i] != '\0'; i++)
    {
        FNameSum += name.FName[i];
    }

    // Golden ratio approach: use primes to avoid clustering
    // No more division by zero, no more fractions!
    return (31 * FNameSum + 37 * LNameSum + 41 * name.MI) % MAX;
}

void initDictionary(Dictionary D)
{
    for (int i = 0; i < MAX; i++)
    {
        D[i] = NULL;
    }
}

void display(Dictionary D)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("[%2d]: ", i);
        for (LIST curr = D[i]; curr != NULL; curr = curr->link)
        {
            printf("{%s, %c, %s} -> ", curr->name.FName, curr->name.MI, curr->name.LName);
        }
        printf("NULL\n");
    }
}

void insertElem(Dictionary D, char *FName, char MI, char *LName)
{
    // Step 1: Create the new node with the data
    LIST newName = (LIST)malloc(sizeof(node_t));
    strcpy(newName->name.FName, FName);
    strcpy(newName->name.LName, LName);
    newName->name.MI = MI;
    newName->link = NULL;

    // Step 2: Check if this person already exists BEFORE inserting
    if (isMember(D, newName->name))
    {
        printf("Person already exists in the dictionary!\n");
        free(newName); 
    }
    else
    {

        // Step 3: If we reach here, person is unique - safe to insert
        int hashValue = goldenHashBrown(newName->name);

        // Step 4: Find the end of the chain at this bucket (standard insertion)
        LIST *trav;
        for (trav = &D[hashValue]; *trav != NULL; trav = &(*trav)->link)
        {
            // Just traverse to the end - no duplicate checking needed here
            // because we already confirmed uniqueness above!
        }

        // Step 5: Attach the new node at the end
        *trav = newName;
        printf("Successfully inserted: %s %c %s\n", FName, MI, LName);
    }
}

void deleteElem(Dictionary D, nameType name)
{

    int hashValue = goldenHashBrown(name);

    if (D[hashValue] != NULL)
    {

        LIST *trav;

        for (trav = &D[hashValue]; *trav != NULL && (strcmp((*trav)->name.LName, name.LName) != 0); trav = &(*trav)->link)
        {
        };

        if (*trav != NULL)
        {

            LIST temp = *trav;
            *trav = temp->link;
            free(temp);
        }
        else
        {

            printf("Not in Dictionary");
        }
    }
    else
    {
        printf("Not in Dictionary");
    }
}

bool isMember(Dictionary D, nameType name)
{
    // Step 1: Hash to find which bucket to search
    int hashValue = goldenHashBrown(name);
    int found = 0;

    // Step 2: Search through the chain at this bucket
    for (LIST trav = D[hashValue]; found != 1 && trav != NULL; trav = trav->link)
    {
        // Step 3: Check ALL three fields for exact match
        // A person is considered duplicate only if ALL fields match
        if (strcmp(trav->name.FName, name.FName) == 0 &&
            strcmp(trav->name.LName, name.LName) == 0 &&
            trav->name.MI == name.MI)
        {

            found = 1; // Found exact match - person exists
        }
    }

    return found; 
}