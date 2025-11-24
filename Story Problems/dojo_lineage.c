/*
 * Story: The Kendo Dojo Lineage
 * Cultural Flavor: Japanese
 *
 * In a quiet corner of Kyoto, the "Silent Blade" Kendo Dojo has trained swordsmen for generations.
 * The dojo's structure is a strict hierarchy, passed down from master to student. This lineage can be
 * represented as a tree, where each practitioner is a node. The great Sensei, the root of the dojo,
 * has several direct students. Each of those students might then take on their own pupils, forming
 * branches in the dojo's history.
 *
 * Your task is to implement the core functions to navigate this complex lineage. You are given the
 * identities of the practitioners as integer IDs. You must implement the functions to find a
 * practitioner's direct master (PARENT), their first and most senior student (LEFTMOST_CHILD),
 * and the next practitioner of the same rank who trained under the same master (RIGHT_SIBLING).
 *
 * The dojo's records are stored using a list of children representation for a general tree.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_PRACTITIONERS 10

// A node in the list of children
typedef struct node {
    int id;
    struct node* next;
}*StudentList;

// The Tree represents the entire Dojo's lineage
typedef struct {
    StudentList masters[MAX_PRACTITIONERS]; // Each master has a list of their students
    int root_sensei_id;                     // The ID of the head of the dojo
} DojoLineage;

// --- Function Prototypes ---
void initialize_dojo(int root_id, DojoLineage *dojo);
void add_student(int master_id, int student_id, DojoLineage *dojo);
void display_lineage(DojoLineage dojo);
int get_master(int student_id, DojoLineage dojo);         // Corresponds to PARENT
int get_first_student(int master_id, DojoLineage dojo);   // Corresponds to LEFTMOST_CHILD
int get_next_dojo_brother(int student_id, DojoLineage dojo); // Corresponds to RIGHT_SIBLING
int get_grand_master(DojoLineage dojo);                   // Corresponds to ROOT

int main() {
    DojoLineage silentBladeDojo;
    
    // The Grand Master is practitioner '5'
    initialize_dojo(5, &silentBladeDojo);

    // Grand Master '5' takes on students '0', '6', and '2'
    add_student(5, 0, &silentBladeDojo);
    add_student(5, 6, &silentBladeDojo);
    add_student(5, 2, &silentBladeDojo);

    // Master '6' takes on students '3' and '1'
    add_student(6, 3, &silentBladeDojo);
    add_student(6, 1, &silentBladeDojo);
    
    // Master '1' takes on students '4' and '7'
    add_student(1, 4, &silentBladeDojo);
    add_student(1, 7, &silentBladeDojo);

    // Master '2' takes on student '8'
    add_student(2, 8, &silentBladeDojo);

    printf("----- Dojo Lineage Structure -----\n");
    display_lineage(silentBladeDojo);

    printf("\n----- Lineage Queries -----\n");
    printf("Who is the master of student 7? Expected: 1. Got: %d\n", get_master(7, silentBladeDojo));
    printf("Who is the master of student 1? Expected: 6. Got: %d\n", get_master(1, silentBladeDojo));
    printf("Who is the master of student 5? Expected: -1 (Grand Master). Got: %d\n", get_master(5, silentBladeDojo));

    printf("\n----- Student Queries -----\n");
    printf("Who is the first student of master 5? Expected: 0. Got: %d\n", get_first_student(5, silentBladeDojo));
    printf("Who is the first student of master 1? Expected: 4. Got: %d\n", get_first_student(1, silentBladeDojo));
    printf("Who is the first student of master 8? Expected: -1 (No students). Got: %d\n", get_first_student(8, silentBladeDojo));

    printf("\n----- Dojo Brother Queries -----\n");
    printf("Who is the next dojo brother of student 0? Expected: 6. Got: %d\n", get_next_dojo_brother(0, silentBladeDojo));
    printf("Who is the next dojo brother of student 6? Expected: 2. Got: %d\n", get_next_dojo_brother(6, silentBladeDojo));
    printf("Who is the next dojo brother of student 2? Expected: -1 (Youngest). Got: %d\n", get_next_dojo_brother(2, silentBladeDojo));
    printf("Who is the next dojo brother of student 4? Expected: 7. Got: %d\n", get_next_dojo_brother(4, silentBladeDojo));

    printf("\n----- Grand Master Query -----\n");
    printf("Who is the Grand Master of the dojo? Expected: 5. Got: %d\n", get_grand_master(silentBladeDojo));

    return 0;
}

// --- Provided Helper Functions ---

void initialize_dojo(int root_id, DojoLineage *dojo) {
    dojo->root_sensei_id = root_id;
    for (int i = 0; i < MAX_PRACTITIONERS; i++) {
        dojo->masters[i] = NULL;
    }
}

void add_student(int master_id, int student_id, DojoLineage *dojo) {
    if (master_id < 0 || master_id >= MAX_PRACTITIONERS) return;

    StudentList new_student = (StudentList)malloc(sizeof(struct node));
    if (new_student != NULL) {
        new_student->id = student_id;
        new_student->next = NULL;

        StudentList *current = &dojo->masters[master_id];
        while (*current != NULL) {
            current = &(*current)->next;
        }
        *current = new_student;
    }
}

void display_lineage(DojoLineage dojo) {
    printf("Grand Master (Root): [%d]\n\n", dojo.root_sensei_id);
    for (int i = 0; i < MAX_PRACTITIONERS; i++) {
        printf("Master [%d] -> ", i);
        StudentList current = dojo.masters[i];
        while (current != NULL) {
            printf("|%d| -> ", current->id);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// --- YOUR IMPLEMENTATION GOES HERE ---

/**
 * @brief Finds the master (parent) of a given student.
 * @param student_id The ID of the student.
 * @param dojo The dojo lineage structure.
 * @return The ID of the master, or -1 if not found or the student is the Grand Master.
 */


 /*
 #define MAX_PRACTITIONERS 10

// A node in the list of children
typedef struct node {
    int id;
    struct node* next;
}*StudentList;

// The Tree represents the entire Dojo's lineage
typedef struct {
    StudentList masters[MAX_PRACTITIONERS]; // Each master has a list of their students
    int root_sensei_id;                     // The ID of the head of the dojo
} DojoLineage;
 
 */
int get_master(int student_id, DojoLineage dojo) {
    // TODO: Implement this function.
    // Traverse the masters array. For each master, traverse their list of students.
    // If student_id is found, return the master's ID (the index).

    for (int i = 0; i < MAX_PRACTITIONERS; i++)
    {
        StudentList trav = dojo.masters[i];

        while (trav != NULL)
        {   
            if (trav->id == student_id) return i;

            trav = trav ->next;
        }
    }

    return -1; // Placeholder
}

/**
 * @brief Finds the first (leftmost) student of a given master.
 * @param master_id The ID of the master.
 * @param dojo The dojo lineage structure.
 * @return The ID of the first student, or -1 if the master has no students.
 */
int get_first_student(int master_id, DojoLineage dojo) {
    // TODO: Implement this function.
    // Check if the master_id is valid and if their student list is not empty.
    // If so, return the ID of the first node in the list.

    if (master_id < MAX_PRACTITIONERS)
    {
        return (dojo.masters[master_id] != NULL) ? dojo.masters[master_id]->id : -1;
    }

}

/**
 * @brief Finds the next practitioner of the same rank (right sibling).
 * @param student_id The ID of the student.
 * @param dojo The dojo lineage structure.
 * @return The ID of the next dojo brother, or -1 if they are the last/only student.
 */
int get_next_dojo_brother(int student_id, DojoLineage dojo) {
    // TODO: Implement this function.
    // First, find the master of the given student_id.
    // Then, traverse that master's student list. When you find the student_id,
    // return the ID of the next student in the list.

    int studentMaster = get_master(student_id, dojo);
    StudentList trav = dojo.masters[studentMaster];

    while (trav -> next != NULL)
    {
        if (trav->id == student_id) return trav->next->id;
        trav = trav -> next;
    }
    return -1; // Placeholder
}

/**
 * @brief Returns the Grand Master (root) of the dojo.
 * @param dojo The dojo lineage structure.
 * @return The ID of the Grand Master.
 */
int get_grand_master(DojoLineage dojo) {
    return dojo.root_sensei_id;
}
