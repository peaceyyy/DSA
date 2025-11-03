/*
/*
[E2] - Sabado Cipher - Decoding
by Janie Lane Sabado

Background:
 

Janie is going back to Davao for All Soul's day and her boyfriend is there to pick her up from the airport. Her boyfriend asked if there is anything she would want as a gift when she arrives and she replies with an encoded message. This encoded message is a series of 4 integer values that can be converted into an 8 letter word. It is now up to you to make sure that Janie's boyfriend will get her the correct gift for when she arrives.

 

Objective:
 

Create the three functions that is necessary in decoding the message in the file decode.c

int* bitmaskToArray(short int word[]) - this function takes the array of integers and returns a a bit vector array
char* decodeString(int arr[]) - this function takes the bit vector array and returns the 8 letter string
void displayBitPattern(int arr[]) - this function displays the bit pattern of the bit vector array
 

Notes:
Remember to terminate the end of the string with \0
Bit vector array is where each index of the array represents a boolean value: 0 or 1
Remember one character is 8 bits, given a binary 01011001 is 89 in decimal, it represents the character 'Y'
 

Decoding Guide:
 

Given the short integer value 22863, it is represented in bits as 0101100101001111. Those bits are then stored in a bit vector array and then converted to represent 2 letters.

 

short int val = 22863

bit representation: 0101100101001111
           letters: YO

Sample Output 

=== Sabado Cipher ===

Given the following integers, decode the numbers to form the 8 letter word
17729 21074 18766 18259

Enter test case choice:
1. Convert the decimal integers into a bit vector Array
2. Decode the String using the converted bit vector Array
3. Convert and Decode while displaying both

Choice: 1

Bit Pattern:
0100010101000001 0101001001010010 0100100101001110 0100011101010011
Sample Output 2

=== Sabado Cipher ===

Given the following integers, decode the numbers to form the 8 letter word
17729 21074 18766 18259

Enter test case choice:
1. Convert the decimal integers into a bit vector Array
2. Decode the String using the converted bit vector Array
3. Convert and Decode while displaying both

Choice: 3

Bit Pattern:
0100010101000001 0101001001010010 0100100101001110 0100011101010011

Decoded Message:
EARRINGS

*/


#include<stdio.h>
#include<stdlib.h>
#include"decode.h"

int main(){
	//short int word[4]={22863,21792,16961,19524};
	short int word[4]={17729,21074,18766,18259};
	int *arr;
	char *string;
	int choice;


    printf("=== Sabado Cipher ===\n\n");
	printf("Given the following integers, decode the numbers to form the 8 letter word\n");
	printf("%d %d %d %d\n\n",word[0],word[1],word[2],word[3]);

    printf("Enter test case choice: \n");
    printf("1. Convert the decimal integers into a bit vector Array\n");
    printf("2. Decode the String using the converted bit vector Array\n");
    printf("3. Convert and Decode while displaying both\n\nChoice: ");
    scanf("%d", &choice);

    printf("\n");
	switch(choice){
		case 1:
			arr=bitmaskToArray(word);
	        printf("Bit Pattern:\n");
			displayBitPattern(arr);
			free(arr);

			break;

		case 2:
			arr=bitmaskToArray(word);
			string=decodeString(arr);
			printf("\nDecoded Message:");
			printf("\n%s",string);
			free(string);
			break;

		case 3:
			arr=bitmaskToArray(word);
	        printf("Bit Pattern:\n");
			displayBitPattern(arr);
			string=decodeString(arr);
			printf("\n\nDecoded Message:");
			printf("\n%s",string);

			free(arr);
			free(string);

			break;

		default:
			printf("Invalid Choice");
			break;
	}



	return 0;

}