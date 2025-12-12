/*
Minimal boilerplate: BST iterative traversals
- Keeps minimal/high-level comments only
- Provides function stubs for you to implement
- Fill each TODO implementation and recompile
*/

#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100
#define QUEUE_SIZE 100

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} Node, *BST;

// --------- Function prototypes (stubs) ---------

// Recursive traversals (review)
void preorder_recursive(BST root);   // Root, Left, Right
void inorder_recursive(BST root);    // Left, Root, Right
void postorder_recursive(BST root);  // Left, Right, Root

// Iterative traversals (you implement)
void preorder_iterative(BST root);   // Use stack: push root, pop->print, push right then left
void inorder_iterative(BST root);    // Use stack: push left spine, pop->print, go right
void postorder_iterative(BST root);  // Two-stack or one-stack+visited flag
void level_order_iterative(BST root);// Use queue: enqueue, dequeue, enqueue children

// Helpers
BST create_node(int data);
BST build_sample_tree(void);

// --------- Minimal stubs ---------

void preorder_recursive(BST root) {
    if (root != NULL){
        printf("%d ", root->data);

        preorder_recursive(root->left);
        preorder_recursive(root->right);
    }

}

void inorder_recursive(BST root) {
    if (root != NULL){
        
        inorder_recursive(root->left);
        printf("%d ", root->data);
        inorder_recursive(root->right);
    }

}

void postorder_recursive(BST root) {
    if (root != NULL){
        
        postorder_recursive(root->left);
        postorder_recursive(root->right);
        printf("%d ", root->data);
    }
}

void preorder_iterative(BST root) {

    if (root == NULL) return;
    
    BST stack[STACK_SIZE];
    int top = 0; 

    stack[top++] = root; 

    while (top > 0){

        BST curr = stack[--top];
        printf("%d ", curr->data);

        if (curr->right != NULL) stack[top++] = curr->right;
        if (curr->left != NULL) stack[top++] = curr->left;

    }
}
/*
 * INORDER ITERATIVE (Left → Root → Right)
 * 
 * Trickier pattern - we need to go left as far as possible,
 * then pop & print, then go right.
 * 
 * Algorithm:
 * 1. current = root
 * 2. While (current != NULL OR stack not empty):
 *    a. If current != NULL:
 *       - Push current onto stack
 *       - Move left: current = current->left
 *    b. Else (current is NULL, we've gone too far left):
 *       - Pop from stack into current
 *       - Print current
 *       - Move right: current = current->right
 */
void inorder_iterative(BST root) {

    if (root == NULL) return;
    
    BST stack[STACK_SIZE];
    int top = 0;
    Node* curr = root;

    // still has to process down || stack still has smthn
    while (curr != NULL || top > 0){

        while (curr != NULL)
        {
            stack[top++] = curr; 
            curr = curr->left;
        }

        curr = stack[--top]; // pop
        printf("%d ", curr->data); 
        curr = curr->right;
    }
}

/*
 * POSTORDER ITERATIVE (Left → Right → Root)
 * 
 * Hardest iterative traversal. We need to ensure we visit a node
 * AFTER both its children.
 * 
 * Two-stack approach (simpler):
 * 1. Use stack1 for traversal (like preorder but reversed)
 * 2. Use stack2 to collect nodes in reverse postorder
 * 3. Stack1: push root, pop, push left then right
 * 4. Whatever we pop from stack1, push to stack2
 * 5. After stack1 empty, pop and print from stack2
 * 
 * Result: Root → Right → Left order in stack2
 *         Reverse it = Left → Right → Root (postorder)
 */

void postorder_iterative(BST root) {
    if (root == NULL) return;

    BST stack1[STACK_SIZE];
    BST stack2[STACK_SIZE];

    int top1 = 0, top2 = 0; 

    stack1[top1++] = root;

    while (top1 > 0)
    {
        Node* popped = stack1[--top1];
        stack2[top2++] = popped;

        if (popped->left != NULL) stack1[top1++] = popped->left;
        if (popped->right != NULL) stack1[top1++] = popped->right;
    }

    while (top2 > 0) printf("%d ", stack2[--top2]->data);
}

void level_order_iterative(BST root) {

    if (root == NULL) return;
    
    BST queue[QUEUE_SIZE];

    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front <  rear)
    {
        BST dequeuedNode = queue[front++];
        printf("%d ", dequeuedNode->data);

       
        if (dequeuedNode->left != NULL) queue[rear++] = dequeuedNode->left;
        if (dequeuedNode->right != NULL) queue[rear++] = dequeuedNode->right;

    }

}

BST create_node(int data) {
    BST node = (BST)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

BST build_sample_tree(void) {
    /* Sample tree (same as your working file):
     *         10
     *        /  \
     *       5    15
     *      / \   / \
     *     3   7 12  18
     */
    BST root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(15);
    root->left->left = create_node(3);
    root->left->right = create_node(7);
    root->right->left = create_node(12);
    root->right->right = create_node(18);
    return root;
}

int main(void) {
    BST tree = build_sample_tree();

    // Calls below are placeholders. Implement functions above,
    // then uncomment calls to test each traversal.

    printf("Recursive Preorder: "); preorder_recursive(tree); printf("\n");
    printf("Iterative Preorder: "); preorder_iterative(tree); printf("\n");

    printf("Recursive Inorder: "); inorder_recursive(tree); printf("\n");
    printf("Iterative Inorder: "); inorder_iterative(tree); printf("\n");

    printf("Recursive Postorder: "); postorder_recursive(tree); printf("\n");
    printf("Iterative Postorder: "); postorder_iterative(tree); printf("\n");

    printf("Level-order: "); level_order_iterative(tree); printf("\n");

    return 0;
}
