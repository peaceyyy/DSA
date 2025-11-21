#include<stdio.h>
#include<stdlib.h>
#include"decode.h"
/*

	short int word[4]={17729,21074,18766,18259};
	int *arr;
	char *string;
	int choice;

*/
// Write your functions here...
int* bitmaskToArray(short int word[])
{
    const int WORDS = 4;
    const int BITS = sizeof(unsigned short) * 8; // 16
    int *bitVectorArr = malloc(WORDS * BITS * sizeof(int));
    int ndx = 0;
    
    for (int i = 0; i < WORDS; i++)
    {
        for (int mask = BITS - 1; mask >= 0; --mask)
        {
            bitVectorArr[ndx++] = ((unsigned short) word[i] >> mask) & 1;
        }
    }
    
    for (int i = 0; i < 8; i++)
    {
        printf("%d", bitVectorArr[i]);
        // printf("\n")
    }
    
    return bitVectorArr;

} decodeString(int arr[])
{
    // array to 8 letter string??
    // char* decodedString;
  
    
    // for (int i = 0; i < 4; i++)
    // {
    //     for (i > )
        
    // }
        
    //     // printf("\n");
    
    // }
    
    // return 
  
}
void displayBitPattern(int arr[])
{   
    // int size = sizeof(arr[0])/sizeof(arr);
    
    for (int i = 0; i <  3; i++)
    {
            printf("this fired!\n");
        int mask = 0;
        while (mask > 8)
        {
            printf("%d ", arr[mask]);
            mask++;
        }
        printf(" ");
    }
}