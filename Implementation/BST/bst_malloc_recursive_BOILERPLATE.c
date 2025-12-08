/*
========================================
BINARY SEARCH TREE - MALLOC-BASED (RECURSIVE)
PRACTICE BOILERPLATE - Implement the functions below
========================================

Instructions:
1. Implement each function following the guided comments
2. Test with the provided main() after completing each function
3. Focus on pointer-to-pointer traversal pattern for INSERT/DELETE

Key Concepts to Master:
- Pointer-to-pointer traversal (no parent tracking needed)
- DELETE: 3 cases (leaf, one child, two children)
- Inorder successor pattern for two-child deletion
- Recursive tree traversal patterns
========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef enum
{
    FALSE,
    TRUE
} boolean;

typedef struct node
{
    int data;
    struct node *LC;
    struct node *RC;
} NodeType, *BST;

// --- Function Prototypes ---
void INIT_BST(BST *T);
void INSERT_BST(BST *T, int elem);
void DELETE_BST(BST *T, int elem);
boolean MEMBER_BST(BST T, int elem);
int MIN_BST(BST T);
int MAX_BST(BST T);

void PREORDER_BST(BST T);
void INORDER_BST(BST T);
void POSTORDER_BST(BST T);

int HEIGHT_BST(BST T);
int COUNT_NODES_BST(BST T);
boolean IS_BALANCED_BST(BST T);
void LEVEL_ORDER_BST(BST T);

// ============================================
// MAIN - TESTING
// ============================================

void main()
{
    printf("========================================\n");
    printf("BST - MALLOC-BASED (RECURSIVE) - PRACTICE\n");
    printf("========================================\n\n");

    BST T;
    INIT_BST(&T);

    printf("Inserting: {10, 5, 14, 12, 7, 18, 15, 3, 8}\n");
    INSERT_BST(&T, 10);
    INSERT_BST(&T, 5);
    INSERT_BST(&T, 14);
    INSERT_BST(&T, 12);
    INSERT_BST(&T, 7);
    INSERT_BST(&T, 18);
    INSERT_BST(&T, 15);
    INSERT_BST(&T, 3);
    INSERT_BST(&T, 8);

    printf("\nTraversals:\n");
    printf("PREORDER  : ");
    PREORDER_BST(T);
    printf("\nINORDER   : ");
    INORDER_BST(T);
    printf("\nPOSTORDER : ");
    POSTORDER_BST(T);

    printf("\n\nTree Statistics:\n");
    printf("Height: %d\n", HEIGHT_BST(T));
    printf("Node Count: %d\n", COUNT_NODES_BST(T));
    printf("MIN: %d\n", MIN_BST(T));
    printf("MAX: %d\n", MAX_BST(T));
    printf("Is Balanced? %s\n", IS_BALANCED_BST(T) ? "Yes" : "No");

    printf("\nLevel-Order: ");
    LEVEL_ORDER_BST(T);

    printf("\n\nMembership:\n");
    printf("Is 7 a member? %s\n", MEMBER_BST(T, 7) ? "Yes" : "No");
    printf("Is 99 a member? %s\n", MEMBER_BST(T, 99) ? "Yes" : "No");

    printf("\nDeleting: 7 (leaf), 5 (one child), 10 (two children)\n");
    DELETE_BST(&T, 7);
    DELETE_BST(&T, 5);
    DELETE_BST(&T, 10);

    printf("INORDER after deletion: ");
    INORDER_BST(T);

    printf("\n\n========================================\n");
}

// ============================================
// TODO: IMPLEMENT THESE FUNCTIONS
// ============================================

/*
 * INIT_BST - Initialize tree to NULL
 *
 * Steps:
 * 1. Set *T to NULL
 */
void INIT_BST(BST *T)
{
    *T = NULL;
    // printf("Tree initialized!");
}

/*
 * INSERT_BST - Insert element using pointer-to-pointer traversal
 *
 * Steps:
 * 1. Declare BST *trav
 * 2. Loop: for (trav = T; *trav != NULL && (*trav)->data != elem; )
 *    - Move trav to &(*trav)->LC or &(*trav)->RC based on comparison
 * 3. If *trav == NULL (not duplicate):
 *    - Malloc new node
 *    - Set data, LC = RC = NULL
 *    - Set *trav = newNode
 *
 * Key: trav is a pointer-to-pointer, so *trav is the actual node pointer
 */
void INSERT_BST(BST *T, int elem)
{

    BST *trav;

    for (trav = T; *trav != NULL && (*trav)->data != elem;)
    {
        if (elem > (*trav)->data)
            trav = &(*trav)->RC;
        else
            trav = &(*trav)->LC;
    }

    if (*trav == NULL)
    {

        NodeType *newLeaf = (NodeType *)malloc(sizeof(NodeType));
        newLeaf->data = elem;
        newLeaf->RC = NULL;
        newLeaf->LC = NULL;
        *trav = newLeaf;
    }
}

/*
 * MIN_BST - Find minimum (leftmost node)
 *
 * Steps:
 * 1. Traverse left until trav->LC == NULL
 * 2. Return trav->data (or -1 if tree empty)
 */
int MIN_BST(BST T)
{
    if (T == NULL)
        return -1;
    BST trav = T;
    while (trav->LC != NULL)
        trav = trav->LC;
    return trav != NULL ? trav->data : -1;
}

/*
 * MAX_BST - Find maximum (rightmost node)
 *
 * Steps:
 * 1. Traverse right until trav->RC == NULL
 * 2. Return trav->data (or -1 if tree empty)
 */
int MAX_BST(BST T)
{
    if (T == NULL)
        return -1;
    BST trav = T;
    while (trav->RC != NULL)
        trav = trav->RC;
    return trav != NULL ? trav->data : -1;
}

/*
 * DELETE_BST - Delete element (3 cases: leaf, one child, two children)
 *
 * Steps:
 * 1. Check if *T == NULL, return
 * 2. Find node using pointer-to-pointer traversal (same as INSERT)
 * 3. If *trav != NULL:
 *    Case 1 & 2 (Leaf or one child):
 *      - temp = *trav
 *      - *trav = ((*trav)->LC == NULL) ? (*trav)->RC : (*trav)->LC
 *      - free(temp)
 *
 *    Case 3 (Two children):
 *      - Find inorder successor: for (successor = &(*trav)->RC; (*successor)->LC != NULL; ...)
 *      - temp = *successor
 *      - *successor = temp->RC (successor has at most one right child)
 *      - (*trav)->data = temp->data (copy data)
 *      - free(temp)
 */
void DELETE_BST(BST *T, int elem)
{
    if (*T == NULL)
        return;

    BST *trav;
    for (trav = T; *trav != NULL && (*trav)->data != elem; trav = (elem > (*trav)->data) ? &(*trav)->RC : &(*trav)->LC){}

    if (*trav != NULL)
    { // Found the node
        BST temp = *trav;
        if (temp->LC == NULL)
        { // No left child or leaf
            *trav = temp->RC;
        }
        else if (temp->RC == NULL)
        { // No right child
            *trav = temp->LC;
        }
        else
        { // Two children: find successor
            BST *succ = &temp->RC;
            while ((*succ)->LC != NULL) succ = &(*succ)->LC;  // gets min at right side
            temp->data = (*succ)->data; // Copy successor data
            temp = *succ;               // Now delete the successor node
            *succ = temp->RC;           // Successor has at most right child
        }
        free(temp);
    }
   
}

/*
 * MEMBER_BST - Check if element exists
 *
 * Steps:
 * 1. Declare BST trav (regular pointer, not pointer-to-pointer)
 * 2. Loop: for (trav = T; trav != NULL && trav->data != elem; )
 *    - Move to trav->LC or trav->RC
 * 3. Return (trav != NULL) ? TRUE : FALSE
 */
boolean MEMBER_BST(BST T, int elem)
{

    for (BST trav = T; trav != NULL; trav = (elem < trav->data) ? trav->LC : trav->RC)
        if (elem == trav->data)
            return TRUE;

    return FALSE;
}

/*
 * PREORDER_BST - Root, Left, Right
 *
 * Steps:
 * 1. if (T != NULL):
 *    - printf("%d ", T->data)
 *    - PREORDER_BST(T->LC)
 *    - PREORDER_BST(T->RC)
 */
void PREORDER_BST(BST T)
{

    if (T != NULL)
    {
        printf("%d ", T->data);
        PREORDER_BST(T->LC);
        PREORDER_BST(T->RC);
    }
}

/*
 * INORDER_BST - Left, Root, Right (gives sorted order)
 *
 * Steps:
 * 1. if (T != NULL):
 *    - INORDER_BST(T->LC)
 *    - printf("%d ", T->data)
 *    - INORDER_BST(T->RC)
 */
void INORDER_BST(BST T)
{

    if (T != NULL)
    {
        INORDER_BST(T->LC);
        printf("%d ", T->data);
        INORDER_BST(T->RC);
    }
}

/*
 * POSTORDER_BST - Left, Right, Root
 *
 * Steps:
 * 1. if (T != NULL):
 *    - POSTORDER_BST(T->LC)
 *    - POSTORDER_BST(T->RC)
 *    - printf("%d ", T->data)
 */
void POSTORDER_BST(BST T)
{

    if (T != NULL)
    {
        POSTORDER_BST(T->LC);
        POSTORDER_BST(T->RC);
        printf("%d ", T->data);
    }
}

int max(int a, int b)
{

    return (a > b) ? a : b;
}

/*
 * HEIGHT_BST - Calculate tree height (recursive)
 *
 * Steps:
 * 1. if (T == NULL) return -1 (empty tree height is -1)
 * 2. leftHeight = HEIGHT_BST(T->LC)
 * 3. rightHeight = HEIGHT_BST(T->RC)
 * 4. return 1 + max(leftHeight, rightHeight)
 */
int HEIGHT_BST(BST T)
{
    // TODO: Implement

    if (T == NULL)
        return -1;

    int leftHeight = HEIGHT_BST(T->LC);
    int rightHeight = HEIGHT_BST(T->RC);

    return 1 + max(leftHeight, rightHeight);
}

/*
 * COUNT_NODES_BST - Count total nodes (recursive)
 *
 * Steps:
 * 1. if (T == NULL) return 0
 * 2. return 1 + COUNT_NODES_BST(T->LC) + COUNT_NODES_BST(T->RC)
 */
int COUNT_NODES_BST(BST T)
{

    if (T == NULL)
        return 0;
    return 1 + COUNT_NODES_BST(T->LC) + COUNT_NODES_BST(T->RC);
}

/*
 * IS_BALANCED_BST - Check if tree is balanced (height difference <= 1)
 *
 * Steps:
 * 1. if (T == NULL) return TRUE
 * 2. Get leftHeight and rightHeight
 * 3. Calculate diff = abs(leftHeight - rightHeight)
 * 4. if (diff > 1) return FALSE
 * 5. return IS_BALANCED_BST(T->LC) && IS_BALANCED_BST(T->RC)
 */
boolean IS_BALANCED_BST(BST T)
{
    if (T == NULL)
        return TRUE;

    int leftHeight = HEIGHT_BST(T->LC);
    int rightHeight = HEIGHT_BST(T->RC);

    if (abs(leftHeight - rightHeight) > 1)
    {
        return FALSE;
    }

    return IS_BALANCED_BST(T->LC) && IS_BALANCED_BST(T->RC);
}

/*
 * LEVEL_ORDER_BST - Breadth-first traversal using queue
 *
 * Steps:
 * 1. if (T == NULL) return
 * 2. Create queue array: BST queue[SIZE]
 * 3. front = 0, rear = 0
 * 4. queue[rear++] = T (enqueue root)
 * 5. while (front < rear):
 *    - current = queue[front++] (dequeue)
 *    - printf("%d ", current->data)
 *    - if (current->LC != NULL) queue[rear++] = current->LC
 *    - if (current->RC != NULL) queue[rear++] = current->RC
 */

void LEVEL_ORDER_BST(BST T)
{
    if (T == NULL)
        return;

    BST queue[SIZE];
    int front = 0, rear = 0;
    queue[rear++] = T;

    while (front < rear)
    {

        BST curr = queue[front++];
        printf("%d", curr->data);

        if (curr->LC != NULL)
            queue[rear++] = curr->LC;
        if (curr->RC != NULL)
            queue[rear++] = curr->RC;
    }
}
