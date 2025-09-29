#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct
{

    int *elem;
    int count;

} charList;

void init(charList *L, int count)
{

    L->elem = malloc(sizeof(char) * SIZE);

    if (L->elem != NULL)
    {
        printf("Memory allocation failed");
    }

    else
    {
        L->count = 0;
    }
}

void delete(charList *L, char element)
{

    if (L->count == 0)
    {

        printf("list is empty");
    }

    else
    {

        int i;
        for (i = 0; i < L->count && L->elem[i] != element; i++)
        {
        }

        if (i == L->count)
        {

            printf("ELEMENT NOT FOUND");
        }
        else
        {

            for (; i < L->count; i++)
            {

                L->elem[i] = L->elem[i + 1];
            }

            L->count--;
        }
    }
}
void deleteAllOccurrences(charList *L, char element)
{

    if (L->count == 0)
    {

        printf("list is empty");
    }
    else
    {

        int ndx;
        for (ndx = 0; ndx < L->count;)
        {
            if (L->elem[ndx] == element)
            {
                for (int x = ndx; x < L->count; x++)
                    L->elem[x] = L->elem[x + 1];
                L->count--;
            }
            else
                ndx++;
        }

    }
}

void printCharList(charList *L)
{

    for (int i = 0; i < L->count; i++)
    {

        printf("%c ", L->elem[i]);
    }
}

int main()
{

    charList L;
    L.elem = malloc(sizeof(char) * SIZE);
    L.count = 4;
    L.elem[0] = 'u';
    L.elem[1] = 'c';
    L.elem[2] = 'c';
    L.elem[3] = 's';

       deleteAllOccurrences(&L, 'c');
    // delete(&L, 'c');
    printCharList(&L);

    return 0;
}