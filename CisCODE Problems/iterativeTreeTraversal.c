
/*
Your task is to traverse the tree and print out the following sequences of numbers:

1) 4 2 5 1 6 3

2) 6 3 5 4 2 1

3) 1 3 6 2 5 4

The main challenge here is to be able to traverse ITERATIVELY, AKA do NOT use any recursive functions whatsoever. You will be provided with a list of helper functions that will assist you in this process (this is already a hint!).

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *left;
    struct node *right;
} *treeNode;

typedef treeNode Tree;

typedef struct node2{
    treeNode data;
    struct node2 *next;
} *List;

typedef List Stack;

/* MAIN FUNCTIONS: DO NOT EDIT */
treeNode createNode(int x);
Stack initStack(); // returns a linked list implementation of a stack
void push(Stack *S, treeNode t); // pushes a tree node to a stack
treeNode pop(Stack *S); // pops the top of the stack and returns it
/* ----------- */

void traversal1(Tree t);
void traversal2(Tree t);
void traversal3(Tree t);

int main() {
    treeNode a = createNode(1);
    treeNode b = createNode(2);
    treeNode c = createNode(3);
    treeNode d = createNode(4);
    treeNode e = createNode(5);
    treeNode f = createNode(6);

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->left = f;

    printf("\nTRAVERSAL 1: \n");
    traversal1(a);

    printf("\nTRAVERSAL 2: \n");
    traversal2(a);

    printf("\nTRAVERSAL 3: \n");
    traversal3(a);
}

treeNode createNode(int x) {
    treeNode t = (treeNode)malloc(sizeof(treeNode));
    if (t != NULL) {
        t->val = x;
        t->left = NULL;
        t->right = NULL;
    }

    return t;
}

Stack initStack() {
    Stack S = (Stack)malloc(sizeof(struct node2));
    S = NULL;
    return S;
}

void push(Stack *S, treeNode t) {
    Stack temp = malloc(sizeof(struct node2));
    if (temp != NULL) {
        temp->data = t;
        temp->next = *S;
        *S = temp;
    }
}

treeNode pop(Stack *S) {
    treeNode t = (*S)->data;
    if (*S != NULL) {
        Stack temp = *S;
        *S = temp->next;
        free(temp);
    }

    return t;
}


// typedef struct node {
//     int val;
//     struct node *left;
//     struct node *right;
// } *treeNode;

// typedef treeNode Tree;

// typedef struct node2{
//     treeNode data;
//     struct node2 *next;
// } *List;

// typedef List Stack;








// 1) 4 2 5 1 6 3
void traversal1(Tree t) {
     Stack S = initStack();
    
     treeNode currNode = t;
     
     while (S != NULL || currNode != NULL)
     {
          while (currNode != NULL) 
            {
                push(&S, currNode);
              currNode = currNode ->left;
            }

            currNode = pop(&S);
            printf("%d ", currNode->val);
            currNode = currNode->right;
        
         
        }
  
    printf("\n");
 
}


// 2) 6 3 5 4 2 1
void traversal2(Tree t) {
    Stack S1 = initStack();
    Stack S2 = initStack();

    push(&S1, t);
    
    while (S1 != NULL)
      {
        treeNode currNode = pop(&S1);
        push(&S2, currNode);
        
        if (currNode -> right != NULL)
        {
          push(&S1, currNode->right);
        }

        if (currNode -> left != NULL)
        {
          push(&S1, currNode->left);
        }
      }


    while (S2 != NULL)
      {
        printf("%d ", pop(&S2)->val);
      }

}


// 3) 1 3 6 2 5 4
void traversal3(Tree t) {   
   Stack S = initStack();
     push(&S, t); 

      while (S != NULL)
        {
          treeNode currNode = pop(&S); 
          printf("%d ", currNode->val);

          if (currNode -> left != NULL) push(&S, currNode->left);
          if (currNode -> right != NULL) push(&S, currNode->right);
        }
  
    printf("\n");
 
}

