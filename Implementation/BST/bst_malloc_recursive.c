/*
========================================
BINARY SEARCH TREE - MALLOC-BASED (RECURSIVE)
Full Implementation Reference
========================================

Core Operations:
- INIT, INSERT, DELETE, MEMBER, MIN, MAX
- PREORDER, INORDER, POSTORDER (Recursive)
- HEIGHT, COUNT_NODES, IS_BALANCED, LEVEL_ORDER

Key Pattern: Pointer-to-pointer traversal for insertion/deletion
========================================
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

typedef enum {FALSE, TRUE} boolean;

typedef struct node {
    int data;
    struct node* LC;
    struct node* RC;
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

void main() {
    printf("========================================\n");
    printf("BST - MALLOC-BASED (RECURSIVE)\n");
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
    printf("PREORDER  : "); PREORDER_BST(T);
    printf("\nINORDER   : "); INORDER_BST(T);
    printf("\nPOSTORDER : "); POSTORDER_BST(T);
    
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
// IMPLEMENTATIONS
// ============================================

void INIT_BST(BST *T) {
    *T = NULL;
}

void INSERT_BST(BST *T, int elem) {
    BST *trav;
    
    // Pointer-to-pointer traversal
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
    
    // Find node to delete
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
        // Case 3: Two children - use inorder successor
        else {
            // Find inorder successor (min of right subtree)
            for (successor = &(*trav)->RC; (*successor)->LC != NULL; successor = &(*successor)->LC) {}
            
            temp = *successor;
            *successor = temp->RC;
            (*trav)->data = temp->data;
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
    
    for (trav = T; trav != NULL && trav->LC != NULL; trav = trav->LC) {}
    
    return (trav != NULL) ? trav->data : -1;
}

int MAX_BST(BST T) {
    BST trav;
    
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

int HEIGHT_BST(BST T) {
    if (T == NULL) return -1;
    
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
