#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 15
#define DELETED "\0"
#define EMPTY ""

typedef char *Dictionary[MAX];

// function prototypes
void initHashTable(Dictionary D);
int HASHCII(char name[]);
void displayHashTable(Dictionary D);
void insertElem(Dictionary D, char name[]);
void deleteElem(Dictionary D, char name[]);
bool isMember(Dictionary D, char name[]);

int main()
{

	Dictionary D;
	initHashTable(D);

	insertElem(D, "Hello");
	insertElem(D, "Not Hello");
	insertElem(D, "Hello");
	insertElem(D, "Hello");
	insertElem(D, "World");
	// deleteElem(D, "World");
	insertElem(D, "Steve");
	insertElem(D, "is");
	insertElem(D, "going");
	insertElem(D, "to");
	insertElem(D, "London");
	insertElem(D, "to");
	insertElem(D, "Hi");
	insertElem(D, "Hi");
	// deleteElem(D, "Hi");
	displayHashTable(D);
	
	char *name = "Hi";
	printf("\nIs ' %s ' a member? ", name);
	(isMember(D, name) != 0) ? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	name = "Not Hello";
	printf("\nIs ' %s ' a member? ", name);
	(isMember(D, name) != 0) ? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	name = "Borderline";
	printf("\nIs ' %s ' a member? ", name);
	(isMember(D, name) != 0) ? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	name = "Not present";
	printf("\nIs ' %s ' a member? ", name);
	(isMember(D, name) != 0) ? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	insertElem(D, "Not present");
	printf("\nIs ' %s ' a member? ", name);
	(isMember(D, name) != 0) ? printf("Yes, it's a member.") : printf("No, it's not a member.");
	
	printf("\n\n");
	displayHashTable(D);
}

void displayHashTable(Dictionary D)
{
	int x;
	int avgSL = 0, elemCount = 0;
	printf("\n Index     Content     Hash Value     Search Length");

	for (x = 0; x < MAX; x++)
	{
		printf("\n  %d", x);
		if ((strcmp(D[x], EMPTY) != 0) && (strcmp(D[x], DELETED) != 0))
		{
			printf("         %s          %d          %d", D[x], HASHCII(D[x]), (x - HASHCII(D[x]) + MAX) % MAX + 1);

			avgSL += (x - HASHCII(D[x]) + MAX) % MAX + 1;
			elemCount++; 
		}
		else if (strcmp(D[x], EMPTY) == 0)
		{
			printf("         EMPTY");
		}
		else
		{
			printf("       DELETED");
		}
	}

	printf("\n--------------\n");
	printf("Average SL = %d\n", avgSL / elemCount);
	printf("# of elements = %d\n", elemCount);
	
}

int HASHCII(char name[])
{

	int asciiCount = 0, i = 0;

	while (name[i] != '\0')
	{
		asciiCount += name[i];
		i++;
	}

	return asciiCount % MAX;
}

void initHashTable(Dictionary D)
{
	for (int i = 0; i < MAX; i++)
	{
		D[i] = EMPTY;
	}
}

void insertElem(Dictionary D, char name[])
{

	int hashValue = HASHCII(name);

	if (strcmp(D[hashValue], name) != 0)
	{
		if (strcmp(D[hashValue], EMPTY) != 0)
		{
			printf("\n Collision at Hash Value %d. I am now going to l i n e a r p r o b e\n", hashValue);
			int temp;
			for (temp = hashValue + 1; temp != hashValue && strcmp(D[temp], name) != 0 && (strcmp(D[temp], EMPTY) != 0) && (strcmp(D[temp], DELETED) != 0); temp = (temp + 1) % MAX)
			{
			};

			if (strcmp(D[temp], name) == 0)
			{

				printf("\n%s is already in dictionary\n", name);
			} else if (temp != -1)
			{
				D[temp] = name;
			}
			else
			{
				printf("Dictionary is full!");
			}
		}
		else
		{
			D[hashValue] = name;
		}
	}
	else
	{
		printf("\n%s is already in dictionary\n", name);
	}
}

void deleteElem(Dictionary D, char name[])
{
	int hashValue = HASHCII(name);
	if (strcmp(D[hashValue], EMPTY) != 0)
	{
		if ((strcmp(D[hashValue], name) != 0)) // element is not in home slot
		{
			int temp;
			for (temp = hashValue + 1; temp != hashValue && (strcmp(D[temp], EMPTY) != 0) && (strcmp(D[temp], name) != 0); temp = (temp + 1) % MAX)
			{
			};

			if (temp != -1)
			{
				D[temp] = DELETED;
			}
			else
			{
				printf("\n%s is not in Dictionary\n", name);
			}
		}
		else
		{
			D[hashValue] = DELETED;
		}
	}
	else
	{
		printf("\n%s is not in Dictionary\n", name);
	}
}

bool isMember (Dictionary D, char name[]){

	int hashValue= HASHCII(name);
	int found = 0;

	if (strcmp(D[hashValue], EMPTY) != 0)
	{
		if (strcmp(D[hashValue], name) == 0)
		{
			found = 1;
		}
		
		else {
			int temp;
			int flag = 0;
			for (temp = hashValue + 1; flag == 0 && temp != hashValue; temp = (temp + 1) % MAX){

				if ( strcmp(D[temp], name) == 0){
					found = 1;
					flag = 1;
				} else if (strcmp(D[temp], EMPTY) == 0){
					flag = 1;
				}
			}
		}
	}

	return found;
}