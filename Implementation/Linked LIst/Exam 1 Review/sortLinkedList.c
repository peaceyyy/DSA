#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {

    char Fname[24];
    char Lname[16];

} NameType;

typedef struct {

    NameType fullName;
    int ID;
    char role[24];
    char department[24];
    

} employeeType; 


typedef struct Node {

    employeeType employee;
    struct Node* link;
} *employeeNode;


void initList(employeeNode *head) {
    *head = NULL;
}

employeeNode createNode(employeeType employee) {
    employeeNode newNode = (employeeNode)malloc(sizeof(struct Node));
    if (newNode) {
        newNode->employee = employee;
        newNode->link = NULL;
    }
    return newNode;
}

void insertLast(employeeNode *head, employeeType employee) {
    employeeNode newNode = createNode(employee);
    if (!*head) {
        *head = newNode;
    } else {
        employeeNode *trav;
        for (trav = head; *trav != NULL; trav = &(*trav)->link) {}
        *trav = newNode;
    }
}

void swapEmployeeData (employeeNode employeeA, employeeNode employeeB){
    
    // printf("i swapped\n");
    employeeType temp = (employeeA)->employee;
    (employeeA)->employee = (employeeB)->employee;
    (employeeB)->employee = temp;
}


void sortEmployees(employeeNode *head) {

    employeeNode* curr;
    employeeNode* trav;

    for (curr = head; (*curr) != NULL; curr = &(*curr)->link){

        int swapped = 0; //false

        for (trav = head; (*trav)->link != NULL; trav = &(*trav)->link){
            if (strcmp((*trav)->employee.fullName.Lname, (*trav)->link->employee.fullName.Lname) > 0){
                // printf("%s compared with %s\n", (*trav)->employee.fullName.Lname, (*trav)->link->employee.fullName.Lname);
                swapEmployeeData(*trav, (*trav)->link);
                swapped = 1;
            }

        }

        if (swapped ==
             0) break;

    }
}

void sortEmployees(employeeNode *head) {

    employeeNode* curr;
    employeeNode* trav;

    for (curr = head; (*curr) != NULL; curr = &(*curr)->link){

        int swapped = 0; //false
        employeeNode minEmployee = *curr; 


        for (trav = curr; (*trav) != NULL; trav = &(*trav)->link){
            if (strcmp((minEmployee)->employee.fullName.Lname, (*trav)->employee.fullName.Lname) > 0){
                // printf("%s compared with %s\n", (*trav)->employee.fullName.Lname, (*trav)->link->employee.fullName.Lname);
                minEmployee = (*trav);
                // swapped = 1;
            }
            
            
        }

        if (minEmployee != *curr){

                swapEmployeeData(*curr, minEmployee);
            }


    }
}


void displayLinkedList (employeeNode* head){

    employeeNode* trav;

    for (trav = head; *trav != NULL; trav = &(*trav)->link){

        printf("%s %s | ID: %d | Department: %s | Role: %s\n", (*trav)->employee.fullName.Fname, (*trav)->employee.fullName.Lname,(*trav)->employee.ID, (*trav)->employee.department, (*trav)->employee.role);
    }
}



int main(){

    employeeNode head;
    initList(&head);

    employeeType emp1 = {{"John", "Doe"}, 1001, "Manager", "Sales"};
    employeeType emp2 = {{"Jane", "Smith"}, 1002, "Developer", "IT"};
    employeeType emp3 = {{"Jane", "Doe"}, 1003, "Developer", "IS"};
    employeeType emp4 = {{"Alice", "Brown"}, 1004, "Analyst", "Finance"};
    employeeType emp5 = {{"Bob", "Adams"}, 1005, "Designer", "Marketing"};

    insertLast(&head, emp1);
    insertLast(&head, emp2);
    insertLast(&head, emp3);
    insertLast(&head, emp4);
    insertLast(&head, emp5);

    printf("Original List:\n");
    displayLinkedList(&head);

    sortEmployees(&head);

    printf("\nSorted List (by Last Name):\n");
    displayLinkedList(&head);

    
    // printf("\n\n%s", head->employee.fullName.Lname);
    

}