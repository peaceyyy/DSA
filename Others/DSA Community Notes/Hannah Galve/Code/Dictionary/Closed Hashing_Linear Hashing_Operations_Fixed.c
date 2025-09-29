// Closed Hashing - Linear Hashing Operations

// c visualization
// https://pythontutor.com/visualize.html#code=//%20Closed%20Hashing%20-%20Linear%20Hashing%20Operations%0A%0A%23include%20%3Cstdio.h%3E%0A%0A%23define%20MAX%2010%0A%23define%20EMPTY%20'%20'%0A%23define%20DELETED%20'!'%20%0A%0Atypedef%20char%20Dictionary%5BMAX%5D%3B%0A%0A//function%20prototypes%0Avoid%20initD%28Dictionary%20D%29%3B%0Aint%20hash%28char%20x%29%3B%0Aint%20member%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20insertD%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20deleteD%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20displayD%28Dictionary%20D%29%3B%0A%0Avoid%20main%20%28%29%7B%0A%20%20%20%20Dictionary%20D%3B%0A%20%20%20%20initD%28D%29%3B%0A%20%20%20%20%0A%20%20%20%20//insert%0A%20%20%20%20insertD%28D,%20'a'%29%3B%0A%20%20%20%20%0A%20%20%20%20insertD%28D,%20'b'%29%3B%0A%20%20%20%20%0A%20%20%20%20insertD%28D,%20'c'%29%3B%0A%20%20%20%20insertD%28D,%20'd'%29%3B%0A%20%20%20%20insertD%28D,%20'e'%29%3B%0A%20%20%20%20insertD%28D,%20'f'%29%3B%0A%20%20%20%20displayD%28D%29%3B%0A%20%20%20%20%0A%20%20%20%20//delete%0A%20%20%20%20deleteD%28D,%20'f'%29%3B%0A%20%20%20%20displayD%28D%29%3B%0A%20%20%20%20%0A%20%20%20%20deleteD%28D,%20'a'%29%3B%0A%20%20%20%20deleteD%28D,%20'b'%29%3B%0A%20%20%20%20deleteD%28D,%20'h'%29%3B%0A%20%20%20%20displayD%28D%29%3B%0A%20%20%20%20%0A%20%20%20%20//reinsert%0A%20%20%20%20insertD%28D,%20'a'%29%3B%0A%20%20%20%20displayD%28D%29%3B%0A%20%20%20%20insertD%28D,%20's'%29%3B%0A%20%20%20%20displayD%28D%29%3B%0A%7D%0A%0Avoid%20initD%28Dictionary%20D%29%20%7B%0A%20%20%20%20int%20x%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28x%20%3D%200%3B%20x%20%3C%20MAX%3B%20x%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D%5Bx%5D%20%3D%20EMPTY%3B%0A%20%20%20%20%7D%0A%7D%0A%0Aint%20hash%28char%20x%29%20%7B%0A%20%20%20%20return%20%28x%20%25%2010%29%3B%0A%7D%0A%0Aint%20member%28Dictionary%20D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp,%20retval%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28temp%20%3D%20hashval%3B%20temp%20%3C%20MAX%20%26%26%20D%5Btemp%5D%20!%3D%20EMPTY%20%26%26%20D%5Btemp%5D%20!%3D%20x%3B%20temp%20%3D%20%28temp%20%2B%201%29%20%25%20MAX%29%20%7B%7D%0A%20%20%20%20%0A%20%20%20%20return%20retval%20%3D%20%28temp%20!%3D%20MAX%29%3F%200%20%3A%201%3B%0A%7D%0A%0Avoid%20insertD%28Dictionary%20D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28temp%20%3D%20hashval%3B%20temp%20%3C%20MAX%20%26%26%20D%5Btemp%5D%20!%3D%20EMPTY%20%26%26%20D%5Btemp%5D%20!%3D%20DELETED%3B%20temp%20%3D%20%28temp%20%2B%201%29%20%25%20MAX%29%20%7B%7D%0A%20%20%20%20%0A%20%20%20%20if%20%28temp%20!%3D%20MAX%29%20%7B%0A%20%20%20%20%20%20%20%20D%5Btemp%5D%20%3D%20x%3B%0A%20%20%20%20%7D%0A%7D%0A%0Avoid%20deleteD%28Dictionary%20D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20for%20%28temp%20%3D%20hashval%3B%20temp%20%3C%20MAX%20%26%26%20D%5Btemp%5D%20!%3D%20x%3B%20temp%20%3D%20%28temp%20%2B%201%29%20%25%20MAX%29%20%7B%7D%0A%20%20%20%20%0A%20%20%20%20if%20%28temp%20!%3D%20MAX%29%20%7B%0A%20%20%20%20%20%20%20%20D%5Btemp%5D%20%3D%20DELETED%3B%0A%20%20%20%20%7D%0A%0A%7D%0A%0Avoid%20displayD%28Dictionary%20D%29%20%7B%0A%20%20%20%20int%20x%3B%0A%20%20%20%20%0A%20%20%20%20printf%28%22%5Cn%5Cn%20%20%20%20%20WHOLE%20DICTIONARY%20%5Cn%22%29%3B%0A%20%20%20%20printf%28%22%5Cn%20INDEX%20%20%20%20%20%20%20%20%20%20%20%20ELEMENT%20%20%20%20%20%20%20%20%20%20HASH%20VALUE%20%22%29%3B%0A%20%20%20%20for%20%28x%20%3D%200%3B%20x%20%3C%20MAX%3B%20x%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20printf%28%22%5Cn%20%20%20%25d%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%25c%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%25d%22,%20x,%20D%5Bx%5D,%20hash%28D%5Bx%5D%29%29%3B%0A%20%20%20%20%7D%0A%7D&cumulative=false&curInstr=223&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false

// fixed pt.2 
 
#include <stdio.h>

#define MAX 10
#define EMPTY ' '
#define DELETED '!' 

typedef char Dictionary[MAX];

//function prototypes
void initD(Dictionary D);
int hash(char x);
int member(Dictionary D, char x);
void insertD(Dictionary D, char x);
void deleteD(Dictionary D, char x);
void displayD(Dictionary D);

void main (){
	Dictionary D;
	initD(D);
	
	printf("\n--------------- INITIAL DICTIONARY -------------------\n");
	displayD(D);
	
	//insert
	printf("\n\n--------------- Insert: 'a' & 'b' -------------------\n");
	insertD(D, 'a');
	displayD(D);
	
	insertD(D, 'b');
	displayD(D);
	
	printf("\n\n--------------- Insert: 'c' to 'k' -------------------\n");
	insertD(D, 'c');
	insertD(D, 'd');
	insertD(D, 'e');
	insertD(D, 'f');
	insertD(D, 'g');
	insertD(D, 'h');
	insertD(D, 'i');
	insertD(D, 'j');
	insertD(D, 'k'); //overfill test
	displayD(D);
	
	//delete
	printf("\n\n--------------- Delete: 'f'   -------------------\n");
	deleteD(D, 'f');
	displayD(D);
	
	printf("\n\n--------------- Delete: 'a' , 'b' , 'h'  -------------------\n");
	deleteD(D, 'a');
	deleteD(D, 'b');
	deleteD(D, 'h');
	displayD(D);
	
	//reinsert
	printf("\n\n--------------- Reinsert: 'a' , 's'  -------------------\n");
	insertD(D, 'a');
	displayD(D);
	insertD(D, 's');
	displayD(D);
	
	//member
	char elem = 'a';
	printf("\n\n\nIs ' %c ' a member? ", elem);
	(member(D, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 's';
	printf("\n\nIs ' %c ' a member? ", elem);
	(member(D, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	elem = 'z';
	printf("\n\nIs ' %c ' a member? ", elem);
	(member(D, elem) == 0)? printf("Yes, it's a member.") : printf("No, it's not a member.");
}

void initD(Dictionary D) {
	int x;
	
	for (x = 0; x < MAX; x++) {
		D[x] = EMPTY;
	}
}

int hash(char x) {
	return (x % 10);
}

int member(Dictionary D, char x) {
	int hashval = hash(x);
	int temp, retval;
	
	if (D[hashval] != x) {          // loop around      // when matched
		for (temp = hashval + 1; temp != hashval && D[temp] != x; temp = (temp + 1) % MAX) {} //temp = ((temp + 1) % MAX
	}
	
	return retval = (temp != hashval)? 0 : 1;
	
}

void insertD(Dictionary D, char x) {
	int hashval = hash(x);
	int temp;
	
	if (D[hashval] != x) { // this basically fires if the place where it's suppose to be is already taken
		for (temp = hashval; member(D, D[temp]) != 1 && D[temp] != EMPTY && D[temp] != DELETED; temp = (temp + 1) % MAX) {}
			D[temp] = x;
	}
}

void deleteD(Dictionary D, char x) {
	int hashval = hash(x);
	int temp = hashval;
	
	if (D[hashval] != x) {
		for (temp = hashval + 1; temp != hashval && D[temp] != x; temp = (temp + 1) % MAX) {}
	}
		D[temp] = DELETED;
	

}

void displayD(Dictionary D) {
	int x;
	
	printf("\n INDEX            ELEMENT          HASH VALUE ");
	for (x = 0; x < MAX; x++) {
		printf("\n   %d                %c                   %d", x, D[x], hash(D[x]));
	}
}


