/*
========================================
PROBLEM 5: Saekano Blessing Software Character Routes
Difficulty: ★★★★★ (Hard)
Topic: Dictionary - Semi-Open Hashing (Cursor-Based Buckets + Closed Probing)
StoryFlavor: anime (Saekano: How to Raise a Boring Girlfriend)
========================================

Story:

Tomoya Aki is developing his visual novel "Blessing Software" and needs to track
player choices across multiple character routes. The game has three heroines:
- Megumi Kato (Main Route)
- Eriri Spencer Sawamura (Childhood Friend Route)
- Utaha Kasumigaoka (Senpai Route)

Each player choice is tracked using a **hybrid dictionary**:
- **Primary Hash Table**: 11 buckets (closed addressing within each bucket)
- **Virtual Heap**: 40 nodes for storing choice records
- **Secondary Probing**: If a bucket is full (max 3 nodes), use linear probing to next bucket

Each choice record stores:
- **choiceID**: Unique identifier (e.g., 101 = "Invite Megumi to cafe")
- **affectionPoints**: -10 to +10 (negative = bad choice)
- **routeFlag**: 'M' (Megumi), 'E' (Eriri), 'U' (Utaha), 'N' (Neutral)

Special mechanics:
- **Route Merging**: If same choiceID appears in different playthroughs, sum affectionPoints
  and keep the most favorable routeFlag (M > E > U > N in priority)
- **Bucket Overflow**: If a bucket has 3 nodes, probe linearly to next bucket

Your mission as Blessing Software's lead programmer:

**Operations Required:**

1. **initVirtualHeap(vh)**: Initialize virtual heap with 40 nodes

2. **allocSpace(vh)**: Allocate node from heap

3. **deallocSpace(vh, index)**: Return node to heap

4. **initRouteDictionary(dict)**: Initialize all bucket heads to -1

5. **hashChoice(choiceID)**: Hash using modulo 11

6. **recordChoice(vh, dict, choiceID, affectionPoints, routeFlag)**:
   - Hash to find primary bucket
   - If bucket has < 3 nodes, insert here
   - If bucket full, probe linearly: (hash + 1) % 11, (hash + 2) % 11, ...
   - If choiceID exists: **Merge** by summing affectionPoints and updating routeFlag priority
   - Insert at front of bucket chain

7. **updateAffection(vh, dict, choiceID, deltaPoints)**:
   - Find the choice and add deltaPoints to current affection
   - Print error if not found

8. **getAffection(vh, dict, choiceID)**: Return total affection for a choice

9. **findChoice(vh, dict, choiceID)**: Return 1 if exists, 0 otherwise

10. **deleteChoice(vh, dict, choiceID)**: Remove choice and deallocate node

11. **getBucketLoad(vh, dict, bucketIndex)**: Count nodes in a bucket

12. **getMostLovedRoute()**: Return route with highest total affection
    - Return 'M', 'E', 'U', or 'N'

13. **displayRouteDictionary(vh, dict)**: Show all buckets and their chains

14. **getAverageAffection(vh, dict)**: Calculate average affection across all choices

========================================
*/

#include <stdio.h>

#define HEAP_SIZE 40
#define BUCKET_COUNT 11
#define MAX_BUCKET_SIZE 3

typedef struct
{
    int choiceID;
    int affectionPoints;
    char routeFlag; // 'M', 'E', 'U', 'N'
    int next;       // Index of next node in bucket chain
} ChoiceNode;

typedef struct
{
    ChoiceNode nodes[HEAP_SIZE];
    int avail;
} VirtualHeap;

typedef int RouteDictionary[BUCKET_COUNT]; // Each bucket stores index of first node

// TODO: Implement these functions
void initVirtualHeap(VirtualHeap *vh)
{
    // TODO
}

int allocSpace(VirtualHeap *vh)
{
    // TODO
    return -1;
}

void deallocSpace(VirtualHeap *vh, int index)
{
    // TODO
}

void initRouteDictionary(RouteDictionary dict)
{
    // TODO
}

int hashChoice(int choiceID)
{
    // TODO
    return 0;
}

void recordChoice(VirtualHeap *vh, RouteDictionary dict, int choiceID, int affectionPoints, char routeFlag)
{
    // TODO
}

void updateAffection(VirtualHeap *vh, RouteDictionary dict, int choiceID, int deltaPoints)
{
    // TODO
}

int getAffection(VirtualHeap vh, RouteDictionary dict, int choiceID)
{
    // TODO
    return 0;
}

int findChoice(VirtualHeap vh, RouteDictionary dict, int choiceID)
{
    // TODO
    return 0;
}

void deleteChoice(VirtualHeap *vh, RouteDictionary dict, int choiceID)
{
    // TODO
}

int getBucketLoad(VirtualHeap vh, RouteDictionary dict, int bucketIndex)
{
    int count = 0;
    int current = dict[bucketIndex];
    while (current != -1)
    {
        count++;
        current = vh.nodes[current].next;
    }
    return count;
}

char getMostLovedRoute(VirtualHeap vh, RouteDictionary dict)
{
    int affectionM = 0, affectionE = 0, affectionU = 0, affectionN = 0;

    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        int current = dict[i];
        while (current != -1)
        {
            switch (vh.nodes[current].routeFlag)
            {
            case 'M':
                affectionM += vh.nodes[current].affectionPoints;
                break;
            case 'E':
                affectionE += vh.nodes[current].affectionPoints;
                break;
            case 'U':
                affectionU += vh.nodes[current].affectionPoints;
                break;
            case 'N':
                affectionN += vh.nodes[current].affectionPoints;
                break;
            }
            current = vh.nodes[current].next;
        }
    }

    int maxAffection = affectionM;
    char bestRoute = 'M';
    if (affectionE > maxAffection)
    {
        maxAffection = affectionE;
        bestRoute = 'E';
    }
    if (affectionU > maxAffection)
    {
        maxAffection = affectionU;
        bestRoute = 'U';
    }
    if (affectionN > maxAffection)
    {
        bestRoute = 'N';
    }

    return bestRoute;
}

float getAverageAffection(VirtualHeap vh, RouteDictionary dict)
{
    int totalAffection = 0;
    int count = 0;

    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        int current = dict[i];
        while (current != -1)
        {
            totalAffection += vh.nodes[current].affectionPoints;
            count++;
            current = vh.nodes[current].next;
        }
    }

    return (count > 0) ? (float)totalAffection / count : 0.0f;
}

void displayRouteDictionary(VirtualHeap vh, RouteDictionary dict)
{
    printf("\n=== Blessing Software Route Tracker ===\n");
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        printf("Bucket [%2d] (Load: %d): ", i, getBucketLoad(vh, dict, i));
        int current = dict[i];
        if (current == -1)
        {
            printf("(empty)\n");
        }
        else
        {
            while (current != -1)
            {
                printf("{ID:%d, Route:%c, Affection:%+d} -> ",
                       vh.nodes[current].choiceID,
                       vh.nodes[current].routeFlag,
                       vh.nodes[current].affectionPoints);
                current = vh.nodes[current].next;
            }
            printf("END\n");
        }
    }
    printf("=======================================\n");
}

const char *getRouteName(char flag)
{
    switch (flag)
    {
    case 'M':
        return "Megumi Kato";
    case 'E':
        return "Eriri Spencer Sawamura";
    case 'U':
        return "Utaha Kasumigaoka";
    case 'N':
        return "Neutral";
    default:
        return "Unknown";
    }
}

// --- Main Function (Test Cases) ---
int main()
{
    printf("========================================\n");
    printf("BLESSING SOFTWARE - CHARACTER ROUTE TRACKER\n");
    printf("Tomoya: 'Let's make the best galge ever!'\n");
    printf("========================================\n");

    VirtualHeap vh;
    RouteDictionary dict;

    initVirtualHeap(&vh);
    initRouteDictionary(dict);

    printf("\n--- Test Case 1: Initial State ---\n");
    printf("Available heap nodes: %d\n", vh.avail);
    displayRouteDictionary(vh, dict);
    // Expected: avail = 39, all buckets empty

    printf("\n--- Test Case 2: Record Choices (No Collisions) ---\n");
    recordChoice(&vh, dict, 101, 8, 'M');  // Megumi route
    recordChoice(&vh, dict, 202, 6, 'E');  // Eriri route
    recordChoice(&vh, dict, 303, 7, 'U');  // Utaha route
    recordChoice(&vh, dict, 45, -3, 'N');  // Bad neutral choice
    displayRouteDictionary(vh, dict);
    // Expected: Choices in respective hash buckets

    printf("\n--- Test Case 3: Bucket Overflow (Linear Probing) ---\n");
    recordChoice(&vh, dict, 112, 5, 'M'); // Hash = 2 (same as 101)
    recordChoice(&vh, dict, 123, 4, 'E'); // Hash = 2 (bucket getting full)
    recordChoice(&vh, dict, 134, 3, 'U'); // Hash = 2 (bucket full, probe to 3)
    displayRouteDictionary(vh, dict);
    // Expected: Bucket 2 has 3 nodes (max), 134 probes to bucket 3

    printf("\n--- Test Case 4: Route Merging (Same ChoiceID) ---\n");
    printf("Before merge: Choice 101 affection = %d\n", getAffection(vh, dict, 101));
    recordChoice(&vh, dict, 101, 5, 'E'); // Merge: sum affection, keep 'M' (higher priority)
    printf("After merge: Choice 101 affection = %d, route = (should still be M)\n",
           getAffection(vh, dict, 101));
    displayRouteDictionary(vh, dict);
    // Expected: Affection = 8 + 5 = 13, routeFlag stays 'M'

    printf("\n--- Test Case 5: Update Affection ---\n");
    updateAffection(&vh, dict, 202, 3); // Add 3 points to Eriri route
    printf("Updated affection for choice 202: %d\n", getAffection(vh, dict, 202));
    // Expected: 6 + 3 = 9

    printf("\n--- Test Case 6: Find Choices ---\n");
    printf("Choice 101 exists? %s\n", findChoice(vh, dict, 101) ? "Yes" : "No");
    printf("Choice 999 exists? %s\n", findChoice(vh, dict, 999) ? "Yes" : "No");
    // Expected: Yes, No

    printf("\n--- Test Case 7: Delete Choice ---\n");
    deleteChoice(&vh, dict, 123); // Delete from middle of chain
    displayRouteDictionary(vh, dict);
    printf("Available heap nodes after deletion: %d\n", vh.avail);
    // Expected: 123 removed, node returned to heap

    printf("\n--- Test Case 8: Get Most Loved Route ---\n");
    char bestRoute = getMostLovedRoute(vh, dict);
    printf("Most loved route: %c (%s)\n", bestRoute, getRouteName(bestRoute));
    // Expected: 'M' (Megumi) based on current affection totals

    printf("\n--- Test Case 9: Playthrough Simulation ---\n");
    printf("Recording Megumi route playthrough...\n");
    recordChoice(&vh, dict, 501, 10, 'M');
    recordChoice(&vh, dict, 502, 9, 'M');
    recordChoice(&vh, dict, 503, 8, 'M');
    recordChoice(&vh, dict, 504, -5, 'N'); // Bad choice
    printf("Recording Utaha route playthrough...\n");
    recordChoice(&vh, dict, 601, 10, 'U');
    recordChoice(&vh, dict, 602, 9, 'U');
    recordChoice(&vh, dict, 603, 8, 'U');
    displayRouteDictionary(vh, dict);

    printf("\nRoute affection totals:\n");
    bestRoute = getMostLovedRoute(vh, dict);
    printf("Winner: %c (%s)\n", bestRoute, getRouteName(bestRoute));
    // Expected: Should show which route has highest total

    printf("\n--- Test Case 10: Average Affection ---\n");
    printf("Average affection across all choices: %.2f\n", getAverageAffection(vh, dict));
    // Expected: Calculated average

    printf("\n--- Test Case 11: Bucket Load Analysis ---\n");
    for (int i = 0; i < BUCKET_COUNT; i++)
    {
        int load = getBucketLoad(vh, dict, i);
        if (load > 0)
        {
            printf("Bucket %d load: %d node(s)", i, load);
            if (load >= MAX_BUCKET_SIZE)
            {
                printf(" (FULL - will probe on next insert)");
            }
            printf("\n");
        }
    }

    printf("\n--- Test Case 12: Stress Test - Overflow Cascading ---\n");
    printf("Filling bucket 5 and testing cascade...\n");
    recordChoice(&vh, dict, 500, 1, 'N'); // Hash 5
    recordChoice(&vh, dict, 511, 1, 'N'); // Hash 5
    recordChoice(&vh, dict, 522, 1, 'N'); // Hash 5 (full)
    recordChoice(&vh, dict, 533, 1, 'N'); // Hash 5 (should probe to 6)
    recordChoice(&vh, dict, 544, 1, 'N'); // Hash 5 (should probe to 6 or 7)
    displayRouteDictionary(vh, dict);
    // Expected: Cascade of probes visible in buckets 5, 6, 7...

    printf("\n--- Test Case 13: Route Priority Merge Test ---\n");
    recordChoice(&vh, dict, 999, 5, 'N');  // Neutral
    printf("Choice 999: Route %c\n", (findChoice(vh, dict, 999) ? 'N' : '?'));
    recordChoice(&vh, dict, 999, 3, 'U');  // Should upgrade to Utaha
    recordChoice(&vh, dict, 999, 2, 'E');  // Should upgrade to Eriri
    recordChoice(&vh, dict, 999, 1, 'M');  // Should upgrade to Megumi (highest)
    printf("After merges: Choice 999 affection = %d\n", getAffection(vh, dict, 999));
    displayRouteDictionary(vh, dict);
    // Expected: Affection = 5+3+2+1 = 11, routeFlag = 'M'

    printf("\n--- Test Case 14: Heap Exhaustion Test ---\n");
    printf("Attempting to fill heap...\n");
    for (int i = 700; i < 750; i++)
    {
        recordChoice(&vh, dict, i, 1, 'N');
    }
    printf("Available heap nodes: %d\n", vh.avail);
    displayRouteDictionary(vh, dict);
    // Expected: Should handle gracefully when heap is full

    printf("\n========================================\n");
    printf("BLESSING SOFTWARE ROUTE TRACKER TEST COMPLETE\n");
    printf("Megumi: 'Tomoya-kun, the player data is saved properly!'\n");
    printf("========================================\n");

    return 0;
}
