/*
========================================
BINARY SEARCH TREE - CURSOR-BASED (VIRTUAL HEAP)
Full Implementation Reference
========================================

Core Operations:
- Virtual Heap management: INIT_VHEAP, ALLOC_SPACE, DEALLOC_SPACE
- BST operations: INIT, INSERT, DELETE, MEMBER, MIN, MAX
- Traversals: PREORDER, INORDER, POSTORDER
- Advanced: HEIGHT, COUNT_NODES

Key Pattern: Pointer-to-index traversal (int* instead of BST*)
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
    printf("BST - CURSOR-BASED (VIRTUAL HEAP)\n");
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
// VIRTUAL HEAP MANAGEMENT
// ============================================

void INIT_VHEAP(VHeap *VH) {
    int i;
    
    *VH = (VHeap)malloc(sizeof(VirtualHeap));
    
    if (*VH != NULL) {
        (*VH)->avail = 0;
        
        // Initialize avail list
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
        VH->avail = VH->Nodes[temp].LC;
    }
    
    return temp;
}

void DEALLOC_SPACE(VHeap VH, int index) {
    VH->Nodes[index].LC = VH->Nodes[index].RC = VH->avail;
    VH->avail = index;
}


// ============================================
// BST OPERATIONS
// ============================================

void INIT_CBTREE(CBTree *T, VHeap *VH) {
    T->root = -1;
    T->VH = *VH;
}

void INSERT_CBTREE(CBTree *T, int elem) {
    int *trav;
    int newIdx;
    
    // Pointer-to-index pattern
    for (trav = &T->root; *trav != -1 && T->VH->Nodes[*trav].data != elem; ) {
        trav = (elem < T->VH->Nodes[*trav].data) ? 
               &T->VH->Nodes[*trav].LC : 
               &T->VH->Nodes[*trav].RC;
    }
    
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
