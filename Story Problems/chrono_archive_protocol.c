/*
 * CHRONO ARCHIVE PROTOCOL
 * By Professor Okabe, Department of Temporal Engineering
 * 
 * STORY:
 * The Organization has infiltrated the SERN mainframe, and you've discovered 
 * a hidden database of IBN 5100 access logs stored as a Binary Search Tree. 
 * Each node contains a timestamp (integer key) and associated metadata.
 * 
 * Your mission: Extract intelligence using four different "reading protocols" 
 * to decrypt the organization's operations timeline.
 * 
 * PROTOCOL DESCRIPTIONS:
 * 
 * 1. ANCESTRAL_LINEAGE_SCAN (ALS)
 *    "Visit the elder before exploring the family tree. Process the patriarch,
 *     then recursively investigate the left lineage, then the right lineage."
 * 
 * 2. SYMMETRIC_CIPHER_WALK (SCW)
 *    "Navigate the vault in ascending order of timestamps. Unlock the smallest
 *     key first, then proceed to the next larger, maintaining strict sequence."
 * 
 * 3. LEGACY_ARCHIVAL_TRACE (LAT)
 *    "Record the descendants before the ancestor. Process the entire left branch,
 *     then the entire right branch, then finally the parent node."
 * 
 * 4. RIPPLE_PROPAGATION_QUERY (RPQ)
 *    "Analyze by temporal distance from root. Process all nodes at depth 0,
 *     then depth 1, depth 2, etc., spreading outward like a wave."
 * 
 * YOUR TASK:
 * Implement all four protocols. Each should print the node keys following 
 * the described traversal logic.
 * 
 * CONSTRAINTS:
 * - Tree nodes contain integer keys (unique timestamps).
 * - All protocols must use the provided stack/queue helpers where applicable.
 * - ALS, SCW, LAT may be implemented recursively or iteratively.
 * - RPQ requires a queue-based approach.
 * 
 * HINTS:
 * - Read the protocol descriptions carefully — they describe *when* you visit a node.
 * - "Elder before family" vs "descendants before ancestor" is the key distinction.
 * - "Ascending order" implies sorted output.
 * - "Temporal distance" = depth/level in the tree.
 * 
 * EXPECTED BEHAVIOR:
 * For the test tree:
 *           50
 *          /  \
 *        30    70
 *       / \    / \
 *     20  40  60  80
 * 
 * ALS output: 50 30 20 40 70 60 80
 * SCW output: 20 30 40 50 60 70 80
 * LAT output: 20 40 30 60 80 70 50
 * RPQ output: 50 30 70 20 40 60 80
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// BST Node
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Stack (for iterative DFS variants)
typedef struct {
    Node *data[MAX];
    int top;
} Stack;

void initStack(Stack *s) { s->top = -1; }
bool isEmptyStack(Stack s) { return s.top == -1; }
void pushStack(Stack *s, Node *n) { if (s->top < MAX - 1) s->data[++s->top] = n; }
Node* popStack(Stack *s) { return (s->top >= 0) ? s->data[s->top--] : NULL; }
Node* peekStack(Stack s) { return (s.top >= 0) ? s.data[s.top] : NULL; }

// Queue (for BFS/level-order)
typedef struct {
    Node *data[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) { q->front = q->rear = -1; }
bool isEmptyQueue(Queue q) { return q.front == -1; }
void enqueue(Queue *q, Node *n) {
    if (q->front == -1) q->front = 0;
    q->data[++q->rear] = n;
}
Node* dequeue(Queue *q) {
    if (isEmptyQueue(*q)) return NULL;
    Node *n = q->data[q->front];
    if (q->front == q->rear) q->front = q->rear = -1;
    else q->front++;
    return n;
}

// BST helper: insert node
Node* insertNode(Node *root, int key) {
    if (!root) {
        Node *n = (Node*)malloc(sizeof(Node));
        n->key = key;
        n->left = n->right = NULL;
        return n;
    }
    if (key < root->key) root->left = insertNode(root->left, key);
    else if (key > root->key) root->right = insertNode(root->right, key);
    return root;
}


/*

 * 1. ANCESTRAL_LINEAGE_SCAN (ALS)
 *    "Visit the elder before exploring the family tree. Process the patriarch,
 *     then recursively investigate the left lineage, then the right lineage."
 * 
 * 2. SYMMETRIC_CIPHER_WALK (SCW)
 *    "Navigate the vault in ascending order of timestamps. Unlock the smallest
 *     key first, then proceed to the next larger, maintaining strict sequence."
 * 
 * 3. LEGACY_ARCHIVAL_TRACE (LAT)
 *    "Record the descendants before the ancestor. Process the entire left branch,
 *     then the entire right branch, then finally the parent node."
 * 
 * 4. RIPPLE_PROPAGATION_QUERY (RPQ)
 *    "Analyze by temporal distance from root. Process all nodes at depth 0,
 *     then depth 1, depth 2, etc., spreading outward like a wave."
 * 
 * 
*/

// =========================================================================
// TODO: IMPLEMENT THE FOUR PROTOCOLS BELOW
// =========================================================================

void ANCESTRAL_LINEAGE_SCAN(Node *root) {

    if (root == NULL) return;
    
    Stack s;
    initStack(&s);

    pushStack(&s, root);

    while (!isEmptyStack(s))
    {
        // printf("test");
        Node* curr = popStack(&s);
        printf("%d ", curr->key);

        if (curr->right != NULL) pushStack(&s, curr->right);
        if (curr->left != NULL) pushStack(&s, curr->left);
    }
    
}

void SYMMETRIC_CIPHER_WALK(Node *root) {
    // TODO: Implement this protocol
    if (root == NULL) return;
    
    Node* curr = root;
    Stack s;
    initStack(&s);

    while (curr != NULL || !isEmptyStack(s))
    {
        while (curr != NULL)
        {
            pushStack(&s, curr);
            curr = curr->left;
        }

        curr = popStack(&s);
        printf("%d ", curr->key);
        
        curr = curr->right;
    }
}

void LEGACY_ARCHIVAL_TRACE(Node *root) {

    if (root == NULL) return;

    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);

    pushStack(&s1, root);

    while (!isEmptyStack(s1))
    {
        Node* curr = popStack(&s1);
        pushStack(&s2, curr);
        
        if (curr->left != NULL) pushStack(&s1, curr->left);
        if (curr->right != NULL) pushStack(&s1, curr->right);
    }

    while(!isEmptyStack(s2))
    {   
        printf("%d ", peekStack(s2)->key);
        popStack(&s2);
    }
}

void RIPPLE_PROPAGATION_QUERY(Node *root) {

    if (root == NULL) return;

    Queue q; 
    initQueue(&q);

    enqueue(&q, root);

    while(!isEmptyQueue(q))
    {
        Node* curr = dequeue(&q);
        printf("%d ", curr->key);

        if (curr->left != NULL) enqueue(&q, curr->left);
        if (curr->right != NULL) enqueue(&q, curr->right);
    }
}

// =========================================================================
// MAIN: TEST HARNESS (DO NOT MODIFY)
// =========================================================================
int main(void) {
    Node *root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(keys) / sizeof(keys[0]);

    // Build test tree
    for (int i = 0; i < n; i++) root = insertNode(root, keys[i]);

    printf("=== CHRONO ARCHIVE PROTOCOL EXECUTION ===\n\n");

    printf("Protocol ALS (ANCESTRAL_LINEAGE_SCAN):\n");
    ANCESTRAL_LINEAGE_SCAN(root);
    printf("\n");
    // Expected: 50 30 20 40 70 60 80

    printf("Protocol SCW (SYMMETRIC_CIPHER_WALK):\n");
    SYMMETRIC_CIPHER_WALK(root);
    printf("\n");
    // // Expected: 20 30 40 50 60 70 80

    printf("Protocol LAT (LEGACY_ARCHIVAL_TRACE):\n");
    LEGACY_ARCHIVAL_TRACE(root);
    printf("\n");
    // Expected: 20 40 30 60 80 70 50

    printf("Protocol RPQ (RIPPLE_PROPAGATION_QUERY):\n");
    RIPPLE_PROPAGATION_QUERY(root);
    printf("\n");
    // Expected: 50 30 70 20 40 60 80

    printf("\n=== PROTOCOL EXECUTION COMPLETE ===\n");
    printf("El. Psy. Kongroo.\n");

    return 0;
}
