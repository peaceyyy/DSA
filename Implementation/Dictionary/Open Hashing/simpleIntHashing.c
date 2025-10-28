#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 18

typedef struct node
{
    int data;
    struct node *link;
} *LIST, node_t;

typedef LIST Dictionary[MAX];

void initDictionary(Dictionary D);
int goldenHashInt(int data);
void insertElem(Dictionary D, int data);
void deleteElem(Dictionary D, int data);
bool isMember(Dictionary D, int data);
void display(Dictionary D);

int main()
{
    Dictionary D;
    initDictionary(D);

    // Test insertions
    insertElem(D, 42);
    insertElem(D, 17);
    insertElem(D, 89);
    insertElem(D, 23);
    insertElem(D, 56);

    printf("After insertions:\n");
    display(D);

    // Test duplicate insertion
    insertElem(D, 42); // Should detect duplicate

    // Test deletion
    printf("\nIs 17 in dictionary? %s\n", isMember(D, 17) ? "Yes" : "No");
    deleteElem(D, 17);
    printf("\nAfter deleting 17:\n");
    display(D);

    // Test membership
    printf("\nMembership tests:\n");
    printf("Is 17 in dictionary? %s\n", isMember(D, 17) ? "Yes" : "No");
    printf("Is 17 in dictionary? %s\n", isMember(D, 17) ? "Yes" : "No");
    printf("Is 89 in dictionary? %s\n", isMember(D, 89) ? "Yes" : "No");

    return 0;
}

int goldenHashInt(int data)
{

    return (31 * data) % MAX;
}

void initDictionary(Dictionary D)
{
    // TODO: Initialize all buckets to NULL
    for (int i = 0; i < MAX; i++)
    {
        D[i] = NULL;
    }
}

void display(Dictionary D)
{
    for (int i = 0; i < MAX; i++)
    {
        printf("[%2d]: ", i);
        for (LIST curr = D[i]; curr != NULL; curr = curr->link)
        {
            printf("%d -> ", curr->data);
        }
        printf("NULL\n");
    }
}

void insertElem(Dictionary D, int data)
{
    // TODO: Implement insertion with duplicate prevention
    // Steps:
    // 1. Check if element already exists using isMember()

    if (isMember(D, data) != 1)
    {
        // 3. If not exists, create new node

        LIST newNode = (LIST)malloc(sizeof(node_t));
        newNode->data = data;
        newNode->link = NULL;

        LIST *trav;
        int hashValue = goldenHashInt(data);

        for (trav = &D[hashValue]; *trav != NULL; trav = &(*trav)->link)
        {
        };

        *trav = newNode;
    }
    else
    { // 2. If exists, print message and return
        printf("\nElement is already in the dictionary!");
    }
}

void deleteElem(Dictionary D, int data)
{
    int hashValue = goldenHashInt(data);
    if (D[hashValue] != NULL)
    {
        LIST *trav;
        for (trav = &D[hashValue]; trav != NULL && (*trav)->data != data; trav = &(*trav)->link)
        {
        }

        if (*trav != NULL)
        {
            LIST temp = *trav;
            *trav = temp->link;
            free(temp);
        }
        else
        {
            printf("\nElement is not in dictionary!");
        }
    }
}

bool isMember(Dictionary D, int data)
{
    // TODO: Implement membership test
    // Steps:
    // 1. Hash to find correct bucket
    int hashValue = goldenHashInt(data);
    int found = 0;

    if (D[hashValue] != NULL)
    {

        LIST trav;

        for (trav = D[hashValue]; trav != NULL && found != 1; trav = trav->link)
        {

            if (trav->data == data)
            {
                found = 1;
            }
        }
    }

    return found;
}