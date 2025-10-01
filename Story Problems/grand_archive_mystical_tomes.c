/*
 * Story Problem: The Grand Archive of Mystical Tomes
 * 
 * In the ancient Kingdom of Algorithmia, the Grand Archive houses thousands of mystical 
 * tomes, each containing powerful spells and incantations. The Head Librarian, Master 
 * Hashenwick, has devised an ingenious cataloging system to quickly locate any tome 
 * within the vast circular library halls.
 * 
 * Each tome is identified by a unique Scroll ID (a positive integer), and contains 
 * important metadata: the tome's title, the author's name, the magical power level,
 * and the number of pages. Due to the circular nature of the library halls, when 
 * a shelf position is occupied, the librarians must walk clockwise to find the next 
 * available shelf using Master Hashenwick's "Sequential Seeking Spell."
 * 
 * The Grand Archive has exactly 23 shelf positions (numbered 0-22), and the 
 * librarians have observed that some tomes seem to mysteriously vanish over time 
 * (marked as "cursed" rather than truly removed, to maintain the seeking spell's 
 * integrity). When scholars request a tome, they must provide the exact Scroll ID, 
 * and the librarians will follow the same path used during cataloging.
 * 
 * Your task is to implement the Grand Archive's mystical cataloging system with 
 * the following enchantments:
 * 
 * 1. **Tome Registration Enchantment**: Add a new tome to the archive
 * 2. **Tome Banishment Enchantment**: Mark a tome as cursed (but keep its shelf marker)
 * 3. **Tome Seeking Enchantment**: Locate a specific tome by its Scroll ID
 * 4. **Archive Viewing Enchantment**: Display the current state of all shelves
 * 5. **Power Level Analysis Enchantment**: Find all tomes within a power level range
 * 6. **Author Collection Enchantment**: List all tomes by a specific author
 * 
 * Master Hashenwick's hashing formula is known to use the "Digital Essence Extraction":
 * He takes the first digit, last digit, and middle digit of the Scroll ID, combines 
 * them using mystical weights, and applies modular arithmetic to determine the 
 * initial shelf position.
 * 
 * The Grand Archive starts with some pre-existing tomes that have been cataloged 
 * for centuries. Some of these ancient tomes have been lost to time and marked as cursed.
 * 
 * ADDITIONAL CHALLENGES:
 * - Handle duplicate Scroll IDs gracefully
 * - Implement overflow handling when the archive is full
 * - Create a statistics function showing archive utilization
 * - Add validation for tome data (positive power levels, non-empty strings)
 * - Implement a "reorganization" function that removes all cursed entries
 * 
 * Test your implementation with the provided ancient tome collection and demonstrate 
 * all enchantments working correctly, including edge cases like seeking non-existent 
 * tomes and handling a full archive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVE_SIZE 23      // Total shelf positions in the Grand Archive
#define MAX_TITLE_LEN 50     // Maximum length for tome titles
#define MAX_AUTHOR_LEN 30    // Maximum length for author names
#define EMPTY_SHELF -1       // Indicator for empty shelf
#define CURSED_TOME -2       // Indicator for banished tome (tombstone)

typedef enum {
    FALSE = 0,
    TRUE = 1
} Boolean;

typedef struct {
    int scrollID;                     // Unique identifier for the tome
    char title[MAX_TITLE_LEN];        // Title of the mystical tome
    char author[MAX_AUTHOR_LEN];      // Author of the tome
    int powerLevel;                   // Magical power level (1-1000)
    int pageCount;                    // Number of pages in the tome
} MysticalTome;

typedef struct {
    MysticalTome tome;                // The actual tome data
    int status;                       // EMPTY_SHELF, CURSED_TOME, or scrollID
} ShelfPosition;

typedef ShelfPosition GrandArchive[ARCHIVE_SIZE];

// Function prototypes - The Mystical Enchantments
void initializeArchive(GrandArchive archive);
int calculateShelfPosition(int scrollID);
Boolean registerTome(GrandArchive archive, MysticalTome newTome);
Boolean banishTome(GrandArchive archive, int scrollID);
Boolean seekTome(GrandArchive archive, int scrollID, MysticalTome* foundTome);
void displayArchive(GrandArchive archive);
void analyzePowerLevels(GrandArchive archive, int minPower, int maxPower);
void listAuthorCollection(GrandArchive archive, const char* authorName);
void displayArchiveStatistics(GrandArchive archive);
Boolean isValidTome(MysticalTome tome);
void reorganizeArchive(GrandArchive archive);

// Helper function prototypes
int getDigitCount(int number);
int getNthDigit(int number, int position);
void printTomeDetails(MysticalTome tome, int shelfPosition, int searchLength);

int main() {
    GrandArchive archive;
    initializeArchive(archive);
    
    printf("=== Welcome to the Grand Archive of Mystical Tomes ===\n");
    printf("Master Hashenwick's Cataloging System v2.3\n\n");
    
    // Ancient tomes that have existed in the archive for centuries
    MysticalTome ancientTomes[] = {
        {1247, "Flame Conjuration Compendium", "Ignis Pyromancer", 750, 342},
        {3891, "Whispers of the Shadow Realm", "Umbra Darkmage", 920, 156},
        {5623, "Healing Light Manuscripts", "Luna Lifebringer", 480, 289},
        {7834, "Temporal Manipulation Theory", "Chronos Timekeeper", 995, 421},
        {2156, "Elemental Harmony Studies", "Terra Earthsong", 670, 378},
        {9012, "Mind Reading Fundamentals", "Mentis Thoughtweaver", 820, 203},
        {4578, "Weather Control Practices", "Ventus Stormcaller", 710, 367},
        {8345, "Necromantic Arts Codex", "Mortis Soulbinder", 980, 445},
        {6729, "Illusion Mastery Guide", "Phantasm Dreamshaper", 590, 234},
        {1893, "Crystal Magic Principles", "Crystallis Gemheart", 640, 312}
    };
    
    printf("--- Cataloging Ancient Tomes ---\n");
    int ancientCount = sizeof(ancientTomes) / sizeof(MysticalTome);
    for (int i = 0; i < ancientCount; i++) {
        if (registerTome(archive, ancientTomes[i])) {
            printf("✓ Cataloged: %s (ID: %d)\n", ancientTomes[i].title, ancientTomes[i].scrollID);
        } else {
            printf("✗ Failed to catalog: %s (ID: %d)\n", ancientTomes[i].title, ancientTomes[i].scrollID);
        }
    }
    
    printf("\n--- Current Archive State ---\n");
    displayArchive(archive);
    
    printf("\n--- Banishing Some Ancient Tomes (They've become too dangerous) ---\n");
    int toBanish[] = {3891, 8345, 1893};  // Shadow, Necromantic, and Crystal magic
    for (int i = 0; i < 3; i++) {
        if (banishTome(archive, toBanish[i])) {
            printf("⚡ Successfully banished tome with ID: %d\n", toBanish[i]);
        } else {
            printf("✗ Could not find tome to banish: %d\n", toBanish[i]);
        }
    }
    
    printf("\n--- Archive State After Banishments ---\n");
    displayArchive(archive);
    
    printf("\n--- Adding New Contemporary Tomes ---\n");
    MysticalTome newTomes[] = {
        {2468, "Modern Potion Brewing", "Alchemis Newage", 350, 180},
        {1357, "Digital Divination Methods", "Techno Oraclesmith", 420, 156},
        {9876, "Quantum Spell Mechanics", "Physics Magebane", 890, 523}
    };
    
    int newCount = sizeof(newTomes) / sizeof(MysticalTome);
    for (int i = 0; i < newCount; i++) {
        if (registerTome(archive, newTomes[i])) {
            printf("✓ Added: %s (ID: %d)\n", newTomes[i].title, newTomes[i].scrollID);
        } else {
            printf("✗ Failed to add: %s (ID: %d)\n", newTomes[i].title, newTomes[i].scrollID);
        }
    }
    
    printf("\n--- Final Archive Display ---\n");
    displayArchive(archive);
    displayArchiveStatistics(archive);
    
    printf("\n--- Seeking Specific Tomes ---\n");
    int searchIDs[] = {1247, 3891, 2468, 9999};  // Mix of existing, banished, and non-existent
    for (int i = 0; i < 4; i++) {
        MysticalTome found;
        if (seekTome(archive, searchIDs[i], &found)) {
            printf("🔍 Found tome %d: %s by %s\n", searchIDs[i], found.title, found.author);
        } else {
            printf("❌ Tome %d not found in archive\n", searchIDs[i]);
        }
    }
    
    printf("\n--- Power Level Analysis (500-800 range) ---\n");
    analyzePowerLevels(archive, 500, 800);
    
    printf("\n--- Author Collection Search ---\n");
    listAuthorCollection(archive, "Ignis Pyromancer");
    listAuthorCollection(archive, "Nonexistent Author");
    
    // Bonus: Try to add duplicate
    printf("\n--- Attempting to Add Duplicate Tome ---\n");
    MysticalTome duplicate = {1247, "Duplicate Flame Book", "Fake Author", 100, 50};
    if (!registerTome(archive, duplicate)) {
        printf("✓ Correctly rejected duplicate Scroll ID: %d\n", duplicate.scrollID);
    }
    
    return 0;
}


// PRINT FUNCTIONS! DO NOT MODIFY!
void displayArchive(GrandArchive archive) {
    for (int i = 0; i < ARCHIVE_SIZE; i++) {
        ShelfPosition *pos = &archive[i];
        if (pos->status == EMPTY_SHELF) {
            printf("%4d | %-11s | %-9s | %-24s | %-20s | %-5s | %-5s\n",
                   i, "Empty", "-", "-", "-", "-", "-");
        } else if (pos->status == CURSED_TOME) {
            printf("%4d | %-11s | %-9s | %-24s | %-20s | %-5s | %-5s\n",
                   i, "Cursed", "-", "-", "-", "-", "-");
        } else {
            printTomeDetails(pos->tome, i, 0);
        }
    }
}

void printTomeDetails(MysticalTome tome, int shelfPosition, int searchLength) {
    // searchLength is unused here, but could be used for probe stats
    printf("%4d | %-11s | %9d | %-24s | %-20s | %5d | %5d\n",
           shelfPosition, "Occupied", tome.scrollID,
           tome.title, tome.author, tome.powerLevel, tome.pageCount);
}



// TODO: Implement all the enchantment functions
// Your task is to implement each function according to the story requirements
// Remember to handle edge cases and maintain the mystical theme in your output messages!

void initializeArchive(GrandArchive archive) {
    // TODO: Initialize all shelf positions to empty
}

int calculateShelfPosition(int scrollID) {
    // TODO: Implement Master Hashenwick's Digital Essence Extraction
    // Use first digit, last digit, and middle digit with mystical weights
    return 0; // placeholder
}

Boolean registerTome(GrandArchive archive, MysticalTome newTome) {
    // TODO: Implement tome registration with collision handling
    

    // simply insertintoDictri
    return FALSE; // placeholder
}

Boolean banishTome(GrandArchive archive, int scrollID) {
    // TODO: Mark tome as cursed (tombstone)
    return FALSE; // placeholder
}

Boolean seekTome(GrandArchive archive, int scrollID, MysticalTome* foundTome) {
    // TODO: Follow the same probe sequence as registration
    return FALSE; // placeholder
}


void analyzePowerLevels(GrandArchive archive, int minPower, int maxPower) {
    // TODO: Find and display all tomes within the power level range
}

void listAuthorCollection(GrandArchive archive, const char* authorName) {
    // TODO: List all tomes by the specified author
}

void displayArchiveStatistics(GrandArchive archive) {
    // TODO: Show archive utilization statistics
}

Boolean isValidTome(MysticalTome tome) {
    // TODO: Validate tome data
    return FALSE; // placeholder
}

void reorganizeArchive(GrandArchive archive) {
    // TODO: Remove all cursed entries and reinsert remaining tomes
}

// Helper functions
int getDigitCount(int number) {
    // TODO: Count digits in number
    return 0; // placeholder
}

int getNthDigit(int number, int position) {
    // TODO: Extract nth digit from number (1-indexed)
    return 0; // placeholder
}

