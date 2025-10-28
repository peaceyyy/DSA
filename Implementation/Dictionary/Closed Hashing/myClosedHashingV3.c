#include <stdio.h>
#include <stdbool.h>
#define MAX 18
#define DELETED '\0'
#define EMPTY ' '

typedef struct {

    char data;
    int link;
} node_t;

typedef struct {

    node_t Nodes[MAX];
    int Avail;

} Dictionary;

void initDictionary (Dictionary *D);
int hash(char x);
int isMember(Dictionary D, char x);
void insertElem(Dictionary *D, char x);
void deleteElem(Dictionary *D, char x);
void display(Dictionary D);
 

void main()
{

	int retval;
	Dictionary D;
	initDictionary(&D);

	// insertElem(&D, 'a'); // ASCII 97 -> hash(97) = 7. No collision.
	insertElem(&D, 'b'); // ASCII 98 -> hash(98) = 8. No collision.
	insertElem(&D, 'c'); // ASCII 99 -> hash(99) = 9. No collision.
	
	insertElem(&D, 'k'); // ASCII 107 -> hash(107) = 7. COLLISION with 'a'.
	insertElem(&D, 'l'); // ASCII 108 -> hash(108) = 8. COLLISION with 'b'.
	insertElem(&D, 'm'); // ASCII 109 -> hash(109) = 9. COLLISION with 'c'.
	
	insertElem(&D, 'u'); // ASCII 117 -> hash(117) = 7. COLLISION with 'a' and 'k'.
	insertElem(&D, 'v'); // ASCII 118 -> hash(118) = 8. COLLISION with 'b' and 'l'.
	insertElem(&D, 'w'); // ASCII 119 -> hash(119) = 9. COLLISION with 'c' and 'm'.

        insertElem(&D, 'a');  // Goes to slot, say index 7
    insertElem(&D, 'k');  // Collides, goes to synonym area
    deleteElem(&D, 'a');  // Slot 7 becomes DELETED, 'k' moves to slot 7
    insertElem(&D, 'a');  // Tries to reuse DELETED slot 7
    // Now slot 7 has 'a' but still has old link from 'k'!

    printf("\n\n");
	
	display(D);
	
    deleteElem(&D, 'b');
	isMember(D, 'b') ? printf("\nb is b member\n") : printf("\nb is not a member\n");
	// deleteElem(&D, 'a'); // ASCII 97 -> hash(97) = 7. No collision./
	isMember(D, 'a') ? printf("a is a member\n") : printf("a is not a member\n");
	
	isMember(D, 'w') ? printf("w is a member\n") : printf("w is not a member\n");

	deleteElem(&D, 'w'); // ASCII 97 -> hash(97) = 7. No collision.
	isMember(D, 'w') ? printf("w is a member\n") : printf("w is not a member\n");



	// deleteElem(&D, 'a');
	// deleteElem(&D, 'l');
	// deleteElem(&D, 'w');
}

void display(Dictionary D)
{
	int index;
	// prime data area
	for (index = 0; index < MAX/2; index++)
	{
		printf("[%d] ", index);
		if (D.Nodes[index].data == EMPTY)
		{
			printf("EMPTY | __");
		}
		else if (D.Nodes[index].data == DELETED)
		{
			printf("DELETED | %d", DELETED);
		}
		else
		{
			printf("%c | %d", D.Nodes[index].data, D.Nodes[index].link);
		}
		printf("\n");
	}
	// synonym area;
	printf("\nSynonym Area:\n");
	for (index = MAX - 1; index > D.Avail; index--)
	{
		printf("[%d] %c | %d | Original Hash: %d\n", index, D.Nodes[index].data, D.Nodes[index].link, hash(D.Nodes[index].data));
	}
	printf("\nCurrent Avail: %d", D.Avail);
}


void initDictionary (Dictionary *D){

    D->Avail = MAX - 1;

    for (int i = 0; i < MAX/2; i++){

        D->Nodes[i].data = EMPTY;
    }

    for (int i = MAX - 1; i >= MAX/2; i--)
    {
        D->Nodes[i].link = i - 1;
    }
}
int hash(char x){

    return ((x * 31) % MAX)/2;

}

void insertElem(Dictionary *D, char x)
{

    // find the hash 
    int hashValue = hash(x);
    
    if (D->Nodes[hashValue].data == DELETED){
        D->Nodes[hashValue].data = x; 
        D->Nodes[hashValue].link = -1;
    }

    else if (D->Nodes[hashValue].data != x && D->Avail != MAX/2){

        if (D->Nodes[hashValue].data == EMPTY) {

        D->Nodes[hashValue].data = x;
        D->Nodes[hashValue].link = -1;
    } 

        else if (isMember(*D, x) != 1){

            int temp = D->Nodes[D->Avail].link;
            D->Nodes[D->Avail].data = x;
            D->Nodes[D->Avail].link = D->Nodes[hashValue].link;
            D->Nodes[hashValue].link = D->Avail;
            D->Avail = temp;

        }


    } else {
        printf("\n%c is already in the dictionary!", x);
    }

 

}
void deleteElem(Dictionary *D, char x){

    int hashValue = hash(x);
    int temp;

    if (D->Nodes[hashValue].data == x){
        temp = D->Nodes[hashValue].link;

        if (temp != -1) // there is a synonym chain 
        {   
            D->Nodes[hashValue] = D->Nodes[temp];


            D->Nodes[temp].link = D->Avail; 
            D->Avail = temp;

        } else 
        {
            D->Nodes[hashValue].data = DELETED;

        }
        
    } else {

        int* trav;

        for (trav = &D->Nodes[hashValue].link; *trav != -1 && D->Nodes[(*trav)].data != x; trav = &D->Nodes[(*trav)].link){};

        if (*trav != -1){

            temp = *trav;
            *trav = D->Nodes[temp].link;

            D->Nodes[temp].link = D->Avail;
            D->Avail = temp;
            
        }

    }
 

}

int isMember(Dictionary D, char x)
{

    int hashValue = hash(x);
    int found = 0;

    if (D.Nodes[hashValue].data == x)
    {
        found = 1;
    } else 
    {   
        if (D.Nodes[hashValue].data != EMPTY && D.Nodes[hashValue].data != DELETED)
        {
            int trav; 
            for (trav = D.Nodes[hashValue].link; found != 1 && trav != -1; trav = D.Nodes[trav].link){
                if (D.Nodes[trav].data == x){
                    found = 1;
                }
            }
        }

    }

    return found; 

}
