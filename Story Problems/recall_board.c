// recall_board.c
// Scaffold for the Recall Board story problem.
// Fill in TODO sections with your chosen data structures and policies.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Recall {
    int id;               // recall identifier (unique)
    int manufacturer;     // manufacturer code
    int severity;         // priority score (lower == more critical)
    struct Recall *next;  // linked-list pointer (change if you choose another container)
} Recall;

typedef struct Slot {
    // Storage for recalls for a single manufacturer slot.
    Recall *head;
    // Optionally track which manufacturer is currently occupying this slot
    // (useful if you implement linear probing for mapping)
    int manufacturerCode; // -1 if empty / unassigned
} Slot;

typedef struct RecallBoard {
    Slot *slots;
    int slotCount; // capacity for mapping manufacturer -> slot
} RecallBoard;

// ---- lifecycle ----
void initBoard(RecallBoard *board, int slotCount);
void freeBoard(RecallBoard *board);

// ---- required operations (implement these) ----
void AddRecall(RecallBoard *board, int id, int manufacturerCode, int severity);
void ResolveRecall(RecallBoard *board, int id);
int GetMostCritical(RecallBoard *board, int manufacturerCode);
void PrintAllRecalls(RecallBoard *board);

// ---- helper prototypes ----
int mapManufacturerToSlot(RecallBoard *board, int manufacturerCode); // mapping policy
Recall *findRecallById(RecallBoard *board, int id, Slot **outSlot);

// ---- simple test harness ----
int main(void)
{
    RecallBoard board;
    initBoard(&board, 5); // example capacity; change for experiments

    // Example adds (IDs are arbitrary unique integers you can replace when testing)
    AddRecall(&board, 1001, 47, 4);
    AddRecall(&board, 1002, 22, 2);
    AddRecall(&board, 1003, 72, 6);
    AddRecall(&board, 1004, 47, 1);
    AddRecall(&board, 1005, 97, 3);

    PrintAllRecalls(&board);

    // Example operations that mirror the story sequence
    ResolveRecall(&board, 1004);      // resolve recall with id 1004
    AddRecall(&board, 1006, 22, 5);   // add another recall for manufacturer 22

    PrintAllRecalls(&board);

    freeBoard(&board);
    return 0;
}

/* ===================================================================
   Implementations
   - Replace or extend the simple linked-list placeholders below.
   - Keep function signatures so the harness compiles.
   =================================================================== */

void initBoard(RecallBoard *board, int slotCount)
{
    board->slotCount = slotCount;
    board->slots = (Slot *)malloc(sizeof(Slot) * slotCount);
    for (int i = 0; i < slotCount; ++i) {
        board->slots[i].head = NULL;
        board->slots[i].manufacturerCode = -1; // unassigned
    }
}

void freeBoard(RecallBoard *board)
{
    if (!board || !board->slots) return;
    for (int i = 0; i < board->slotCount; ++i) {
        Recall *cur = board->slots[i].head;
        while (cur) {
            Recall *n = cur->next;
            free(cur);
            cur = n;
        }
    }
    free(board->slots);
    board->slots = NULL;
    board->slotCount = 0;
}

int mapManufacturerToSlot(RecallBoard *board, int manufacturerCode)
{
    // Default mapping: simple modulo (f(x) = x mod slotCount).
    // If you implement open addressing / linear probing, use this as the base hash.
    if (board->slotCount <= 0) return 0;
    return (manufacturerCode % board->slotCount + board->slotCount) % board->slotCount;
}

Recall *findRecallById(RecallBoard *board, int id, Slot **outSlot)
{
    if (!board) { if (outSlot) *outSlot = NULL; return NULL; }
    for (int i = 0; i < board->slotCount; ++i) {
        Recall *cur = board->slots[i].head;
        while (cur) {
            if (cur->id == id) {
                if (outSlot) *outSlot = &board->slots[i];
                return cur;
            }
            cur = cur->next;
        }
    }
    if (outSlot) *outSlot = NULL;
    return NULL;
}

void AddRecall(RecallBoard *board, int id, int manufacturerCode, int severity)
{
    // TODO: Implement your chosen approach.
    // This naive version:
    int idx = mapManufacturerToSlot(board, manufacturerCode);

    // If slot's manufacturerCode is unassigned, assign it.
    if (board->slots[idx].manufacturerCode == -1) {
        board->slots[idx].manufacturerCode = manufacturerCode;
    }

    // Simple insert at head (not priority-ordered). Replace with a priority queue / sorted insert if required.
    Recall *r = (Recall *)malloc(sizeof(Recall));
    r->id = id;
    r->manufacturer = manufacturerCode;
    r->severity = severity;
    r->next = board->slots[idx].head;
    board->slots[idx].head = r;
}

void ResolveRecall(RecallBoard *board, int id)
{
    Slot *slotFound = NULL;
    Recall *target = findRecallById(board, id, &slotFound);
    if (!target || !slotFound) return;

    Recall *cur = slotFound->head, *prev = NULL;
    while (cur) {
        if (cur->id == id) {
            if (prev) prev->next = cur->next;
            else slotFound->head = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

int GetMostCritical(RecallBoard *board, int manufacturerCode)
{
    int idx = mapManufacturerToSlot(board, manufacturerCode);
    Recall *cur = board->slots[idx].head;
    if (!cur) return -1;
    Recall *best = cur;
    while (cur) {
        if (cur->severity < best->severity) best = cur;
        cur = cur->next;
    }
    return best ? best->id : -1;
}

void PrintAllRecalls(RecallBoard *board)
{
    if (!board) return;
    printf("Board contents (by slots):\n{\n");
    for (int i = 0; i < board->slotCount; ++i) {
        printf(" Slot %d (manu=%d):\n", i, board->slots[i].manufacturerCode);
        Recall *cur = board->slots[i].head;
        while (cur) {
            printf("  id=%d  m=%d  sev=%d\n", cur->id, cur->manufacturer, cur->severity);
            cur = cur->next;
        }
    }
    printf("}\n");
}
