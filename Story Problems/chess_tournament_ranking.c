/*
Started September 22
Completed September 24
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PLAYERS 20

typedef struct
{
    char name[30];
    int rating;
    int wins;
} Player;

typedef struct
{
    Player players[MAX_PLAYERS];
    int count;
} Tournament;

// ========================================
// PROVIDED FUNCTIONS (DO NOT MODIFY)
// ========================================

void initTournament(Tournament *t)
{
    t->count = 0;
}

void displayRankings(Tournament t)
{
    printf("\n=== CURRENT RANKINGS ===\n");
    for (int i = 0; i < t.count; i++)
    {
        printf("%d. %s (Rating: %d, Wins: %d)\n",
               i + 1, t.players[i].name, t.players[i].rating, t.players[i].wins);
    }
    printf("\n");
}

bool isFull(Tournament t)
{
    return t.count >= MAX_PLAYERS;
}

bool isEmpty(Tournament t)
{
    return t.count == 0;
}

// ========================================
// YOUR TASK: IMPLEMENT THESE FUNCTIONS
// ========================================

/*
 * Insert player maintaining sorted order by:
 * 1. Wins (descending) - higher wins rank first
 * 2. If wins equal, then by rating (descending)
 * 3. If both equal, alphabetical by name
 */
void insertPlayerRanked(Tournament *t, char name[], int rating, int wins)
{

    // make person
    Player newPlayer;

    // see if element of array in the struct matches with the params
    // had to create player type
    // i missed it somehow - probably an essential key step in most story problems
    strcpy(newPlayer.name, name);
    newPlayer.rating = rating;
    newPlayer.wins = wins;

    int i;

    for (i = 0; i < (t)->count && wins < (t)->players[i].wins; i++)
    {
    };

    if (i < t->count)
    {

        // shift right to make space
        int j;
        for (j = t->count; j > i; j--) // no need for i + 1 apparently--it already stops an index ahead of insertion point
        {
            t->players[j] = t->players[j - 1];
        }

        // three possible cases

        // alphabetical (does this have to happen first? the more conditions an if has, should it be the one checked first?)
        if (wins == (t)->players[i].wins && rating == (t)->players[i].rating)
        {
            printf("i is at %s | %d\n", t->players[i].name, i);
            if (strcmp(name, t->players[i].name) < 0)
            {
                
                t->players[i] = newPlayer; // bcs we shifted right
                
            }
            else
            {
                t->players[i + 1] =  t->players[i + 2];
                 t->players[i + 2] = newPlayer;
            }

             
        }

        else if (wins == (t)->players[i].wins)
        {
            if (rating < (t)->players[i].rating)
            {

                t->players[i] = t->players[i + 1];
                t->players[i + 1] = newPlayer;
            }
            else
            {
                t->players[i] = newPlayer;
            }
        }
        else
        {

            t->players[i] = newPlayer; // typical insert middle after shifting
        }
    }
    else
    {

        t->players[t->count] = newPlayer; // insert last
    }

    t->count++; // PLEASE REMEMBER TO INCREMENT THESE TYPES OF VARIABLES AT THE END
}

/*
 * Update a player's wins and re-rank them in the tournament
 * Find player by name, update wins, then move to correct position
 */
void updatePlayerWins(Tournament *t, char name[], int newWins)
{

    // function implementation reflection
    /*
        timet taken: 30-35 minutes, granted that I was doing commenting and being extra meticulous about my thought process
        determining the conditions of when and where to insert and delete respecitvely took the longest

        win:
        found that neat little optimization in the first for loop
        i said out loud "AT LEAST one of them has to be true before we stop traversing" and immediately linked it to the OR logical operator

        to improve on (late realizations):

        - edge case awareness
        inserting last if the player win is somehow updated to be the lowest (forgot the else statemet therefore newPos is remains as -1)


    */
    int currPos = -1;
    int newPos = -1;

    // what if you can traverse to find the player AND the new position?
    // you have to traverse up until count to find both so this is a one-condition trav
    // look and store for index of player (currPosition) but keep going till you find valid position (newPosition) for win count

    for (int i = 0; i < t->count && (currPos == -1 || newPos == -1); i++)
    { // optimization: if both positions are determined, we can end (realized this upon coding the if statements)

        if (newWins > t->players[i].wins) // if it gets compared with a win thats lower then it should go b4 i - 1 or just i??
        {
            newPos = i - 1;
        }
        else if (newWins == -1)
        {
            newPos = 0;
        }
        else
        {
            // goes  at the last index since we inserting by rank

            newPos = t->count - 1;
        }

        if (strcmp(name, t->players[i].name) == 0) // find curent position
        {
            currPos = i;
        }
    }
    // if that new index is not the same as current index

    if (newPos != currPos)
    {

        // store player in a temp for reinsertion
        Player temp = t->players[currPos];
        temp.wins = newWins;

        // delete current position of player  (shifting left from currPosition)
        for (int i = currPos; i < t->count; i++)
        {

            t->players[i] = t->players[i + 1];
        }

        // THEN reinsert player using newPosition
        // shift right from newPos, doesnt matter where (suuuurely)
        for (int j = t->count; j > newPos; j--)
        {
            t->players[j] = t->players[j - 1];
        }
        // insert the player in newPosition
        t->players[newPos] = temp;
    }

    // else do nothing (no updates happened at all)

    // change the player count
    // t->count++; // IT'S JUST UPDATE  NO NEED TO ADD HAHAHA
}
/*
 * Remove the lowest ranked player (last in array)
 * This happens when tournament is full and a new player wants to join
 */
void removeLowestRanked(Tournament *t)
{
    // TODO: Remove last player if tournament not empty

    if (!isEmpty(*t))
    {
        // this is a simple delete last, it's funny that i didnt notice this when i was doing the previous function
        // only possible if all players were inserted using insertSorted function
        t->count--;
    }
    else
    {
        printf("There are no players!\n");
    }
}

// ========================================
// MAIN FUNCTION (PROVIDED - DO NOT MODIFY)
// ========================================

int main()
{
    Tournament tournament;
    initTournament(&tournament);

    printf("🏆 CHESS TOURNAMENT RANKING SYSTEM 🏆\n");
    printf("=====================================\n");

    // Test Case 1: Insert into empty tournament
    printf("Test 1 - Insert into empty tournament:\n");
    insertPlayerRanked(&tournament, "Magnus", 2800, 5);
    displayRankings(tournament);
    /* Expected rankings after Test 1:
       === CURRENT RANKINGS ===
       1. Magnus (Rating: 2800, Wins: 5)
    */

    // Test Case 2: Multi-criteria sorting
    printf("Test 2 - Multi-criteria insertion:\n");
    insertPlayerRanked(&tournament, "Hikaru", 2750, 6);  // Higher wins
    insertPlayerRanked(&tournament, "Fabiano", 2780, 4); // Lower wins
    insertPlayerRanked(&tournament, "Ding", 2790, 4);    // Same wins, higher rating
    insertPlayerRanked(&tournament, "Arjun", 2780, 4);   // Same wins, same rating (alphabetical)
    displayRankings(tournament);
    /* Expected rankings after Test 2:
       === CURRENT RANKINGS ===
       1. Hikaru (Rating: 2750, Wins: 6)
       2. Magnus (Rating: 2800, Wins: 5)
       3. Ding (Rating: 2790, Wins: 4)
       4. Arjun (Rating: 2780, Wins: 4)
       5. Fabiano (Rating: 2780, Wins: 4)
    */

    // Test Case 3: Update to become highest ranked
    printf("Test 3 - Update player to top rank:\n");
    updatePlayerWins(&tournament, "Magnus", 8);
    displayRankings(tournament);
    /* Expected rankings after Test 3:
       1. Magnus (Rating: 2800, Wins: 8)
       2. Hikaru (Rating: 2750, Wins: 6)
       3. Ding (Rating: 2790, Wins: 4)
       4. Arjun (Rating: 2780, Wins: 4)
       5. Fabiano (Rating: 2780, Wins: 4)
    */

    // Test Case 4: Update to become lowest ranked
    printf("Test 4 - Update player to bottom rank:\n");
    updatePlayerWins(&tournament, "Hikaru", 1);
    displayRankings(tournament);
    /* Expected rankings after Test 4:
       1. Magnus (Rating: 2800, Wins: 8)
       2. Ding (Rating: 2790, Wins: 4)
       3. Arjun (Rating: 2780, Wins: 4)
       4. Fabiano (Rating: 2780, Wins: 4)
       5. Hikaru (Rating: 2750, Wins: 1)
    */

    // Test Case 5: Update with no position change
    printf("Test 5 - Update with no rank change:\n");
    updatePlayerWins(&tournament, "Ding", 4); // Same wins
    displayRankings(tournament);
    /* Expected rankings after Test 5 (no change from Test 4):
       1. Magnus (Rating: 2800, Wins: 8)
       2. Ding (Rating: 2790, Wins: 4)
       3. Arjun (Rating: 2780, Wins: 4)
       4. Fabiano (Rating: 2780, Wins: 4)
       5. Hikaru (Rating: 2750, Wins: 1)
    */

    // Test Case 6: Edge case - identical wins/ratings
    printf("Test 6 - Identical stats (alphabetical test):\n");
    insertPlayerRanked(&tournament, "Alireza", 2780, 4);
    insertPlayerRanked(&tournament, "Boris", 2780, 4);
    displayRankings(tournament);
    /* Expected rankings after Test 6:
       1. Magnus (Rating: 2800, Wins: 8)
       2. Ding (Rating: 2790, Wins: 4)
       3. Alireza (Rating: 2780, Wins: 4)
       4. Arjun (Rating: 2780, Wins: 4)
       5. Boris (Rating: 2780, Wins: 4)
       6. Fabiano (Rating: 2780, Wins: 4)
       7. Hikaru (Rating: 2750, Wins: 1)
    */

    // Test Case 7: Remove operations
    printf("Test 7 - Remove lowest ranked:\n");
    removeLowestRanked(&tournament);
    displayRankings(tournament);
    /* Expected rankings after Test 7 (after removing lowest):
       1. Magnus (Rating: 2800, Wins: 8)
       2. Ding (Rating: 2790, Wins: 4)
       3. Alireza (Rating: 2780, Wins: 4)
       4. Arjun (Rating: 2780, Wins: 4)
       5. Boris (Rating: 2780, Wins: 4)
       6. Fabiano (Rating: 2780, Wins: 4)
    */

    printf("Test 8 - Remove from empty (should handle gracefully):\n");
    Tournament empty;
    initTournament(&empty);
    removeLowestRanked(&empty);
    /* Expected behavior for Test 8:
       Operation is handled gracefully with no crash.
       If the implementation prints a message on empty removal, it may output:
       "There are no players!"
       Then the following line will print:
       "Empty tournament removal completed."
    */
    printf("Empty tournament removal completed.\n");

    return 0;
}