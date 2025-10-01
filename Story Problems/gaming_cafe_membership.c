/*
 * Story Problem: The Gaming Café Membership System
 * 
 * "Pixel Paradise Gaming Café" is a popular spot where gamers gather to play their 
 * favorite titles. The café owner, Maya, wants to track which gaming stations (numbered 0-9) 
 * are currently occupied by different types of memberships. She has three membership tiers:
 * 
 * - **Regular Members**: Basic gaming access
 * - **Premium Members**: Extended hours + special perks  
 * - **VIP Members**: All access + private tournament entry
 * 
 * Maya needs a simple system to help her staff manage daily operations. Each gaming 
 * station can either be occupied (1) or empty (0) for each membership type.
 * 
 * During peak hours, Maya wants to quickly answer questions like:
 * 
 * 1. "Which stations have both Regular AND Premium members?" (busy stations)
 * 2. "Which stations have Regular members but NOT VIP members?" (upgrade opportunities)  
 * 3. "Which stations are completely free from Premium members?" (available for promotions)
 * 4. "Are all the VIP stations also occupied by Premium members?" (service consistency check)
 * 5. "Which stations have ANY type of member?" (general occupancy)
 * 6. "Which stations have ONLY Regular members?" (basic service areas)
 * 
 * Maya has noticed some interesting patterns:
 * - Weekend rush: Stations 1,3,5,7,9 tend to fill with Regular members
 * - Premium cluster: Stations 2,4,6,8 are preferred by Premium members  
 * - VIP corner: Stations 7,8,9 are the VIP gaming zone
 * 
 * Your task is to help Maya by implementing her membership tracking system.
 * The system should handle these scenarios and provide clear answers to her questions.
 * 
 * **Sample Day Scenario:**
 * - Regular Members occupy: Stations 1, 3, 5, 7, 9
 * - Premium Members occupy: Stations 2, 4, 6, 7, 8  
 * - VIP Members occupy: Stations 7, 8, 9
 * 
 * Test your system with this scenario and make sure you can answer all of Maya's 
 * questions correctly. Pay attention to the subtle differences between each query!
 * 
 * **Bonus Challenge:** 
 * Maya also wants to know if her "VIP upgrade promotion" is working - that is, 
 * whether every station with a VIP member also has them registered as Premium 
 * (since VIP includes Premium benefits).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATIONS 10

typedef int MembershipSet[MAX_STATIONS];
typedef enum { FALSE = 0, TRUE = 1 } Boolean;

// Function prototypes
void initMembershipSet(MembershipSet set);
void displayMembershipSet(MembershipSet set, const char* membershipType);
void occupyStation(MembershipSet set, int stationNum);
void freeStation(MembershipSet set, int stationNum);
Boolean isStationOccupied(MembershipSet set, int stationNum);

// Set operations for membership analysis
MembershipSet* getBusyStations(MembershipSet regular, MembershipSet premium);




MembershipSet* getUpgradeOpportunities(MembershipSet regular, MembershipSet vip);

//Which stations have Regular members but NOT VIP members?" (upgrade opportunities)  


MembershipSet* getPromotionStations(MembershipSet premium);


Boolean checkServiceConsistency(MembershipSet vip, MembershipSet premium);




MembershipSet* getGeneralOccupancy(MembershipSet regular, MembershipSet premium, MembershipSet vip);
MembershipSet* getBasicServiceAreas(MembershipSet regular, MembershipSet premium, MembershipSet vip);

// Helper function
void printAnalysis(const char* analysisName, MembershipSet* result, Boolean isBoolean, Boolean boolResult);

int main() {
    printf("=== COMPREHENSIVE TEST SUITE FOR GAMING CAFÉ SYSTEM ===\n\n");
    
    // ========== TEST 1: Basic Function Tests ==========
    printf("TEST 1: Basic Function Tests\n");
    printf("================================\n");
    
    MembershipSet testSet;
    initMembershipSet(testSet);
    
    printf("After initialization:\n");
    displayMembershipSet(testSet, "Test");
    printf("\n// EXPECTED: Test Members: [0][0][0][0][0][0][0][0][0][0]\n\n");
    
    // Test occupyStation and isStationOccupied
    occupyStation(testSet, 3);
    occupyStation(testSet, 7);
    printf("After occupying stations 3 and 7:\n");
    displayMembershipSet(testSet, "Test");
    printf("\n// EXPECTED: Test Members: [0][0][0][1][0][0][0][1][0][0]\n");
    printf("Station 3 occupied? %s (EXPECTED: YES)\n", isStationOccupied(testSet, 3) ? "YES" : "NO");
    printf("Station 5 occupied? %s (EXPECTED: NO)\n", isStationOccupied(testSet, 5) ? "YES" : "NO");
    
    // Test freeStation
    freeStation(testSet, 3);
    printf("After freeing station 3:\n");
    displayMembershipSet(testSet, "Test");
    printf("\n// EXPECTED: Test Members: [0][0][0][0][0][0][0][1][0][0]\n\n");
    
    // ========== TEST 2: Story Problem Scenario ==========
    printf("TEST 2: Original Story Problem Scenario\n");
    printf("==========================================\n");
    
    MembershipSet regularMembers, premiumMembers, vipMembers;
    
    // Initialize all membership sets
    initMembershipSet(regularMembers);
    initMembershipSet(premiumMembers);
    initMembershipSet(vipMembers);
    
    // Regular Members: Stations 1, 3, 5, 7, 9 (weekend rush pattern)
    printf("Setting up: Regular at 1,3,5,7,9 | Premium at 2,4,6,7,8 | VIP at 7,8,9\n");
    occupyStation(regularMembers, 1);
    occupyStation(regularMembers, 3);
    occupyStation(regularMembers, 5);
    occupyStation(regularMembers, 7);
    occupyStation(regularMembers, 9);
    
    // Premium Members: Stations 2, 4, 6, 7, 8 (premium cluster + overlap)
    occupyStation(premiumMembers, 2);
    occupyStation(premiumMembers, 4);
    occupyStation(premiumMembers, 6);
    occupyStation(premiumMembers, 7);
    occupyStation(premiumMembers, 8);
    
    // VIP Members: Stations 7, 8, 9 (VIP corner)
    occupyStation(vipMembers, 7);
    occupyStation(vipMembers, 8);
    occupyStation(vipMembers, 9);
    
    printf("\n--- Current Status ---\n");
    displayMembershipSet(regularMembers, "Regular");
    printf("\n// EXPECTED: Regular Members: [0][1][0][1][0][1][0][1][0][1]\n");
    displayMembershipSet(premiumMembers, "Premium");
    printf("\n// EXPECTED: Premium Members: [0][0][1][0][1][0][1][1][1][0]\n");
    displayMembershipSet(vipMembers, "VIP");
    printf("\n// EXPECTED: VIP Members: [0][0][0][0][0][0][0][1][1][1]\n");
    
    // Test set operations with expected results
    printf("\n--- Set Operations Tests ---\n");
    
    // 1. Busy stations (Regular AND Premium) - Should be station 7 only
    MembershipSet* busyStations = getBusyStations(regularMembers, premiumMembers);
    printAnalysis("Busy Stations (Regular AND Premium)", busyStations, FALSE, FALSE);
    printf("// EXPECTED STATIONS: 7 (only station with both Regular and Premium)\n");
    
    // 2. Upgrade opportunities (Regular but NOT VIP) - Should be 1, 3, 5
    MembershipSet* upgradeOps = getUpgradeOpportunities(regularMembers, vipMembers);
    printAnalysis("Upgrade Opportunities (Regular but NOT VIP)", upgradeOps, FALSE, FALSE);
    printf("// EXPECTED STATIONS: 1 3 5 (Regular members without VIP upgrade)\n");
    
    // 3. Promotion stations (NOT Premium) - Should be 0, 1, 3, 5, 9
    MembershipSet* promoStations = getPromotionStations(premiumMembers);
    printAnalysis("Promotion Available Stations (NOT Premium)", promoStations, FALSE, FALSE);
    printf("// EXPECTED STATIONS: 0 1 3 5 9 (stations without Premium members)\n");
    
    // 4. Service consistency (All VIP also Premium?) - Should be YES
    Boolean consistency = checkServiceConsistency(vipMembers, premiumMembers);
    printAnalysis("Service Consistency (All VIP also Premium?)", NULL, TRUE, consistency);
    printf("// EXPECTED RESULT: YES (stations 7,8,9 have VIP and all also have Premium)\n");
    
    // 5. General occupancy (ANY member type) - Should be 1,2,3,4,5,6,7,8,9
    MembershipSet* anyOccupied = getGeneralOccupancy(regularMembers, premiumMembers, vipMembers);
    printAnalysis("General Occupancy (ANY member type)", anyOccupied, FALSE, FALSE);
    printf("// EXPECTED STATIONS: 1 2 3 4 5 6 7 8 9 (all occupied stations)\n");
    
    // 6. Basic service areas (ONLY Regular) - Should be 1, 3, 5
    MembershipSet* basicAreas = getBasicServiceAreas(regularMembers, premiumMembers, vipMembers);
    printAnalysis("Basic Service Areas (ONLY Regular)", basicAreas, FALSE, FALSE);
    printf("// EXPECTED STATIONS: 1 3 5 (Regular only, no Premium or VIP)\n");
    
    // ========== TEST 3: Edge Case Scenarios ==========
    printf("\nTEST 3: Edge Case Scenarios\n");
    printf("==============================\n");
    
    // Empty sets test
    MembershipSet emptySet1, emptySet2, emptySet3;
    initMembershipSet(emptySet1);
    initMembershipSet(emptySet2);
    initMembershipSet(emptySet3);
    
    printf("--- Test A: All Empty Sets ---\n");
    MembershipSet* emptyResult = getBusyStations(emptySet1, emptySet2);
    printAnalysis("Busy Stations (Empty AND Empty)", emptyResult, FALSE, FALSE);
    printf("// EXPECTED STATIONS: None\n");
    
    Boolean emptyConsistency = checkServiceConsistency(emptySet1, emptySet2);
    printf("Service Consistency (Empty VIP, Empty Premium): %s\n", emptyConsistency ? "YES" : "NO");
    printf("// EXPECTED RESULT: YES (vacuously true - no VIP to check)\n");
    
    // Single station tests
    printf("\n--- Test B: Single Station Scenarios ---\n");
    MembershipSet singleReg, singlePrem, singleVip;
    initMembershipSet(singleReg);
    initMembershipSet(singlePrem);
    initMembershipSet(singleVip);
    
    occupyStation(singleReg, 5);
    occupyStation(singlePrem, 5);
    occupyStation(singleVip, 3); // Different station for VIP
    
    MembershipSet* singleBusy = getBusyStations(singleReg, singlePrem);
    printAnalysis("Single Station Busy (Both at 5)", singleBusy, FALSE, FALSE);
    printf("// EXPECTED STATIONS: 5\n");
    
    Boolean singleConsistency = checkServiceConsistency(singleVip, singlePrem);
    printf("Service Consistency (VIP at 3, Premium at 5): %s\n", singleConsistency ? "YES" : "NO");
    printf("// EXPECTED RESULT: NO (VIP at station 3 but no Premium at station 3)\n");
    
    // All stations occupied test
    printf("\n--- Test C: All Stations Occupied ---\n");
    MembershipSet fullSet;
    initMembershipSet(fullSet);
    for(int i = 0; i < MAX_STATIONS; i++) {
        occupyStation(fullSet, i);
    }
    
    MembershipSet* fullPromo = getPromotionStations(fullSet);
    printAnalysis("Promotion Stations (All Premium Occupied)", fullPromo, FALSE, FALSE);
    printf("// EXPECTED STATIONS: None (all stations have Premium members)\n");
    
    printf("\n--- Test D: Boundary Station Tests ---\n");
    MembershipSet boundarySet;
    initMembershipSet(boundarySet);
    occupyStation(boundarySet, 0); // First station
    occupyStation(boundarySet, 9); // Last station
    
    displayMembershipSet(boundarySet, "Boundary Test");
    printf("\n// EXPECTED: Boundary Test Members: [1][0][0][0][0][0][0][0][0][1]\n");
    
    printf("\n=== END OF COMPREHENSIVE TESTING ===\n");
    printf("Review all outputs above and compare with expected results!\n");
    
    // Clean up all allocated memory
    free(busyStations);
    free(upgradeOps);
    free(promoStations);
    free(anyOccupied);
    free(basicAreas);
    free(emptyResult);
    free(singleBusy);
    free(fullPromo);
    
    return 0;
}

// TODO: Implement all the functions below
// Remember: Each function should solve one of Maya's questions
// Pay attention to the logical relationships between different membership types!

void initMembershipSet(MembershipSet set) {
    // TODO: Initialize all stations to unoccupied (0)

    for (int i = 0; i < MAX_STATIONS; i++){
        set[i] = 0;
    }
}

void displayMembershipSet(MembershipSet set, const char* membershipType) {
    // TODO: Display which stations are occupied for this membership type
    // Format: "Regular Members: [0][1][0][1][0][1][0][1][0][1]"
    
    printf("\n%s Members: ", membershipType);
    for (int i = 0; i < MAX_STATIONS; i++){
        printf("[%d]", set[i]);
    }
}


void occupyStation(MembershipSet set, int stationNum) {
    // TODO: Mark a station as occupied for this membership type

    set[stationNum] = 1;
}

void freeStation(MembershipSet set, int stationNum) {
    // TODO: Mark a station as free for this membership type
    set[stationNum] = 0;
}

Boolean isStationOccupied(MembershipSet set, int stationNum) {
    // TODO: Check if a specific station is occupied


    // isMember function 

    return (set[stationNum] == 1) ? TRUE : FALSE;
}

MembershipSet* getBusyStations(MembershipSet regular, MembershipSet premium) {
    // TODO: Find stations that have BOTH Regular AND Premium members

    MembershipSet* busyStations =  (MembershipSet*) malloc(sizeof(MembershipSet)); 

    for (int i = 0; i < MAX_STATIONS; i++){

        (*busyStations)[i] = regular[i] && premium[i];
    }

    
    return busyStations; 
}

MembershipSet* getUpgradeOpportunities(MembershipSet regular, MembershipSet vip) {
    

     MembershipSet* forUpgrades =  (MembershipSet*) malloc(sizeof(MembershipSet));  

    for (int i = 0; i < MAX_STATIONS; i++){

        (*forUpgrades)[i] = regular[i] && !(vip[i]);
    }

    
    return forUpgrades; 

}

MembershipSet* getPromotionStations(MembershipSet premium) {
    
    MembershipSet* noPremium=  (MembershipSet*) malloc(sizeof(MembershipSet));  

    for (int i = 0; i < MAX_STATIONS; i++){

       (*noPremium)[i] = !(premium[i]);
    }

    
    return noPremium; 


}

Boolean checkServiceConsistency(MembershipSet vip, MembershipSet premium) {
    // TODO: Check if every VIP station also has Premium service


     int isNotConsistentService = FALSE;

    for (int i = 0; i < MAX_STATIONS; i++){

        if (vip[i] == 1 ){ // for every VIP, the station must also be premium
            // printf("this fired");
            if (premium[i] == 0) isNotConsistentService = TRUE;
        }
        
    }

    
    return isNotConsistentService; 

    //  subset
    return FALSE; // placeholder
}

MembershipSet* getGeneralOccupancy(MembershipSet regular, MembershipSet premium, MembershipSet vip) {
   
     MembershipSet* allStations =  (MembershipSet*) malloc(sizeof(MembershipSet));  

    for (int i = 0; i < MAX_STATIONS; i++){

        (*allStations)[i] = regular[i] || vip[i] || premium[i];
    }

    
    return allStations; 
}

MembershipSet* getBasicServiceAreas(MembershipSet regular, MembershipSet premium, MembershipSet vip) {
    // TODO: Find stations with ONLY Regular members (no Premium or VIP)

    // in regular, NOT PREMIUM, NOT VIP

    
     MembershipSet* basicServiceAreas =  (MembershipSet*) malloc(sizeof(MembershipSet));  

    for (int i = 0; i < MAX_STATIONS; i++){

        (*basicServiceAreas)[i] = regular[i] && !vip[i] && !premium[i];
    }

    
    return basicServiceAreas; 
}

void printAnalysis(const char* analysisName, MembershipSet* result, Boolean isBoolean, Boolean boolResult) {
    printf("\n%s:\n", analysisName);
    
    if (isBoolean) {
        printf("   Result: %s\n", boolResult ? "YES" : "NO");
    } else if (result != NULL) {
        printf("   Stations: ");
        Boolean hasAny = FALSE;
        for (int i = 0; i < MAX_STATIONS; i++) {
            if ((*result)[i] == 1) {
                printf("%d ", i);
                hasAny = TRUE;
            }
        }
        if (!hasAny) {
            printf("None");
        }
        printf("\n");
    } else {
        printf("   Error: Could not perform analysis\n");
    }
}