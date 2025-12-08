/*
========================================
BST ITERATIVE TRAVERSALS (DFS & BFS)
Implementation Mode - Compare Recursive vs Iterative
========================================

GOAL: Understand how to convert recursive tree traversals to iterative
using explicit stacks (DFS) and queues (BFS).

WHY THIS MATTERS:
- Some environments have limited stack space → recursion risks overflow
- Iterative patterns transfer directly to graph traversals tomorrow
- Exams sometimes require "implement without recursion"
- Deepens understanding of call stack mechanics

KEY INSIGHT: 
Recursion uses the call stack implicitly. 
Iterative uses an explicit data structure (array/stack/queue).

========================================
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

// ============================================
// RECURSIVE TRAVERSALS (Review)
// ============================================

void preorder_recursive(BST root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder_recursive(root->left);
    preorder_recursive(root->right);
}

void inorder_recursive(BST root) {
    if (root == NULL) return;
    inorder_recursive(root->left);
    printf("%d ", root->data);
    inorder_recursive(root->right);
}

void postorder_recursive(BST root) {
    if (root == NULL) return;
    postorder_recursive(root->left);
    postorder_recursive(root->right);
    printf("%d ", root->data);
}


// ============================================
// ITERATIVE DFS TRAVERSALS (Using Stack)
// ============================================

/*
 * PREORDER ITERATIVE (Root → Left → Right)
 * 
 * Stack pattern:
 * 1. Push root
 * 2. While stack not empty:
 *    - Pop node, print it
 *    - Push RIGHT child first (so LEFT is processed first when popped)
 *    - Push LEFT child
 * 
 * Why right first? Stack is LIFO → we want left processed before right.
 */
void preorder_iterative(BST root) {
    if (root == NULL) return;
    
    BST stack[STACK_SIZE];
    int top = -1;
    
    stack[++top] = root;  // Push root
    
    while (top >= 0) {
        BST current = stack[top--];  // Pop
        printf("%d ", current->data);
        
        // Push right first, then left (LIFO order)
        if (current->right != NULL) stack[++top] = current->right;
        if (current->left != NULL) stack[++top] = current->left;
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
    int top = -1;
    BST current = root;
    
    while (current != NULL || top >= 0) {
        // Go left as far as possible, pushing nodes
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        
        // Backtrack: pop, print, go right
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
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
    
    BST stack1[STACK_SIZE], stack2[STACK_SIZE];
    int top1 = -1, top2 = -1;
    
    stack1[++top1] = root;
    
    // Modified preorder: push to stack2 instead of printing
    while (top1 >= 0) {
        BST current = stack1[top1--];
        stack2[++top2] = current;
        
        // Push left first, then right (reverse of preorder)
        if (current->left != NULL) stack1[++top1] = current->left;
        if (current->right != NULL) stack1[++top1] = current->right;
    }
    
    // Print stack2 in reverse (pop order gives postorder)
    while (top2 >= 0) {
        printf("%d ", stack2[top2--]->data);
    }
}


// ============================================
// ITERATIVE BFS (Level-Order using Queue)
// ============================================

/*
 * BFS / LEVEL-ORDER (You already did this!)
 * 
 * Queue pattern:
 * 1. Enqueue root
 * 2. While queue not empty:
 *    - Dequeue node, print it
 *    - Enqueue left child (if exists)
 *    - Enqueue right child (if exists)
 * 
 * This is breadth-first: visit all nodes at depth d before depth d+1.
 */
void level_order_iterative(BST root) {
    if (root == NULL) return;
    
    BST queue[QUEUE_SIZE];
    int front = 0, rear = 0;
    
    queue[rear++] = root;  // Enqueue root
    
    while (front < rear) {
        BST current = queue[front++];  // Dequeue
        printf("%d ", current->data);
        
        if (current->left != NULL) queue[rear++] = current->left;
        if (current->right != NULL) queue[rear++] = current->right;
    }
}


// ============================================
// HELPER: Build Sample BST
// ============================================

BST create_node(int data) {
    BST node = (BST)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

BST build_sample_tree() {
    /*
     * Build tree:
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


// ============================================
// MAIN - COMPARE RECURSIVE VS ITERATIVE
// ============================================

int main() {
    printf("========================================\n");
    printf("  BST ITERATIVE TRAVERSALS (DFS & BFS)\n");
    printf("========================================\n\n");
    
    BST tree = build_sample_tree();
    
    printf("Tree Structure:\n");
    printf("         10\n");
    printf("        /  \\\n");
    printf("       5    15\n");
    printf("      / \\   / \\\n");
    printf("     3   7 12  18\n\n");
    
    // ===== PREORDER =====
    printf("=== PREORDER (Root → Left → Right) ===\n");
    printf("Recursive : "); preorder_recursive(tree); printf("\n");
    printf("Iterative : "); preorder_iterative(tree); printf("\n");
    printf("Expected  : 10 5 3 7 15 12 18\n\n");
    
    // ===== INORDER =====
    printf("=== INORDER (Left → Root → Right) ===\n");
    printf("Recursive : "); inorder_recursive(tree); printf("\n");
    printf("Iterative : "); inorder_iterative(tree); printf("\n");
    printf("Expected  : 3 5 7 10 12 15 18 (sorted!)\n\n");
    
    // ===== POSTORDER =====
    printf("=== POSTORDER (Left → Right → Root) ===\n");
    printf("Recursive : "); postorder_recursive(tree); printf("\n");
    printf("Iterative : "); postorder_iterative(tree); printf("\n");
    printf("Expected  : 3 7 5 12 18 15 10\n\n");
    
    // ===== LEVEL-ORDER (BFS) =====
    printf("=== LEVEL-ORDER / BFS (Breadth-First) ===\n");
    printf("Iterative : "); level_order_iterative(tree); printf("\n");
    printf("Expected  : 10 5 15 3 7 12 18\n\n");
    
    printf("========================================\n");
    printf("  KEY TAKEAWAYS\n");
    printf("========================================\n");
    printf("1. DFS (Preorder/Inorder/Postorder) → Use STACK\n");
    printf("2. BFS (Level-order) → Use QUEUE\n");
    printf("3. Preorder iterative: easiest (push right, then left)\n");
    printf("4. Inorder iterative: trickier (push left spine first)\n");
    printf("5. Postorder iterative: hardest (two stacks or visited flag)\n");
    printf("6. BFS: same as your tree level-order!\n\n");
    printf("TOMORROW: Apply these patterns to GRAPHS\n");
    printf("(adjacency lists + visited tracking)\n");
    printf("========================================\n");
    
    return 0;
}


/*
========================================
PRACTICE EXERCISES (15-20 min)
========================================

1. MODIFY PREORDER ITERATIVE:
   - Track depth of each node as you pop
   - Print: "Node X at depth D"

2. MODIFY INORDER ITERATIVE:
   - Count how many nodes you visit
   - Verify count == total nodes in tree

3. MODIFY LEVEL-ORDER:
   - Print each level on a new line
   - Hint: Track level boundaries using a sentinel or count

4. CHALLENGE:
   - Implement postorder with ONE stack + visited flag
   - (Harder but more space-efficient)

5. TRACE BY HAND:
   - Draw the tree on paper
   - Simulate preorder_iterative step-by-step
   - Write down stack contents after each push/pop

========================================
WHY THIS PREPARES YOU FOR GRAPHS
========================================

- Graphs don't have "parent" pointers → must use stack/queue
- Graphs can have cycles → need "visited" tracking
- DFS on graph = exactly like tree DFS + visited array
- BFS on graph = exactly like tree BFS + visited array

PATTERN TRANSFER (Tomorrow):
- Tree: stack[++top] = node->left;
- Graph: for each neighbor: if (!visited[neighbor]) stack[++top] = neighbor;

You've already got the mechanics — graphs just add visited tracking!

========================================
*/
