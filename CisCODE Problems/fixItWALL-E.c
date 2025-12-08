/*
Fix it! WALL-E! By Cliff Jharel Jao

Infix and Postfix Expressions are two common ways of writing arithmetic operations. Infix expressions are the standard mathematical form where the operator is placed between the operands. On the other hand, postfix expressions places the operator after the operands, such as "AB+" or "AB+C*". Concept-wise, humans prefer Infix while computers prefer Postfix. (Research more about them if description is vague)

Suppose you have a computer friend, WALL-E, capable of revitalizing an entire planet with sufficient instructions. However, WALL-E can only comprehend Postfix notations which is out of your scope of knowledge.

To solve this, given a mathematical infix expression, you are to create a function that converts it into a postfix expression using an Array-Stack Implementation. The function should return a stack that already contains the postfix expression in its elemental array.

ASSUME and LIMITATIONS:

Valid Operators -> (+, -, /, *, ^)
Valid Operands are only single digits (0-9)
NOTE ON HELPER FUNCTIONS!

findPrecedence()
There is no way of identifying an operator's precedence if it is of data type char. This function will help in identifying that operator's precedence.
Stack Operation Functions
Utilize these to implement stack operations for efficiency
SAVE WALL-E!

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50

typedef struct
{
    char elem[MAX];
    int top;
} Stack;

// Helper Function | DO NOT TOUCH
void init(Stack *s);
bool isEmpty(Stack s);
bool isFull(Stack s);
char top(Stack s);
void pop(Stack *s);
void push(Stack *s, char data);
int findPrecedence(char op);

// YOUR TASK
Stack InfixTOPostfix(char infix[MAX]);

// Main Function | DO NOT TOUCH
int main()
{
    char infix[256];

    printf("(STRICTLY NO SPACES!)\nEnter infix expression: ");
    scanf("%s", infix);

    Stack postfix = InfixTOPostfix(infix);

    printf("Postfix Expression: %s\n", postfix.elem);

    return 0;
}

Stack InfixTOPostfix(char infix[MAX])
{

    Stack operatorStack;
    init(&operatorStack);
    Stack postFix;
    init(&postFix);
    int i = 0;
    
    while (infix[i] != '\0')
    {
        char current = infix[i];

        // If operand (digit or letter) -> append to output
        if ((current >= '0' && current <= '9') || (current >= 'A' && current <= 'Z') || (current >= 'a' && current <= 'z'))
        {
            push(&postFix, current);
        }

        // Opening parenthesis -> push to operator stack
        else if (current == '(')
        {
            push(&operatorStack, current);
        }

        // Closing parenthesis -> pop until matching '('
        else if (current == ')')
        {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(')
            {
                push(&postFix, top(operatorStack));
                pop(&operatorStack);
            }
            // pop the '('
            if (!isEmpty(operatorStack) && top(operatorStack) == '(') pop(&operatorStack);
        }

        // Operator
        else if (findPrecedence(current) > 0)
        {
            while (!isEmpty(operatorStack) && findPrecedence(top(operatorStack)) > 0)
            {
                int precTop = findPrecedence(top(operatorStack));
                int precCurr = findPrecedence(current);
                // If top has higher precedence, or same precedence and current is left-associative
                if (precTop > precCurr || (precTop == precCurr && current != '^'))
                {
                    push(&postFix, top(operatorStack));
                    pop(&operatorStack);
                }
                else break;
            }
            push(&operatorStack, current);
        }

        // else: ignore unknown characters (or spaces)

        i++;
    }

    // Pop any remaining operators
    while (!isEmpty(operatorStack))
    {
        char t = top(operatorStack);
        pop(&operatorStack);
        if (t != '(' && t != ')') push(&postFix, t);
    }

    // Null-terminate postfix string
    postFix.elem[postFix.top + 1] = '\0';
    return postFix;
}

// Helper Functions
void init(Stack *s)
{
    s->top = -1;
}

bool isEmpty(Stack s)
{
    return (s.top == -1) ? true : false;
}

bool isFull(Stack s)
{
    return (s.top == MAX - 1) ? true : false;
}

char top(Stack s)
{
    char d = '\0';
    return (!isEmpty(s)) ? s.elem[s.top] : d;
}

void pop(Stack *s)
{
    if (!isEmpty(*s))
    {
        s->top--;
    }
}

void push(Stack *s, char data)
{
    if (!isFull(*s))
    {
        s->elem[++s->top] = data;
    }
}

int findPrecedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}
