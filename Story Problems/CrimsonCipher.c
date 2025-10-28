/*
 * =====================================================================================
 *
 *       Filename:  CrimsonCipher.c
 *
 *    Description: Story problem for set operations.
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// You can define your Set data structure and functions here.
// Or, if you're feeling brave, you can implement them in a separate header file.
// Just don't make a mess.

int main() {
    // --- The Story ---
    /*
     * The year is 2048. You're a junior data forensics analyst at a megacorp,
     * and it's been a bad day. The corporation's central authentication server,
     * codenamed "Aegis," has been breached. The attacker, known only as "Crimson,"
     * left behind a digital mess.
     *
     * Your team has managed to capture two fragmented data logs from the time of the
     * intrusion. These logs, Log A and Log B, contain streams of user ID numbers
     * that accessed critical systems. The logs are noisy and full of duplicate entries.
     *
     * Your mission, should you choose to accept it (and you will, because you need
     * to pay rent), is to analyze these two logs and report back to your superior.
     *
     * She needs four key pieces of information, and she needs them yesterday:
     *
     * 1.  "The Overlap": A list of user IDs that appear in BOTH Log A and Log B.
     *     These are your primary suspects.
     *
     * 2.  "The Ghosts": A list of user IDs that appear ONLY in Log A. These could be
     *     compromised accounts used as the initial entry point.
     *
     * 3.  "The Echoes": A list of user IDs that appear ONLY in Log B. The attacker
     *     might have pivoted to these accounts after the initial breach.
     *
     * 4.  "The Blast Radius": The TOTAL number of unique user IDs involved across
     *     both logs. This will help determine the full scope of the incident.
     *
     * The raw data streams are provided below. Your task is to process them
     * using set operations to find the answers. No brute-forcing with nested loops
     * like a caveman. Think efficiently. Think sets.
    */

    int logA[] = {101, 202, 303, 404, 202, 505, 606, 101, 808, 909};
    int sizeA = sizeof(logA) / sizeof(logA);

    int logB[] = {202, 404, 606, 808, 111, 222, 333, 202, 404, 101};
    int sizeB = sizeof(logB) / sizeof(logB);

    printf("--- Aegis Server Breach Report ---\n");
    printf("Log A raw count: %d\n", sizeA);
    printf("Log B raw count: %d\n", sizeB);
    printf("----------------------------------\n\n");

    // Your implementation goes here.
    // 1. Create two sets, one for each log. Remember to handle duplicates.
    // 2. Compute the intersection ("The Overlap").
    // 3. Compute the difference A - B ("The Ghosts").
    // 4. Compute the difference B - A ("The Echoes").
    // 5. Compute the union and find its size ("The Blast Radius").
    // 6. Print your results clearly.

    printf("Analysis complete. Now, get me those numbers before I lose my patience.\n");

    return 0;
}