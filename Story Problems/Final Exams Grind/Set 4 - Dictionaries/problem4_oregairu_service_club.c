/*
========================================
PROBLEM 4: Oregairu Service Club Request Board
Difficulty: ★★★★☆ (Medium-Hard)
Topic: Dictionary - Closed Hashing (Quadratic Probing)
StoryFlavor: anime (My Teen Romantic Comedy SNAFU / Oregairu)
========================================

Story:

At Soubu High School, Hachiman Hikigaya's Service Club handles student requests with
his trademark cynicism. To manage the flood of requests, Yukino Yukinoshita implements
a **Request Tracking System** using closed hashing.

Unlike linear probing (which Hachiman calls "following the herd"), this system uses
**quadratic probing** to reduce clustering:
- Probe sequence: `hash + 1², hash + 2², hash + 3², ...` (mod table size)

The system tracks:
- **requestID**: Unique identifier (3-digit integer)
- **priorityLevel**: 1-5 (5 = urgent, 1 = trivial)

Special rule: "Genuine" requests (requestID divisible by 7) bypass normal hashing
and are stored at index `requestID % 17` without probing.

Your mission as the Service Club's reluctant helper:

**Operations Required:**

1. **initRequestBoard()**: Initialize all slots to EMPTY (0)

2. **hashRequest(requestID)**: Hash function using modulo 17
   Formula: `requestID % 17`

3. **isGenuine(requestID)**: Check if request is "genuine"
   - Return 1 if `requestID % 7 == 0`, else 0

4. **submitRequest(board, requestID, priorityLevel)**: Add a request
   - If genuine: Place at `hash(requestID)` without probing (overwrite if needed)
   - If not genuine: Use quadratic probing to find EMPTY or DELETED slot
     Probe sequence: `(hash + i*i) % 17` for i = 0, 1, 2, 3, ...
   - Store as positive value: `requestID`
   - Track priority separately (see struct below)
   - If duplicate found, update priority instead

5. **resolveRequest(board, requestID)**: Mark request as DELETED
   - Use quadratic probing to find it
   - Set to DELETED (-1)

6. **findRequest(board, requestID)**: Check if request exists
   - Return 1 if found, 0 otherwise
   - Must probe quadratically

7. **getPriority(board, requestID)**: Return priority level
   - Return priority if found, -1 otherwise

8. **calculateProbeCount(board, requestID)**: Count probes needed to find or place
   - Return number of probes (1 if at home position, >1 if probed)
   - Return -1 if not found

9. **displayBoard()**: Show all slots with probe counts

10. **getHighestPriorityRequest(board)**: Find requestID with highest priority
    - Return requestID, or -1 if board empty

========================================
*/

#include <stdio.h>

#define BOARD_SIZE 17
#define EMPTY 0
#define DELETED -1
#define MAX_PROBES 17 // Prevent infinite loops

typedef struct
{
    int requestID;     // Stores requestID (positive), EMPTY (0), or DELETED (-1)
    int priorityLevel; // 1-5, or 0 if slot empty/deleted
} RequestSlot;

typedef RequestSlot RequestBoard[BOARD_SIZE];

/*
2. **hashRequest(requestID)**: Hash function using modulo 17
   Formula: `requestID % 17`

3. **isGenuine(requestID)**: Check if request is "genuine"
   - Return 1 if `requestID % 7 == 0`, else 0
*/

void initRequestBoard(RequestBoard board)
{
    for (int i = 0; i < MAX_PROBES; i++)
    {
        board[i].priorityLevel = EMPTY;
        board[i].requestID = EMPTY;
    }
}

int hashRequest(int requestID)
{

    return requestID % 17;
}

int isGenuine(int requestID)
{

    return (requestID % 7 == 0) ? 1 : 0;
}

/*
4. **submitRequest(board, requestID, priorityLevel)**: Add a request
   - If genuine: Place at `hash(requestID)` without probing (overwrite if needed)
   - If not genuine: Use quadratic probing to find EMPTY or DELETED slot
     Probe sequence: `(hash + i*i) % 17` for i = 0, 1, 2, 3, ...
   - Store as positive value: `requestID`
   - Track priority separately (see struct below)
   - If duplicate found, update priority instead


*/
void submitRequest(RequestBoard board, int requestID, int priorityLevel) {
    int hashValue = hashRequest(requestID);
    
    // Genuine requests bypass probing
    if (isGenuine(requestID)) {
        board[hashValue].requestID = requestID;
        board[hashValue].priorityLevel = priorityLevel;
        return;
    }
    
    // Quadratic probing for regular requests
    int firstDeletedSlot = -1;
    for (int i = 0; i < MAX_PROBES; i++) {
        int probe_idx = (hashValue + i * i) % BOARD_SIZE;
        
        // Duplicate found — update priority
        if (board[probe_idx].requestID == requestID) {
            board[probe_idx].priorityLevel = priorityLevel;
            return;
        }
        
        // Track first DELETED for reuse
        if (board[probe_idx].requestID == DELETED && firstDeletedSlot == -1) {
            firstDeletedSlot = probe_idx;
        }
        
        // EMPTY found — insert here or at first DELETED
        if (board[probe_idx].requestID == EMPTY) {
            int insert_pos = (firstDeletedSlot == -1) ? probe_idx : firstDeletedSlot;
            board[insert_pos].requestID = requestID;
            board[insert_pos].priorityLevel = priorityLevel;
            return;
        }
    }
    
    // If we exit loop without inserting, table is full (or use firstDeletedSlot)
    if (firstDeletedSlot != -1) {
        board[firstDeletedSlot].requestID = requestID;
        board[firstDeletedSlot].priorityLevel = priorityLevel;
    }
}

/*


5. **resolveRequest(board, requestID)**: Mark request as DELETED
   - Use quadratic probing to find it
   - Set to DELETED (-1)



*/

void resolveRequest(RequestBoard board, int requestID)
{
    int hashValue = hashRequest(requestID);
    int firstDeletedSlot, foundDeletedSlot = 0;
    if (board[hashValue].requestID == requestID)
    {
        // printf("Request ID of %d updated in home slot!\n", requestID);
        board[hashValue].requestID = DELETED;
        return;
    }
    if (board[hashValue].requestID == EMPTY)
    {
        // printf("Request ID of %d not in the board\n", requestID);
    }
    else
    {
        if (isGenuine(requestID))
        {

            board[hashValue].requestID = DELETED;
        }
        else
        {
            int i;
            for (i = 0; i < MAX_PROBES; i++)
            {

                int probe_idx = (hashValue + i * i) % BOARD_SIZE;

                if (board[probe_idx].requestID == requestID)
                {
                    // printf("Request ID of %d in probed slot of index %d! Updating request ID!", requestID, i);
                    board[probe_idx].requestID = DELETED;
                    return;
                }

                if (board[probe_idx].requestID == EMPTY)
                {
                    printf("Request ID of %d not in the board!\n", requestID);
                    return;
                }
            }
        }
    }
}

/*

6. **findRequest(board, requestID)**: Check if request exists
   - Return 1 if found, 0 otherwise
   - Must probe quadratically


*/

int findRequest(RequestBoard board, int requestID)
{
    int hashValue = hashRequest(requestID);
    int firstDeletedSlot, foundDeletedSlot = 0;
    if (board[hashValue].requestID == requestID)
    {
        // printf("Request ID %d found in home slot!\n", requestID);
        return 1;
    }
    if (board[hashValue].requestID == EMPTY)
    {
        // printf("Request ID of %d not in the board\n", requestID);
        return 0;
    }
    else
    {
        if (isGenuine(requestID))
        {
            if(board[hashValue].requestID == requestID){
                return 1;
            } else 
            {
                return 0;
            }
        }
        else
        {
            int i;
            for (i = 0; i < MAX_PROBES; i++)
            {

                int probe_idx = (hashValue + i * i) % BOARD_SIZE;

                if (board[probe_idx].requestID == requestID)
                {
                    printf("Request ID of %d in probed slot of index %d!", requestID, i);
                    return 1;
                }

                if (board[probe_idx].priorityLevel == EMPTY)
                {
                    printf("Request ID of %d not in the board!\n", requestID);
                    return 0;
                }
            }
        }
    }
}

/*
7. **getPriority(board, requestID)**: Return priority level
   - Return priority if found, -1 otherwise



*/

int getPriority(RequestBoard board, int requestID)
{
    int hashValue = hashRequest(requestID);
    int firstDeletedSlot, foundDeletedSlot = 0;
    if (board[hashValue].requestID == requestID)
    {
        // printf("Request ID %d found in home slot!\n", requestID);
        return board[hashValue].priorityLevel;
    }
    if (board[hashValue].requestID == EMPTY)
    {
        // printf("Request ID of %d not in the board\n", requestID);
        return -1;
    }
    else
    {
        if (isGenuine(requestID))
        {
            if(board[hashValue].requestID == requestID){
                return board[hashValue].priorityLevel;
            } else 
            {
                return -1;
            }
        }
        else
        {
            int i;
            for (i = 0; i < MAX_PROBES; i++)
            {

                int probe_idx = (hashValue + i * i) % BOARD_SIZE;

                if (board[probe_idx].requestID == requestID)
                {
                    printf("Request ID of %d in probed slot of index %d Returning prio level\n!", requestID, i);
                    return board[probe_idx].priorityLevel;
                }

                if (board[probe_idx].priorityLevel == EMPTY)
                { 
                    printf("Request ID of %d not in the board!\n", requestID);
                    return -1;
                }
            }
        }
    }
    return -1;
}
/*
8. **calculateProbeCount(board, requestID)**: Count probes needed to find or place
   - Return number of probes (1 if at home position, >1 if probed)
   - Return -1 if not found

*/
int calculateProbeCount(RequestBoard board, int requestID)
{
    
     int hashValue = hashRequest(requestID);
    int firstDeletedSlot, foundDeletedSlot = 0;
    if (board[hashValue].requestID == requestID)
    {
        // printf("Request ID %d found in home slot!\n", requestID);
        return 1;
    }
    if (board[hashValue].requestID == EMPTY)
    {
        printf("Request ID of %d not in the board\n", requestID);
        return -1;
    }
    else
    {
        if (isGenuine(requestID))
        {
            if(board[hashValue].requestID == requestID){
                return 1;
            } else 
            {
                return -1;
            }
        }
        else
        {
            int i;
            for (i = 0; i < MAX_PROBES; i++)
            {

                int probe_idx = (hashValue + i * i) % BOARD_SIZE;

                if (board[probe_idx].requestID == requestID)
                {
                    printf("Request ID of %d in probed slot of index %d Returning prio level\n!", requestID, i);
                    return i;
                }

                if (board[probe_idx].priorityLevel == EMPTY)
                { 
                    printf("Request ID of %d not in the board!\n", requestID);
                    return -1;
                }
            }
        }
    }
    return -1;
}

/*
9. **getHighestPriorityRequest(board)**: Find requestID with highest priority
    - Return requestID, or -1 if board empty

*/

int getHighestPriorityRequest(RequestBoard board)
{

    int highestPrioRequest = -1;

    for (int i = 0; i < BOARD_SIZE; i++)
    {

        if (board[i].priorityLevel > highestPrioRequest) highestPrioRequest = board[i].requestID;
    }

    return highestPrioRequest;
}

void displayBoard(RequestBoard board)
{
    printf("\n=== Service Club Request Board ===\n");
    printf("Index | RequestID | Priority | Hash | ProbeCount | Status\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("[%2d]  | ", i);
        if (board[i].requestID == EMPTY)
        {
            printf("   EMPTY   |    -     |  -   |     -      | Available\n");
        }
        else if (board[i].requestID == DELETED)
        {
            printf("  DELETED  |    -     |  -   |     -      | Resolved\n");
        }
        else
        {
            int hash = hashRequest(board[i].requestID);
            int probes = calculateProbeCount(board, board[i].requestID);
            const char *type = isGenuine(board[i].requestID) ? "Genuine" : "Regular";
            printf("   %3d     |    %d     | %2d   |     %d      | %s\n",
                   board[i].requestID, board[i].priorityLevel, hash, probes, type);
        }
    }
    printf("=======================================================\n");
}

// --- Main Function (Test Cases) ---
int main()
{
    printf("========================================\n");
    printf("SOUBU HIGH - SERVICE CLUB REQUEST TRACKER\n");
    printf("Hachiman: 'Youth is a lie. So are hash collisions.'\n");
    printf("========================================\n");

    RequestBoard board;
    initRequestBoard(board);

    printf("\n--- Test Case 1: Initial State ---\n");
    displayBoard(board);
    // Expected: All slots EMPTY

    printf("\n--- Test Case 2: Submit Regular Requests (No Collisions) ---\n");
    submitRequest(board, 100, 3); // Hash 15
    submitRequest(board, 120, 4); // Hash 1
    submitRequest(board, 135, 2); // Hash 16
    displayBoard(board);
    // Expected:
    // [1]: 120 | Priority 4 | Hash 1 | ProbeCount 1 | Regular
    // [15]: 100 | Priority 3 | Hash 15 | ProbeCount 1 | Regular
    // [16]: 135 | Priority 2 | Hash 16 | ProbeCount 1 | Regular

    printf("\n--- Test Case 3: Submit Genuine Requests ---\n");
    submitRequest(board, 14, 5);  // 14 % 7 = 0 (genuine), placed at 14 % 17 = 14
    submitRequest(board, 21, 5);  // 21 % 7 = 0 (genuine), placed at 21 % 17 = 4
    submitRequest(board, 119, 5); // 119 % 7 = 0 (genuine), placed at 119 % 17 = 0
    displayBoard(board);
    // Expected: Genuine requests at slots 14, 4, 0

    printf("\n--- Test Case 4: Quadratic Probing on Collision ---\n");
    submitRequest(board, 117, 3); // Hash 15 (collision with 100)
    // Probe sequence: 15, (15+1)%17=16 (occupied), (15+4)%17=2 (free!)
    submitRequest(board, 134, 4); // Hash 15 (collision again)
    // Probe sequence: 15, 16, 2, (15+9)%17=7
    displayBoard(board);
    // Expected:
    // [2]: 117 | ProbeCount 3 (0² collision, 1² collision, 2² success)
    // [7]: 134 | ProbeCount 4

    printf("\n--- Test Case 5: Find Requests ---\n");
    printf("Request 100 found? %s\n", findRequest(board, 100) ? "Yes" : "No");
    printf("Request 14 (genuine) found? %s\n", findRequest(board, 14) ? "Yes" : "No");
    printf("Request 999 found? %s\n", findRequest(board, 999) ? "Yes" : "No");
    // Expected: Yes, Yes, No

    printf("\n--- Test Case 6: Get Priority ---\n");
    printf("Priority of request 14: %d\n", getPriority(board, 14));
    printf("Priority of request 117: %d\n", getPriority(board, 117));
    printf("Priority of request 999: %d\n", getPriority(board, 999));
    // Expected: 5, 3, -1

    printf("\n--- Test Case 7: Update Duplicate (Priority Change) ---\n");
    submitRequest(board, 100, 5); // Duplicate, should update priority
    printf("Updated priority of 100: %d\n", getPriority(board, 100));
    displayBoard(board);
    // Expected: Priority changed from 3 to 5

    printf("\n--- Test Case 8: Resolve Requests ---\n");
    resolveRequest(board, 117); // Quadratically probed request
    resolveRequest(board, 14);  // Genuine request
    displayBoard(board);
    // Expected: Slots 2 and 14 marked DELETED

    printf("\n--- Test Case 9: Search Through DELETED ---\n");
    printf("Request 134 still findable? %s (should probe through DELETED slot 2)\n",
           findRequest(board, 134) ? "Yes" : "No");
    // Expected: Yes (quadratic probing continues through DELETED)

    printf("\n--- Test Case 10: Genuine Overwrite Test ---\n");
    submitRequest(board, 35, 1); // 35 % 7 = 0 (genuine), hash = 1
    // Should overwrite slot 1 (currently holds 120)
    displayBoard(board);
    printf("Request 120 still exists? %s\n", findRequest(board, 120) ? "Yes" : "No");
    // Expected: No (120 overwritten by genuine request 35)

    printf("\n--- Test Case 11: Highest Priority Request ---\n");
    int highestPriority = getHighestPriorityRequest(board);
    printf("Highest priority request: %d (Priority: %d)\n",
           highestPriority, getPriority(board, highestPriority));
    // Expected: Should be a request with priority 5

    printf("\n--- Test Case 12: Probe Count Analysis ---\n");
    submitRequest(board, 200, 2); // Hash 13
    submitRequest(board, 217, 3); // Hash 13 (collision)
    submitRequest(board, 234, 4); // Hash 13 (collision)
    printf("\nProbe counts for collision chain at hash 13:\n");
    printf("  Request 200: %d probe(s)\n", calculateProbeCount(board, 200));
    printf("  Request 217: %d probe(s)\n", calculateProbeCount(board, 217));
    printf("  Request 234: %d probe(s)\n", calculateProbeCount(board, 234));
    displayBoard(board);
    // Expected: Increasing probe counts due to quadratic sequence

    printf("\n--- Test Case 13: Edge Case - Full Board Simulation ---\n");
    for (int i = 300; i < 320; i++)
    {
        submitRequest(board, i, (i % 5) + 1);
    }
    displayBoard(board);
    printf("Attempting to submit when full:\n");
    submitRequest(board, 999, 5);
    // Expected: Should handle gracefully (error or wraparound detection)

    printf("\n========================================\n");
    printf("SERVICE CLUB REQUEST TRACKER TEST COMPLETE\n");
    printf("Yukino: 'Efficient, as always. Well done.'\n");
    printf("========================================\n");

    return 0;
}
