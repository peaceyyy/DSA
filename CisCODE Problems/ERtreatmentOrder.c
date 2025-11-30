#include <stdio.h>     
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>    
#include <time.h>

#define MAXPatient 20

typedef struct {
    char fName[24];
    char mi;
    char lName[16];
} nametype;

typedef struct {
    nametype name;
    char patientID[9];
    int age;
    int emergencyLevel;
    char arrivalTime[11]; // "yyyy-mm-dd" 
} patient;

typedef struct {
    patient patients[MAXPatient];
    int lastNdx;
} patientList;



// -- HELPER FUNCTIONS --
void initPatients(patientList *p, int test) {
    static const patient testSet1[MAXPatient] = {
        {{"John", 'A', "Doe"}, "P001", 30, 1, "2025-11-05"},   
        {{"Jane", 'B', "Smith"}, "P002", 80, 1, "2025-11-04"}, 
        {{"Mike", 'C', "Lee"}, "P003", 2, 1, "2025-11-05"},   
        {{"Sarah", 'D', "Jones"}, "P004", 72, 2, "2025-11-05"}, 
        {{"Adam", 'E', "Brown"}, "P005", 25, 2, "2025-11-05"}, 
        {{"Baby", 'F', "Ruth"}, "P006", 1, 2, "2025-11-04"},    
        {{"Chris", 'G', "Wilson"}, "P007", 40, 3, "2025-11-03"},
        {{"Tom", 'H', "Davis"}, "P008", 42, 3, "2025-11-05"},    
        {{"Lisa", 'I', "Hall"}, "P009", 85, 3, "2025-11-05"},    
        {{"Mark", 'J', "Baker"}, "P010", 60, 4, "2025-11-05"},
        {{"Beth", 'K', "White"}, "P011", 22, 4, "2025-11-05"},
        {{"Ken", 'L', "Clark"}, "P012", 75, 4, "2025-11-04"}, 
        {{"Sue", 'M', "Allen"}, "P013", 19, 5, "2025-11-05"},
        {{"Sam", 'N', "King"}, "P014", 33, 5, "2025-11-05"},
        {{"Mia", 'O', "Hill"}, "P015", 50, 5, "2025-11-03"}, 
        {{"Anna", 'P', "Scott"}, "P016", 25, 2, "2025-11-03"}, 
        {{"Paul", 'Q', "Green"}, "P017", 42, 3, "2025-11-04"}, 
        {{"Eva", 'R', "Adams"}, "P018", 1, 1, "2025-11-05"},  
        {{"Leo", 'S', "Ward"}, "P019", 90, 2, "2025-11-04"}, 
        {{"Nina", 'T', "Gray"}, "P020", 38, 4, "2025-11-05"}
    };
    static const patient testSet2[MAXPatient] = {
        {{"Robert", 'A', "Smith"}, "P021", 80, 1, "2025-11-06"}, 
        {{"Mary", 'B', "Johnson"}, "P022", 3, 1, "2025-11-07"},
        {{"James", 'C', "Williams"}, "P023", 40, 1, "2025-11-06"},
        {{"David", 'D', "Miller"}, "P024", 80, 1, "2025-11-06"}, 
        {{"Patricia", 'E', "Jones"}, "P025", 75, 2, "2025-11-05"}, 
        {{"Linda", 'F', "Garcia"}, "P026", 30, 2, "2025-11-05"},
        {{"Michael", 'G', "Davis"}, "P027", 2, 2, "2025-11-07"},
        {{"Susan", 'H', "Lopez"}, "P028", 60, 3, "2025-11-07"},
        {{"Richard", 'I', "Hernandez"}, "P029", 65, 3, "2025-11-06"},
        {{"Maria", 'J', "Rodriguez"}, "P030", 80, 3, "2025-11-07"}, 
        {{"Daniel", 'K', "Martinez"}, "P031", 1, 3, "2025-11-07"}, 
        {{"Karen", 'L', "Anderson"}, "P032", 22, 4, "2025-11-07"},
        {{"Joseph", 'M', "Thomas"}, "P033", 22, 4, "2025-11-07"}, 
        {{"Charles", 'N', "Gonzalez"}, "P034", 90, 4, "2025-11-07"}, 
        {{"Lisa", 'O', "Wilson"}, "P035", 18, 4, "2025-11-06"},
        {{"William", 'P', "Jackson"}, "P036", 50, 5, "2025-11-07"},
        {{"Nancy", 'Q', "Moore"}, "P037", 50, 5, "2025-11-06"}, 
        {{"Thomas", 'R', "Taylor"}, "P038", 75, 5, "2025-11-07"}, 
        {{"Mark", 'S', "Martin"}, "P039", 5, 5, "2025-11-07"},
        {{"Paul", 'T', "Lee"}, "P040", 50, 5, "2025-11-07"} 
    };
    static const patient testSet3[MAXPatient] = {
        {{"Tom", 'T', "Turner"}, "P120", 5, 5, "2025-11-11"},   
        {{"Sam", 'S', "Scott"}, "P119", 70, 5, "2025-11-11"},
        {{"Rose", 'R', "Reed"}, "P118", 50, 5, "2025-11-10"},
        {{"Peter", 'P', "Parker"}, "P116", 50, 5, "2025-11-09"}, 
        {{"Quinn", 'Q', "Quinn"}, "P117", 50, 5, "2025-11-10"},
        {{"Olivia", 'O', "Olson"}, "P115", 3, 5, "2025-11-10"}, 
        {{"Noah", 'N', "Nelson"}, "P114", 75, 5, "2025-11-10"}, 
        {{"Mia", 'M', "Miller"}, "P113", 80, 4, "2025-11-11"},  
        {{"Liam", 'L', "Lee"}, "P112", 30, 4, "2025-11-11"},
        {{"Kate", 'K', "King"}, "P111", 30, 4, "2025-11-11"},
        {{"Alice", 'A', "Abbott"}, "P101", 71, 1, "2025-11-10"},
        {{"Jack", 'J', "Jackson"}, "P110", 30, 4, "2025-11-11"},
        {{"Ivy", 'I', "Ingram"}, "P109", 25, 3, "2025-11-08"},
        {{"Henry", 'H', "Hall"}, "P108", 90, 3, "2025-11-09"},
        {{"Grace", 'G', "Green"}, "P107", 90, 3, "2025-11-08"},
        {{"Frank", 'F', "Ford"}, "P106", 40, 2, "2025-11-10"},
        {{"Eve", 'E', "Evans"}, "P105", 40, 2, "2025-11-10"},
        {{"Charles", 'C', "Chen"}, "P103", 70, 1, "2025-11-09"}, 
        {{"Diana", 'D', "Davis"}, "P104", 5, 1, "2025-11-10"},   
        {{"Bob", 'B', "Baker"}, "P102", 4, 1, "2025-11-10"} 
    };

    const patient *sourceData = NULL;

    switch (test) {
        case 1:
            sourceData = testSet1;
            break;
        case 2:
            sourceData = testSet2;
            break;
        case 3:
            sourceData = testSet3;
            break;
        default:
            printf("Invalid Test Case Choice: %d\n", test);
            exit(1); 
    }

    memcpy(p->patients, sourceData, sizeof(patient) * MAXPatient);
    p->lastNdx = MAXPatient - 1;
    
}

void treatPatients(patientList *p) {
    printf("--- Official Patient Treatment Order ---\n");
    printf("Order | ID   | Name                    | Lvl | Age | Arrival\n");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i <= p->lastNdx; i++) {
        patient pd = (p->patients)[i];
        printf("#%-4d | %-4s | %-20s %c. | %-3d | %-3d | %s\n", 
               (i + 1),                  
               pd.patientID, 
               pd.name.lName, pd.name.mi, 
               pd.emergencyLevel, 
               pd.age, 
               pd.arrivalTime);
    }
}

void swapPatients(patient *a, patient *b) {
    patient temp = *a;
    *a = *b;
    *b = temp;
}

// Returns true if p1 has higher priority than p2
bool hasHigherPriority(const patient *p1, const patient *p2) {
    if (p1->emergencyLevel != p2->emergencyLevel) {
        return p1->emergencyLevel < p2->emergencyLevel;
    }

    // Emergency levels are equal, check age
    bool p1_high_risk_age = (p1->age < 5 || p1->age > 70);
    bool p2_high_risk_age = (p2->age < 5 || p2->age > 70);

    if (p1_high_risk_age != p2_high_risk_age) {
        return p1_high_risk_age; // High risk age has higher priority
    }

    // Age risk categories are equal, check arrival time
    int p1_timestamp = parse_date_to_timestamp(p1->arrivalTime);
    int p2_timestamp = parse_date_to_timestamp(p2->arrivalTime);

    if (p1_timestamp != p2_timestamp) {
        return p1_timestamp < p2_timestamp; // Earlier arrival time has higher priority
    }

    // Arrival times are equal, check patient ID
    return strcmp(p1->patientID, p2->patientID) < 0; // Lower patient ID has higher priority
}

// helper functions

int parse_date_to_timestamp(const char *date_str) {
    int year, month, day;

    if (sscanf(date_str, "%d-%d-%d", &year, &month, &day) != 3) {
        return -1; // parse error
    }

    struct tm tm_date;
    memset(&tm_date, 0, sizeof tm_date);
    tm_date.tm_year = year - 1900;
    tm_date.tm_mon  = month - 1;
    tm_date.tm_mday = day;
    tm_date.tm_hour = 0;
    tm_date.tm_min  = 0;
    tm_date.tm_sec  = 0;
    tm_date.tm_isdst = -1; // let mktime determine DST

    time_t ts = mktime(&tm_date);
    if (ts == (time_t)-1) {
        return -1; // conversion failed or out of range
    }

    // Validate that mktime did not normalize an invalid date (e.g., 2025-02-30)
    if (tm_date.tm_year != year - 1900 || tm_date.tm_mon != month - 1 || tm_date.tm_mday != day) {
        return -1; // invalid calendar date
    }

    return (int)ts;
}


/*
#define MAXPatient 20

typedef struct {
    char fName[24];
    char mi;
    char lName[16];
} nametype;

typedef struct {
    nametype name;
    char patientID[9];
    int age;
    int emergencyLevel;
    char arrivalTime[11]; // "yyyy-mm-dd" 
} patient;

typedef struct {
    patient patients[MAXPatient];
    int lastNdx;
} patientList;

The final output must be sorted from highest priority to lowest priority.
Emergency Level - most important factor,
'1' - means highest priority,
'10' - lowest priority

Age - second factor, those below 5 (<5) and above 70 (>70) have higher priority than those between those ages
Date of Arrival - third factor, patients who arrived first are given higher priority
Patient ID - the tie breaker, if all factors are the same for two patients, a patient with a lower patient ID is given a higher priority
Rule Precedence: Subsequent factors are "ONLY" tested if the previous factor results in a tie
For example: If Patient A and Patient B have the same Emergency Level, 
            you then check their Age. 
            If their Age category is also the same, 
            you check their Arrival Date, 
            and so on, until the tie is broken.

*/


void heapify (patientList *p, int i)
{
    int currentNdx = i;

    while (currentNdx * 2 + 1 <= p->lastNdx)
    {
        int LC = (currentNdx * 2) + 1;
        int RC = (currentNdx * 2) + 2;
        int smallerNdx = LC;
        if (RC <= p->lastNdx && hasHigherPriority(&p->patients[RC], &p->patients[LC])) {
            smallerNdx = RC;
        }

        if (hasHigherPriority(&p->patients[currentNdx], &p->patients[smallerNdx])) {
            // currentNdx is already higher priority than its smallest child, so heap property is maintained
            break;
        } else {
            swapPatients(&p->patients[currentNdx], &p->patients[smallerNdx]);
            currentNdx = smallerNdx;
        }
    }
}

patient deleteMin (patientList *p)
{
    patient temp = p->patients[0];
    p->patients[0] =  p->patients[p->lastNdx--]; 
    
    heapify(p, 0);
    
        
}


void minHeapify(patientList* p)
{

    for (int parentNdx = (p->lastNdx - 1)/2; parentNdx >= 0; parentNdx--) heapify(p, parentNdx);
}
// ---- TASKs -----
void prioritify(patientList *p){

    int oldLast = p->lastNdx;
    patient tempList[MAXPatient];

    minHeapify(p);
    int i = 0;
    
    // Extract all patients from the min-heap into tempList in sorted order
    while (p->lastNdx >= 0) { // Changed condition to include the last element
        patient temp = deleteMin(p);
        tempList[i] = temp;
        i++;
    }

    // Copy the sorted patients back to the original array
    for (i = 0; i <= oldLast; i++) { // Correctly iterate up to oldLast
        p->patients[i] = tempList[i];
    }

    p->lastNdx = oldLast; 
    

}
// ADD FUNCTIONS as NEEDED


int main() {
    patientList P;
    int test;

    printf("What to test? ");
    scanf("%d", &test);

    initPatients(&P, test);

    prioritify(&P); // heapsort
    treatPatients(&P);

    return 0;
}