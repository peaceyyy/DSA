// dictionary: open hashing operations

// c visualization link: 
// https://pythontutor.com/visualize.html#code=//%20dictionary%20operations%0A%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%23define%20SIZE%2010%0A%0Atypedef%20struct%20node%20%7B%0A%20%20%20%20int%20data%3B%0A%20%20%20%20struct%20node*%20link%3B%0A%7D*LIST%3B%0A%0Atypedef%20LIST%20Dictionary%5BSIZE%5D%3B%0A%0A//function%20prototypes%0Avoid%20initDictionary%20%28Dictionary%20D%29%3B%0Aint%20hash%28int%20x%29%3B%0Avoid%20insertDictionary%20%28Dictionary%20D,%20int%20x%29%3B%0Avoid%20deleteDictionary%20%28Dictionary%20D,%20int%20x%29%3B%0Aint%20isMember%28Dictionary%20D,%20int%20x%29%3B%0Avoid%20makeNull%28Dictionary%20D%29%3B%0A%0Aint%20main%20%28%29%20%7B%0A%20%20%20%20%0A%20%20%20%20Dictionary%20newDic%3B%0A%20%20%20%20initDictionary%20%28newDic%29%3B%0A%20%20%20%20%0A%20%20%20%20insertDictionary%20%28newDic,%2010%29%3B%0A%20%20%20%20insertDictionary%20%28newDic,%207%29%3B%0A%20%20%20%20insertDictionary%20%28newDic,%2020%29%3B%0A%20%20%20%20insertDictionary%20%28newDic,%2017%29%3B%0A%20%20%20%20%0A%20%20%20%20int%20retval%20%3D%20isMember%20%28newDic,%201%29%3B%0A%20%20%20%20%0A%20%20%20%20insertDictionary%20%28newDic,%2030%29%3B%0A%20%20%20%20insertDictionary%20%28newDic,%2040%29%3B%0A%20%20%20%20insertDictionary%20%28newDic,%2050%29%3B%0A%20%20%20%20%0A%20%20%20%20return%200%3B%0A%7D%0A%0Avoid%20initDictionary%20%28Dictionary%20D%29%20%7B%0A%20%20%20%20int%20x%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28x%20%3D%200%3B%20x%20%3C%20SIZE%3B%20x%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D%5Bx%5D%20%3D%20NULL%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%7D%0A%0Aint%20hash%28int%20x%29%7B%0A%20%20%20%20return%20%28x%20%25%20SIZE%29%3B%20%20//return%20digit%20in%20ones%20place%0A%7D%0A%0Avoid%20insertDictionary%20%28Dictionary%20D,%20int%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20%0A%20%20%20%20LIST%20temp%20%3D%20%28LIST%29%20malloc%20%28sizeof%28struct%20node%29%29%3B%0A%20%20%20%20LIST%20*trav%20%3D%20%26D%5Bhashval%5D%3B%0A%20%20%20%20%0A%20%20%20%20%0A%20%20%20%20for%20%28%3B%20%28*trav%29%20!%3D%20NULL%20%26%26%20%28*trav%29-%3Edata%20%3C%3D%20x%3B%20trav%20%3D%20%26%28*trav%29-%3Elink%29%20%7B%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20temp-%3Edata%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20temp-%3Elink%20%3D%20*trav%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20*trav%20%3D%20temp%3B%0A%7D%0A%0Avoid%20deleteDictionary%20%28Dictionary%20D,%20int%20x%29%20%7B%0A%20%20%20%20int%20hashval%3D%20hash%28x%29%3B%0A%20%20%20%20LIST%20temp%3B%0A%20%20%20%20LIST%20*trav%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D%5Bhashval%5D%20!%3D%20NULL%29%20%7B%0A%20%20%20%20%20%20%20%20for%20%28trav%20%3D%20%26D%5Bhashval%5D%3B%20%28*trav%29%20!%3D%20NULL%20%26%26%20%28*trav%29-%3Edata%20!%3D%20x%3B%20trav%20%3D%20%26%28*trav%29-%3Elink%29%20%7B%7D%0A%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20temp%20%3D%20*trav%3B%0A%20%20%20%20%20%20%20%20*trav%20%3D%20temp-%3Elink%3B%0A%20%20%20%20%20%20%20%20free%28temp%29%3B%0A%20%20%20%20%7D%20%20%20%20%0A%7D%0A%0Aint%20isMember%28Dictionary%20D,%20int%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20%0A%20%20%20%20LIST%20trav%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28trav%20%3D%20D%5Bhashval%5D%3B%20trav%20!%3D%20NULL%20%26%26%20trav-%3Edata%20!%3D%20x%3B%20trav%20%3D%20trav-%3Elink%29%20%7B%7D%0A%20%20%20%20%0A%20%20%20%20return%20%28trav%20!%3D%20NULL%29%3F%200%3A1%3B%0A%20%20%20%20%0A%7D&cumulative=false&curInstr=134&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct node {
	int data;
	struct node* link;
}*LIST;

typedef LIST Dictionary[SIZE];

//function prototypes
void initDictionary (Dictionary D);
int hash(int x);
void insertDictionary (Dictionary D, int x);
void deleteDictionary (Dictionary D, int x);
int isMember(Dictionary D, int x);
void display (Dictionary D, int x);

int main () {
	
	Dictionary newDic;
	initDictionary (newDic);
	
	insertDictionary (newDic, 10);
	insertDictionary (newDic, 7);
	insertDictionary (newDic, 20);
	insertDictionary (newDic, 17);
	
	//deleteDictionary (newDic, 10);
	//deleteDictionary (newDic, 17);
	
	int retval = isMember (newDic, 20);
	
	insertDictionary (newDic, 30);
	insertDictionary (newDic, 40);
	insertDictionary (newDic, 50);
	
	display(newDic, 0); //print sub-group 0
	
	return 0;
}

void initDictionary (Dictionary D) {
	int x;
	
	for (x = 0; x < SIZE; x++) {
		D[x] = NULL;
	}
	
}

int hash(int x){
	return (x % SIZE);  //return digit in ones place
}

void insertDictionary (Dictionary D, int x) {
	int hashval = hash(x);
	
	LIST temp = (LIST) malloc (sizeof(struct node));
	LIST *trav = &D[hashval];
	
	
	for (; (*trav) != NULL && (*trav)->data <= x; trav = &(*trav)->link) {}
		
		temp->data = x;
		temp->link = *trav;
		*trav = temp;
}


void deleteDictionary (Dictionary D, int x) {
	int hashval= hash(x);
	LIST temp;
	LIST *trav;
	
	if (D[hashval] != NULL) {
		for (trav = &D[hashval]; (*trav) != NULL && (*trav)->data != x; trav = &(*trav)->link) {}
		
		temp = *trav;
		*trav = temp->link;
		free(temp);
	}	
}
int isMember(Dictionary D, int x) {
	int hashval = hash(x);
	
	LIST trav;
	
	for (trav = D[hashval]; trav != NULL && trav->data != x; trav = trav->link) {}
	
	return (trav != NULL)? 0:1;
	
}
void display (Dictionary D, int x) {
	int hashval = hash(x);
	
	LIST trav;
	
	for (trav = D[hashval]; trav != NULL; trav = trav->link) {
		printf("%d ", trav->data);
	}
}

