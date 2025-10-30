/*
Dictionary collision handling using VirtualHeap
By Rusk Rye Ioan Alarde


A collision in a dictionary simply means that the hash has already been taken by a previous element, implying that an element can be UNIQUE, but the hash is NOT guaranteed to be unique. To mitigate this, The algorithm in this problem requires the user to store the "synonyms" or the duplicate elements into a separate area, which is the VirtualHeap.

The Prime table area will be the first field to be occupied, and then if another element were to be inserted with an already existing hash in the prime data area, the "synonym" will then be placed into the virtualHeap.

The prime data area will link to the first synonym  in the virtualHeap (if any), and if there are no synonyms, the link field will remain -1.

insertAuto():
this function "automatically" decides wether to insert into the prime table, or into the synonyms table. there should be no duplicate elements.

function-specific messages:

"[INSERT] ELEM ALREADY EXISTS!"
"[INSERT] VH OUT OF SPACE!"

deleteAuto():
this function will find the element and delete the element, and therefore will have to decide if the element is in the prime table or in the synonym table.

function-specific messages:

"[DELETE] Element not found!"

finder():
scans the appropriate table for the element. if found, it prints a message showing its found.

function-specific messages:

"[FINDER] Element found at HASH ID %d"
"[FINDER] Element does not exist!"


notes:
 - the synonym table will remain unoccupied until an element with an already pre-existing hash is inserted.

 - deleting an element in the prime table will only set the link field to -1 when there are no synonyms. otherwise leave as is.

 - the link field of the prime table will only point to the FIRST added synonym, and will behave just like a virtualheap. if no synonym, leave at -1.


*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 15
#define EMPTY '\0'
#define DELETED '~'

typedef struct node
{
    char data;
    int link;
} NODE_T;

typedef struct
{
    NODE_T synonyms[MAX];
    int avail;
} virtualHeap;

typedef struct
{
    NODE_T elems[MAX];
    virtualHeap VH;
} *dictionary, DICT_T;

dictionary *GLOBAL_DICT;

// main functions (do not touch)
void SIGHANDLER(int signal);
int HASH_FUNC(char SRC);
void appendHandler(dictionary D);
void deleteHandler(dictionary D);
void finderHandler(dictionary D);
void checkHash();
void switcher(dictionary D, int choice);
void looper(dictionary D);
void displayDataStructure(dictionary D);
void initVirtualHeap(virtualHeap *VH);
void initHashTable(NODE_T *SRC);
void initDictionary(dictionary *D);
int allocSpace(virtualHeap *VH);
void deallocSpace(virtualHeap *VH, int ndx);
//--------------------------------
//|---user functions (modify)----|
//--------------------------------
void insertAuto(dictionary D, char elem);
void deleteAuto(dictionary D, char TARG);
void finder(dictionary D, char elem);

/*

typedef struct node{
    char data;
    int link;
}NODE_T;

typedef struct{
    NODE_T synonyms[MAX];
    int avail;
}virtualHeap;

typedef struct{
    NODE_T elems[MAX];
    virtualHeap VH;
}*dictionary, DICT_T;

dictionary *GLOBAL_DICT;

*/
void insertAuto(dictionary D, char elem)
{
    int ELEM_NDX = HASH_FUNC(elem);
    NODE_T *ptr;


    if (D->elems[ELEM_NDX].data == EMPTY || D->elems[ELEM_NDX].data == DELETED)
    {
        D->elems[ELEM_NDX].data = elem;
    }
    else
    {

        if (D->elems[ELEM_NDX].data != elem)
        {

            int *trav;
            int found = 0;

            for (trav = &D->elems[ELEM_NDX].link; (*trav) != -1 && found != 1; trav = &D->VH.synonyms[*trav].link)
            {
              if (D->VH.synonyms[*trav].data == elem) found = 1;
            }

            if (*trav == -1)
            {

                int availNdx = allocSpace(&D->VH);

                if (availNdx != -1)
                {
                    D->VH.synonyms[availNdx].data = elem;
                    D->VH.synonyms[availNdx].link = D->elems[ELEM_NDX].link;
                    D->elems[ELEM_NDX].link = availNdx;
                                      
                }
                else
                {
                    printf("\n[INSERT] VH OUT OF SPACE!\n");
                }
            }
            else
            {
                printf("\n[INSERT] ELEM ALREADY EXISTS!\n");
            }
        }

        else
        {
            printf("\n[INSERT] ELEM ALREADY EXISTS!\n");
        }
    }
}

void deleteAuto(dictionary D, char TARG)
{
    int ELEM_NDX = HASH_FUNC(TARG);
    NODE_T *ptr;

    if (D->elems[ELEM_NDX].data == EMPTY || D->elems[ELEM_NDX].data == DELETED)
    {
        printf("\n[DELETE] Element not found!\n");
    }
    else
    {

        if (D->elems[ELEM_NDX].data == TARG)
        {
            D->elems[ELEM_NDX].data = DELETED;
        }

        else
        {

            // check if its down the link

            int *trav;

            for (trav = &D->elems[ELEM_NDX].link; (*trav) != -1 && D->VH.synonyms[*trav].data != TARG; trav = &D->VH.synonyms[*trav].link)
            {
            }

            if (*trav != -1)
            {
                // D->VH.synonyms[*trav].data = DELETED;
                int temp = *trav;
                *trav = D->VH.synonyms[temp].link;
                deallocSpace(&D->VH, temp);
            }
            else
            {

                printf("\n[DELETE] Element not found!\n");
            }
        }
    }
}

void finder(dictionary D, char elem)
{
    int ELEM_NDX = HASH_FUNC(elem);
    NODE_T *ptr;

    if (D->elems[ELEM_NDX].data == EMPTY || D->elems[ELEM_NDX].data == DELETED)
    {
        printf("\n[FINDER] Element does not exist!");
    }
    else
    {

        if (D->elems[ELEM_NDX].data == elem)
        {

            printf("\n[FINDER] Element found at HASH ID %d", ELEM_NDX);
        }

        else if (D->elems[ELEM_NDX].link != -1)
        {

            // check if its down the link

            int *trav;

            for (trav = &D->elems[ELEM_NDX].link; (*trav) != -1 && D->VH.synonyms[*trav].data != elem; trav = &D->VH.synonyms[*trav].link)
            {
            }

            // printf("\ntrav is equal to %d\n", *trav);

            if (*trav != -1)
            {
                printf("\n[FINDER] Element found at HASH ID %d", ELEM_NDX);
            }
            else
            {

                printf("\n[FINDER] Element does not exist!");
            }
        }
        else
        {

            printf("\n[FINDER] Element does not exist!");
        }
    }
}

dictionary D;
int main()
{
    initDictionary(&D);

    GLOBAL_DICT = &D;
    looper(D);
    return 0;
}
//--------------------------------
//|---DO NOT MODIFY!!!!!!!!!!!---|
//--------------------------------
void displayDataStructure(dictionary D)
{
    NODE_T *HPTR = D->elems;
    NODE_T *VPTR = D->VH.synonyms;

    printf("\nDICTIONARY STATUS");
    printf("\n%-32s", "--------------------------------------------");
    printf("\n| %-4s | %-15s | %-15s |", "BASE", "Prime Table", "Synonym Table");
    printf("\n| %-4s | %-7s %-7s | %-7s %-7s |", "NDX", "Data", "Link", "Data", "Link");
    for (int i = 0; i < MAX; i++)
    {
        printf("\n| %-4d | %-7c %-7d | %-7c %-7d |",
               i,
               (HPTR[i].data == EMPTY || HPTR[i].data == DELETED) ? ' ' : HPTR[i].data,
               HPTR[i].link,
               (VPTR[i].data == EMPTY || HPTR[i].data == DELETED) ? ' ' : VPTR[i].data,
               VPTR[i].link);
    }
    printf("\n%-32s", "--------------------------------------------");
}

void initVirtualHeap(virtualHeap *VH)
{
    for (int i = 0; i < MAX; i++)
    {
        VH->synonyms[i].link = i - 1;
        VH->synonyms[i].data = EMPTY;
    }
    VH->avail = MAX - 1;
}

void initHashTable(NODE_T *SRC)
{
    for (int i = 0; i < MAX; i++)
    {
        SRC[i].data = EMPTY;
        SRC[i].link = -1;
    }
}

void initDictionary(dictionary *D)
{
    *D = (dictionary)malloc(sizeof(DICT_T));
    initVirtualHeap(&(*D)->VH);
    initHashTable((*D)->elems);
}

int allocSpace(virtualHeap *VH)
{
    int ndx = VH->avail;
    if (ndx != -1)
    {
        VH->avail = VH->synonyms[ndx].link;
    }
    return ndx;
}



void deallocSpace(virtualHeap *VH, int ndx)
{
    if (ndx > -1 && ndx < MAX)
    {
        VH->synonyms[ndx].link = VH->avail;
        VH->synonyms[ndx].data = DELETED;
        VH->avail = ndx;
    }
}

void SIGHANDLER(int signal)
{
    if (signal)
    {
        printf("\nSIGINT - Premature termination!");
    }
    printf("\nFreeing dictionary with [%lu] bytes", (unsigned long)sizeof(DICT_T));
    free(*GLOBAL_DICT);
}

int HASH_FUNC(char SRC)
{
    return ((unsigned char)SRC * 31) % MAX;
}

void appendHandler(dictionary D)
{
    char elem;

    printf("Enter the element to append: ");
    scanf(" %c", &elem);
    insertAuto(D, elem);
}

void deleteHandler(dictionary D)
{
    char elem;

    printf("Enter the element to delete: ");
    scanf(" %c", &elem);
    deleteAuto(D, elem);
}

void finderHandler(dictionary D)
{
    char TARGET;

    printf("Enter what element to search: ");
    scanf(" %c", &TARGET);
    finder(D, TARGET);
}

void checkHash()
{
    char elem;
    int hash;

    printf("\nEnter an element to check hash: ");
    scanf(" %c", &elem);
    hash = HASH_FUNC(elem);
    printf("\nReturned hash: [%c] -> [%d]", elem, hash);
}

void switcher(dictionary D, int choice)
{
    switch (choice)
    {
    case 0:
        printf("\nProgram terminated.");
        displayDataStructure(D);
        SIGHANDLER(0);
        break;
    case 1:
        appendHandler(D);
        break;
    case 2:
        deleteHandler(D);
        break;
    case 3:
        finderHandler(D);
        break;

        checkHash();
        break;
    default:
        printf("\nInvalid choice!");
        break;
    }
}

void looper(dictionary D)
{
    int choice = -1;

    while (choice != 0)
    {
        scanf("%d", &choice);
        switcher(D, choice);
    }
}
