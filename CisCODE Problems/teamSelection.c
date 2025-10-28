/*

Team Project Selection By Ethan Andre Dalocanog
DSA Categories: Sets


You're managing a university project team with three departments:
   - Design
   - Programming
   - Marketing

Each department submitted a list of tools they want to use for the project. However, you can't use every tool — you need to decide which ones will actually be part of the final approved toolset.

Each tool is represented by a bit (1 = wants to use it, 0 = doesn't want it):
   - Index 0: Canva
   - Index 1: Figma
   - Index 2: GitHub
   - Index 3: Trello
   - Index 4: ChatGPT


Main Task:
Write a function called FindApprovedTools() that determines which tools will be officially approved, following these rules:

1. The Programming team's tools are mandatory — every approved tool must at least include everything Programming wants.
2. Tools that Design and Marketing both want are also automatically approved.
3. However, if Programming doesn't want a tool, and only Marketing wants it, that tool should NOT be approved. This means that Marketing-only choices are rejected.

This function should return a new SET representing all approved tools.


Implementation Rules:

You must use the provided Set Operations:
   - Union(A, B)
   - Intersection(A, B)
   - Difference(A, B)

Do NOT use loops or arithmetic to compute the logic directly inside FindApprovedTools().


Additional Tasks:

Implement the following set operation functions as well:
   - SET* Union(SET A, SET B);
   - SET* Intersection(SET A, SET B);
   - SET* Difference(SET A, SET B);

Each of these should return a new dynamically allocated SET representing the result of the operation.

*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

typedef int SET[MAX];

// Function prototypes
SET *Union(SET A, SET B);
SET *Intersection(SET A, SET B);
SET *Difference(SET A, SET B);
void displaySet(SET S);
void assignSet(SET target, int values[MAX]);

SET *FindApprovedTools(SET Design, SET Programming, SET Marketing);

int main()
{
    int testCase;
    SET Design;
    SET Programming;
    SET Marketing;

    printf("Select a project scenario to simulate (1-10): ");
    scanf("%d", &testCase);

    int d[MAX], p[MAX], m[MAX];

    switch (testCase)
    {
    case 1:
        assignSet(d, (int[]){1, 1, 0, 0, 1});
        assignSet(p, (int[]){0, 0, 1, 0, 1});
        assignSet(m, (int[]){1, 0, 0, 1, 1});
        break;
    case 2:
        assignSet(d, (int[]){1, 1, 1, 1, 1});
        assignSet(p, (int[]){1, 1, 1, 1, 1});
        assignSet(m, (int[]){1, 1, 1, 1, 1});
        break;
    case 3:
        assignSet(d, (int[]){0, 0, 0, 0, 0});
        assignSet(p, (int[]){1, 1, 1, 1, 1});
        assignSet(m, (int[]){0, 0, 0, 0, 0});
        break;
    case 4:
        assignSet(d, (int[]){0, 0, 0, 0, 0});
        assignSet(p, (int[]){0, 0, 0, 0, 0});
        assignSet(m, (int[]){1, 1, 1, 1, 1});
        break;
    case 5:
        assignSet(d, (int[]){1, 1, 0, 0, 0});
        assignSet(p, (int[]){0, 0, 1, 0, 1});
        assignSet(m, (int[]){1, 0, 0, 1, 0});
        break;
    case 6:
        assignSet(d, (int[]){1, 0, 1, 0, 1});
        assignSet(p, (int[]){0, 1, 0, 1, 0});
        assignSet(m, (int[]){1, 1, 1, 1, 1});
        break;
    case 7:
        assignSet(d, (int[]){0, 1, 0, 1, 0});
        assignSet(p, (int[]){0, 0, 0, 0, 0});
        assignSet(m, (int[]){1, 1, 1, 1, 1});
        break;
    case 8:
        assignSet(d, (int[]){1, 1, 0, 1, 0});
        assignSet(p, (int[]){1, 0, 1, 0, 1});
        assignSet(m, (int[]){0, 1, 0, 1, 0});
        break;
    case 9:
        assignSet(d, (int[]){1, 0, 0, 0, 0});
        assignSet(p, (int[]){0, 1, 0, 0, 0});
        assignSet(m, (int[]){0, 0, 1, 0, 0});
        break;
    case 10:
        assignSet(d, (int[]){0, 0, 0, 0, 0});
        assignSet(p, (int[]){0, 0, 0, 0, 0});
        assignSet(m, (int[]){0, 0, 0, 0, 0});
        break;
    default:
        printf("Invalid test case.\n");
        return 1;
    }

    assignSet(Design, d);
    assignSet(Programming, p);
    assignSet(Marketing, m);

    SET *Approved = FindApprovedTools(Design, Programming, Marketing);

    displaySet(*Approved);

    free(Approved);
    return 0;
}

/*
   Your task:
   - Compute which tools are approved based on the given logic.
   - Use only the provided set operations.
   - Return the resulting SET.
 */
SET *FindApprovedTools(SET Design, SET Programming, SET Marketing)
{

    SET *designAndMarketingTools = (SET *)malloc(sizeof(SET));

    // when bit is both on design and marketing, its also always on -- intersection
    designAndMarketingTools = Intersection(Design, Marketing);

    // marketing only tools are off -- use difference
    SET *MarketingOnlyTools = (SET *)malloc(sizeof(SET));
    MarketingOnlyTools = Difference(Marketing, Programming);

    SET *unifiedTools = (SET *)malloc(sizeof(SET));
    // programmin teams tool arem mandatory -- one default bit always on?
    unifiedTools = Union(*MarketingOnlyTools, *designAndMarketingTools);

    return unifiedTools;
}

// ====== SET OPERATION IMPLEMENTATIONS ======
SET *Union(SET A, SET B)
{
    // Implement the code for this function
    SET *C = (SET *)malloc(sizeof(SET));

    for (int i = 0; i < MAX; i++)
    {
        (*C)[i] = A[i] || B[i];
    }

    return C;
}

SET *Intersection(SET A, SET B)
{
    // Implement the code for this function
    SET *C = (SET *)malloc(sizeof(SET));

    for (int i = 0; i < MAX; i++)
    {
        (*C)[i] = A[i] && B[i];
    }

    return C;
}

SET *Difference(SET A, SET B)
{
    // Implement the code for this function

    SET *C = (SET *)malloc(sizeof(SET));

    for (int i = 0; i < MAX; i++)
    {
        (*C)[i] = A[i] && !B[i];
    }

    return C;
}

void displaySet(SET S)
{
    printf("\nApproved Tools for the Project:\n");
    printf("(1 = approved, 0 = not approved)\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", S[i]);
    }

    const char *tools[MAX] = {"Canva", "Figma", "GitHub", "Trello", "ChatGPT"};
    printf("\n\n%-10s | %-10s\n", "Tool", "Approved?");
    printf("------------------------\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("%-10s | %s\n", tools[i], S[i] == 1 ? "YES" : "NO");
    }
    printf("\n");
}

void assignSet(SET target, int values[MAX])
{
    int ctr;
    for (ctr = 0; ctr < MAX; ctr++)
    {
        target[ctr] = values[ctr];
    }
}