/*
========================================
PROBLEM 1: The Cipher Division's Encrypted Access Logs
Difficulty: ★★★★☆ (Medium-Hard)
Topic: Computer Word Set Operations (Bit Extraction & Reconstruction)
StoryFlavor: anime (Steins;Gate inspired)
========================================

Story:

Deep in the Future Gadget Laboratory's secure vault, Daru has discovered corrupted 
access logs from SERN's network intrusion attempts. Each log entry is stored as a 
16-bit unsigned short integer, where bits represent timestamps of unauthorized access 
attempts across 16 critical time slots (0-15).

However, SERN's countermeasure system scrambled the logs using a multi-layer obfuscation:
1. Access patterns are XOR-encrypted with a rotating key
2. Certain bit ranges must be extracted and analyzed separately
3. Logs must be merged back after decryption for timeline reconstruction

Daru needs your help to implement forensic analysis operations:

**Operations Required:**

1. **extractBitRange(log, startBit, endBit)**: Extract a contiguous range of bits 
   from a 16-bit log and return them as a new unsigned short (shifted to LSB position)
   - Example: log = 0b1010110011001100, extractBitRange(log, 4, 7) → 0b0000000000001001

2. **reconstructLog(highByte, lowByte)**: Combine two 8-bit values into a single 
   16-bit log entry (highByte in upper 8 bits, lowByte in lower 8 bits)

3. **decryptWithKey(encryptedLog, key)**: XOR the log with a rotating key pattern
   
4. **countSuspiciousSlots(log1, log2, log3)**: Find time slots where ALL three logs 
   show activity (multi-log intersection)

5. **isolateAnomalies(primaryLog, baselinePattern)**: Find time slots active in 
   primaryLog but NOT in baselinePattern (set difference)

6. **bitRotateLeft(log, positions)**: Circular left shift of bits 
   (e.g., rotating 0b0000000000001101 left by 2 → 0b0000000000110100)

========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned short LOG_ENTRY;  // 16-bit access log

// TODO: Implement these functions

/*
1. **extractBitRange(log, startBit, endBit)**: Extract a contiguous range of bits 
   from a 16-bit log and return them as a new unsigned short (shifted to LSB position)
   - Example: log = 0b1010110011001100, extractBitRange(log, 4, 7) → 0b0000000000001001
*/
LOG_ENTRY extractBitRange(LOG_ENTRY log, int startBit, int endBit){


    
}
LOG_ENTRY reconstructLog(unsigned char highByte, unsigned char lowByte);
LOG_ENTRY decryptWithKey(LOG_ENTRY encryptedLog, LOG_ENTRY key);
LOG_ENTRY countSuspiciousSlots(LOG_ENTRY log1, LOG_ENTRY log2, LOG_ENTRY log3);
LOG_ENTRY isolateAnomalies(LOG_ENTRY primaryLog, LOG_ENTRY baselinePattern);
LOG_ENTRY bitRotateLeft(LOG_ENTRY log, int positions);

// --- Helper Functions (Already Implemented) ---
void displayBinary16(LOG_ENTRY log, const char* label) {
    printf("%s: ", label);
    for(int i = 15; i >= 0; i--) {
        printf("%d", (log >> i) & 1);
        if(i == 8) printf(" ");
    }
    printf(" (Decimal: %u, Hex: 0x%04X)\n", log, log);
}

int countActiveBits(LOG_ENTRY log) {
    int count = 0;
    for(int i = 0; i < 16; i++) {
        if((log >> i) & 1) count++;
    }
    return count;
}

// --- Main Function (Test Cases) ---
int main() {
    printf("========================================\n");
    printf("FUTURE GADGET LAB - SERN ACCESS LOG FORENSICS\n");
    printf("Daru's Note: 'Time to crack SERN's obfuscation, nyan~'\n");
    printf("========================================\n\n");
    
    printf("--- Test Case 1: Bit Range Extraction ---\n");
    LOG_ENTRY sampleLog = 0b1010110011001100;  // 44236
    displayBinary16(sampleLog, "Original Log");
    
    LOG_ENTRY extracted = extractBitRange(sampleLog, 4, 7);
    displayBinary16(extracted, "Bits [4-7] Extracted");
    // Expected Output:
    //   Bits [4-7] Extracted: 0000000000001100 (Decimal: 12, Hex: 0x000C)
    
    LOG_ENTRY extracted2 = extractBitRange(sampleLog, 8, 11);
    displayBinary16(extracted2, "Bits [8-11] Extracted");
    // Expected Output:
    //   Bits [8-11] Extracted: 0000000000001001 (Decimal: 9, Hex: 0x0009)
    
    printf("\n--- Test Case 2: Log Reconstruction ---\n");
    unsigned char highByte = 0b10101100;  // 172
    unsigned char lowByte = 0b11001100;   // 204
    LOG_ENTRY reconstructed = reconstructLog(highByte, lowByte);
    displayBinary16(reconstructed, "Reconstructed Log");
    // Expected Output:
    //   Reconstructed Log: 1010110011001100 (Decimal: 44236, Hex: 0xACCC)
    
    printf("\n--- Test Case 3: XOR Decryption ---\n");
    LOG_ENTRY encryptedLog = 0b1100110010101010;  // 52394
    LOG_ENTRY key = 0b1010101010101010;           // 43690
    displayBinary16(encryptedLog, "Encrypted Log");
    displayBinary16(key, "Decryption Key");
    
    LOG_ENTRY decrypted = decryptWithKey(encryptedLog, key);
    displayBinary16(decrypted, "Decrypted Result");
    // Expected Output:
    //   Decrypted Result: 0110011000000000 (Decimal: 26112, Hex: 0x6600)
    
    printf("\n--- Test Case 4: Multi-Log Suspicious Slot Detection ---\n");
    LOG_ENTRY log1 = 0b0000111111110000;  // 4080
    LOG_ENTRY log2 = 0b0000110011110000;  // 3312
    LOG_ENTRY log3 = 0b0000111100110000;  // 3888
    
    displayBinary16(log1, "SERN Log A");
    displayBinary16(log2, "SERN Log B");
    displayBinary16(log3, "SERN Log C");
    
    LOG_ENTRY suspicious = countSuspiciousSlots(log1, log2, log3);
    displayBinary16(suspicious, "Slots Active in ALL Logs");
    printf("  → %d time slots flagged as critical overlap\n", countActiveBits(suspicious));
    // Expected Output:
    //   Slots Active in ALL Logs: 0000110000110000 (Decimal: 3120, Hex: 0x0C30)
    //   → 4 time slots flagged as critical overlap
    
    printf("\n--- Test Case 5: Anomaly Isolation ---\n");
    LOG_ENTRY primaryLog = 0b1111000011110000;    // 61680
    LOG_ENTRY baselinePattern = 0b0011000011000000; // 12480
    
    displayBinary16(primaryLog, "Primary Access Log");
    displayBinary16(baselinePattern, "Baseline Pattern");
    
    LOG_ENTRY anomalies = isolateAnomalies(primaryLog, baselinePattern);
    displayBinary16(anomalies, "Isolated Anomalies");
    printf("  → %d anomalous time slots detected\n", countActiveBits(anomalies));
    // Expected Output:
    //   Isolated Anomalies: 1100000000110000 (Decimal: 49200, Hex: 0xC030)
    //   → 4 anomalous time slots detected
    
    printf("\n--- Test Case 6: Bit Rotation for Pattern Matching ---\n");
    LOG_ENTRY pattern = 0b0000000000001101;  // 13
    displayBinary16(pattern, "Original Pattern");
    
    LOG_ENTRY rotated2 = bitRotateLeft(pattern, 2);
    displayBinary16(rotated2, "Rotated Left by 2");
    // Expected Output:
    //   Rotated Left by 2: 0000000000110100 (Decimal: 52, Hex: 0x0034)
    
    LOG_ENTRY rotated8 = bitRotateLeft(pattern, 8);
    displayBinary16(rotated8, "Rotated Left by 8");
    // Expected Output:
    //   Rotated Left by 8: 0000110100000000 (Decimal: 3328, Hex: 0x0D00)
    
    printf("\n--- Test Case 7: Edge Case - Full Rotation ---\n");
    LOG_ENTRY fullRotate = bitRotateLeft(pattern, 16);
    displayBinary16(fullRotate, "Rotated Left by 16 (Full Circle)");
    // Expected Output:
    //   Rotated Left by 16 (Full Circle): 0000000000001101 (Decimal: 13, Hex: 0x000D)
    
    printf("\n--- Test Case 8: Complex Forensic Workflow ---\n");
    // Scenario: Extract middle byte, decrypt it, check for anomalies
    LOG_ENTRY suspectLog = 0b1110011010100101;  // 58789
    displayBinary16(suspectLog, "Suspect Log (Full)");
    
    LOG_ENTRY middleByte = extractBitRange(suspectLog, 4, 11);
    displayBinary16(middleByte, "Middle Byte Extracted [4-11]");
    
    LOG_ENTRY decryptKey = 0b0000000011111111;  // 255
    LOG_ENTRY decryptedMiddle = decryptWithKey(middleByte, decryptKey);
    displayBinary16(decryptedMiddle, "Decrypted Middle Byte");
    
    LOG_ENTRY baseline = 0b0000000001010000;  // 80
    LOG_ENTRY finalAnomalies = isolateAnomalies(decryptedMiddle, baseline);
    displayBinary16(finalAnomalies, "Final Anomalies After Decryption");
    printf("  → Forensic analysis complete: %d suspicious bits remain\n", countActiveBits(finalAnomalies));
    // Expected Output:
    //   Final Anomalies After Decryption: 0000000010000101 (depends on decryption result)
    
    printf("\n========================================\n");
    printf("FORENSIC ANALYSIS COMPLETE\n");
    printf("Daru: 'Got 'em. SERN's encryption is child's play.'\n");
    printf("========================================\n");
    
    return 0;
}
