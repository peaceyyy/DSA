// displaying array lists

#include <stdio.h>
#include <stdlib.h>

// data type definitions
typedef enum {TRUE, FALSE} boolean;


// function prototypes
void displayArray(int A[], int size);
int* inputArray();
boolean isMember(int A[], int size, int x);

void main () {
	
	int* List;
	int elem = 3;
	boolean check;
	
	printf("\n**** Task 1 **** \n");
	List = inputArray();
	displayArray(List+1, List[0]);
	
	printf("\n**** Task 2 **** \n");
	check = isMember(List+1,List[0],3);
	(check == TRUE) ? printf("Element is found! \n") : printf("Element is not found! \n");
	
	check = isMember(List+1,List[0],7);
	(check == TRUE) ? printf("Element is found! \n") : printf("Element is not found! \n");
	
}

void displayArray(int A[], int size) {
	int i;
	
	printf("\nElements in array list: \n");
	
	for (i = 0; i < size; i++) {
		printf("%d\n", A[i]);
	}
}
int* inputArray() {
	int N, ctr;
	
	printf("\nInput size of array: ");
	scanf("%d", &N);
	
	int* arr = (int*) malloc (sizeof(int)*(N+1));
	
	if (arr != NULL) {
		arr[0] = N;
		
		printf("\nInput numbers:\n");
		for (ctr = 1; ctr <= N; ctr++) {
			scanf("%d", &arr[ctr]);
		}
	}
	return arr;
}

boolean isMember(int A[], int size, int x) {
	int n;
	
	for (n = 0; n < size && A[n]!= x; n++) {}
	return (n < size) ? TRUE : FALSE;
}



