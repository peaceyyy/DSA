/*
Check for Anagrams using Closed Hashing
By Cris Lawrence Lucero

DSA
Categories:

None
Given two strings, determine if they are anagrams of each other. An anagram is a word or phrase formed by rearranging the letters of another word or phrase, using all original letters exactly once.

REQUIREMENTS:
-Must use a DICTIONARY (hash table) with CLOSED HASHING
-Must use LINEAR PROBING for collision resolution (key = (key + 1) % MAX)
-Must track CHARACTER FREQUENCIES in the hash table
-Must handle EMPTY and DELETED states properly
-Returns true if strings are anagrams, false otherwise

CONSTRAINTS:
-Input strings contain only ASCII characters
-CASE-SENSITIVE: 'A' and 'a' are treated as different characters
-Strings of DIFFERENT LENGTHS are NOT anagrams

FUNCTIONS:
-initDict() → initialize dictionary with EMPTY markers
-insert() → insert character and track frequency
-delete() → remove/decrement character frequency
-isMember() → check if character exists with frequency > 0
-isAnagram() → main function to check if two strings are anagrams

*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define EMPTY '~'
#define DELETED '!'
#define MAX 211

/*********************************/
/*    USER-DEFINED DATA TYPES    */
/*********************************/
typedef struct {
    char elem;
    int frequency;
} Element;

typedef Element Dictionary[MAX];

/*********************************/
/*       HELPER FUNCTIONS        */
/*********************************/
void initDict(Dictionary D);
int hash(char elem);

/*********************************/
/*          YOUR TASKS           */
/*********************************/

void insert(Dictionary D, char elem);
void delete(Dictionary D, char elem);
bool isMember(Dictionary D, char elem);
bool isAnagram(char* s, char* t);

int main(void) {
    char s1[100], s2[100];

    printf("Enter first string: ");
    scanf("%s", s1);

    printf("Enter second string: ");
    scanf("%s", s2);

    if (isAnagram(s1, s2)) {
        printf("\"%s\" and \"%s\" are anagrams.\n", s1, s2);
    } else {
        printf("\"%s\" and \"%s\" are NOT anagrams.\n", s1, s2);
    }

    return 0;
}

/*********************************/
/*       HELPER FUNCTIONS        */
/*********************************/
void initDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        D[i].elem = EMPTY;
        D[i].frequency = 0;
    }
}

int hash(char elem) {
    return ((int)elem) % MAX;
}

/*********************************/
/*          YOUR TASKS           */
/*********************************/


void insert(Dictionary D, char elem) {
    // TODO: Implement insert with linear probing
    int hashVal = hash(elem);

    if (D[hashVal].elem == EMPTY) {
        // printf("Inserted home pos\n");
        D[hashVal].elem = elem;
        D[hashVal].frequency++;
    }
    else 
    {   
        int i;
        int firstDeletedIndex = -1, found = 0;
        for (i = hashVal + 1; hashVal != i && D[i].elem != EMPTY; i = (i + 1) % MAX){
            if (D[i].elem == elem)
            {
                // printf("Found duplicate..incrementing\n");
                D[i].frequency++;
                found = 1;
                break;
            }

            
        }
        if (D[i].elem == EMPTY)
        {
            // printf("Inserted somewhere else\n");
            D[i].elem = elem;
            D[i].frequency++;
        } else if (found && firstDeletedIndex != -1)
        {
            D[firstDeletedIndex].elem = elem;
            D[firstDeletedIndex].frequency++;
        }
        
    } 
    
}

void delete(Dictionary D, char elem) {
    // TODO: Implement delete with linear probing

    int hashVal = hash(elem);

    if (D[hashVal].elem == EMPTY) return;


    if (D[hashVal].elem != elem)
    {   
        int i;
        for (i = hashVal + 1; hashVal != i && D[i].elem != EMPTY; i = (i + 1) % MAX){
            if (D[i].elem == elem)
            {   
                // printf("Deleted %c \n", D[i].elem);
                D[i].frequency--;
                if (D[i].frequency == 0) D[i].elem = DELETED;
                break;
            }
        }        
    } 
    else {
        // printf("Deleted %c \n", D[hashVal].elem);
        D[hashVal].frequency-- ;
        if (D[hashVal].frequency == 0) D[hashVal].elem = DELETED;
    }
    
}

bool isMember(Dictionary D, char elem) {
    // TODO: Implement membership check

    int hashVal = hash(elem);

    if (D[hashVal].elem == EMPTY) return false;

    else if (D[hashVal].elem == elem && D[hashVal].frequency > 0)  return true;

    else
    {   
        int i;
        for (i = hashVal + 1; i != hashVal && D[i].elem != EMPTY; i = (i + 1) % MAX){
            if (D[i].elem == elem && D[i].frequency > 0){
            // {   printf("fired");
                return true;
            }
        }        
    } 
    return false;

    
}


void displayHashTable(Dictionary D) {
	int x;
	
	printf("\n Index     Content     Freq.   Search Length");
	
	for (x = 0; x < MAX ; x++) {
		printf("\n  %d", x);
		if (D[x].elem != EMPTY && D[x].elem != DELETED) {
			printf("         %c           %d           %d ", D[x].elem, D[x].frequency, (x - hash(D[x].elem)+ 1));
		} else if (D[x].elem == EMPTY) {
			printf("         EMPTY");
		} else {
			printf("       DELETED");
		}
	}
}




bool isAnagram(char* s, char* t) {
    // TODO: Implement anagram checker

    if (strlen(s) != strlen(t)) return false;

    // Dictionary firstStr;
    Dictionary secondStr;
    initDict(secondStr);
    
    for (int i = 0; i < strlen(t); i++)
    {
        insert(secondStr, t[i]);
    }
    
    for (int j = 0; j < strlen(s); j++)
    {   
        
        delete(secondStr, s[j]);
    }
    
    // displayHashTable(secondStr);
    for (int k = 0; k < strlen(s); k++)
    {
        if(isMember(secondStr, t[k])) return false; 
    }
    

    return true;

}


