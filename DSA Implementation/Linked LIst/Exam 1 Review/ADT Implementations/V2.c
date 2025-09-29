// List is a structure with an array & variable count (a variable that keeps track of the number of elements in the array list)

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef struct
{

    int elems[MAX];
    int count;

} *LIST;

void initList(LIST *L)
{
    *L = malloc(sizeof(LIST)); // remember to malloc if pointer to struct
    (*L)->count = 0;
}

void insertElem(LIST *L, int elem)
{

    if ((*L)->count < MAX)
    {

        (*L)->elems[(*L)->count++] = elem;
    }
}

void insertElemAtPos(LIST L, int elem, int pos)
{

    if (L->count < MAX && (pos >= 0 && pos < MAX))
    {

        for (int i = L->count; i > pos; i--)
        {
            L->elems[i] = L->elems[i - 1];
        }

        L->elems[pos] = elem;
        L->count = L->count + 1;
    }
}

void deleteElem(LIST L, int elem)
{

    int i;
    for (i = 0; i < L->count && L->elems[i] != elem; i++)
    {
    }

    if (i < L->count)
    {

        for (int j = i; j < L->count; j++)
        {
            L->elems[j] = L->elems[j + 1];
        }
        L->count--;
    }
}

void deleteAllOccurrences(LIST L, int elem)
{

    int i = 0;

    while (i < L->count)
    {

        if (L->elems[i] == elem)
        {

            for (int j = i; j < L->count; j++)
            {
                L->elems[j] = L->elems[j + 1];
            }
            L->count--;
        }

        else
        {

            i++;
        }
    }
}
void searchElem(LIST L, int elem)
{
    int i;
    for (i = 0; i < L->count && L->elems[i] != elem; i++)
    {
    }

    if (i < L->count)
    {
        printf("%d is at index %d", elem, i);
    }
    else
    {
        printf("Element not found!");
    }
}
void displayList(LIST L)
{

    for (int i = 0; i < L->count; i++)
        printf("%d ", L->elems[i]);
}

int main()
{

    LIST L;
    initList(&L);

    insertElem(&L, 2);
    insertElem(&L, 2);
    insertElem(&L, 2);
    insertElem(&L, 4);

    displayList(L);

    printf("\n\n");

    deleteAllOccurrences(L, 2);
    displayList(L);

    printf("\n\n");
    searchElem(L, 2);
}
