/*
========================================
PROBLEM 3: The Thunder Spears Guild Recruitment Ledger
Difficulty: ★★★★☆ (Medium-Hard)
Topic: Linked List Set Operations (Sorted Merge with Priority Filtering)
StoryFlavor: epic (Epic: The Musical × isekai fusion)
========================================

Story:

In the aftermath of the Trojan War, Odysseus has been isekai'd into a fantasy realm
where adventurer guilds reign supreme. He now leads the "Thunder Spears" — an elite
guild that tracks member contributions via a mystical ledger system.

Each guild member is represented by:
- **heroID**: Unique identifier (integer, serves as sort key)
- **contributionPoints**: Total quest contributions
- **divineBlessing**: Type of godly favor (0=None, 1=Athena, 2=Poseidon, 3=Zeus, 4=Hermes)

The ledger is maintained as a **sorted linked list** (ascending by heroID).
Unlike standard sets, this ledger has a TWIST:


Your mission as Odysseus's tactical advisor:

**Operations Required:**

1. **initLedger()**: Initialize empty ledger (return NULL)

2. **insertHero(ledger, heroID, contributionPoints, divineBlessing)**: Insert new hero
   in sorted order (ascending heroID). If heroID already exists, REJECT the insertion
   and print a warning.

3. **mergeLedgers(ledgerA, ledgerB)**: Merge two sorted ledgers into a new sorted ledger.
   - If heroID appears in BOTH: SUM contributionPoints, take MAX divineBlessing
   - If heroID appears in only one: Copy as-is
   - Result must be sorted by heroID (ascending)
   - Original ledgers remain intact (create new nodes)

4. **filterByBlessing(ledger, minBlessing)**: Create a new ledger containing only heroes
   with divineBlessing >= minBlessing (maintain sorted order)

5. **findTopContributor(ledger)**: Return pointer to hero with highest contributionPoints
   (if tie, return first occurrence in sorted order)

6. **removeHero(ledger, heroID)**: Remove hero from ledger, return updated ledger head

7. **displayLedger(ledger)**: Print all heroes in format:
   "HeroID | Contributions | Blessing"

========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct HeroNode
{
    int heroID;
    int contributionPoints;
    int divineBlessing; // 0=None, 1=Athena, 2=Poseidon, 3=Zeus, 4=Hermes
    struct HeroNode *next;
} HeroNode;

typedef HeroNode *GUILD_LEDGER;

// TODO: Implement these functions
GUILD_LEDGER initLedger()
{

    // GUILD_LEDGER newGuildLedger = NULL;
    // return newGuildLedger;

    return NULL;
}

GUILD_LEDGER insertHero(GUILD_LEDGER ledger, int heroID, int contributionPoints, int divineBlessing)
{

    GUILD_LEDGER updatedLedger = ledger;

    HeroNode **trav;

    for (trav = &updatedLedger; *trav != NULL && heroID >= (*trav)->heroID; trav = &(*trav)->next)
    {
        if (heroID == (*trav)->heroID)
        {

            printf("Hero with ID %d is already in the ledger!\n\n", heroID);
            return updatedLedger;
        }
    }

    HeroNode *newHeroNode = (HeroNode *)malloc(sizeof(HeroNode));
    newHeroNode->heroID = heroID;
    newHeroNode->contributionPoints = contributionPoints;
    newHeroNode->divineBlessing = divineBlessing;
    newHeroNode->next = *trav;
    *trav = newHeroNode;

    return updatedLedger;
}

/*

**The Twist:**
When merging two ledgers (e.g., after a guild alliance), members with matching heroIDs
must have their contributionPoints SUMMED and keep the HIGHER divineBlessing value.
This is NOT a pure set union — it's a priority merge with aggregation.


Each guild member is represented by:
- **heroID**: Unique identifier (integer, serves as sort key)
- **contributionPoints**: Total quest contributions
- **divineBlessing**: Type of godly favor (0=None, 1=Athena, 2=Poseidon, 3=Zeus, 4=Hermes)

*/

HeroNode *copyHeroNode(HeroNode hero)
{
    HeroNode *newHero = (HeroNode *)malloc(sizeof(HeroNode));
    newHero->heroID = hero.heroID;
    newHero->contributionPoints = hero.contributionPoints;
    newHero->divineBlessing = hero.divineBlessing;
    newHero->next = NULL;

    return newHero;
}
GUILD_LEDGER mergeLedgers(GUILD_LEDGER ledgerA, GUILD_LEDGER ledgerB)
{

    GUILD_LEDGER aptr, bptr, *cptr, C;
    C = NULL;
    aptr = ledgerA;
    bptr = ledgerB;
    cptr = &C;

    while (aptr != NULL && bptr != NULL)
    {

        // *cptr = (HeroNode *)malloc(sizeof(HeroNode));

        if (aptr->heroID < bptr->heroID)
        {

            *cptr = copyHeroNode(*aptr);
            aptr = aptr->next;
        }
        else
        {

            if (aptr->heroID == bptr->heroID)
            {
                *cptr = copyHeroNode(*aptr);
                (*cptr)->contributionPoints = aptr->contributionPoints + bptr->contributionPoints;
                (*cptr)->divineBlessing = (aptr->divineBlessing > bptr->divineBlessing) ? aptr->divineBlessing : bptr->divineBlessing;
                aptr = aptr->next;
            }
            else
            {

                *cptr = copyHeroNode(*bptr);
            }

            bptr = bptr->next;
        }

        cptr = &(*cptr)->next;
    }

    HeroNode *dptr = (aptr != NULL) ? aptr : bptr;

    while (dptr != NULL)
    {

        // *cptr = (HeroNode *)malloc(sizeof(HeroNode));
        *cptr = copyHeroNode(*dptr);
        dptr = dptr->next;
        cptr = &(*cptr)->next;
    }

    // C = NULL;

    return C;
}

/*

4. **filterByBlessing(ledger, minBlessing)**: Create a new ledger containing only heroes
   with divineBlessing >= minBlessing (maintain sorted order)
*/
GUILD_LEDGER filterByBlessing(GUILD_LEDGER ledger, int minBlessing)
{

    GUILD_LEDGER filteredLedger, trav, *cptr;
    filteredLedger = initLedger(); 
    cptr = &filteredLedger;

    for (trav = ledger; trav != NULL; trav = trav->next)
    {

        if (trav->divineBlessing >= minBlessing)
        {
            *cptr = copyHeroNode(*trav);
            cptr = &(*cptr)->next;
        }
    }

   
    return filteredLedger;
}
/*
5. **findTopContributor(ledger)**: Return pointer to hero with highest contributionPoints
   (if tie, return first occurrence in sorted order)
*/
HeroNode *findTopContributor(GUILD_LEDGER ledger)
{

    HeroNode *trav = ledger;
    int topContributionPoints = 0;

    while (trav != NULL)
    {

        if (trav->contributionPoints > topContributionPoints)
            topContributionPoints = trav->contributionPoints;
        trav = trav->next;
    }

    trav = ledger;

    while (trav != NULL)
    {

        if (trav->contributionPoints == topContributionPoints)
            return trav;
        trav = trav->next;
    }

    return NULL;
}
/*
. **removeHero(ledger, heroID)**: Remove hero from ledger, return updated ledger head
*/
GUILD_LEDGER removeHero(GUILD_LEDGER ledger, int heroID)
{

    GUILD_LEDGER updatedLedger = ledger;
    HeroNode **trav;

    for (trav = &ledger; *trav != NULL && (*trav)->heroID != heroID; trav = &(*trav)->next)
    {
    };

    if (*trav != NULL){

        HeroNode *temp = *trav;
        *trav = temp->next;
        free(temp);

    }
    
    return updatedLedger;
}

// --- Helper Functions (Already Implemented) ---
const char *blessingName(int blessing)
{
    switch (blessing)
    {
    case 0:
        return "None";
    case 1:
        return "Athena";
    case 2:
        return "Poseidon";
    case 3:
        return "Zeus";
    case 4:
        return "Hermes";
    default:
        return "Unknown";
    }
}

/*
7. **displayLedger(ledger)**: Print all heroes in format:
   "HeroID | Contributions | Blessing"
*/

void displayLedger(GUILD_LEDGER ledger)
{
    HeroNode *trav = ledger;
    printf("HeroID | Contributions | Blessing\n");
    printf("---------------------------------------\n");
    while (trav != NULL)
    {
        printf("  %3d  |      %3d      | %s\n", trav->heroID, trav->contributionPoints, blessingName(trav->divineBlessing));
        trav = trav->next;
    }
}

int countHeroes(GUILD_LEDGER ledger)
{
    int count = 0;
    HeroNode *trav = ledger;
    while (trav != NULL)
    {
        count++;
        trav = trav->next;
    }
    return count;
}

// --- Main Function (Test Cases) ---
int main()
{
    printf("========================================\n");
    printf("THUNDER SPEARS GUILD - RECRUITMENT LEDGER SYSTEM\n");
    printf("Odysseus: 'Cunning and strength — the keys to survival.'\n");
    printf("========================================\n\n");

    printf("--- Test Case 1: Building Initial Ledger ---\n");
    GUILD_LEDGER ledgerA = initLedger();

    ledgerA = insertHero(ledgerA, 102, 350, 1); // Athena's blessing
    ledgerA = insertHero(ledgerA, 105, 420, 3); // Zeus's blessing
    ledgerA = insertHero(ledgerA, 101, 280, 0); // No blessing
    ledgerA = insertHero(ledgerA, 107, 510, 2); // Poseidon's blessing
    ledgerA = insertHero(ledgerA, 103, 290, 1); // Athena's blessing

    printf("Ledger A (Thunder Spears):\n");
    displayLedger(ledgerA);
    // Expected Output (sorted by heroID):
    // HeroID | Contributions | Blessing
    // ---------------------------------------
    //   101  |      280      | None
    //   102  |      350      | Athena
    //   103  |      290      | Athena
    //   105  |      420      | Zeus
    //   107  |      510      | Poseidon

    printf("\n--- Test Case 2: Duplicate Insertion Prevention ---\n");
    printf("Attempting to insert Hero 105 again (duplicate):\n");
    ledgerA = insertHero(ledgerA, 105, 999, 4); // Should be rejected
    displayLedger(ledgerA);
    // Expected: Warning message, ledger unchanged

    printf("\n--- Test Case 3: Building Allied Ledger ---\n");
    GUILD_LEDGER ledgerB = initLedger();

    ledgerB = insertHero(ledgerB, 104, 310, 2); // Poseidon
    ledgerB = insertHero(ledgerB, 105, 180, 1); // Zeus (overlaps with ledgerA)
    ledgerB = insertHero(ledgerB, 106, 400, 4); // Hermes
    ledgerB = insertHero(ledgerB, 101, 120, 2); // Poseidon (overlaps with ledgerA)

    printf("Ledger B (Allied Guild):\n");
    displayLedger(ledgerB);
    // Expected Output:
    //   101  |      120      | Poseidon
    //   104  |      310      | Poseidon
    //   105  |      180      | Athena
    //   106  |      400      | Hermes

    printf("\n--- Test Case 4: Priority Merge (The Twist!) ---\n");
    GUILD_LEDGER merged = mergeLedgers(ledgerA, ledgerB);
    printf("Merged Ledger (Thunder Spears + Allied Guild):\n");
    displayLedger(merged);
    // Expected Output:
    //   101  |      400      | Poseidon  ← SUM(280+120), MAX(0, 2)
    //   102  |      350      | Athena    ← Only in A
    //   103  |      290      | Athena    ← Only in A
    //   104  |      310      | Poseidon  ← Only in B
    //   105  |      600      | Zeus      ← SUM(420+180), MAX(3, 1)
    //   106  |      400      | Hermes    ← Only in B
    //   107  |      510      | Poseidon  ← Only in A

    printf("\n--- Test Case 5: Filter by Divine Blessing ---\n");
    GUILD_LEDGER eliteOnly = filterByBlessing(merged, 2); // Poseidon, Zeus, Hermes
    printf("Elite Members (Blessing >= Poseidon):\n");
    displayLedger(eliteOnly);
    // Expected Output:
    //   101  |      400      | Poseidon
    //   104  |      310      | Poseidon
    //   105  |      600      | Zeus
    //   106  |      400      | Hermes
    //   107  |      510      | Poseidon

    printf("\n--- Test Case 6: Find Top Contributor ---\n");
    HeroNode *topHero = findTopContributor(merged);
    if (topHero != NULL)
    {
        printf("Top Contributor:\n");
        printf("  Hero ID: %d | Contributions: %d | Blessing: %s\n",
               topHero->heroID, topHero->contributionPoints, blessingName(topHero->divineBlessing));
    }
    // Expected Output:
    //   Hero ID: 105 | Contributions: 600 | Blessing: Zeus

    printf("\n--- Test Case 7: Remove Hero from Ledger ---\n");
    printf("Removing Hero 105 from merged ledger...\n");
    merged = removeHero(merged, 105);
    displayLedger(merged);
    // Expected: Hero 105 no longer appears

    printf("\n--- Test Case 8: Edge Case - Merge with Empty Ledger ---\n");
    GUILD_LEDGER emptyLedger = initLedger();
    GUILD_LEDGER mergedWithEmpty = mergeLedgers(ledgerA, emptyLedger);
    printf("Merged (LedgerA + Empty):\n");
    displayLedger(mergedWithEmpty);
    printf("  Count: %d (should match original LedgerA count: %d)\n",
           countHeroes(mergedWithEmpty), countHeroes(ledgerA));
    // Expected: Identical to ledgerA

    printf("\n--- Test Case 9: Edge Case - Filter with No Matches ---\n");
    GUILD_LEDGER noMatches = filterByBlessing(ledgerA, 5); // No blessing level 5
    printf("Filtered by Blessing >= 5:\n");
    displayLedger(noMatches);
    // Expected: Empty ledger

    printf("\n--- Test Case 10: Complex Merge Chain ---\n");
    GUILD_LEDGER ledgerC = initLedger();
    ledgerC = insertHero(ledgerC, 101, 50, 4);  // Overlaps with A & B
    ledgerC = insertHero(ledgerC, 108, 700, 3); // New hero

    printf("Ledger C:\n");
    displayLedger(ledgerC);

    GUILD_LEDGER triMerge = mergeLedgers(merged, ledgerC);
    printf("Triple Merge (Merged + LedgerC):\n");
    displayLedger(triMerge);
    // Expected:
    //   101  |      450      | Hermes    ← SUM(400+50), MAX(2, 4)
    //   102  |      350      | Athena
    //   103  |      290      | Athena
    //   104  |      310      | Poseidon
    //   106  |      400      | Hermes
    //   107  |      510      | Poseidon
    //   108  |      700      | Zeus      ← New from C

    printf("\n========================================\n");
    printf("GUILD LEDGER SYSTEM TEST COMPLETE\n");
    printf("Odysseus: 'A worthy alliance. To Ithaca — and beyond!'\n");
    printf("========================================\n");

    return 0;
}
