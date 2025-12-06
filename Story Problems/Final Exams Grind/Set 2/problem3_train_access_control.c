/*
========================================
PROBLEM 3: The Train Line Access Control System
Difficulty: ★★★★☆ (Medium-Hard)
Topic: Computer Word Set Operations (Advanced Bit Manipulation with Masking)
========================================

Story:

At Tokyo Metro's central operations center, senior engineer Tanaka-san oversees an 8-line 
access control system for JR Pass holders. Each of the 8 train lines (Yamanote, Chuo, 
Sobu, Keihin-Tohoku, Shonan-Shinjuku, Saikyo, Yokosuka, Narita Express) is represented 
by a bit position (0-7) in a compact access badge register.

Three categories of passengers hold different access privileges:

- Local Commuters: Lines {0, 1, 2, 3} (inner-city routes)
- Express Travelers: Lines {2, 3, 4, 5, 6} (rapid transit + suburbs)
- Airport Shuttles: Lines {6, 7} (Narita/Haneda connections)

A system upgrade requires implementing complex access validation logic:

1. **Restricted Zone Detection**: Lines accessible to Express but FORBIDDEN to Local 
   (security-critical rapid routes)

2. **Universal Access Verification**: Lines available to ALL three passenger types 
   (core infrastructure)

3. **Priority Lane Extraction**: Given a bitmask of "premium service" lines, extract 
   which lines are accessible to Express travelers AND match the premium criteria

4. **Selective Revocation**: Remove specific line access from a passenger's badge 
   (complementary masking operation)

5. **Cascade Union**: Merge all three passenger type registers into a master "All Lines" 
   register, then determine which lines are NOT covered by any pass type (maintenance gaps)

The system uses bitwise operations for microsecond-level validation at ticket gates.

========================================
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char ACCESS_BADGE;

// TODO: Implement these functions
ACCESS_BADGE restrictedZoneDetection(ACCESS_BADGE express, ACCESS_BADGE local);
ACCESS_BADGE universalAccessVerification(ACCESS_BADGE local, ACCESS_BADGE express, ACCESS_BADGE airport);
ACCESS_BADGE priorityLaneExtraction(ACCESS_BADGE express, ACCESS_BADGE premiumMask);
ACCESS_BADGE selectiveRevocation(ACCESS_BADGE badge, ACCESS_BADGE revokeLines);
ACCESS_BADGE cascadeUnion(ACCESS_BADGE local, ACCESS_BADGE express, ACCESS_BADGE airport);
ACCESS_BADGE maintenanceGaps(ACCESS_BADGE allLines);

// --- Helper Functions (Already Implemented) ---
void initBadge(ACCESS_BADGE *badge) {
    *badge = 0;
}

void grantLineAccess(ACCESS_BADGE *badge, int lineID) {
    if(lineID >= 0 && lineID < 8) {
        *badge |= (1 << lineID);
    }
}

int hasLineAccess(ACCESS_BADGE badge, int lineID) {
    return (badge & (1 << lineID)) != 0;
}

void displayBadge(ACCESS_BADGE badge, const char* name) {
    printf("%s: { ", name);
    int first = 1;
    for(int i = 0; i < 8; i++) {
        if(hasLineAccess(badge, i)) {
            if(!first) printf(", ");
            printf("Line%d", i);
            first = 0;
        }
    }
    printf(" }\n");
}

void displayBinary(ACCESS_BADGE badge) {
    printf("  Binary: ");
    for(int i = 7; i >= 0; i--) {
        printf("%d", hasLineAccess(badge, i) ? 1 : 0);
        if(i == 4) printf(" ");
    }
    printf(" (Decimal: %d)\n", badge);
}

const char* lineNames[8] = {
    "Yamanote", "Chuo", "Sobu", "Keihin-Tohoku",
    "Shonan-Shinjuku", "Saikyo", "Yokosuka", "Narita Express"
};

void displayLines(ACCESS_BADGE badge) {
    printf("  Lines: ");
    int count = 0;
    for(int i = 0; i < 8; i++) {
        if(hasLineAccess(badge, i)) {
            if(count > 0) printf(", ");
            printf("%s", lineNames[i]);
            count++;
        }
    }
    if(count == 0) printf("(none)");
    printf("\n");
}

// --- Main Function (Test Cases) ---
int main() {
    ACCESS_BADGE local, express, airport, premium;
    
    printf("========================================\n");
    printf("TOKYO METRO - TRAIN LINE ACCESS CONTROL ANALYSIS\n");
    printf("========================================\n\n");
    
    initBadge(&local);
    initBadge(&express);
    initBadge(&airport);
    initBadge(&premium);
    
    printf("--- Test Case 1: Passenger Access Profiles ---\n");
    
    // Local Commuters: Lines 0, 1, 2, 3
    grantLineAccess(&local, 0);
    grantLineAccess(&local, 1);
    grantLineAccess(&local, 2);
    grantLineAccess(&local, 3);
    
    // Express Travelers: Lines 2, 3, 4, 5, 6
    grantLineAccess(&express, 2);
    grantLineAccess(&express, 3);
    grantLineAccess(&express, 4);
    grantLineAccess(&express, 5);
    grantLineAccess(&express, 6);
    
    // Airport Shuttles: Lines 6, 7
    grantLineAccess(&airport, 6);
    grantLineAccess(&airport, 7);
    
    // Premium Service Mask: Lines 3, 4, 5, 6, 7
    grantLineAccess(&premium, 3);
    grantLineAccess(&premium, 4);
    grantLineAccess(&premium, 5);
    grantLineAccess(&premium, 6);
    grantLineAccess(&premium, 7);
    
    printf("Local Commuters Badge:\n");
    displayBadge(local, "  ");
    displayBinary(local);
    displayLines(local);
    // Expected Output:
    //   : { Line0, Line1, Line2, Line3 }
    //   Binary: 0000 1111 (Decimal: 15)
    //   Lines: Yamanote, Chuo, Sobu, Keihin-Tohoku
    
    printf("\nExpress Travelers Badge:\n");
    displayBadge(express, "  ");
    displayBinary(express);
    displayLines(express);
    // Expected Output:
    //   : { Line2, Line3, Line4, Line5, Line6 }
    //   Binary: 0111 1100 (Decimal: 124)
    //   Lines: Sobu, Keihin-Tohoku, Shonan-Shinjuku, Saikyo, Yokosuka
    
    printf("\nAirport Shuttles Badge:\n");
    displayBadge(airport, "  ");
    displayBinary(airport);
    displayLines(airport);
    // Expected Output:
    //   : { Line6, Line7 }
    //   Binary: 1100 0000 (Decimal: 192)
    //   Lines: Yokosuka, Narita Express
    
    printf("\nPremium Service Mask:\n");
    displayBadge(premium, "  ");
    displayBinary(premium);
    displayLines(premium);
    // Expected Output:
    //   : { Line3, Line4, Line5, Line6, Line7 }
    //   Binary: 1111 1000 (Decimal: 248)
    //   Lines: Keihin-Tohoku, Shonan-Shinjuku, Saikyo, Yokosuka, Narita Express
    
    printf("\n--- Test Case 2: Restricted Zone Detection ---\n");
    printf("Lines accessible to Express but FORBIDDEN to Local:\n");
    ACCESS_BADGE restricted = restrictedZoneDetection(express, local);
    displayBadge(restricted, "  ");
    displayBinary(restricted);
    displayLines(restricted);
    // Expected Output:
    //   : { Line4, Line5, Line6 }
    //   Binary: 0111 0000 (Decimal: 112)
    //   Lines: Shonan-Shinjuku, Saikyo, Yokosuka
    
    printf("\n--- Test Case 3: Universal Access Verification ---\n");
    printf("Lines available to ALL three passenger types:\n");
    ACCESS_BADGE universal = universalAccessVerification(local, express, airport);
    displayBadge(universal, "  ");
    displayBinary(universal);
    displayLines(universal);
    // Expected Output:
    //   : { }
    //   Binary: 0000 0000 (Decimal: 0)
    //   Lines: (none)
    
    printf("\n--- Test Case 4: Priority Lane Extraction ---\n");
    printf("Express lines that match Premium Service criteria:\n");
    ACCESS_BADGE priority = priorityLaneExtraction(express, premium);
    displayBadge(priority, "  ");
    displayBinary(priority);
    displayLines(priority);
    // Expected Output:
    //   : { Line3, Line4, Line5, Line6 }
    //   Binary: 0111 1000 (Decimal: 120)
    //   Lines: Keihin-Tohoku, Shonan-Shinjuku, Saikyo, Yokosuka
    
    printf("\n--- Test Case 5: Selective Revocation ---\n");
    ACCESS_BADGE revokeLines;
    initBadge(&revokeLines);
    grantLineAccess(&revokeLines, 2);
    grantLineAccess(&revokeLines, 4);
    printf("Revoking Lines {2, 4} from Express badge:\n");
    ACCESS_BADGE revoked = selectiveRevocation(express, revokeLines);
    displayBadge(revoked, "  ");
    displayBinary(revoked);
    displayLines(revoked);
    // Expected Output:
    //   : { Line3, Line5, Line6 }
    //   Binary: 0110 1000 (Decimal: 104)
    //   Lines: Keihin-Tohoku, Saikyo, Yokosuka
    
    printf("\n--- Test Case 6: Cascade Union (All Lines Merge) ---\n");
    printf("Master register of ALL accessible lines:\n");
    ACCESS_BADGE allLines = cascadeUnion(local, express, airport);
    displayBadge(allLines, "  ");
    displayBinary(allLines);
    displayLines(allLines);
    // Expected Output:
    //   : { Line0, Line1, Line2, Line3, Line4, Line5, Line6, Line7 }
    //   Binary: 1111 1111 (Decimal: 255)
    //   Lines: Yamanote, Chuo, Sobu, Keihin-Tohoku, Shonan-Shinjuku, Saikyo, Yokosuka, Narita Express
    
    printf("\n--- Test Case 7: Maintenance Gaps Detection ---\n");
    printf("Lines NOT covered by any pass type (requires full 8-line complement):\n");
    ACCESS_BADGE gaps = maintenanceGaps(allLines);
    displayBadge(gaps, "  ");
    displayBinary(gaps);
    displayLines(gaps);
    // Expected Output:
    //   : { }
    //   Binary: 0000 0000 (Decimal: 0)
    //   Lines: (none)
    
    printf("\n--- Test Case 8: Partial Coverage Scenario ---\n");
    ACCESS_BADGE partialLocal;
    initBadge(&partialLocal);
    grantLineAccess(&partialLocal, 0);
    grantLineAccess(&partialLocal, 2);
    
    ACCESS_BADGE partialExpress;
    initBadge(&partialExpress);
    grantLineAccess(&partialExpress, 4);
    grantLineAccess(&partialExpress, 6);
    
    ACCESS_BADGE partialAirport;
    initBadge(&partialAirport);
    grantLineAccess(&partialAirport, 7);
    
    printf("Partial coverage scenario (Local={0,2}, Express={4,6}, Airport={7}):\n");
    ACCESS_BADGE partialUnion = cascadeUnion(partialLocal, partialExpress, partialAirport);
    ACCESS_BADGE partialGaps = maintenanceGaps(partialUnion);
    displayBadge(partialGaps, "  ");
    displayBinary(partialGaps);
    displayLines(partialGaps);
    // Expected Output:
    //   : { Line1, Line3, Line5 }
    //   Binary: 0010 1010 (Decimal: 42)
    //   Lines: Chuo, Keihin-Tohoku, Saikyo
    
    printf("\n========================================\n");
    printf("ACCESS CONTROL ANALYSIS COMPLETE\n");
    printf("Tanaka-san's Log: 'Bit precision ensures zero gate failures.'\n");
    printf("========================================\n");
    
    return 0;
}
