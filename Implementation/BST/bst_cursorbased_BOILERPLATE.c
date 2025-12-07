/*
========================================
BINARY SEARCH TREE - CURSOR-BASED (VIRTUAL HEAP)
PRACTICE BOILERPLATE - Implement the functions below
========================================

Instructions:
1. Implement Virtual Heap management first (INIT_VHEAP, ALLOC, DEALLOC)
2. Then implement BST operations using pointer-to-index pattern
3. Test incrementally after completing each function

Key Concepts to Master:
- Virtual Heap as LIFO stack for available space
- Pointer-to-index traversal (int* instead of BST*)
- Preserving original root index in recursive traversals
- All logic mirrors malloc-based, just using array indices
========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef enum {FALSE, TRUE} boolean;

typedef struct {
    int data;
    int LC;
    int RC;
} CNodeType;

typedef struct {
    CNodeType Nodes[SIZE];
    int avail;
} VirtualHeap, *VHeap;

typedef struct {
    int root;
    VHeap VH;
} CBTree;

// --- Function Prototypes ---
void INIT_VHEAP(VHeap *VH);
int ALLOC_SPACE(VHeap VH);
void DEALLOC_SPACE(VHeap VH, int index);

void INIT_CBTREE(CBTree *T, VHeap *VH);
void INSERT_CBTREE(CBTree *T, int elem);
void DELETE_CBTREE(CBTree *T, int elem);
boolean MEMBER_CBTREE(CBTree T, int elem);
int MIN_CBTREE(CBTree T);
int MAX_CBTREE(CBTree T);

void PREORDER_CBTREE(CBTree T);
void INORDER_CBTREE(CBTree T);
void POSTORDER_CBTREE(CBTree T);

int HEIGHT_CBTREE(CBTree T);
int COUNT_NODES_CBTREE(CBTree T);


// ============================================
// MAIN - TESTING
// ============================================

void main() {
    printf("========================================\n");
    printf("BST - CURSOR-BASED - PRACTICE\n");
    printf("========================================\n\n");
    
    VHeap VH;
    INIT_VHEAP(&VH);
    
    CBTree T;
    INIT_CBTREE(&T, &VH);
    
    printf("Inserting: {10, 5, 14, 12, 7, 18, 15}\n");
    INSERT_CBTREE(&T, 10);
    INSERT_CBTREE(&T, 5);
    INSERT_CBTREE(&T, 14);
    INSERT_CBTREE(&T, 12);
    INSERT_CBTREE(&T, 7);
    INSERT_CBTREE(&T, 18);
    INSERT_CBTREE(&T, 15);
    
    printf("\nTraversals:\n");
    printf("PREORDER  : "); PREORDER_CBTREE(T);
    printf("\nINORDER   : "); INORDER_CBTREE(T);
    printf("\nPOSTORDER : "); POSTORDER_CBTREE(T);
    
    printf("\n\nTree Statistics:\n");
    printf("Height: %d\n", HEIGHT_CBTREE(T));
    printf("Node Count: %d\n", COUNT_NODES_CBTREE(T));
    printf("MIN: %d\n", MIN_CBTREE(T));
    printf("MAX: %d\n", MAX_CBTREE(T));
    
    printf("\nMembership:\n");
    printf("Is 12 a member? %s\n", MEMBER_CBTREE(T, 12) ? "Yes" : "No");
    printf("Is 99 a member? %s\n", MEMBER_CBTREE(T, 99) ? "Yes" : "No");
    
    printf("\nDeleting: 7, 14, 10\n");
    DELETE_CBTREE(&T, 7);
    DELETE_CBTREE(&T, 14);
    DELETE_CBTREE(&T, 10);
    
    printf("INORDER after deletion: ");
    INORDER_CBTREE(T);
    
    printf("\n\n========================================\n");
}


// ============================================
// TODO: IMPLEMENT THESE FUNCTIONS
// ============================================

/*
 * INIT_VHEAP - Initialize Virtual Heap with avail list
 * 
 * Steps:
 * 1. Malloc the VirtualHeap structure: *VH = (VHeap)malloc(sizeof(VirtualHeap))
 * 2. Set (*VH)->avail = 0
 * 3. Loop i from 0 to SIZE-2:
 *    - (*VH)->Nodes[i].LC = i + 1
 *    - (*VH)->Nodes[i].RC = i + 1
 * 4. Last node: (*VH)->Nodes[SIZE-1].LC = (*VH)->Nodes[SIZE-1].RC = -1
 * 
 * Why: Avail list links all free nodes, LC/RC both point to next available
 */
void INIT_VHEAP(VHeap *VH) {
    // TODO: Implement
}

/*
 * ALLOC_SPACE - Allocate a node from avail list (pop from stack)
 * 
 * Steps:
 * 1. temp = VH->avail
 * 2. if (temp != -1):
 *    - VH->avail = VH->Nodes[temp].LC (move to next available)
 * 3. return temp
 * 
 * Returns: Index of allocated node, or -1 if heap full
 */
int ALLOC_SPACE(VHeap VH) {
    // TODO: Implement
    return -1;
}

/*
 * DEALLOC_SPACE - Return node to avail list (push to stack)
 * 
 * Steps:
 * 1. VH->Nodes[index].LC = VH->avail
 * 2. VH->Nodes[index].RC = VH->avail (both point to current avail)
 * 3. VH->avail = index (make this node the new head)
 */
void DEALLOC_SPACE(VHeap VH, int index) {
    // TODO: Implement
}

/*
 * INIT_CBTREE - Initialize cursor-based tree
 * 
 * Steps:
 * 1. T->root = -1
 * 2. T->VH = *VH
 */
void INIT_CBTREE(CBTree *T, VHeap *VH) {
    // TODO: Implement
}

/*
 * INSERT_CBTREE - Insert using pointer-to-index pattern
 * 
 * Steps:
 * 1. Declare int *trav
 * 2. Loop: for (trav = &T->root; *trav != -1 && T->VH->Nodes[*trav].data != elem; )
 *    - Move trav to &T->VH->Nodes[*trav].LC or &T->VH->Nodes[*trav].RC
 * 3. if (*trav == -1):
 *    - newIdx = ALLOC_SPACE(T->VH)
 *    - if (newIdx != -1):
 *      * T->VH->Nodes[newIdx].data = elem
 *      * T->VH->Nodes[newIdx].LC = T->VH->Nodes[newIdx].RC = -1
 *      * *trav = newIdx
 * 
 * Key: Same logic as malloc INSERT, but using indices instead of pointers
 */
void INSERT_CBTREE(CBTree *T, int elem) {
    // TODO: Implement
}

/*
 * DELETE_CBTREE - Delete using pointer-to-index pattern
 * 
 * Steps:
 * 1. if (T->root == -1) return
 * 2. Find node: for (trav = &T->root; *trav != -1 && T->VH->Nodes[*trav].data != elem; ...)
 * 3. if (*trav != -1):
 *    Case 1 & 2 (Leaf or one child):
 *      - temp = *trav
 *      - *trav = (T->VH->Nodes[*trav].LC == -1) ? T->VH->Nodes[*trav].RC : T->VH->Nodes[*trav].LC
 *      - DEALLOC_SPACE(T->VH, temp)
 *    
 *    Case 3 (Two children):
 *      - Find successor: for (successor = &T->VH->Nodes[*trav].RC; T->VH->Nodes[*successor].LC != -1; ...)
 *      - temp = *successor
 *      - *successor = T->VH->Nodes[temp].RC
 *      - T->VH->Nodes[*trav].data = T->VH->Nodes[temp].data
 *      - DEALLOC_SPACE(T->VH, temp)
 */
void DELETE_CBTREE(CBTree *T, int elem) {
    // TODO: Implement
}

/*
 * MEMBER_CBTREE - Check membership
 * 
 * Steps:
 * 1. Declare int trav (regular int, not int*)
 * 2. Loop: for (trav = T.root; trav != -1 && T.VH->Nodes[trav].data != elem; )
 *    - Move to T.VH->Nodes[trav].LC or T.VH->Nodes[trav].RC
 * 3. return (trav != -1) ? TRUE : FALSE
 */
boolean MEMBER_CBTREE(CBTree T, int elem) {
    // TODO: Implement
    return FALSE;
}

/*
 * MIN_CBTREE - Find minimum
 * 
 * Steps:
 * 1. Traverse left: for (trav = T.root; trav != -1 && T.VH->Nodes[trav].LC != -1; trav = T.VH->Nodes[trav].LC)
 * 2. return (trav != -1) ? T.VH->Nodes[trav].data : -1
 */
int MIN_CBTREE(CBTree T) {
    // TODO: Implement
    return -1;
}

/*
 * MAX_CBTREE - Find maximum
 * 
 * Steps:
 * 1. Traverse right: for (trav = T.root; trav != -1 && T.VH->Nodes[trav].RC != -1; trav = T.VH->Nodes[trav].RC)
 * 2. return (trav != -1) ? T.VH->Nodes[trav].data : -1
 */
int MAX_CBTREE(CBTree T) {
    // TODO: Implement
    return -1;
}

/*
 * PREORDER_CBTREE - Root, Left, Right (must preserve original root)
 * 
 * Steps:
 * 1. int og = T.root (save original)
 * 2. if (T.root != -1):
 *    - printf("%d ", T.VH->Nodes[T.root].data)
 *    - T.root = T.VH->Nodes[T.root].LC
 *    - PREORDER_CBTREE(T)
 *    - T.root = og (restore)
 *    - T.root = T.VH->Nodes[T.root].RC
 *    - PREORDER_CBTREE(T)
 * 
 * Key: Must save og before recursion or root gets lost
 */
void PREORDER_CBTREE(CBTree T) {
    // TODO: Implement
}

/*
 * INORDER_CBTREE - Left, Root, Right
 * 
 * Steps:
 * 1. int og = T.root
 * 2. if (T.root != -1):
 *    - T.root = T.VH->Nodes[T.root].LC
 *    - INORDER_CBTREE(T)
 *    - T.root = og
 *    - printf("%d ", T.VH->Nodes[T.root].data)
 *    - T.root = T.VH->Nodes[T.root].RC
 *    - INORDER_CBTREE(T)
 */
void INORDER_CBTREE(CBTree T) {
    // TODO: Implement
}

/*
 * POSTORDER_CBTREE - Left, Right, Root
 * 
 * Steps:
 * 1. int og = T.root
 * 2. if (T.root != -1):
 *    - T.root = T.VH->Nodes[T.root].LC
 *    - POSTORDER_CBTREE(T)
 *    - T.root = og
 *    - T.root = T.VH->Nodes[T.root].RC
 *    - POSTORDER_CBTREE(T)
 *    - T.root = og (restore again before printing)
 *    - printf("%d ", T.VH->Nodes[T.root].data)
 */
void POSTORDER_CBTREE(CBTree T) {
    // TODO: Implement
}

/*
 * HEIGHT_CBTREE - Calculate height
 * 
 * Steps:
 * 1. if (T.root == -1) return -1
 * 2. Create left and right subtrees:
 *    - CBTree left = T, right = T
 *    - left.root = T.VH->Nodes[T.root].LC
 *    - right.root = T.VH->Nodes[T.root].RC
 * 3. leftHeight = HEIGHT_CBTREE(left)
 * 4. rightHeight = HEIGHT_CBTREE(right)
 * 5. return 1 + max(leftHeight, rightHeight)
 */
int HEIGHT_CBTREE(CBTree T) {
    // TODO: Implement
    return -1;
}

/*
 * COUNT_NODES_CBTREE - Count nodes
 * 
 * Steps:
 * 1. if (T.root == -1) return 0
 * 2. Create left and right subtrees (same as HEIGHT)
 * 3. return 1 + COUNT_NODES_CBTREE(left) + COUNT_NODES_CBTREE(right)
 */
int COUNT_NODES_CBTREE(CBTree T) {
    // TODO: Implement
    return 0;
}
