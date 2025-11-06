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
    
    // array to bit vvector
    
    // 8 bits, 4 words
    int* bitVectorArray = malloc(sizeof(int) * 16);
  
    
    for (int i = 0; i < 4; i++)
    {
        int currWord = word[i];
        int currNdx = 7; 
        
        while (currNdx >= 0)
        {

            // printf("currNdx: %d = [%d], ", currNdx, currWord % 2);
            bitVectorArray[i][currNdx--] = currWord % 2;
            currWord = currWord / 2;
        }
        
        // printf("\n");
    
    }
    // displayBitPattern(bitVectorArray);
    return bitVectorArray;

}
char* decodeString(int arr[])
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