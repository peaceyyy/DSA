// dictionary - closed hashing (variation 3) operations

/* c visualization links:

 - insert()
https://pythontutor.com/visualize.html#code=//%20dictionary%20-%20closed%20hashing%20%28variation%203%29%20operations%0A%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%23define%20MAX%2020%0A%23define%20EMPTY%200%0A%23define%20DELETED%20-1%0A%0Atypedef%20struct%20node%20%7B%0A%20%20%20%20char%20data%3B%0A%20%20%20%20int%20link%3B%0A%7Dnodetype%3B%0A%0Atypedef%20struct%20%7B%0A%20%20%20%20nodetype%20Nodes%5BMAX%5D%3B%0A%20%20%20%20int%20avail%3B%0A%7DDictionary%3B%0A%0A//function%20prototypes%0Avoid%20initialize%28Dictionary%20*D%29%3B%0Aint%20hash%28char%20x%29%3B%0Aint%20isMember%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%3B%0A%0Avoid%20main%20%28%29%20%7B%0A%20%20%20%20%0A%20%20%20%20Dictionary%20D%3B%0A%20%20%20%20initialize%20%28%26D%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'a'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'b'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'c'%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'k'%29%3B%20//107%0A%20%20%20%20insert%28%26D,%20'l'%29%3B%20//108%0A%20%20%20%20insert%28%26D,%20'm'%29%3B%20//109%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'u'%29%3B%20//117%0A%20%20%20%20insert%28%26D,%20'v'%29%3B%20//118%0A%20%20%20%20insert%28%26D,%20'w'%29%3B%20//119%0A%7D%0A%0Avoid%20initialize%28Dictionary%20*D%29%20%7B%0A%20%20%20%20D-%3Eavail%20%3D%20MAX%20/%202%3B%0A%20%20%20%20int%20index%3B%0A%20%20%20%20%0A%20%20%20%20//initialize%20prime%20data%20area%20to%20EMPTY%0A%20%20%20%20for%20%28index%20%3D%200%3B%20index%20%3C%20D-%3Eavail%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.data%20%3D%20EMPTY%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20//link%20all%20nodes%20in%20synonym%20area%0A%20%20%20%20for%20%28index%20%3D%20D-%3Eavail%3B%20index%20%3C%20MAX%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.link%20%3D%20index%20%2B%201%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20D-%3ENodes%5Bindex-1%5D.link%20%3D%20-1%3B%0A%7D%0A%0Aint%20hash%28char%20x%29%20%7B%0A%20%20%20%20return%20%28x%20%25%2010%29%3B%0A%7D%0A%0Aint%20isMember%20%28Dictionary%20D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp,%20retval%20%3D%20-1%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D.Nodes%5Bhashval%5D.data%20!%3D%20x%29%20%7B%0A%20%20%20%20%20%20%20%20for%20%28temp%20%3D%20D.Nodes%5Bhashval%5D.link%3B%20temp%20!%3D%20-1%20%26%26%20D.Nodes%5Btemp%5D.data%20!%3D%20x%20%3B%20temp%20%3D%20D.Nodes%5Btemp%5D.link%29%20%7B%7D%0A%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20if%20%28temp%20!%3D%20-1%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20retval%20%3D%200%3B%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20return%20retval%3B%0A%7D%0A%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20%3D%3D%20EMPTY%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20-1%3B%0A%20%20%20%20%7D%20else%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20temp%20%3D%20D-%3ENodes%5BD-%3Eavail%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.link%20%3D%20D-%3ENodes%5Bhashval%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20D-%3Eavail%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3Eavail%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%7D%0A%7D&cumulative=false&curInstr=167&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false

 - delete ()
https://pythontutor.com/visualize.html#code=//%20dictionary%20-%20closed%20hashing%20%28variation%203%29%20operations%0A%0A%23include%20%3Cstdio.h%3E%0A%23include%20%3Cstdlib.h%3E%0A%0A%23define%20MAX%2020%0A%23define%20EMPTY%200%0A%23define%20DELETED%20-1%0A%0Atypedef%20struct%20node%20%7B%0A%20%20%20%20char%20data%3B%0A%20%20%20%20int%20link%3B%0A%7Dnodetype%3B%0A%0Atypedef%20struct%20%7B%0A%20%20%20%20nodetype%20Nodes%5BMAX%5D%3B%0A%20%20%20%20int%20avail%3B%0A%7DDictionary%3B%0A%0A//function%20prototypes%0Avoid%20initialize%28Dictionary%20*D%29%3B%0Aint%20hash%28char%20x%29%3B%0Aint%20isMember%28Dictionary%20D,%20char%20x%29%3B%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%3B%0Avoid%20deleteElem%20%28Dictionary%20*D,%20char%20x%29%3B%0A%0A%0Avoid%20main%20%28%29%20%7B%0A%20%20%20%20%0A%20%20%20%20Dictionary%20D%3B%0A%20%20%20%20initialize%20%28%26D%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'a'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'b'%29%3B%20%0A%20%20%20%20insert%28%26D,%20'c'%29%3B%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'k'%29%3B%20//107%0A%20%20%20%20insert%28%26D,%20'l'%29%3B%20//108%0A%20%20%20%20insert%28%26D,%20'm'%29%3B%20//109%0A%20%20%20%20%0A%20%20%20%20insert%28%26D,%20'u'%29%3B%20//117%0A%20%20%20%20insert%28%26D,%20'v'%29%3B%20//118%0A%20%20%20%20insert%28%26D,%20'w'%29%3B%20//119%0A%20%20%20%20%0A%20%20%0A%20%20%20%20deleteElem%28%26D,%20'a'%29%3B%0A%20%20%20%20deleteElem%28%26D,%20'l'%29%3B%0A%20%20%20%20deleteElem%28%26D,%20'w'%29%3B%0A%7D%0A%0Avoid%20initialize%28Dictionary%20*D%29%20%7B%0A%20%20%20%20D-%3Eavail%20%3D%20MAX%20/%202%3B%0A%20%20%20%20int%20index%3B%0A%20%20%20%20%0A%20%20%20%20//initialize%20prime%20data%20area%20to%20EMPTY%0A%20%20%20%20for%20%28index%20%3D%200%3B%20index%20%3C%20D-%3Eavail%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.data%20%3D%20EMPTY%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20//link%20all%20nodes%20in%20synonym%20area%0A%20%20%20%20for%20%28index%20%3D%20D-%3Eavail%3B%20index%20%3C%20MAX%3B%20index%2B%2B%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bindex%5D.link%20%3D%20index%20%2B%201%3B%0A%20%20%20%20%7D%0A%20%20%20%20%0A%20%20%20%20D-%3ENodes%5Bindex-1%5D.link%20%3D%20-1%3B%0A%7D%0A%0Aint%20hash%28char%20x%29%20%7B%0A%20%20%20%20return%20%28x%20%25%2010%29%3B%0A%7D%0A%0A%0A%0Avoid%20insert%28Dictionary%20*D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20%3D%3D%20EMPTY%29%20%7B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20-1%3B%0A%20%20%20%20%7D%20else%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20temp%20%3D%20D-%3ENodes%5BD-%3Eavail%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.data%20%3D%20x%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5BD-%3Eavail%5D.link%20%3D%20D-%3ENodes%5Bhashval%5D.link%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.link%20%3D%20D-%3Eavail%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3Eavail%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%7D%0A%7D%0A%0Avoid%20deleteElem%20%28Dictionary%20*D,%20char%20x%29%20%7B%0A%20%20%20%20int%20hashval%20%3D%20hash%28x%29%3B%0A%20%20%20%20int%20temp%3B%0A%20%20%20%20%0A%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20!%3D%20EMPTY%29%20%7B%0A%20%20%20%20%20%20%20%20if%20%28D-%3ENodes%5Bhashval%5D.data%20%3D%3D%20x%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Bhashval%5D.data%20%3D%20DELETED%3B%0A%20%20%20%20%20%20%20%20%7D%20else%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20for%20%28temp%20%3D%20D-%3ENodes%5Bhashval%5D.link%3B%20temp%20!%3D%20-1%20%26%26%20D-%3ENodes%5Btemp%5D.data%20!%3D%20x%20%3B%20temp%20%3D%20D-%3ENodes%5Btemp%5D.link%29%20%7B%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%20%20%20%20%20%20%20%20if%20%28temp%20!%3D%20-1%29%20%7B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Btemp%5D.data%20%3D%20DELETED%3B%20%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20D-%3ENodes%5Btemp%5D.link%20%3D%20D-%3Eavail%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20%20D-%3Eavail%20%3D%20temp%3B%0A%20%20%20%20%20%20%20%20%20%20%20%20%7D%20%20%20%20%0A%20%20%20%20%20%20%20%20%7D%0A%20%20%20%20%20%20%20%20%20%20%20%20%0A%20%20%20%20%7D%0A%7D&cumulative=false&curInstr=208&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define EMPTY 0
#define DELETED -1 

typedef struct node {
	char data;
	int link;
}nodetype;

typedef struct {
	nodetype Nodes[MAX];
	int avail;
}Dictionary;

//function prototypes
void initialize(Dictionary *D);
int hash(char x);
int isMember(Dictionary D, char x);
void insert(Dictionary *D, char x);
void deleteElem (Dictionary *D, char x);

void main () {
	
	int retval;
	Dictionary D;
	initialize (&D);
	
	
	insert(&D, 'a'); //97
	insert(&D, 'b'); //98
	insert(&D, 'c'); //99
	
	insert(&D, 'k'); //107
	insert(&D, 'l'); //108
	insert(&D, 'm'); //109
	
	insert(&D, 'u'); //117
	insert(&D, 'v'); //118
	insert(&D, 'w'); //119
	
	
	retval = isMember(D, 'a');
	printf("%d", retval);
	retval = isMember(D, 'l');
	printf("%d", retval);
	retval = isMember(D, 'w');
	printf("%d", retval);
	
	retval = isMember(D, 'd');
	printf("\n%d", retval);
	retval = isMember(D, 'h');
	printf("%d", retval);
	retval = isMember(D, 'e');
	printf("%d", retval);
	
	
	deleteElem(&D, 'a');
	deleteElem(&D, 'l');
	deleteElem(&D, 'w');
	
}

void initialize(Dictionary *D) {
	D->avail = MAX / 2;
	int index;
	
	//initialize prime data area to EMPTY
	for (index = 0; index < D->avail; index++) {
		D->Nodes[index].data = EMPTY;
	}
	
	//link all nodes in synonym area
	for (index = D->avail; index < MAX; index++) {
		D->Nodes[index].link = index + 1;
	}
	
	D->Nodes[MAX-1].link = -1;
}

int hash(char x) {
	return (x % 10);
}

int isMember (Dictionary D, char x) {
	int hashval = hash(x);
	int temp = 0, retval = -1;
	
	if (D.Nodes[hashval].data != EMPTY) {
		if (D.Nodes[hashval].data != x) {
			for (temp = D.Nodes[hashval].link; temp != -1 && D.Nodes[temp].data != x ; temp = D.Nodes[temp].link) {}
		}
		if (temp != -1) {
				retval = 0;
			}
	}
	
	return retval;
}

void insert(Dictionary *D, char x) {
	int hashval = hash(x);
	int temp;
	
	if (D->Nodes[hashval].data == EMPTY) {
		D->Nodes[hashval].data = x;
		D->Nodes[hashval].link = -1;
	} else {
		//insertFirst()
		 	temp = D->Nodes[D->avail].link;
		 	
			D->Nodes[D->avail].data = x;
			
			D->Nodes[D->avail].link = D->Nodes[hashval].link;
			D->Nodes[hashval].link = D->avail;
			D->avail = temp;
		}
}

void deleteElem (Dictionary *D, char x) {
	int hashval = hash(x);
	int temp;
	
	if (D->Nodes[hashval].data != EMPTY) {
		if (D->Nodes[hashval].data == x) {
			D->Nodes[hashval].data = DELETED;
		} else {
			for (temp = D->Nodes[hashval].link; temp != -1 && D->Nodes[temp].data != x ; temp = D->Nodes[temp].link) {}
			
			if (temp != -1) {
				D->Nodes[temp].data = DELETED; 
				D->Nodes[temp].link = D->avail;
				D->avail = temp;
			}	
		}
			
	}
}

