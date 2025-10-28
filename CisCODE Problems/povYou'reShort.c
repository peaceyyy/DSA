/*
    POV: You're short and at the back of the class
    By Ma. Crista Niña Ariosa

    Data Structures and Algorithms

    Start Date: September 20, 2025
    Completion Date: September 20, 2025

    After Affinity Week, it's finally class time! You wake up early, make it through traffic, and arrive in time for your first subject. You're hoping that you could sit beside your best friend this time!

    However, your professor decided to arrange all of you in alphabetical order instead. To your horror, your last name is way on the other end of the alphabet, so you have no choice but to sit on the back row. To make things worse, your classmates in front of you are taller than you are, so you can't see the board easily.

    Instead of complaining to your professor about this obviously unfair seating arrangement, you decided to wonder: how many students in your column could actually see the board? (unlike your unfortunate self, that is)

    Your task is to determine how many students in a column can see the board. Given an array column containing the heights of each student, assume that a student "can see the board" if all students in front of them are shorter than them.

    ASSUMPTIONS:
    1. The first element in the array equates to the student in front of the class.
    2. If a student in front of you has the same height, you cannot see the board.
    3. Heights are all integers.

    Do not modify the code except for canSeeBoard()!
*/




#include <stdio.h>

#define SIZE 100

typedef struct
{
    int arr[SIZE];
    int top;
} Stack;

void init(Stack *S);
void push(Stack *S, int x);
void pop(Stack *S);
int top(Stack S);
int canSeeBoard(int column[], int length); // TODO

int main()
{
    int len;
    int col[SIZE];
    printf("How many students in a column: ");
    scanf("%d", &len);

    printf("Enter the heights of the students (in inches): \n");
    for (int i = 0; i < len; i++) {
        scanf("%d", &col[i]);
    }
    printf("In this column, only %d student(s) can see the board.\n", canSeeBoard(col, len));
}

int canSeeBoard(int column[], int length)
{
    int canSee = 1;

    Stack studentStack;
    init(&studentStack);

    for (int i = length; i >= 0; i--){

        // printf("pushing %d..\n", column[i]);
        push(&studentStack, column[i]);

    }

    int tallest = top(studentStack);
    // printf("front person: %d\n", tallest);
     pop(&studentStack);

    while (studentStack.top != -1){

        int currentPersonHeight = top(studentStack);
        if (currentPersonHeight > tallest ){

            tallest = currentPersonHeight;
            canSee++;
        } 
        pop(&studentStack);

    }

    return canSee;
}

void init(Stack *S)
{
    S->top = -1;
}

void push(Stack *S, int x)
{
    if (S->top != SIZE - 1)
    {
        S->arr[++(S->top)] = x;
    }
}

void pop(Stack *S)
{
    if (S->top != -1)
    {
        S->top--;
    }
}

int top(Stack S)
{
    return (S.top != -1) ? S.arr[S.top] : -1;
}
