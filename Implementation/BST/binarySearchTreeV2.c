/*
========================================
BINARY SEARCH TREE - COMPREHENSIVE IMPLEMENTATION BOILERPLATE
Implementation Mode: Practice-Focused
========================================

This file covers:
1. BST using MALLOC (Pointer-based)
2. BST using CURSOR-BASED / Virtual Heap (Array-based)
3. Core operations: INIT, INSERT, DELETE, MEMBER, MIN, MAX
4. Traversals: PREORDER, INORDER, POSTORDER (Recursive & Iterative)
5. Advanced: HEIGHT, COUNT_NODES, LEVEL_ORDER, IS_BALANCED
6. DELETE variations: All 3 cases (leaf, one child, two children)

Note: Both implementations use pointer-to-pointer traversal pattern
for clean insertion/deletion without parent tracking.
========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20  // Virtual Heap size for cursor-based implementation

typedef enum {FALSE, TRUE} boolean;

// ============================================
// PART 1: MALLOC-BASED BST IMPLEMENTATION
// ============================================

typedef struct node {
    int data;
    struct node* LC;  // Left Child
    struct node* RC;  // Right Child
} NodeType, *BST;

// --- Core Operations (Malloc-based) ---
void INIT_BST(BST *T);
void INSERT_BST(BST *T, int elem);
void DELETE_BST(BST *T, int elem);
boolean MEMBER_BST(BST T, int elem);
int MIN_BST(BST T);
int MAX_BST(BST T);

// --- Traversals (Recursive) ---
void PREORDER_BST(BST T);
void INORDER_BST(BST T);
void POSTORDER_BST(BST T);

// --- Traversals (Iterative - using stack simulation) ---
void INORDER_ITERATIVE_BST(BST T);

// --- Advanced Operations ---
int HEIGHT_BST(BST T);
int COUNT_NODES_BST(BST T);
boolean IS_BALANCED_BST(BST T);
void LEVEL_ORDER_BST(BST T);

// --- Helper for DELETE (find inorder successor) ---
BST* FIND_MIN_NODE(BST *T);


// ============================================
// PART 2: CURSOR-BASED BST IMPLEMENTATION
// ============================================

typedef struct {
    int data;
    int LC;  // Left Child index
    int RC;  // Right Child index
} CNodeType;

typedef struct {
    CNodeType Nodes[SIZE];
    int avail;  // Head of available space list
} VirtualHeap, *VHeap;

typedef struct {
    int root;    // Index of root node (-1 if empty)
    VHeap VH;    // Pointer to Virtual Heap
} CBTree;

// --- Virtual Heap Management ---
void INIT_VHEAP(VHeap *VH);
int ALLOC_SPACE(VHeap VH);
void DEALLOC_SPACE(VHeap VH, int index);

// --- Core Operations (Cursor-based) ---
void INIT_CBTREE(CBTree *T, VHeap *VH);
void INSERT_CBTREE(CBTree *T, int elem);
void DELETE_CBTREE(CBTree *T, int elem);
boolean MEMBER_CBTREE(CBTree T, int elem);
int MIN_CBTREE(CBTree T);
int MAX_CBTREE(CBTree T);

// --- Traversals (Cursor-based) ---
void PREORDER_CBTREE(CBTree T);
void INORDER_CBTREE(CBTree T);
void POSTORDER_CBTREE(CBTree T);

// --- Advanced Operations (Cursor-based) ---
int HEIGHT_CBTREE(CBTree T);
int COUNT_NODES_CBTREE(CBTree T);


// ============================================
// MAIN - TESTING BOTH IMPLEMENTATIONS
// ============================================

void main() {
    printf("========================================\n");
    printf("BINARY SEARCH TREE - IMPLEMENTATION MODE\n");
    printf("Testing: Malloc-based & Cursor-based BST\n");
    printf("========================================\n\n");

    // ===== PART 1: MALLOC-BASED BST =====
    printf("--- MALLOC-BASED BST ---\n\n");
    
    BST T1;
    INIT_BST(&T1);
    
    printf("Inserting: {10, 5, 14, 12, 7, 18, 15, 3, 8}\n");
    INSERT_BST(&T1, 10);
    INSERT_BST(&T1, 5);
    INSERT_BST(&T1, 14);
    INSERT_BST(&T1, 12);
    INSERT_BST(&T1, 7);
    INSERT_BST(&T1, 18);
    INSERT_BST(&T1, 15);
    INSERT_BST(&T1, 3);
    INSERT_BST(&T1, 8);
    
    printf("\nTraversals:\n");
    printf("PREORDER  : "); PREORDER_BST(T1);
    printf("\nINORDER   : "); INORDER_BST(T1);
    printf("\nPOSTORDER : "); POSTORDER_BST(T1);
    printf("\nINORDER (Iterative): "); INORDER_ITERATIVE_BST(T1);
    
    printf("\n\nTree Statistics:\n");
    printf("Height: %d\n", HEIGHT_BST(T1));
    printf("Node Count: %d\n", COUNT_NODES_BST(T1));
    printf("MIN: %d\n", MIN_BST(T1));
    printf("MAX: %d\n", MAX_BST(T1));
    printf("Is Balanced? %s\n", IS_BALANCED_BST(T1) ? "Yes" : "No");
    
    printf("\nLevel-Order Traversal: ");
    LEVEL_ORDER_BST(T1);
    
    printf("\n\nMembership Tests:\n");
    printf("Is 7 a member? %s\n", MEMBER_BST(T1, 7) ? "Yes" : "No");
    printf("Is 99 a member? %s\n", MEMBER_BST(T1, 99) ? "Yes" : "No");
    
    printf("\nDeleting: 7 (leaf), 5 (one child), 10 (two children)\n");
    DELETE_BST(&T1, 7);
    DELETE_BST(&T1, 5);
    DELETE_BST(&T1, 10);
    
    printf("INORDER after deletion: ");
    INORDER_BST(T1);
    printf("\n");

    // ===== PART 2: CURSOR-BASED BST =====
    printf("\n\n--- CURSOR-BASED BST ---\n\n");
    
    VHeap VH;
    INIT_VHEAP(&VH);
    
    CBTree T2;
    INIT_CBTREE(&T2, &VH);
    
    printf("Inserting: {10, 5, 14, 12, 7, 18, 15}\n");
    INSERT_CBTREE(&T2, 10);
    INSERT_CBTREE(&T2, 5);
    INSERT_CBTREE(&T2, 14);
    INSERT_CBTREE(&T2, 12);
    INSERT_CBTREE(&T2, 7);
    INSERT_CBTREE(&T2, 18);
    INSERT_CBTREE(&T2, 15);
    
    printf("\nTraversals:\n");
    printf("PREORDER  : "); PREORDER_CBTREE(T2);
    printf("\nINORDER   : "); INORDER_CBTREE(T2);
    printf("\nPOSTORDER : "); POSTORDER_CBTREE(T2);
    
    printf("\n\nTree Statistics:\n");
    printf("Height: %d\n", HEIGHT_CBTREE(T2));
    printf("Node Count: %d\n", COUNT_NODES_CBTREE(T2));
    printf("MIN: %d\n", MIN_CBTREE(T2));
    printf("MAX: %d\n", MAX_CBTREE(T2));
    
    printf("\nMembership Tests:\n");
    printf("Is 12 a member? %s\n", MEMBER_CBTREE(T2, 12) ? "Yes" : "No");
    printf("Is 99 a member? %s\n", MEMBER_CBTREE(T2, 99) ? "Yes" : "No");
    
    printf("\nDeleting: 7, 14, 10\n");
    DELETE_CBTREE(&T2, 7);
    DELETE_CBTREE(&T2, 14);
    DELETE_CBTREE(&T2, 10);
    
    printf("INORDER after deletion: ");
    INORDER_CBTREE(T2);
    printf("\n");

    printf("\n========================================\n");
    printf("BST IMPLEMENTATION TESTING COMPLETE\n");
    printf("========================================\n");
}


// ============================================
// MALLOC-BASED BST IMPLEMENTATIONS
// ============================================

void INIT_BST(BST *T) {
    *T = NULL;
}

void INSERT_BST(BST *T, int elem) {
    BST *trav;
    
    // Use pointer-to-pointer to avoid parent tracking
    for (trav = T; *trav != NULL && (*trav)->data != elem; ) {
        trav = (elem < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
    }
    
    // Insert only if not duplicate
    if (*trav == NULL) {
        BST newNode = (BST)malloc(sizeof(NodeType));
        if (newNode != NULL) {
            newNode->data = elem;
            newNode->LC = newNode->RC = NULL;
            *trav = newNode;
        }
    }
}

void DELETE_BST(BST *T, int elem) {
    BST *trav, *successor, temp;
    
    if (*T == NULL) return;
    
    // Find the node to delete
    for (trav = T; *trav != NULL && (*trav)->data != elem; ) {
        trav = (elem < (*trav)->data) ? &(*trav)->LC : &(*trav)->RC;
    }
    
    if (*trav != NULL) {
        // Case 1 & 2: Leaf or one child
        if ((*trav)->LC == NULL || (*trav)->RC == NULL) {
            temp = *trav;
            *trav = ((*trav)->LC == NULL) ? (*trav)->RC : (*trav)->LC;
            free(temp);
        }
        // Case 3: Two children - use inorder successor (min of right subtree)
        else {
            // Find inorder successor (leftmost node in right subtree)
            for (successor = &(*trav)->RC; (*successor)->LC != NULL; successor = &(*successor)->LC) {}
            
            temp = *successor;
            *successor = temp->RC;  // Successor has at most one child (right)
            (*trav)->data = temp->data;  // Copy successor's data
            free(temp);
        }
    }
}

boolean MEMBER_BST(BST T, int elem) {
    BST trav;
    
    for (trav = T; trav != NULL && trav->data != elem; ) {
        trav = (elem < trav->data) ? trav->LC : trav->RC;
    }
    
    return (trav != NULL) ? TRUE : FALSE;
}

int MIN_BST(BST T) {
    BST trav;
    
    // Traverse left until leaf
    for (trav = T; trav != NULL && trav->LC != NULL; trav = trav->LC) {}
    
    return (trav != NULL) ? trav->data : -1;
}

int MAX_BST(BST T) {
    BST trav;
    
    // Traverse right until leaf
    for (trav = T; trav != NULL && trav->RC != NULL; trav = trav->RC) {}
    
    return (trav != NULL) ? trav->data : -1;
}

void PREORDER_BST(BST T) {
    if (T != NULL) {
        printf("%d ", T->data);
        PREORDER_BST(T->LC);
        PREORDER_BST(T->RC);
    }
}

void INORDER_BST(BST T) {
    if (T != NULL) {
        INORDER_BST(T->LC);
        printf("%d ", T->data);
        INORDER_BST(T->RC);
    }
}

void POSTORDER_BST(BST T) {
    if (T != NULL) {
        POSTORDER_BST(T->LC);
        POSTORDER_BST(T->RC);
        printf("%d ", T->data);
    }
}

// Iterative Inorder using explicit stack simulation
void INORDER_ITERATIVE_BST(BST T) {
    BST stack[SIZE];
    int top = -1;
    BST current = T;
    
    while (current != NULL || top >= 0) {
        // Reach leftmost node
        while (current != NULL) {
            stack[++top] = current;
            current = current->LC;
        }
        
        // Current is NULL, pop and print
        current = stack[top--];
        printf("%d ", current->data);
        
        // Visit right subtree
        current = current->RC;
    }
}

int HEIGHT_BST(BST T) {
    if (T == NULL) return -1;  // Height of empty tree is -1
    
    int leftHeight = HEIGHT_BST(T->LC);
    int rightHeight = HEIGHT_BST(T->RC);
    
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

int COUNT_NODES_BST(BST T) {
    if (T == NULL) return 0;
    
    return 1 + COUNT_NODES_BST(T->LC) + COUNT_NODES_BST(T->RC);
}

boolean IS_BALANCED_BST(BST T) {
    if (T == NULL) return TRUE;
    
    int leftHeight = HEIGHT_BST(T->LC);
    int rightHeight = HEIGHT_BST(T->RC);
    int diff = (leftHeight > rightHeight) ? (leftHeight - rightHeight) : (rightHeight - leftHeight);
    
    if (diff > 1) return FALSE;
    
    return IS_BALANCED_BST(T->LC) && IS_BALANCED_BST(T->RC);
}

void LEVEL_ORDER_BST(BST T) {
    if (T == NULL) return;
    
    // Simple queue using array (circular queue would be better)
    BST queue[SIZE];
    int front = 0, rear = 0;
    
    queue[rear++] = T;
    
    while (front < rear) {
        BST current = queue[front++];
        printf("%d ", current->data);
        
        if (current->LC != NULL) queue[rear++] = current->LC;
        if (current->RC != NULL) queue[rear++] = current->RC;
    }
}


// ============================================
// CURSOR-BASED BST IMPLEMENTATIONS
// ============================================

void INIT_VHEAP(VHeap *VH) {
    int i;
    
    *VH = (VHeap)malloc(sizeof(VirtualHeap));
    
    if (*VH != NULL) {
        (*VH)->avail = 0;
        
        // Initialize avail list (each node points to next available)
        for (i = 0; i < SIZE - 1; i++) {
            (*VH)->Nodes[i].LC = i + 1;
            (*VH)->Nodes[i].RC = i + 1;
        }
        (*VH)->Nodes[SIZE - 1].LC = (*VH)->Nodes[SIZE - 1].RC = -1;
    }
}

int ALLOC_SPACE(VHeap VH) {
    int temp = VH->avail;
    
    if (temp != -1) {
        VH->avail = VH->Nodes[temp].LC;  // Move to next available
    }
    
    return temp;
}

void DEALLOC_SPACE(VHeap VH, int index) {
    VH->Nodes[index].LC = VH->Nodes[index].RC = VH->avail;
    VH->avail = index;
}

void INIT_CBTREE(CBTree *T, VHeap *VH) {
    T->root = -1;
    T->VH = *VH;
}

void INSERT_CBTREE(CBTree *T, int elem) {
    int *trav;
    int newIdx;
    
    // Use pointer-to-index pattern (same as pointer-to-pointer for malloc)
    for (trav = &T->root; *trav != -1 && T->VH->Nodes[*trav].data != elem; ) {
        trav = (elem < T->VH->Nodes[*trav].data) ? 
               &T->VH->Nodes[*trav].LC : 
               &T->VH->Nodes[*trav].RC;
    }
    
    // Insert only if not duplicate
    if (*trav == -1) {
        newIdx = ALLOC_SPACE(T->VH);
        if (newIdx != -1) {
            T->VH->Nodes[newIdx].data = elem;
            T->VH->Nodes[newIdx].LC = T->VH->Nodes[newIdx].RC = -1;
            *trav = newIdx;
        }
    }
}

void DELETE_CBTREE(CBTree *T, int elem) {
    int *trav, *successor, temp;
    
    if (T->root == -1) return;
    
    // Find the node to delete
    for (trav = &T->root; *trav != -1 && T->VH->Nodes[*trav].data != elem; ) {
        trav = (elem < T->VH->Nodes[*trav].data) ? 
               &T->VH->Nodes[*trav].LC : 
               &T->VH->Nodes[*trav].RC;
    }
    
    if (*trav != -1) {
        // Case 1 & 2: Leaf or one child
        if (T->VH->Nodes[*trav].LC == -1 || T->VH->Nodes[*trav].RC == -1) {
            temp = *trav;
            *trav = (T->VH->Nodes[*trav].LC == -1) ? 
                    T->VH->Nodes[*trav].RC : 
                    T->VH->Nodes[*trav].LC;
            DEALLOC_SPACE(T->VH, temp);
        }
        // Case 3: Two children
        else {
            // Find inorder successor
            for (successor = &T->VH->Nodes[*trav].RC; 
                 T->VH->Nodes[*successor].LC != -1; 
                 successor = &T->VH->Nodes[*successor].LC) {}
            
            temp = *successor;
            *successor = T->VH->Nodes[temp].RC;
            T->VH->Nodes[*trav].data = T->VH->Nodes[temp].data;
            DEALLOC_SPACE(T->VH, temp);
        }
    }
}

boolean MEMBER_CBTREE(CBTree T, int elem) {
    int trav;
    
    for (trav = T.root; trav != -1 && T.VH->Nodes[trav].data != elem; ) {
        trav = (elem < T.VH->Nodes[trav].data) ? 
               T.VH->Nodes[trav].LC : 
               T.VH->Nodes[trav].RC;
    }
    
    return (trav != -1) ? TRUE : FALSE;
}

int MIN_CBTREE(CBTree T) {
    int trav;
    
    for (trav = T.root; trav != -1 && T.VH->Nodes[trav].LC != -1; trav = T.VH->Nodes[trav].LC) {}
    
    return (trav != -1) ? T.VH->Nodes[trav].data : -1;
}

int MAX_CBTREE(CBTree T) {
    int trav;
    
    for (trav = T.root; trav != -1 && T.VH->Nodes[trav].RC != -1; trav = T.VH->Nodes[trav].RC) {}
    
    return (trav != -1) ? T.VH->Nodes[trav].data : -1;
}

void PREORDER_CBTREE(CBTree T) {
    int og = T.root;
    
    if (T.root != -1) {
        printf("%d ", T.VH->Nodes[T.root].data);
        
        T.root = T.VH->Nodes[T.root].LC;
        PREORDER_CBTREE(T);
        
        T.root = og;
        T.root = T.VH->Nodes[T.root].RC;
        PREORDER_CBTREE(T);
    }
}

void INORDER_CBTREE(CBTree T) {
    int og = T.root;
    
    if (T.root != -1) {
        T.root = T.VH->Nodes[T.root].LC;
        INORDER_CBTREE(T);
        
        T.root = og;
        printf("%d ", T.VH->Nodes[T.root].data);
        
        T.root = T.VH->Nodes[T.root].RC;
        INORDER_CBTREE(T);
    }
}

void POSTORDER_CBTREE(CBTree T) {
    int og = T.root;
    
    if (T.root != -1) {
        T.root = T.VH->Nodes[T.root].LC;
        POSTORDER_CBTREE(T);
        
        T.root = og;
        T.root = T.VH->Nodes[T.root].RC;
        POSTORDER_CBTREE(T);
        
        T.root = og;
        printf("%d ", T.VH->Nodes[T.root].data);
    }
}

int HEIGHT_CBTREE(CBTree T) {
    if (T.root == -1) return -1;
    
    CBTree left = T, right = T;
    left.root = T.VH->Nodes[T.root].LC;
    right.root = T.VH->Nodes[T.root].RC;
    
    int leftHeight = HEIGHT_CBTREE(left);
    int rightHeight = HEIGHT_CBTREE(right);
    
    return 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
}

int COUNT_NODES_CBTREE(CBTree T) {
    if (T.root == -1) return 0;
    
    CBTree left = T, right = T;
    left.root = T.VH->Nodes[T.root].LC;
    right.root = T.VH->Nodes[T.root].RC;
    
    return 1 + COUNT_NODES_CBTREE(left) + COUNT_NODES_CBTREE(right);
}
