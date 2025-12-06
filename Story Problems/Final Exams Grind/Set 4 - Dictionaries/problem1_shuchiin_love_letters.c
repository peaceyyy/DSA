/*
========================================
PROBLEM 1: Shuchiin Academy Love Letter Tracker
Difficulty: ★★☆☆☆ (Easy)
Topic: Dictionary - Open Hashing (Linked List Implementation)
StoryFlavor: anime (Kaguya-sama: Love is War)
========================================

Story:

At Shuchiin Academy, the prestigious Student Council office has become the epicenter
of romantic chaos. Kaguya Shinomiya and Miyuki Shirogane wage psychological warfare,
each trying to make the other confess first.

To track the flood of anonymous love letters flooding the school's confession mailboxes,
the council has implemented a **Love Letter Registry** — a hash-based system where:

- **letterID**: Unique identifier (integer)
- **senderInitials**: Two-character code (e.g., "KS" for Kaguya Shinomiya)
- **recipientMailbox**: Hash bucket (0-14)

The system uses **open hashing with linked lists** to handle collisions (because
multiple confessions to the same mailbox are inevitable at Shuchiin).

Your mission as acting secretary:

**Operations Required:**

1. **initRegistry()**: Initialize all mailbox chains to NULL

2. **hashMailbox(letterID)**: Hash function using modulo 15
   Formula: `letterID % 15`

3. **registerLetter(registry, letterID, senderInitials)**: Insert a new love letter
   - Hash the letterID to find the mailbox
   - Insert at the **front** of the chain (newest letters first)
   - If letterID already exists, print warning and reject

4. **removeLetter(registry, letterID)**: Remove a letter from the system
   - Find and delete the node
   - Free the memory

5. **findLetter(registry, letterID)**: Check if a letter exists
   - Return 1 if found, 0 otherwise

6. **displayRegistry(registry)**: Display all mailboxes and their letter chains

7. **countLettersInMailbox(registry, mailboxIndex)**: Count letters in a specific mailbox

========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAILBOX_COUNT 15

typedef struct LetterNode
{
    int letterID;
    char senderInitials[3]; // 2 chars + null terminator
    struct LetterNode *next;
} LetterNode;

typedef LetterNode *LetterChain;
typedef LetterChain LoveLetterRegistry[MAILBOX_COUNT];

// TODO: Implement these functions
void initRegistry(LoveLetterRegistry registry)
{
    for (int i = 0; i < MAILBOX_COUNT; i++){

        registry[i] = NULL;
    }
}

int hashMailbox(int letterID)
{
    // TODO
    return letterID % MAILBOX_COUNT;
}

/*
3. **registerLetter(registry, letterID, senderInitials)**: Insert a new love letter
   - Hash the letterID to find the mailbox
   - Insert at the **front** of the chain (newest letters first)
   - If letterID already exists, print warning and reject
*/

void registerLetter(LoveLetterRegistry registry, int letterID, const char *senderInitials)
{
    int hashValue = hashMailbox(letterID);
    LetterChain trav;

    
    // check first if no duplicates 
    for (trav = registry[hashValue]; trav != NULL && trav->letterID != letterID; trav = trav -> next){}

    if (trav == NULL){
       
        LetterNode* newLetterNode = (LetterNode*) malloc(sizeof(LetterNode));
        newLetterNode->letterID = letterID;
        strcpy(newLetterNode->senderInitials, senderInitials);

        LetterChain temp = registry[hashValue];
        newLetterNode->next = temp;
        registry[hashValue] = newLetterNode;

    } else {
        printf("Letter with ID %d already in mailbox!\n", letterID);
    }

}

void removeLetter(LoveLetterRegistry registry, int letterID)
{
    
    int hashValue = hashMailbox(letterID);

    

    LetterChain* trav;
    for (trav = &registry[hashValue]; *trav != NULL && (*trav)->letterID != letterID; trav = &(*trav) -> next){}

    if (*trav != NULL){

        LetterChain temp = *trav;
        *trav = temp -> next;
        free(temp);
    }
}

int findLetter(LoveLetterRegistry registry, int letterID)
{
    
    int hashValue = hashMailbox(letterID);

    LetterChain trav;
    
    // check first if no duplicates 
    for (trav = registry[hashValue]; trav != NULL; trav = trav -> next){
        if (trav->letterID == letterID) return 1;
    }


    return 0;
}

int countLettersInMailbox(LoveLetterRegistry registry, int mailboxIndex)
{
    

    LetterChain trav;
    int letterCount = 0;
    for (trav = registry[mailboxIndex]; trav != NULL; trav = trav -> next, letterCount++){};
    return letterCount;
}

void displayRegistry(LoveLetterRegistry registry)
{
    printf("\n=== Shuchiin Love Letter Registry ===\n");
    for (int i = 0; i < MAILBOX_COUNT; i++)
    {
        printf("Mailbox [%2d]: ", i);
        LetterNode *current = registry[i];
        if (current == NULL)
        {
            printf("(empty)\n");
        }
        else
        {
            while (current != NULL)
            {
                printf("{ID:%d, From:%s} -> ", current->letterID, current->senderInitials);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("=====================================\n");
}

// --- Main Function (Test Cases) ---
int main()
{
    printf("========================================\n");
    printf("SHUCHIIN ACADEMY - LOVE LETTER TRACKING SYSTEM\n");
    printf("Kaguya: 'How cute... tracking confessions like data.'\n");
    printf("========================================\n");

    LoveLetterRegistry registry;
    initRegistry(registry);

    printf("\n--- Test Case 1: Initial State ---\n");
    displayRegistry(registry);
    // Expected: All mailboxes empty

    printf("\n--- Test Case 2: Register Letters ---\n");
    registerLetter(registry, 15, "KS"); // Kaguya -> Mailbox 0
    registerLetter(registry, 30, "MS"); // Miyuki -> Mailbox 0 (collision!)
    registerLetter(registry, 7, "CL");  // Chika -> Mailbox 7
    registerLetter(registry, 22, "IH"); // Ishigami -> Mailbox 7 (collision!)
    registerLetter(registry, 45, "KH"); // Kashiwagi -> Mailbox 0 (another collision!)
    registerLetter(registry, 13, "TT"); // Tsubame -> Mailbox 13
    displayRegistry(registry);
    // Expected:
    // Mailbox [0]: {ID:45, From:KH} -> {ID:30, From:MS} -> {ID:15, From:KS} -> NULL
    // Mailbox [7]: {ID:22, From:IH} -> {ID:7, From:CL} -> NULL
    // Mailbox [13]: {ID:13, From:TT} -> NULL

    printf("\n--- Test Case 3: Duplicate Prevention ---\n");
    registerLetter(registry, 15, "XX"); // Duplicate letterID
    displayRegistry(registry);
    // Expected: Warning message, no change

    printf("\n--- Test Case 4: Find Letters ---\n");
    printf("Finding letter 15: %s\n", findLetter(registry, 15) ? "Found" : "Not Found");
    printf("Finding letter 7: %s\n", findLetter(registry, 7) ? "Found" : "Not Found");
    printf("Finding letter 99: %s\n", findLetter(registry, 99) ? "Found" : "Not Found");
    // Expected: Found, Found, Not Found

    printf("\n--- Test Case 5: Count Letters in Mailbox ---\n");
    printf("Mailbox 0 has %d letter(s)\n", countLettersInMailbox(registry, 0));
    printf("Mailbox 7 has %d letter(s)\n", countLettersInMailbox(registry, 7));
    printf("Mailbox 5 has %d letter(s)\n", countLettersInMailbox(registry, 5));
    // Expected: 3, 2, 0

    printf("\n--- Test Case 6: Remove Letters ---\n");
    removeLetter(registry, 30); // Remove from middle of chain
    removeLetter(registry, 7);  // Remove from head of chain
    removeLetter(registry, 99); // Remove non-existent
    displayRegistry(registry);
    // Expected:
    // Mailbox [0]: {ID:45, From:KH} -> {ID:15, From:KS} -> NULL (30 removed)
    // Mailbox [7]: {ID:22, From:IH} -> NULL (7 removed)
    // Mailbox [13]: {ID:13, From:TT} -> NULL

    printf("\n--- Test Case 7: Edge Case - Remove All from Mailbox ---\n");
    removeLetter(registry, 45);
    removeLetter(registry, 15);
    displayRegistry(registry);
    // Expected: Mailbox [0] now empty

    printf("\n--- Test Case 8: Mass Registration ---\n");
    for (int i = 1; i <= 50; i++)
    {
        char initials[3];
        sprintf(initials, "%02d", i % 26); // Generate dummy initials
        registerLetter(registry, i * 3, initials);
    }
    displayRegistry(registry);
    // Expected: Multiple letters in various mailboxes, demonstrating collision handling

    printf("\n--- Test Case 9: Final Count ---\n");
    int totalLetters = 0;
    for (int i = 0; i < MAILBOX_COUNT; i++)
    {
        int count = countLettersInMailbox(registry, i);
        if (count > 0)
        {
            printf("Mailbox %d: %d letter(s)\n", i, count);
            totalLetters += count;
        }
    }
    printf("Total letters in registry: %d\n", totalLetters);
    // Expected: Should equal 52 (2 from initial tests still present + 50 from mass registration)

    printf("\n========================================\n");
    printf("LOVE LETTER REGISTRY TEST COMPLETE\n");
    printf("Miyuki: 'Efficient... as expected of Shuchiin.'\n");
    printf("========================================\n");

    return 0;
}
