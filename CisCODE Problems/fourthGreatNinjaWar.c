/*

Fourth Great Ninja War
By Cliff Jharel Jao

DSA
Categories:

None
Gaara, as a military strategist, wants to efficiently create groups of distinct ninjas assigned on different locations. This is in order to have an effective front against the Akatsuki, their opponent.

Your Task is to create the ff. functions:

1. void markNinjaToWar(Alliance *S, ninjaType a);
- Given a List of ninjas and a ninja, the function should insert the ninja into the list using linked list implementation in a SORTED MANNER based on an identifier. Remember that the list should have distinct elements and avoid duplicates.
2. Alliance assembleNinjas(Alliance A, Alliance B);
- Given two sorted ninja lists, the function will return a new ninja list C that is the combined SORTED version of the two based on an identifier
3. Alliance neededNinjas(Alliance A, Alliance B);
- Given two sorted ninja lists, the function will return a SORTED ninja list that contains ninjas that are in both of the lists.
4. Alliance relocatingNinjas(Alliance A, Alliance B);
- Given two sorted ninja lists, the function will return a SORTED ninja list that contains ninjas from list A but not in list B.

Assume:
1-5 are Hidden Leaf | 6-10 = Hidden Mist | 11-15 Hidden Sand | 16-20 = Hidden Stone | 21-25 = Hidden Cloud | NOTE! This is for context purposes, NOT APPLICABLE ON YOUR CODING ANSWER!

"In order to escape a road of solitude, one has to work hard, and forge a new path with their own power." - Gaara

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int ninjaID; // Identifier
    char ninjaName[24];
    char village[24];
    int powerLevel;
} ninjaType;

typedef struct node
{
    ninjaType ninja;
    struct node *next;
} ninjaNode, *Alliance;

// HELPER FUNCTIONS | Below Main Function
void initAlliance(Alliance *S);
void displayNinjas(Alliance S); // Bracket Number pertains to ninjaID | Utilize for Sorting Purposes

void markNinjaToWar(Alliance *S, ninjaType a)
{
    // insert Sorted using an ID
    // condition is ninjaID > (*trav)->id
    ninjaNode *newNinja = (ninjaNode *)malloc(sizeof(ninjaNode));
    newNinja->ninja = a;
    ninjaNode **trav;

    for (trav = S; (*trav) != NULL && a.ninjaID > (*trav)->ninja.ninjaID; trav = &(*trav)->next)
    {
    }
    if (*trav != NULL && (*trav)->ninja.ninjaID == a.ninjaID)
    {
        // do nothing
    }
    else
    {
        newNinja->next = *trav;
        *trav = newNinja;
    }
}

Alliance assembleNinjas(Alliance A, Alliance B)
{
    // linked list set union

    Alliance C, aptr, bptr, *cptr;
    C = NULL;
    aptr = A;
    bptr = B;
    cptr = &C;

    while (aptr != NULL && bptr != NULL)
    {
        *cptr = (ninjaNode *)malloc(sizeof(ninjaNode));

        if (aptr->ninja.ninjaID < bptr->ninja.ninjaID)
        {
            (*cptr)->ninja = aptr->ninja;
            aptr = aptr->next;
        }
        else
        {

            if (aptr->ninja.ninjaID == bptr->ninja.ninjaID)
            {
                aptr = aptr->next;
            }

            (*cptr)->ninja = bptr->ninja;
            bptr = bptr->next;
        }

        cptr = &(*cptr)->next;
    }

    Alliance dptr = (aptr != NULL) ? aptr : bptr;

    while (dptr != NULL)
    {
        *cptr = (ninjaNode *)malloc(sizeof(ninjaNode));
        (*cptr)->ninja = dptr->ninja;
        dptr = dptr -> next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;
    return C;
}

Alliance neededNinjas(Alliance A, Alliance B)
{
    // linked list set intersection -- move only one node at a time, if ninja id in A is lower than in B then you move A since there is no hope that the lower value will be further down in B

    // if ninja id in A is greater, you move B

    // if equal, you insert to new set then move both

    Alliance C, aptr, bptr, *cptr;
    C = NULL;
    aptr = A;
    bptr = B;
    cptr = &C;

    while (aptr != NULL && bptr != NULL)
    {

        
        if (aptr->ninja.ninjaID < bptr->ninja.ninjaID)
        {
            aptr = aptr->next;
        }
        else if (aptr->ninja.ninjaID > bptr->ninja.ninjaID)
        {
            bptr = bptr->next;
        }

        else if (aptr->ninja.ninjaID == bptr->ninja.ninjaID)
        {
            
          *cptr = (ninjaNode *)malloc(sizeof(ninjaNode));
            (*cptr)->ninja = bptr->ninja;
            cptr = &(*cptr)->next;
            aptr = aptr->next;
            bptr = bptr->next;
        }

    }

    *cptr = NULL;
    return C;
}

Alliance relocatingNinjas(Alliance A, Alliance B)
{
    // printf("hi");

    Alliance C, aptr, bptr, *cptr;
    C = NULL;
    aptr = A;
    bptr = B;
    cptr = &C;

    while (aptr != NULL && bptr != NULL)
    {
       
        Alliance tempPtr = bptr; 
        while (tempPtr != NULL)
        {
            if (tempPtr->ninja.ninjaID == aptr->ninja.ninjaID)
            {
                break;
            }

            tempPtr = tempPtr ->next;

        }

        if (tempPtr == NULL)
        {   
             *cptr = (ninjaNode *)malloc(sizeof(ninjaNode));
            (*cptr)->ninja = aptr->ninja;
            cptr = &(*cptr)->next;
        }
        
        aptr = aptr->next;
        bptr = bptr->next;
    }

    while (aptr != NULL)
    {
       *cptr = (ninjaNode *)malloc(sizeof(ninjaNode));
        (*cptr)->ninja = aptr->ninja;
      aptr = aptr -> next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;
    return C;
}
// Main Function & Helper Funtions | DO NOT TOUCH
int main()
{

    Alliance HiddenLeaf;
    initAlliance(&HiddenLeaf);
    Alliance HiddenMist;
    initAlliance(&HiddenMist);
    Alliance HiddenSand;
    initAlliance(&HiddenSand);
    Alliance HiddenStone;
    initAlliance(&HiddenStone);
    Alliance HiddenCloud;
    initAlliance(&HiddenCloud);
    Alliance U;
    initAlliance(&U);
    Alliance I;
    initAlliance(&I);
    Alliance D;
    initAlliance(&D);
    Alliance V;
    initAlliance(&V);

    ninjaType ninjas[25] = {{1, "Sasuke", "Hidden Leaf", 900}, {2, "Tsunade", "Hidden Leaf", 213}, {3, "Sai", "Hidden Leaf", 306}, {4, "Kakashi", "Hidden Leaf", 732}, {5, "Ino", "Hidden Leaf", 887}, {6, "Mei", "Hidden Mist", 814}, {7, "Haku", "Hidden Mist", 204}, {8, "Mangetsu", "Hidden Mist", 100}, {9, "Kisame", "Hidden Mist", 643}, {10, "Yagura", "Hidden Mist", 632}, {11, "Sasori", "Hidden Sand", 999}, {12, "Gaara", "Hidden Sand", 215}, {13, "Pakura", "Hidden Sand", 525}, {14, "Maki", "Hidden Sand", 568}, {15, "Chiyo", "Hidden Sand", 834}, {16, "Mu", "Hidden Stone", 840}, {17, "Roshi", "Hidden Stone", 686}, {18, "Gari", "Hidden Stone", 683}, {19, "Onoki", "Hidden Stone", 176}, {20, "Deidara", "Hidden Stone", 119}, {21, "Darui", "Hidden Cloud", 591}, {22, "Killer B", "Hidden Cloud", 702}, {23, "Yugito", "Hidden Cloud", 442}, {24, "Ayo", "Hidden Cloud", 408}, {25, "Samui", "Hidden Cloud", 315}};

    int c;
    scanf("%d", &c);

    switch (c)
    {
    case 1:
        printf("Gaara gathering Hidden Leaf Shinobis...\n");
        markNinjaToWar(&HiddenLeaf, ninjas[2]);
        markNinjaToWar(&HiddenLeaf, ninjas[0]);
        markNinjaToWar(&HiddenLeaf, ninjas[3]);
        markNinjaToWar(&HiddenLeaf, ninjas[1]);
        markNinjaToWar(&HiddenLeaf, ninjas[4]);
        displayNinjas(HiddenLeaf);
        printf("Gaara gathering Hidden Cloud Shinobis...\n");
        markNinjaToWar(&HiddenCloud, ninjas[24]);
        markNinjaToWar(&HiddenCloud, ninjas[21]);
        markNinjaToWar(&HiddenCloud, ninjas[23]);
        markNinjaToWar(&HiddenCloud, ninjas[22]);
        markNinjaToWar(&HiddenCloud, ninjas[20]);
        displayNinjas(HiddenCloud);
        printf("Gaara Assembling for Regional Deployment...\n");
        displayNinjas(assembleNinjas(HiddenLeaf, HiddenCloud));
        printf("Gaara fled the Scene as Task is Completed...\n");
        break;
    case 2:
        printf("Gaara gathering Hidden Mist Shinobis...\n");
        markNinjaToWar(&HiddenMist, ninjas[5]);
        markNinjaToWar(&HiddenMist, ninjas[9]);
        markNinjaToWar(&HiddenMist, ninjas[8]);
        markNinjaToWar(&HiddenMist, ninjas[6]);
        markNinjaToWar(&HiddenMist, ninjas[8]); // Duplicate
        markNinjaToWar(&HiddenMist, ninjas[7]);
        displayNinjas(HiddenMist);
        printf("Gaara gathering Hidden Stone Shinobis...\n");
        markNinjaToWar(&HiddenStone, ninjas[19]);
        markNinjaToWar(&HiddenStone, ninjas[18]);
        markNinjaToWar(&HiddenStone, ninjas[19]); // Duplicate
        markNinjaToWar(&HiddenStone, ninjas[17]);
        markNinjaToWar(&HiddenStone, ninjas[16]);
        markNinjaToWar(&HiddenStone, ninjas[15]);
        displayNinjas(HiddenStone);
        printf("Gaara Assembling for Regional Deployment...\n");
        displayNinjas(assembleNinjas(HiddenMist, HiddenStone));
        printf("Gaara fled the Scene as Task is Completed...\n");
        break;
    case 3:
        printf("Gaara Gathering Shinobis for Sand Area...\n");
        markNinjaToWar(&HiddenStone, ninjas[19]);
        markNinjaToWar(&HiddenStone, ninjas[18]);
        markNinjaToWar(&HiddenStone, ninjas[16]);
        markNinjaToWar(&HiddenCloud, ninjas[23]);
        markNinjaToWar(&HiddenCloud, ninjas[22]);
        markNinjaToWar(&HiddenCloud, ninjas[20]);
        U = assembleNinjas(HiddenStone, HiddenCloud);
        displayNinjas(U);
        printf("Gaara Gathering Shinobis for Grass Area...\n");
        markNinjaToWar(&HiddenCloud, ninjas[23]);
        markNinjaToWar(&HiddenCloud, ninjas[22]);
        markNinjaToWar(&HiddenCloud, ninjas[20]);
        markNinjaToWar(&HiddenSand, ninjas[10]);
        markNinjaToWar(&HiddenSand, ninjas[14]);
        markNinjaToWar(&HiddenSand, ninjas[11]);
        I = assembleNinjas(HiddenCloud, HiddenSand);
        displayNinjas(I);
        printf("Gaara made a Mistake in Assignment! Find Hidden Cloud Shinobis!\n");
        displayNinjas(neededNinjas(U, I));
        printf("Gaara wants to find Shinobi assigned in Sand Area not in Grass Area\n");
        displayNinjas(relocatingNinjas(U, I));
        break;
    case 4:
        printf("Gaara Gathering Shinobis for Cannon Valley...\n");
        markNinjaToWar(&HiddenLeaf, ninjas[0]);
        markNinjaToWar(&HiddenLeaf, ninjas[3]);
        markNinjaToWar(&HiddenLeaf, ninjas[1]);
        markNinjaToWar(&HiddenMist, ninjas[5]);
        markNinjaToWar(&HiddenMist, ninjas[9]);
        markNinjaToWar(&HiddenMist, ninjas[8]);
        markNinjaToWar(&HiddenMist, ninjas[6]);
        markNinjaToWar(&HiddenMist, ninjas[8]); // Duplicate
        markNinjaToWar(&HiddenMist, ninjas[7]);
        U = assembleNinjas(HiddenMist, HiddenLeaf);
        displayNinjas(U);
        printf("Gaara Gathering Shinobis for Forest of Life...\n");
        markNinjaToWar(&HiddenMist, ninjas[5]);
        markNinjaToWar(&HiddenMist, ninjas[9]);
        markNinjaToWar(&HiddenMist, ninjas[9]); // Duplicate
        markNinjaToWar(&HiddenMist, ninjas[8]);
        markNinjaToWar(&HiddenMist, ninjas[6]);
        markNinjaToWar(&HiddenMist, ninjas[7]);
        markNinjaToWar(&HiddenCloud, ninjas[23]);
        markNinjaToWar(&HiddenCloud, ninjas[22]);
        markNinjaToWar(&HiddenCloud, ninjas[20]);
        I = assembleNinjas(HiddenMist, HiddenCloud);
        displayNinjas(I);
        printf("Oh No! We're Fighting Madara! Gaara assembles people from the Hidden Mist!\n");
        displayNinjas(neededNinjas(U, I));
        break;
    case 5:
        printf("Gaara Gathering Shinobis for Hidden Rain...\n");
        markNinjaToWar(&HiddenSand, ninjas[10]);
        markNinjaToWar(&HiddenSand, ninjas[11]);
        markNinjaToWar(&HiddenSand, ninjas[13]);
        markNinjaToWar(&HiddenSand, ninjas[12]);
        markNinjaToWar(&HiddenMist, ninjas[5]);
        markNinjaToWar(&HiddenMist, ninjas[9]);
        U = assembleNinjas(HiddenSand, HiddenMist);
        displayNinjas(U);
        printf("Gaara Gathering Shinobis for Naka Shrine...\n");
        markNinjaToWar(&HiddenSand, ninjas[10]);
        markNinjaToWar(&HiddenSand, ninjas[11]);
        markNinjaToWar(&HiddenSand, ninjas[13]);
        markNinjaToWar(&HiddenSand, ninjas[12]);
        markNinjaToWar(&HiddenStone, ninjas[18]);
        markNinjaToWar(&HiddenStone, ninjas[16]);
        I = assembleNinjas(HiddenSand, HiddenStone);
        displayNinjas(I);
        printf("Need Wind Jutsu Users against A! Gaara Assembles Hidden Sand Shinobis...\n");
        displayNinjas(neededNinjas(U, I));
        printf("The Remaining Ninjas from both Areas Assemble at Konoha Hospital for Retrieval...\n");
        displayNinjas(assembleNinjas(relocatingNinjas(U, I), relocatingNinjas(I, U)));
        break;
    default:
        break;
    }
    return 0;
}

void initAlliance(Alliance *S)
{
    *S = NULL;
}

void displayNinjas(Alliance S)
{
    printf("{\n");
    while (S != NULL)
    { // Bracket Number pertains to NINJAID | Utilize for Sorting Purposes
        printf("Name: %-10s\tVillage: %-14s\tPower Level: %d [%d]\n", S->ninja.ninjaName, S->ninja.village, S->ninja.powerLevel, S->ninja.ninjaID);
        S = S->next;
    }
    printf("}\n");
}