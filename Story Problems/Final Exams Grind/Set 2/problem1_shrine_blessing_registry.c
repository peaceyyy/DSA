/*
========================================
PROBLEM 1: The Shrine Blessing Registry
Difficulty: ★★☆☆☆ (Easy-Medium)
Topic: Computer Word Set Operations (Basic Bitwise Practice)
========================================

Story:

At the ancient Tsukimori Shrine in rural Kyoto, the head priestess Ayame-san maintains 
a blessing registry for eight sacred festivals throughout the year. Each festival is 
represented by a position (0-7), and shrine visitors receive blessing marks indicating 
which festivals they've attended.

Two visitors arrive seeking marriage compatibility blessings:

- Haruto: Attended festivals at positions {1, 3, 5, 7} (odd-numbered festivals)
- Sakura: Attended festivals at positions {1, 2, 3, 6} (spring and summer festivals)

Ayame-san must determine:
1. Which festivals BOTH visitors attended (shared blessings)
2. Which festivals ONLY Haruto attended (his unique path)
3. Festivals attended by EITHER visitor (combined experience)
4. Festivals Haruto has NOT attended (missing blessings)
5. Whether Sakura's festival attendance is contained within Haruto's path

The shrine's ancient records use a compact 8-bit encoding system where each bit 
represents a festival. Your task is to implement the ritual analysis operations.

========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BLESSING_MARK;

// TODO: Implement these functions
BLESSING_MARK sharedBlessings(BLESSING_MARK haruto, BLESSING_MARK sakura);
BLESSING_MARK uniquePath(BLESSING_MARK haruto, BLESSING_MARK sakura);
BLESSING_MARK combinedExperience(BLESSING_MARK haruto, BLESSING_MARK sakura);
BLESSING_MARK missingBlessings(BLESSING_MARK haruto);
int isPathContained(BLESSING_MARK container, BLESSING_MARK subset);

// --- Helper Functions (Already Implemented) ---
void initMark(BLESSING_MARK *mark) {
    *mark = 0;
}

void attendFestival(BLESSING_MARK *mark, int festivalID) {
    if(festivalID >= 0 && festivalID < 8) {
        *mark |= (1 << festivalID);
    }
}

int hasAttended(BLESSING_MARK mark, int festivalID) {
    return (mark & (1 << festivalID)) != 0;
}

void displayMark(BLESSING_MARK mark, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < 8; i++) {
        if(hasAttended(mark, i)) {
            if(!first) printf(", ");
            printf("Festival%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

void displayBinary(BLESSING_MARK mark) {
    printf("  Binary: ");
    for(int i = 7; i >= 0; i--) {
        printf("%d", hasAttended(mark, i) ? 1 : 0);
        if(i == 4) printf(" ");
    }
    printf(" (Decimal: %d)\n", mark);
}

const char* festivalNames[8] = {
    "New Year", "Spring Equinox", "Cherry Blossom", "Summer Solstice",
    "Autumn Harvest", "Moon Viewing", "Winter Solstice", "Year-End Purification"
};

void displayFestivalNames(BLESSING_MARK mark) {
    printf("  Festivals: ");
    int count = 0;
    for(int i = 0; i < 8; i++) {
        if(hasAttended(mark, i)) {
            if(count > 0) printf(", ");
            printf("%s", festivalNames[i]);
            count++;
        }
    }
    if(count == 0) printf("(none)");
    printf("\n");
}

// --- Main Function (Test Cases) ---
int main() {
    BLESSING_MARK haruto, sakura, emptyMark;
    
    printf("========================================\n");
    printf("TSUKIMORI SHRINE - BLESSING COMPATIBILITY ANALYSIS\n");
    printf("========================================\n\n");
    
    initMark(&haruto);
    initMark(&sakura);
    initMark(&emptyMark);
    
    printf("--- Test Case 1: Visitor Registry ---\n");
    
    // Haruto: Festivals 1, 3, 5, 7 (odd-numbered)
    attendFestival(&haruto, 1);
    attendFestival(&haruto, 3);
    attendFestival(&haruto, 5);
    attendFestival(&haruto, 7);
    
    // Sakura: Festivals 1, 2, 3, 6 (spring/summer)
    attendFestival(&sakura, 1);
    attendFestival(&sakura, 2);
    attendFestival(&sakura, 3);
    attendFestival(&sakura, 6);
    
    printf("Haruto's Blessing Mark:\n");
    displayMark(haruto, "  ");
    displayBinary(haruto);
    displayFestivalNames(haruto);
    // Expected Output:
    //   : { Festival1, Festival3, Festival5, Festival7 }
    //   Binary: 1010 1010 (Decimal: 170)
    //   Festivals: Spring Equinox, Summer Solstice, Moon Viewing, Year-End Purification
    
    printf("\nSakura's Blessing Mark:\n");
    displayMark(sakura, "  ");
    displayBinary(sakura);
    displayFestivalNames(sakura);
    // Expected Output:
    //   : { Festival1, Festival2, Festival3, Festival6 }
    //   Binary: 0100 1110 (Decimal: 78)
    //   Festivals: Spring Equinox, Cherry Blossom, Summer Solstice, Winter Solstice
    
    printf("\n--- Test Case 2: Shared Blessings ---\n");
    printf("Festivals BOTH attended:\n");
    BLESSING_MARK shared = sharedBlessings(haruto, sakura);
    displayMark(shared, "  ");
    displayBinary(shared);
    displayFestivalNames(shared);
    // Expected Output:
    //   : { Festival1, Festival3 }
    //   Binary: 0000 1010 (Decimal: 10)
    //   Festivals: Spring Equinox, Summer Solstice
    
    printf("\n--- Test Case 3: Haruto's Unique Path ---\n");
    printf("Festivals ONLY Haruto attended:\n");
    BLESSING_MARK unique = uniquePath(haruto, sakura);
    displayMark(unique, "  ");
    displayBinary(unique);
    displayFestivalNames(unique);
    // Expected Output:
    //   : { Festival5, Festival7 }
    //   Binary: 1010 0000 (Decimal: 160)
    //   Festivals: Moon Viewing, Year-End Purification
    
    printf("\n--- Test Case 4: Combined Experience ---\n");
    printf("Festivals attended by EITHER visitor:\n");
    BLESSING_MARK combined = combinedExperience(haruto, sakura);
    displayMark(combined, "  ");
    displayBinary(combined);
    displayFestivalNames(combined);
    // Expected Output:
    //   : { Festival1, Festival2, Festival3, Festival5, Festival6, Festival7 }
    //   Binary: 1110 1110 (Decimal: 238)
    //   Festivals: Spring Equinox, Cherry Blossom, Summer Solstice, Moon Viewing, Winter Solstice, Year-End Purification
    
    printf("\n--- Test Case 5: Haruto's Missing Blessings ---\n");
    printf("Festivals Haruto has NOT attended:\n");
    BLESSING_MARK missing = missingBlessings(haruto);
    displayMark(missing, "  ");
    displayBinary(missing);
    displayFestivalNames(missing);
    // Expected Output:
    //   : { Festival0, Festival2, Festival4, Festival6 }
    //   Binary: 0101 0101 (Decimal: 85)
    //   Festivals: New Year, Cherry Blossom, Autumn Harvest, Winter Solstice
    
    printf("\n--- Test Case 6: Path Containment Analysis ---\n");
    printf("Is Sakura's path contained within Haruto's? ");
    if(isPathContained(haruto, sakura)) {
        printf("YES\n");
    } else {
        printf("NO\n");
        printf("  → Sakura attended festivals Haruto did not.\n");
    }
    // Expected Output:
    // NO
    //   → Sakura attended festivals Haruto did not.
    
    printf("\n--- Test Case 7: Edge Case - Empty Mark ---\n");
    printf("Is an empty blessing mark contained in Haruto's path? ");
    if(isPathContained(haruto, emptyMark)) {
        printf("YES (vacuous truth)\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // YES (vacuous truth)
    
    printf("\n========================================\n");
    printf("COMPATIBILITY ANALYSIS COMPLETE\n");
    printf("Ayame-san's Blessing: 'Shared festivals reveal harmony.'\n");
    printf("========================================\n");
    
    return 0;
}
