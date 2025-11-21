#include <stdio.h>
#include <stdlib.h>

typedef struct Node {

    int elem;
    struct Node* LC; 
    struct Node* RC; 
    
    
} *BST;


/* Initialize the BST root to NULL (empty tree). */
void initBST (BST *T)
{   
    *T = NULL;
}


/* Pre-order traversal (root, left, right).
   NULL-guard prevents crashes when called on empty subtree. */
void preOrderPrint(BST T)
{
    if (T == NULL) return;
    printf("%d ", T->elem);
    preOrderPrint(T->LC);
    preOrderPrint(T->RC);
}


/* In-order traversal (left, root, right).
   Fixed: use inOrderPrint recursively (previously called preOrderPrint).
*/
void inOrderPrint(BST T)
{
    if (T == NULL) return;
    inOrderPrint(T->LC);
    printf("%d ", T->elem);
    inOrderPrint(T->RC);
}


/* Post-order traversal (left, right, root). */
void postOrderPrint(BST T)
{
    if (T == NULL) return;
    postOrderPrint(T->LC);
    postOrderPrint(T->RC);
    printf("%d ", T->elem);
}


/* Insert element into BST.
   Uses pointer-to-pointer traversal to link new node directly into the
   parent's child pointer. Allocates a new node when reaching a NULL child.
*/
void insertElem (BST* T, int n)
{
    BST *trav = T;

    while (*trav != NULL && (*trav)->elem != n)
    {
        if (n < (*trav)->elem ) trav = &(*trav)->LC;
        else trav = &(*trav)->RC;
    }

    if (*trav == NULL) {
        /* allocate and link new node */
        *trav = malloc(sizeof(struct Node));
     
        (*trav)->LC = NULL;
        (*trav)->RC = NULL;
        (*trav)->elem = n;   
    }
    else {
        printf("%d is already in the BST!\n", n);
    }

}


/* Remove and return minimum element from subtree rooted at *T.
   Traverses to the leftmost node, relinks its right child (if any),
   frees the removed node and returns its value. */
int deleteMin (BST* T)
{
    if (T == NULL || *T == NULL) {
        fprintf(stderr, "deleteMin called on empty subtree\n");
        exit(EXIT_FAILURE);
    }

    BST *p = T;
    while ((*p)->LC != NULL) p = &(*p)->LC;

    int val = (*p)->elem;
    BST toFree = *p;
    /* replace leftmost node with its right child (may be NULL) */
    *p = toFree->RC;
    free(toFree);
    return val;

}


/* Delete element n from BST (if present). Uses pointer-to-pointer
   traversal like insert so we can relink parent pointers easily. */
void deleteElem (BST* T, int n)
{
    BST *trav = T;

    while (*trav != NULL && (*trav)->elem != n)
    {
        if (n < (*trav)->elem ) trav = &(*trav)->LC;
        else trav = &(*trav)->RC;
    }

    if (*trav == NULL) return; /* not found */

    if ((*trav)->LC == NULL && (*trav)->RC  == NULL)
    {   
        BST node = *trav;
        *trav = NULL;
        free(node);
    }

    else if ((*trav)->LC == NULL)
    {
        BST node = *trav;
        *trav = node->RC;
        free(node);   
    }

    else if ((*trav)->RC == NULL)
    {
        BST node = *trav;
        *trav = node->LC;
        free(node);
    }

    else 
    {
        /* two children: replace value with successor and remove successor */
        (*trav)->elem = deleteMin(&(*trav)->RC);
    }

} 


int isMember (BST T, int n)
{
    while (T != NULL && T->elem != n)
    {
        if (n < T->elem) T = T->LC;
        else if (n > T->elem) T = T->RC;
    }

    return (T != NULL) ? 1 : 0;

}

int main()
{
    BST T;
    initBST(&T);


    insertElem(&T, 1);
    insertElem(&T, 2);
    insertElem(&T, 3);
    insertElem(&T, 4);
    insertElem(&T, 5);
    inOrderPrint(T);
    printf("\n");
    
    deleteElem(&T, 3);
    inOrderPrint(T);
    return 0;
}
