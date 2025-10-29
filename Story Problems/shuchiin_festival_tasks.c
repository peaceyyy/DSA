/*
Shuchiin Cultural Festival Conundrum

The annual Shuchiin Academy Cultural Festival is fast approaching, and as usual, the Student Council is at the heart of the chaos. Kaguya Shinomiya and Miyuki Shirogane, in their eternal battle of wits, have each compiled a "To-Do List" for the festival preparations. These aren't just any lists; they're meticulously sorted by task ID, and each task is unique.

Kaguya, ever the perfectionist, has her list `KaguyaTasks`. Shirogane, the diligent president, has his list `ShiroganeTasks`. Chika Fujiwara, oblivious to their mind games, just wants to make sure everything gets done. Ishigami Yu is, as always, trying to avoid extra work, while Ai Hayasaka is silently observing, ready to intervene if things go off the rails.

Your mission, Lab Member, is to help the Student Council efficiently manage these task lists.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// --- Data Structures ---
typedef struct
{
    int taskID;
    char description[100];
    int priority;
} Task;

typedef struct Node
{
    Task task;
    struct Node *next;
} TaskNode, *TaskList;

// --- Function Prototypes ---
void initializeTaskList(TaskList *list);
void displayTaskList(TaskList list, const char *name);

// TODO: Implement these functions
void markTaskToList(TaskList *list, Task t);            // Inserts a task into a sorted list, no duplicates
TaskList commonTasks(TaskList A, TaskList B);           // Set Intersection
TaskList kaguyaOnlyTasks(TaskList A, TaskList B);       // Set Difference (A - B)
TaskList shiroganeOnlyTasks(TaskList A, TaskList B);    // Set Difference (B - A)
TaskList allFestivalTasks(TaskList A, TaskList B);      // Set Union
bool isKaguyaSubsetOfShirogane(TaskList A, TaskList B); // Is Subset (A is subset of B)

// --- Helper Functions (Provided) ---
void initializeTaskList(TaskList *list)
{
    *list = NULL;
}

void displayTaskList(TaskList list, const char *name)
{
    printf("-- %s ---\n", name);
    if (list == NULL)
    {
        printf("  [Empty]\n");
    }
    else
    {
        for (TaskList trav = list; trav != NULL; trav = trav->next)
        {
            printf("  Task ID: %d, Description: %s, Priority: %d\n", trav->task.taskID, trav->task.description, trav->task.priority);
        }
    }
    printf("--------------------\n");
}

// --- Main Function (Test Cases) ---
int main()
{
    TaskList kaguyaTasks;
    TaskList shiroganeTasks;

    initializeTaskList(&kaguyaTasks);
    initializeTaskList(&shiroganeTasks);

    // Kaguya's Tasks
    markTaskToList(&kaguyaTasks, (Task){1, "Prepare festival budget", 3});
    markTaskToList(&kaguyaTasks, (Task){3, "Oversee cultural exhibits", 1});
    markTaskToList(&kaguyaTasks, (Task){5, "Arrange tea ceremony", 2});
    markTaskToList(&kaguyaTasks, (Task){7, "Review club proposals", 4});
    markTaskToList(&kaguyaTasks, (Task){9, "Secretly help Shirogane", 5});

    // Shirogane's Tasks
    markTaskToList(&shiroganeTasks, (Task){1, "Prepare festival budget", 3});
    markTaskToList(&shiroganeTasks, (Task){2, "Coordinate security", 1});
    markTaskToList(&shiroganeTasks, (Task){5, "Arrange tea ceremony", 2});
    markTaskToList(&shiroganeTasks, (Task){6, "Manage student volunteers", 3});
    markTaskToList(&shiroganeTasks, (Task){9, "Secretly help Kaguya", 5});
    markTaskToList(&shiroganeTasks, (Task){10, "Final speech preparation", 1});

    displayTaskList(kaguyaTasks, "Kaguya's Tasks");
    displayTaskList(shiroganeTasks, "Shirogane's Tasks");

    printf("\n--- Testing Set Operations ---\n");

    // 1. Common Tasks (Intersection)
    TaskList common = commonTasks(kaguyaTasks, shiroganeTasks);
    displayTaskList(common, "Common Tasks (Expected: 1, 5, 9)");
    // Expected Output:
    // --- Common Tasks ---
    //   Task ID: 1, Description: Prepare festival budget, Priority: 3
    //   Task ID: 5, Description: Arrange tea ceremony, Priority: 2
    //   Task ID: 9, Description: Secretly help Kaguya, Priority: 5
    // --------------------

    // 2. Kaguya Only Tasks (Difference A - B)
    TaskList kaguyaOnly = kaguyaOnlyTasks(kaguyaTasks, shiroganeTasks);
    displayTaskList(kaguyaOnly, "Kaguya Only Tasks (Expected: 3, 7)");
    // Expected Output:
    // --- Kaguya Only Tasks ---
    //   Task ID: 3, Description: Oversee cultural exhibits, Priority: 1
    //   Task ID: 7, Description: Review club proposals, Priority: 4
    // --------------------

    // 3. Shirogane Only Tasks (Difference B - A)
    TaskList shiroganeOnly = shiroganeOnlyTasks(shiroganeTasks, kaguyaTasks);
    displayTaskList(shiroganeOnly, "Shirogane Only Tasks (Expected: 2, 6, 10)");
    // Expected Output:
    // --- Shirogane Only Tasks ---
    //   Task ID: 2, Description: Coordinate security, Priority: 1
    //   Task ID: 6, Description: Manage student volunteers, Priority: 3
    //   Task ID: 10, Description: Final speech preparation, Priority: 1
    // --------------------

    // 4. All Festival Tasks (Union)
    TaskList allTasks = allFestivalTasks(kaguyaTasks, shiroganeTasks);
    displayTaskList(allTasks, "All Festival Tasks (Expected: 1, 2, 3, 5, 6, 7, 9, 10)");
    // Expected Output:
    // --- All Festival Tasks ---
    //   Task ID: 1, Description: Prepare festival budget, Priority: 3
    //   Task ID: 2, Description: Coordinate security, Priority: 1
    //   Task ID: 3, Description: Oversee cultural exhibits, Priority: 1
    //   Task ID: 5, Description: Arrange tea ceremony, Priority: 2
    //   Task ID: 6, Description: Manage student volunteers, Priority: 3
    //   Task ID: 7, Description: Review club proposals, Priority: 4
    //   Task ID: 9, Description: Secretly help Kaguya, Priority: 5
    //   Task ID: 10, Description: Final speech preparation, Priority: 1
    // --------------------

    // 5. Is Kaguya Subset of Shirogane?
    printf("\nIs Kaguya's Tasks a subset of Shirogane's Tasks? (Expected: False)\n");
    if (isKaguyaSubsetOfShirogane(kaguyaTasks, shiroganeTasks))
    {
        printf("  Yes, Kaguya's tasks are a subset of Shirogane's.\n");
    }
    else
    {
        printf("  No, Kaguya's tasks are NOT a subset of Shirogane's.\n");
    }
    // Expected Output:
    // Is Kaguya's Tasks a subset of Shirogane's Tasks? (Expected: False)
    //   No, Kaguya's tasks are NOT a subset of Shirogane's.

    return 0;
}

/*
typedef struct {
    int taskID;
    char description[100];
    int priority;
} Task;

typedef struct Node {
    Task task;
    struct Node *next;
} TaskNode, *TaskList;
*/

// TODO: Implement these functions
void markTaskToList(TaskList *list, Task t)
{
    int found = 0;
    TaskNode *newTask = (TaskNode *)malloc(sizeof(TaskNode));

    if (!newTask)
        return;

    TaskList *trav;

    for (trav = list; found != 1 && *trav != NULL; trav = &(*trav)->next)
    {
        if ((*trav)->task.taskID == t.taskID) found = 1;
    }

    if (!found)
    {
        newTask->task = t;
        newTask->next = *trav;
        *trav = newTask;
    }
}
TaskList commonTasks(TaskList A, TaskList B)
{

    TaskList C, aptr, bptr, *cptr;
    C = NULL;
    cptr = &C;
    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        if (aptr->task.taskID == bptr->task.taskID)
        {
            // printf("\nIntersection found!\n");
            *cptr = (TaskNode *)malloc(sizeof(TaskNode));
            (*cptr)->task = aptr->task;
            aptr = aptr->next;
            bptr = bptr->next;
            cptr = &(*cptr)->next;
        }
        else if (aptr->task.taskID < bptr->task.taskID)
        {
            aptr = aptr->next;
        }
        else
        {
            bptr = bptr->next;
        }
    }

    *cptr = NULL;

    return C;
}
TaskList kaguyaOnlyTasks(TaskList A, TaskList B)
{

    TaskList C, aptr, bptr, *cptr;
    C = NULL;
    cptr = &C;
    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        if (aptr->task.taskID == bptr->task.taskID)
        {
            aptr = aptr->next;
            bptr = bptr->next;
        }
        else if (aptr->task.taskID < bptr->task.taskID)
        {
            // printf("\nDifference found!\n");
            *cptr = (TaskNode *)malloc(sizeof(TaskNode));
            (*cptr)->task = aptr->task;
            aptr = aptr->next;
            cptr = &(*cptr)->next;
        }
        else
        {
            bptr = bptr->next;
        }
    }

    while (aptr != NULL)
    {
        *cptr = (TaskNode *)malloc(sizeof(TaskNode));
        (*cptr)->task = aptr->task;
        aptr = aptr->next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;

    return C;
}
TaskList shiroganeOnlyTasks(TaskList A, TaskList B)
{

    TaskList C, aptr, bptr, *cptr;
    C = NULL;
    cptr = &C;
    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        if (aptr->task.taskID == bptr->task.taskID)
        {
            aptr = aptr->next;
            bptr = bptr->next;
        }
        else if (aptr->task.taskID < bptr->task.taskID)
        {
            // printf("\nDifference found!\n");
            *cptr = (TaskNode *)malloc(sizeof(TaskNode));
            (*cptr)->task = aptr->task;
            aptr = aptr->next;
            cptr = &(*cptr)->next;
        }
        else
        {
            bptr = bptr->next;
        }
    }

    while (aptr != NULL)
    {
        *cptr = (TaskNode *)malloc(sizeof(TaskNode));
        (*cptr)->task = aptr->task;
        aptr = aptr->next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;

    return C;
}
TaskList allFestivalTasks(TaskList A, TaskList B)
{

    TaskList C, aptr, bptr, *cptr;
    C = NULL;
    cptr = &C;
    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {

        if (aptr->task.taskID < bptr->task.taskID)
        {
            *cptr = (TaskNode *)malloc(sizeof(TaskNode));
            (*cptr)->task = aptr->task;
            aptr = aptr->next;
        }
        else
        {

            *cptr = (TaskNode *)malloc(sizeof(TaskNode));
            if (aptr->task.taskID == bptr->task.taskID) aptr = aptr->next;
            (*cptr)->task = bptr->task;
            bptr = bptr->next;
        }

        cptr = &(*cptr)->next;
    }

    aptr = (aptr != NULL) ? aptr : bptr;

    while (aptr != NULL)
    {
        *cptr = (TaskNode *)malloc(sizeof(TaskNode));
        (*cptr)->task = aptr->task;
        aptr = aptr->next;
        cptr = &(*cptr)->next;
    }

    *cptr = NULL;

    return C;
}
bool isKaguyaSubsetOfShirogane(TaskList A, TaskList B)
{

    TaskList aptr, bptr;
    aptr = A;
    bptr = B;

    while (aptr != NULL && bptr != NULL)
    {
        if (aptr->task.taskID == bptr->task.taskID)
        {
            // printf("\nMove both!\n");
            aptr = aptr->next;
            bptr = bptr->next;
        }
        else if (aptr->task.taskID < bptr->task.taskID)
        {
            // printf("\nDifference found!\n");
            return false;
        }
        else
        {
            bptr = bptr->next;
        }
    }

    return (aptr == NULL);
}
