/*
========================================
PROBLEM 2: The Titan Regiment's Formation Cipher
Difficulty: ★★★★★ (Hard)
Topic: Computer Word Set Operations (Multi-Bit Manipulation with Masking Patterns)
StoryFlavor: anime (Attack on Titan inspired)
========================================

Story:

Commander Erwin Smith has devised a new encrypted communication system for the Survey Corps. 
Each soldier's position in formation is encoded as an 8-bit value, where:
- Bits 0-2: Squad ID (0-7)
- Bits 3-5: Flank Position (0-7: Center, Left, Right, Rear, Vanguard, etc.)
- Bits 6-7: Titan Threat Level (0-3: None, Low, Medium, High)

During the expedition beyond Wall Maria, the regiment must rapidly decode formation 
data, perform real-time threat analysis, and coordinate squad movements using only 
bitwise operations (no division, modulo, or array lookups—ODM gear comms are minimal).

Your mission as Hange's tactical analyst is to implement the cipher operations.

**Operations Required:**

1. **encodePosition(squadID, flankPos, threatLevel)**: Pack three values into a single 
   8-bit formation code
   - squadID: 3 bits (0-2)
   - flankPos: 3 bits (3-5)
   - threatLevel: 2 bits (6-7)

2. **decodeSquadID(formationCode)**: Extract squad ID from bits 0-2

3. **decodeFlankPosition(formationCode)**: Extract flank position from bits 3-5

4. **decodeThreatLevel(formationCode)**: Extract threat level from bits 6-7

5. **updateThreatLevel(formationCode, newThreatLevel)**: Replace threat level bits 
   without affecting squad/flank data (bit masking + insertion)

6. **swapSquadAndFlank(formationCode)**: Exchange the 3-bit squad ID and 3-bit flank 
   position values while preserving threat level

7. **aggregateThreatMap(formations[], count)**: Given an array of formation codes, 
   create a threat summary where each 2-bit pair represents the MAX threat level 
   seen at each flank position (0-7). Return as a 16-bit value (8 positions × 2 bits each).

8. **mirrorFormation(formationCode)**: Reverse all 8 bits (defensive retreat pattern)

========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char FORMATION_CODE;  // 8-bit soldier position encoding


/*

1. **encodePosition(squadID, flankPos, threatLevel)**: Pack three values into a single 
   8-bit formation code
   - squadID: 3 bits (0-2)
   - flankPos: 3 bits (3-5)
   - threatLevel: 2 bits (6-7)

*/
FORMATION_CODE encodePosition(int squadID, int flankPos, int threatLevel){
    // Mask each input to its specified bit width to prevent overflow
    FORMATION_CODE squad_masked = squadID & 0b111;      // 3 bits for squad (0-7)
    FORMATION_CODE flank_masked = flankPos & 0b111;      // 3 bits for flank (0-7)
    FORMATION_CODE threat_masked = threatLevel & 0b11;  // 2 bits for threat (0-3)

    // Shift each masked value into its correct position and combine with OR
    // SSS is at bits 0-2 (no shift)
    // FFF is at bits 3-5 (shift by 3)
    // TT is at bits 6-7 (shift by 6)
    return (threat_masked << 6) | (flank_masked << 3) | squad_masked;
}


int decodeSquadID(FORMATION_CODE code){
    // Squad ID is in bits 0-2. Just mask to extract.
    return code & 0b111;
}

int decodeFlankPosition(FORMATION_CODE code){
    // Flank position is in bits 3-5. Shift right by 3, then mask.
    return (code >> 3) & 0b111;
}

int decodeThreatLevel(FORMATION_CODE code){
    // Threat level is in bits 6-7. Shift right by 6, then mask.
    return (code >> 6) & 0b11;
}

/*
5. **updateThreatLevel(formationCode, newThreatLevel)**: Replace threat level bits 
   without affecting squad/flank data (bit masking + insertion)
*/
FORMATION_CODE updateThreatLevel(FORMATION_CODE code, int newThreatLevel){
    // 1. Create a mask to clear out the old threat level bits (bits 6-7).
    //    This is the inverse of the threat mask shifted into position.
    FORMATION_CODE clear_mask = ~(0b11 << 6);

    // 2. Mask the new threat level to ensure it's only 2 bits.
    FORMATION_CODE new_threat_masked = newThreatLevel & 0b11;

    // 3. Clear the threat bits in the original code, then OR in the new shifted threat.
    return (code & clear_mask) | (new_threat_masked << 6);
}

FORMATION_CODE swapSquadAndFlank(FORMATION_CODE code){
    // 1. Extract all three components using the decode functions
    int squad = decodeSquadID(code);
    int flank = decodeFlankPosition(code);
    int threat = decodeThreatLevel(code);

    // 2. Re-encode them with squad and flank swapped, preserving threat
    return encodePosition(flank, squad, threat);
}

unsigned short aggregateThreatMap(FORMATION_CODE formations[], int count){
    // Phase 1: Initialize storage for max threat per flank
    int max_threats_per_flank[8] = {0}; // Initializes all to 0

    // Phase 2: Iterate through formations and update the max threats
    for (int i = 0; i < count; i++) {
        FORMATION_CODE current_code = formations[i];
        int flank = decodeFlankPosition(current_code);
        int threat = decodeThreatLevel(current_code);

        if (threat > max_threats_per_flank[flank]) {
            max_threats_per_flank[flank] = threat;
        }
    }

    // Phase 3: Pack the results into a 16-bit unsigned short
    unsigned short threatMap = 0;
    for (int i = 0; i < 8; i++) {
        // Shift the 2-bit threat value into the correct 2-bit slot (i * 2)
        threatMap |= (max_threats_per_flank[i] << (i * 2));
    }

    return threatMap;
}

FORMATION_CODE mirrorFormation(FORMATION_CODE code){
    FORMATION_CODE result = 0;

    // Loop 8 times for an 8-bit char
    for (int i = 0; i < 8; i++) {
        // Get the last bit of the input code
        FORMATION_CODE lastBit = code & 1;

        // Make space in the result by shifting left
        result = result << 1;

        // Add the new bit to the end of the result
        result |= lastBit;

        // Move to the next bit of the input by shifting right
        code = code >> 1;
    }
    return result;
}

// --- Helper Functions (Already Implemented) ---
void displayBinary8(FORMATION_CODE code, const char* label) {
    printf("%s: ", label);
    for(int i = 7; i >= 0; i--) {
        printf("%d", (code >> i) & 1);
        if(i == 6 || i == 3) printf("|");
    }
    printf(" (Decimal: %u, Hex: 0x%02X)\n", code, code);
    printf("        TT|FFF|SSS  [T=Threat, F=Flank, S=Squad]\n");
}

void displayBinary16(unsigned short value, const char* label) {
    printf("%s: ", label);
    for(int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if(i % 2 == 0 && i != 0) printf("|");
    }
    printf(" (Hex: 0x%04X)\n", value);
}

const char* threatLevelName(int level) {
    switch(level) {
        case 0: return "None";
        case 1: return "Low";
        case 2: return "Medium";
        case 3: return "High";
        default: return "Invalid";
    }
}

const char* flankName(int flank) {
    const char* names[] = {"Center", "Left", "Right", "Rear", "Vanguard", "LeftRear", "RightRear", "Scout"};
    return (flank >= 0 && flank < 8) ? names[flank] : "Unknown";
}

// --- Main Function (Test Cases) ---
int main() {
    printf("========================================\n");
    printf("SURVEY CORPS - FORMATION CIPHER SYSTEM\n");
    printf("Commander Erwin: 'Soldiers, prepare for deployment!'\n");
    printf("========================================\n\n");
    
    printf("--- Test Case 1: Encoding Positions ---\n");
    FORMATION_CODE soldier1 = encodePosition(3, 1, 2);  // Squad 3, Left Flank, Medium Threat
    displayBinary8(soldier1, "Soldier #1 Encoded");
    printf("  Decoded: Squad %d, Flank %s, Threat %s\n", 
           decodeSquadID(soldier1), flankName(decodeFlankPosition(soldier1)), 
           threatLevelName(decodeThreatLevel(soldier1)));
    // Expected Output:
    //   Soldier #1 Encoded: 10|001|011 (Decimal: 139, Hex: 0x8B)
    //   Decoded: Squad 3, Flank Left, Threat Medium
    
    FORMATION_CODE soldier2 = encodePosition(7, 4, 3);  // Squad 7, Vanguard, High Threat
    displayBinary8(soldier2, "Soldier #2 Encoded");
    printf("  Decoded: Squad %d, Flank %s, Threat %s\n", 
           decodeSquadID(soldier2), flankName(decodeFlankPosition(soldier2)), 
           threatLevelName(decodeThreatLevel(soldier2)));
    // Expected Output:
    //   Soldier #2 Encoded: 11|100|111 (Decimal: 231, Hex: 0xE7)
    //   Decoded: Squad 7, Flank Vanguard, Threat High
    
    printf("\n--- Test Case 2: Decoding Individual Fields ---\n");
    FORMATION_CODE testCode = 0b01011010;  // 90
    displayBinary8(testCode, "Test Formation Code");
    printf("  Squad ID: %d\n", decodeSquadID(testCode));
    printf("  Flank Position: %s (%d)\n", flankName(decodeFlankPosition(testCode)), decodeFlankPosition(testCode));
    printf("  Threat Level: %s (%d)\n", threatLevelName(decodeThreatLevel(testCode)), decodeThreatLevel(testCode));
    // Expected Output:
    //   Squad ID: 2
    //   Flank Position: Left (1)
    //   Threat Level: Low (1)
    
    printf("\n--- Test Case 3: Updating Threat Level (In-Place) ---\n");
    FORMATION_CODE original = encodePosition(5, 3, 0);  // Squad 5, Rear, No Threat
    displayBinary8(original, "Original Formation");
    
    FORMATION_CODE updated = updateThreatLevel(original, 3);  // Escalate to High Threat
    displayBinary8(updated, "After Threat Update");
    printf("  Squad/Flank preserved: Squad %d, Flank %s\n", 
           decodeSquadID(updated), flankName(decodeFlankPosition(updated)));
    printf("  New Threat: %s\n", threatLevelName(decodeThreatLevel(updated)));
    // Expected Output:
    //   After Threat Update: 11|011|101 (Decimal: 221, Hex: 0xDD)
    //   Squad/Flank preserved: Squad 5, Flank Rear
    //   New Threat: High
    
    printf("\n--- Test Case 4: Squad-Flank Swap (Tactical Redeployment) ---\n");
    FORMATION_CODE beforeSwap = encodePosition(2, 6, 1);  // Squad 2, RightRear, Low Threat
    displayBinary8(beforeSwap, "Before Swap");
    printf("  Original: Squad %d, Flank %s\n", 
           decodeSquadID(beforeSwap), flankName(decodeFlankPosition(beforeSwap)));
    
    FORMATION_CODE afterSwap = swapSquadAndFlank(beforeSwap);
    displayBinary8(afterSwap, "After Swap");
    printf("  Swapped: Squad %d, Flank %s (Threat preserved: %s)\n", 
           decodeSquadID(afterSwap), flankName(decodeFlankPosition(afterSwap)), 
           threatLevelName(decodeThreatLevel(afterSwap)));
    // Expected Output:
    //   After Swap: 01|010|110 (Decimal: 86, Hex: 0x56)
    //   Swapped: Squad 6, Flank Left (Threat preserved: Low)
    
    printf("\n--- Test Case 5: Aggregate Threat Map (Strategic Overview) ---\n");
    FORMATION_CODE regiment[] = {
        encodePosition(1, 0, 2),  // Center: Medium threat
        encodePosition(2, 0, 3),  // Center: High threat (max)
        encodePosition(3, 1, 1),  // Left: Low threat
        encodePosition(4, 1, 2),  // Left: Medium threat (max)
        encodePosition(5, 4, 3),  // Vanguard: High threat
        encodePosition(6, 4, 2),  // Vanguard: Medium threat (max is High)
    };
    int count = sizeof(regiment) / sizeof(regiment[0]);
    
    printf("Regiment Formation Data (%d soldiers):\n", count);
    for(int i = 0; i < count; i++) {
        printf("  Soldier %d: Squad %d, Flank %s, Threat %s\n", 
               i+1, decodeSquadID(regiment[i]), 
               flankName(decodeFlankPosition(regiment[i])), 
               threatLevelName(decodeThreatLevel(regiment[i])));
    }
    
    unsigned short threatMap = aggregateThreatMap(regiment, count);
    displayBinary16(threatMap, "Aggregate Threat Map");
    printf("  [Each 2-bit pair = max threat at flank 0-7]\n");
    printf("  Flank 0 (Center): %s\n", threatLevelName((threatMap >> 0) & 0b11));
    printf("  Flank 1 (Left): %s\n", threatLevelName((threatMap >> 2) & 0b11));
    printf("  Flank 4 (Vanguard): %s\n", threatLevelName((threatMap >> 8) & 0b11));
    // Expected Output:
    //   Flank 0 (Center): High (3)
    //   Flank 1 (Left): Medium (2)
    //   Flank 4 (Vanguard): High (3)
    
    printf("\n--- Test Case 6: Formation Mirroring (Defensive Retreat) ---\n");
    FORMATION_CODE attackFormation = encodePosition(1, 4, 3);  // Squad 1, Vanguard, High
    displayBinary8(attackFormation, "Attack Formation");
    
    FORMATION_CODE retreatFormation = mirrorFormation(attackFormation);
    displayBinary8(retreatFormation, "Mirrored Retreat Formation");
    printf("  Mirrored: Squad %d, Flank %s, Threat %s\n", 
           decodeSquadID(retreatFormation), flankName(decodeFlankPosition(retreatFormation)), 
           threatLevelName(decodeThreatLevel(retreatFormation)));
    // Expected Output:
    //   Mirrored Retreat Formation: 11|101|000 (bit-reversed pattern)
    
    printf("\n--- Test Case 7: Edge Case - All Zeros ---\n");
    FORMATION_CODE zeroCode = encodePosition(0, 0, 0);
    displayBinary8(zeroCode, "Zero Formation");
    FORMATION_CODE zeroSwapped = swapSquadAndFlank(zeroCode);
    displayBinary8(zeroSwapped, "Zero Formation Swapped");
    printf("  Should remain identical: %s\n", (zeroCode == zeroSwapped) ? "PASS" : "FAIL");
    
    printf("\n--- Test Case 8: Edge Case - All Ones ---\n");
    FORMATION_CODE maxCode = encodePosition(7, 7, 3);  // Max values
    displayBinary8(maxCode, "Max Formation");
    FORMATION_CODE maxUpdated = updateThreatLevel(maxCode, 0);
    displayBinary8(maxUpdated, "Max Formation (Threat Cleared)");
    printf("  Threat cleared to: %s\n", threatLevelName(decodeThreatLevel(maxUpdated)));
    
    printf("\n========================================\n");
    printf("FORMATION CIPHER SYSTEM TEST COMPLETE\n");
    printf("Hange: 'Fascinating! The cipher holds perfectly!'\n");
    printf("========================================\n");
    
    return 0;
}
