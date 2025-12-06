/*
========================================
PROBLEM 4: The Ramen Shop Membership Database
Difficulty: ★★★☆☆ (Medium - Dictionary Warmup)
Topic: Open Hashing with Linked Lists (Basic Insert/Search/Delete)
========================================

Story:

In the backstreets of Shibuya, the legendary "Ichiran Horizon" ramen shop has been
serving signature tonkotsu bowls for 47 years. Owner Masato-san keeps a handwritten
membership ledger of loyal patrons who've earned lifetime discount privileges.

Each member record contains:
- Customer ID (4-digit number, used as hash key)
- Name (family name)
- Visit count (number of bowls consumed lifetime)
- Loyalty tier (Bronze < 50 bowls, Silver < 150, Gold < 300, Platinum >= 300)

Due to a recent health inspection requiring digital records, Masato's granddaughter
Aiko is converting the paper ledger into a hash table system. The shop expects:

- ~50 regular members currently
- Hash table size: 13 (prime number for better distribution)
- Hash function: `h(customerID) = customerID % TABLE_SIZE`
- Collision resolution: Separate chaining (linked lists)

Operations needed:
1. **enrollMember**: Add a new member (insert with duplicate ID check)
2. **findMember**: Look up member by ID and display their record
3. **updateVisitCount**: Increment bowl count and recalculate tier
4. **revokeMembership**: Remove a member from the system
5. **displayLedger**: Show all members in hash table order

========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13
#define NAME_LENGTH 30

typedef enum
{
    BRONZE,  // < 50 bowls
    SILVER,  // < 150 bowls
    GOLD,    // < 300 bowls
    PLATINUM // >= 300 bowls
} LoyaltyTier;

typedef struct MemberNode
{
    int customerID;
    char name[NAME_LENGTH];
    int visitCount;
    LoyaltyTier tier;
    struct MemberNode *next;
} MemberNode;

typedef MemberNode *MEMBERSHIP_LEDGER[TABLE_SIZE];

/*

Operations needed:
1. **enrollMember**: Add a new member (insert with duplicate ID check)
2. **findMember**: Look up member by ID and display their record
3. **updateVisitCount**: Increment bowl count and recalculate tier
4. **revokeMembership**: Remove a member from the system
5. **displayLedger**: Show all members in hash table order

typedef enum {
    BRONZE,   // < 50 bowls
    SILVER,   // < 150 bowls
    GOLD,     // < 300 bowls
    PLATINUM  // >= 300 bowls
} LoyaltyTier;

typedef struct MemberNode {
    int customerID;
    char name[NAME_LENGTH];
    int visitCount;
    LoyaltyTier tier;
    struct MemberNode *next;
} MemberNode;

typedef MemberNode* MEMBERSHIP_LEDGER[TABLE_SIZE];

*/

// TODO: Implement these functions
void initLedger(MEMBERSHIP_LEDGER ledger)
{

    for (int i = 0; i < TABLE_SIZE; i++)
        ledger[i] = NULL;
}
int hashFunction(int customerID)
{

    return customerID % TABLE_SIZE;
}
LoyaltyTier calculateTier(int visitCount)
{

    if (visitCount < 50)
    {
        return BRONZE;
    }
    else if (visitCount >= 50 && visitCount < 150)
    {
        return SILVER;
    }
    else if (visitCount >= 150 && visitCount < 300)
    {
        return GOLD;
    }
    else
    {
        return PLATINUM;
    }
}
const char *tierToString(LoyaltyTier tier)
{

    if (tier == BRONZE)
    {
        return "BRONZE";
    }
    else if (tier == SILVER)
    {
        return "SILVER";
    }
    else if (tier == GOLD)
    {
        return "GOLD";
    }
    else
    {
        return "PLATINUM";
    }
}
void enrollMember(MEMBERSHIP_LEDGER ledger, int customerID, const char *name, int visitCount)
{

    int hashValue = hashFunction(customerID);

    MemberNode **trav;

    for (trav = &ledger[hashValue]; *trav != NULL && (*trav)->customerID != customerID; trav = &(*trav)->next){}

    if (*trav == NULL){
        MemberNode *newMember = (MemberNode *)malloc(sizeof(MemberNode));

        if (newMember != NULL)
        {

            newMember->customerID = customerID;
            strcpy(newMember->name, name);
            newMember->visitCount = visitCount;
            newMember->tier = calculateTier(visitCount);
            newMember->next = NULL;
            *trav = newMember;
        }
    } else {
        printf("\nDUPLICATE\n");
    }
}
MemberNode *findMember(MEMBERSHIP_LEDGER ledger, int customerID)
{

    int hashValue = hashFunction(customerID);

    MemberNode *trav;

    for (trav = ledger[hashValue]; trav != NULL; trav = trav->next)
    {

        if (trav->customerID == customerID)
            return trav;
    }
    return NULL;
}

void updateVisitCount(MEMBERSHIP_LEDGER ledger, int customerID, int additionalBowls)
{

    MemberNode *memberToUpdate = findMember(ledger, customerID);
    if (memberToUpdate == NULL) {
        printf("Member ID %d not found.\n", customerID);
        return;
    }

    memberToUpdate->visitCount += additionalBowls;
    memberToUpdate->tier = calculateTier(memberToUpdate->visitCount);
}

void revokeMembership(MEMBERSHIP_LEDGER ledger, int customerID)
{

    int hashValue = hashFunction(customerID);

    MemberNode **trav;

    for (trav = &ledger[hashValue]; *trav != NULL && (*trav)->customerID != customerID; trav = &(*trav)->next)
    {
    };

    if (*trav != NULL)
    {

        MemberNode *temp = *trav;
        (*trav) = temp->next;
        free(temp);
    }
    else
    {
        printf("\nMember not found in the ledger!");
    }
}

void displayLedger(MEMBERSHIP_LEDGER ledger)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        printf("Bucket %d: ", i);
        MemberNode *trav = ledger[i];
        if (trav == NULL)
        {
            printf("(empty)\n");
        }
        else
        {
            while (trav != NULL)
            {
                printf("%s(%d,%d,%s)", trav->name, trav->customerID, trav->visitCount, tierToString(trav->tier));
                if (trav->next != NULL)
                {
                    printf(" -> ");
                }
                trav = trav->next;
            }
            printf("\n");
        }
    }
}

// --- Main Function (Test Cases) ---
int main()
{
    MEMBERSHIP_LEDGER ledger;

    printf("========================================\n");
    printf("ICHIRAN HORIZON - MEMBERSHIP LEDGER SYSTEM\n");
    printf("========================================\n\n");

    initLedger(ledger);

    printf("--- Test Case 1: Initial Enrollment ---\n");
    enrollMember(ledger, 1001, "Tanaka", 45);
    enrollMember(ledger, 1014, "Suzuki", 120); // Same hash as 1001 (collision)
    enrollMember(ledger, 2003, "Yamamoto", 280);
    enrollMember(ledger, 3005, "Kobayashi", 350);
    enrollMember(ledger, 1027, "Sato", 75); // Same hash as 1001, 1014 (chain of 3)
    enrollMember(ledger, 4007, "Nakamura", 15);
    enrollMember(ledger, 5002, "Ito", 200);

    printf("Expected: 7 members enrolled with collision chains\n");
    printf("Hash collisions at bucket 1001%%13=1: Tanaka, Suzuki, Sato\n\n");

    printf("--- Test Case 2: Display Full Ledger ---\n");
    displayLedger(ledger);
    // Expected Output (hash order):
    // Bucket 0: Tanaka(1001,45,BRONZE) -> Suzuki(1014,120,SILVER) -> Sato(1027,75,SILVER)
    // Bucket 1: Yamamoto(2003,280,GOLD)
    // Bucket 2: Kobayashi(3005,350,PLATINUM)
    // Bucket 3: Nakamura(4007,15,BRONZE)
    // Bucket 4: (empty)
    // Bucket 5: (empty)
    // Bucket 6: (empty)
    // Bucket 7: (empty)
    // Bucket 8: (empty)
    // Bucket 9: (empty)
    // Bucket 10: Ito(5002,200,GOLD)
    // Bucket 11: (empty)
    // Bucket 12: (empty)

    printf("\n--- Test Case 3: Member Lookup ---\n");
    printf("Searching for Customer ID 1014 (Suzuki):\n");
    MemberNode *member = findMember(ledger, 1014);
    if (member != NULL)
    {
        printf("  Found: %s | Visits: %d | Tier: %s\n",
               member->name, member->visitCount, tierToString(member->tier));
    }
    else
    {
        printf("  Not found\n");
    }
    // Expected Output:
    //   Found: Suzuki | Visits: 120 | Tier: SILVER

    printf("\nSearching for non-existent ID 9999:\n");
    member = findMember(ledger, 9999);
    if (member != NULL)
    {
        printf("  Found: %s\n", member->name);
    }
    else
    {
        printf("  Not found (expected behavior)\n");
    }
    // Expected Output:
    //   Not found (expected behavior)

    printf("\n--- Test Case 4: Visit Count Update (Tier Promotion) ---\n");
    printf("Customer 1001 (Tanaka) eats 30 more bowls (45 -> 75):\n");
    updateVisitCount(ledger, 1001, 30);
    member = findMember(ledger, 1001);
    if (member != NULL)
    {
        printf("  Updated: %s | Visits: %d | Tier: %s\n",
               member->name, member->visitCount, tierToString(member->tier));
    }
    // Expected Output:
    //   Updated: Tanaka | Visits: 75 | Tier: SILVER

    printf("\nCustomer 5002 (Ito) eats 150 more bowls (200 -> 350):\n");
    updateVisitCount(ledger, 5002, 150);
    member = findMember(ledger, 5002);
    if (member != NULL)
    {
        printf("  Updated: %s | Visits: %d | Tier: %s\n",
               member->name, member->visitCount, tierToString(member->tier));
    }
    // Expected Output:
    //   Updated: Ito | Visits: 350 | Tier: PLATINUM

    printf("\n--- Test Case 5: Membership Revocation ---\n");
    printf("Revoking membership for ID 1014 (Suzuki - middle of chain):\n");
    revokeMembership(ledger, 1014);
    member = findMember(ledger, 1014);
    if (member == NULL)
    {
        printf("  Successfully removed (ID 1014 no longer exists)\n");
    }

    printf("\nVerifying chain integrity after deletion:\n");
    printf("  ID 1001 (Tanaka): ");
    member = findMember(ledger, 1001);
    printf("%s\n", member ? "Still exists ✓" : "ERROR - Lost!");

    printf("  ID 1027 (Sato): ");
    member = findMember(ledger, 1027);
    printf("%s\n", member ? "Still exists ✓" : "ERROR - Lost!");
    // Expected Output:
    //   Successfully removed (ID 1014 no longer exists)
    //   ID 1001 (Tanaka): Still exists ✓
    //   ID 1027 (Sato): Still exists ✓

    printf("\n--- Test Case 6: Duplicate Enrollment Prevention ---\n");
    printf("Attempting to re-enroll ID 1001 (Tanaka - already exists):\n");
    enrollMember(ledger, 1001, "Duplicate", 999);
    member = findMember(ledger, 1001);
    if (member != NULL)
    {
        printf("  Existing record preserved: %s (visits=%d)\n",
               member->name, member->visitCount);
        printf("  Duplicate enrollment rejected ✓\n");
    }
    // Expected Output:
    //   Existing record preserved: Tanaka (visits=75)
    //   Duplicate enrollment rejected ✓

    printf("\n--- Test Case 7: Final Ledger State ---\n");
    displayLedger(ledger);
    // Expected Output:
    // Bucket 1: Tanaka(1001,75,SILVER) -> Sato(1027,75,SILVER)  [Suzuki removed]
    // Bucket 2: Ito(5002,350,PLATINUM)  [Tier upgraded]
    // Bucket 3: Yamamoto(2003,280,GOLD)
    // Bucket 5: Kobayashi(3005,350,PLATINUM)
    // Bucket 7: Nakamura(4007,15,BRONZE)

    printf("\n========================================\n");
    printf("LEDGER SYSTEM TEST COMPLETE\n");
    printf("Aiko's Note: 'Digital records are ready for inspection!'\n");
    printf("========================================\n");

    return 0;
}
