/*
========================================
PROBLEM 2: The Arcade High Score Ledger Challenge
Difficulty: ★★★☆☆ (Medium)
Topic: Computer Word Set Operations (Multi-Register Bitwise Analysis)
========================================

Story:

In the neon-lit basement of Akihabara's legendary "Pixel Palace" arcade, store manager 
Kenji maintains an 8-bit achievement ledger system for tracking player milestones across 
different game cabinets. Each bit position (0-7) represents a specific achievement rank.

Four gaming regulars compete for bragging rights this month:

- Ryota: The rhythm game specialist (achievements at positions {0, 2, 4, 6})
- Yuki: The fighting game champion (achievements at positions {1, 2, 5, 6})
- Hana: The puzzle game prodigy (achievements at positions {2, 3, 6, 7})
- Takeshi: The shmup (shoot-em-up) ace (achievements at positions {2, 6})

Kenji needs to analyze the achievement patterns to determine:
1. "Universal Elite" - achievements earned by ALL four players
2. "Exclusive Mastery" - achievements earned by EITHER Ryota or Yuki, but NOT both
3. "Combined Legacy" - all achievements across any of the four players
4. "Mutual Gaps" - whether Ryota and Yuki have NO overlapping achievements
5. "Mentorship Check" - whether Takeshi's achievements are fully contained within Hana's

The arcade's legacy system uses compact 8-bit registers for efficient storage.

========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char ACHIEVEMENT_REGISTER;

// TODO: Implement these functions
ACHIEVEMENT_REGISTER universalElite(ACHIEVEMENT_REGISTER *players, int count){
    
    ACHIEVEMENT_REGISTER result = players[0];
    for (int i = 1; i < count; i++){

    result = result & players[i];
        
    }

    return result;

}
ACHIEVEMENT_REGISTER exclusiveMastery(ACHIEVEMENT_REGISTER ryota, ACHIEVEMENT_REGISTER yuki){
    return ryota ^ yuki;
}
ACHIEVEMENT_REGISTER combinedLegacy(ACHIEVEMENT_REGISTER *players, int count){
    ACHIEVEMENT_REGISTER result = players[0];
    for (int i = 1; i < count; i++){

    result = result | players[i];
        
    }

    return result;
}
int mutualGaps(ACHIEVEMENT_REGISTER ryota, ACHIEVEMENT_REGISTER yuki){

    return ((ryota & yuki) == 0) ? 1 : 0;
}
int mentorshipCheck(ACHIEVEMENT_REGISTER mentor, ACHIEVEMENT_REGISTER mentee){
    return ((mentor & mentee) == mentee) ? 1 : 0;
}

// --- Helper Functions (Already Implemented) ---
void initRegister(ACHIEVEMENT_REGISTER *reg) {
    *reg = 0;
}

void unlockAchievement(ACHIEVEMENT_REGISTER *reg, int achievementID) {
    if(achievementID >= 0 && achievementID < 8) {
        *reg |= (1 << achievementID);
    }
}

int hasAchievement(ACHIEVEMENT_REGISTER reg, int achievementID) {
    return (reg & (1 << achievementID)) != 0;
}

void displayRegister(ACHIEVEMENT_REGISTER reg, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < 8; i++) {
        if(hasAchievement(reg, i)) {
            if(!first) printf(", ");
            printf("Rank%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

void displayBinary(ACHIEVEMENT_REGISTER reg) {
    printf("  Binary: ");
    for(int i = 7; i >= 0; i--) {
        printf("%d", hasAchievement(reg, i) ? 1 : 0);
        if(i == 4) printf(" ");
    }
    printf(" (Decimal: %d)\n", reg);
}

const char* achievementNames[8] = {
    "Bronze Elite", "Silver Streak", "Gold Master", "Platinum Legend",
    "Diamond Soul", "Mythic Ascent", "Immortal Champion", "Godlike Domination"
};

void displayAchievements(ACHIEVEMENT_REGISTER reg) {
    printf("  Achievements: ");
    int count = 0;
    for(int i = 0; i < 8; i++) {
        if(hasAchievement(reg, i)) {
            if(count > 0) printf(", ");
            printf("%s", achievementNames[i]);
            count++;
        }
    }
    if(count == 0) printf("(none)");
    printf("\n");
}

// --- Main Function (Test Cases) ---
int main() {
    ACHIEVEMENT_REGISTER ryota, yuki, hana, takeshi;
    ACHIEVEMENT_REGISTER players[4];
    
    printf("========================================\n");
    printf("PIXEL PALACE ARCADE - HIGH SCORE LEDGER ANALYSIS\n");
    printf("========================================\n\n");
    
    initRegister(&ryota);
    initRegister(&yuki);
    initRegister(&hana);
    initRegister(&takeshi);
    
    printf("--- Test Case 1: Player Achievement Profiles ---\n");
    
    // Ryota (Rhythm): Ranks 0, 2, 4, 6
    unlockAchievement(&ryota, 0);
    unlockAchievement(&ryota, 2);
    unlockAchievement(&ryota, 4);
    unlockAchievement(&ryota, 6);
    
    // Yuki (Fighting): Ranks 1, 2, 5, 6
    unlockAchievement(&yuki, 1);
    unlockAchievement(&yuki, 2);
    unlockAchievement(&yuki, 5);
    unlockAchievement(&yuki, 6);
    
    // Hana (Puzzle): Ranks 2, 3, 6, 7
    unlockAchievement(&hana, 2);
    unlockAchievement(&hana, 3);
    unlockAchievement(&hana, 6);
    unlockAchievement(&hana, 7);
    
    // Takeshi (Shmup): Ranks 2, 6
    unlockAchievement(&takeshi, 2);
    unlockAchievement(&takeshi, 6);
    
    printf("Ryota (Rhythm Specialist):\n");
    displayRegister(ryota, "  ");
    displayBinary(ryota);
    displayAchievements(ryota);
    // Expected Output:
    //   : { Rank0, Rank2, Rank4, Rank6 }
    //   Binary: 0101 0101 (Decimal: 85)
    //   Achievements: Bronze Elite, Gold Master, Diamond Soul, Immortal Champion
    
    printf("\nYuki (Fighting Champion):\n");
    displayRegister(yuki, "  ");
    displayBinary(yuki);
    displayAchievements(yuki);
    // Expected Output:
    //   : { Rank1, Rank2, Rank5, Rank6 }
    //   Binary: 0110 0110 (Decimal: 102)
    //   Achievements: Silver Streak, Gold Master, Mythic Ascent, Immortal Champion
    
    printf("\nHana (Puzzle Prodigy):\n");
    displayRegister(hana, "  ");
    displayBinary(hana);
    displayAchievements(hana);
    // Expected Output:
    //   : { Rank2, Rank3, Rank6, Rank7 }
    //   Binary: 1100 1100 (Decimal: 204)
    //   Achievements: Gold Master, Platinum Legend, Immortal Champion, Godlike Domination
    
    printf("\nTakeshi (Shmup Ace):\n");
    displayRegister(takeshi, "  ");
    displayBinary(takeshi);
    displayAchievements(takeshi);
    // Expected Output:
    //   : { Rank2, Rank6 }
    //   Binary: 0100 0100 (Decimal: 68)
    //   Achievements: Gold Master, Immortal Champion
    
    players[0] = ryota;
    players[1] = yuki;
    players[2] = hana;
    players[3] = takeshi;
    
    printf("\n--- Test Case 2: Universal Elite Achievements ---\n");
    printf("Achievements earned by ALL four players:\n");
    ACHIEVEMENT_REGISTER elite = universalElite(players, 4);
    displayRegister(elite, "  ");
    displayBinary(elite);
    displayAchievements(elite);
    // Expected Output:
    //   : { Rank2, Rank6 }
    //   Binary: 0100 0100 (Decimal: 68)
    //   Achievements: Gold Master, Immortal Champion
    
    printf("\n--- Test Case 3: Exclusive Mastery (Ryota XOR Yuki) ---\n");
    printf("Achievements earned by EITHER Ryota or Yuki, but NOT both:\n");
    ACHIEVEMENT_REGISTER exclusive = exclusiveMastery(ryota, yuki);
    displayRegister(exclusive, "  ");
    displayBinary(exclusive);
    displayAchievements(exclusive);
    // Expected Output:
    //   : { Rank0, Rank1, Rank4, Rank5 }
    //   Binary: 0011 0011 (Decimal: 51)
    //   Achievements: Bronze Elite, Silver Streak, Diamond Soul, Mythic Ascent
    
    printf("\n--- Test Case 4: Combined Legacy (All Players Union) ---\n");
    printf("All achievements unlocked by any player:\n");
    ACHIEVEMENT_REGISTER legacy = combinedLegacy(players, 4);
    displayRegister(legacy, "  ");
    displayBinary(legacy);
    displayAchievements(legacy);
    // Expected Output:
    //   : { Rank0, Rank1, Rank2, Rank3, Rank4, Rank5, Rank6, Rank7 }
    //   Binary: 1111 1111 (Decimal: 255)
    //   Achievements: Bronze Elite, Silver Streak, Gold Master, Platinum Legend, Diamond Soul, Mythic Ascent, Immortal Champion, Godlike Domination
    
    printf("\n--- Test Case 5: Mutual Gaps Check (Ryota vs Yuki) ---\n");
    printf("Do Ryota and Yuki have NO overlapping achievements? ");
    if(mutualGaps(ryota, yuki)) {
        printf("YES (completely disjoint)\n");
    } else {
        printf("NO\n");
        printf("  → They share some achievements.\n");
    }
    // Expected Output:
    // NO
    //   → They share some achievements.
    
    printf("\n--- Test Case 6: Mentorship Validation (Hana mentoring Takeshi) ---\n");
    printf("Are all of Takeshi's achievements contained in Hana's set? ");
    if(mentorshipCheck(hana, takeshi)) {
        printf("YES\n");
        printf("  → Takeshi's progress is a subset of Hana's mastery.\n");
    } else {
        printf("NO\n");
    }
    // Expected Output:
    // YES
    //   → Takeshi's progress is a subset of Hana's mastery.
    
    printf("\n--- Test Case 7: Edge Case - Single Player Analysis ---\n");
    ACHIEVEMENT_REGISTER singlePlayer[1] = {ryota};
    ACHIEVEMENT_REGISTER singleElite = universalElite(singlePlayer, 1);
    printf("Universal elite for single player (Ryota):\n");
    displayRegister(singleElite, "  ");
    displayAchievements(singleElite);
    // Expected Output:
    //   : { Rank0, Rank2, Rank4, Rank6 }
    //   Achievements: Bronze Elite, Gold Master, Diamond Soul, Immortal Champion
    
    printf("\n========================================\n");
    printf("LEDGER ANALYSIS COMPLETE\n");
    printf("Kenji's Note: 'Shared mastery defines the arcade legends.'\n");
    printf("========================================\n");
    
    return 0;
}
