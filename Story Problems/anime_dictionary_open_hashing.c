/*
Anime Dictionary: Open Hashing (Cursor-Based)

Cultural flavor applied: Anime — Otaku references, club settings, and character names used respectfully.

Story Problem:

In the bustling halls of Neo-Tokyo Academy, the "Anime Club" is hosting its annual Otaku Treasure Hunt. Each member, from the stoic Shoto to the energetic Hinata, brings a rare anime DVD to contribute to the club's secret vault. The vault is organized using a magical Dictionary, powered by open hashing and cursor-based memory (rumor has it, the system was coded by a mysterious hacker known only as "Daru").

Your mission, Lab Member, is to help the club:
- Add new anime DVDs to the vault (insert)
- Remove DVDs that have been borrowed (delete)
- Check if a particular DVD is still in the vault (isMember)
- Display the current state of the vault

Each DVD is represented by a unique integer code (e.g., 3 for "Attack on Titan", 60 for "One Piece"). The vault can hold up to 10 hash buckets, and the magical heap has space for 20 DVDs. The club expects you to implement the missing functions so their treasure hunt runs smoothly!
*/

// --- Anime Dictionary Open Hashing (Cursor-Based) ---
#include <stdio.h>

#define HEAPMAX 20
#define MAX 10

typedef struct{
    int data;
    int link;
}NodeType;

typedef struct{
    NodeType Nodes[HEAPMAX];
    int Avail;
}VirtualHeap;

typedef int Dictionary[MAX];

// --- Function Prototypes ---
void initVirtualHeap(VirtualHeap *VH); // Already implemented
int allocSpace(VirtualHeap *VH);       // Already implemented
void deallocSpace(VirtualHeap *VH, int index); // Already implemented
void initDict(Dictionary D);           // Already implemented
void displayDict(VirtualHeap VH, Dictionary D); // Already implemented
int hash(int elem);                    // Already implemented

// --- Functions to Implement ---
void insertDict(VirtualHeap *VH, Dictionary D, int elem); // TODO: Fill out
void deleteDict(VirtualHeap *VH, Dictionary D, int elem); // TODO: Fill out
int isMember(VirtualHeap VH, Dictionary D, int elem);     // TODO: Fill out

// --- Main: Anime Club Vault Demo ---
int main(){
    VirtualHeap VH;
    Dictionary D;
    printf("\n***** NEO-TOKYO ANIME VAULT INIT *****\n");
    initVirtualHeap(&VH);
    initDict(D);
    displayDict(VH,D);
    
    printf("\n**** INSERT ANIME DVDS ****\n");
    // Shoto brings "Attack on Titan" (3)
    insertDict(&VH, D, 3);
    // Hinata brings "One Piece" (60)
    insertDict(&VH, D, 60);
    // Sakura brings "Demon Slayer" (4)
    insertDict(&VH, D, 4);
    // L brings "Death Note" (20)
    insertDict(&VH, D, 20);
    // Mikasa brings "Naruto" (69)
    insertDict(&VH, D, 69);
    displayDict(VH,D); // Expected: All DVDs appear in their hash buckets
    
    printf("\n**** DELETE ANIME DVDS ****\n");
    // Hinata borrows "One Piece" (60)
    deleteDict(&VH, D, 60);
    displayDict(VH, D); // Expected: "One Piece" (60) removed from vault
    
    printf("\n***** CHECK DVD MEMBERSHIP *****\n");
    printf("Is 'Naruto' (69) in the vault?: %d // Expected: 1\n", isMember(VH,D,69));
    printf("Is 'Dragon Ball' (80) in the vault?: %d // Expected: 0\n", isMember(VH,D,80));
    
    return 0;
}

// --- Implementations ---
// TODO: Fill out insertDict
void insertDict(VirtualHeap *VH, Dictionary D, int elem){
    // ...
}
// TODO: Fill out deleteDict
void deleteDict(VirtualHeap *VH, Dictionary D, int elem){
    // ...
}
// TODO: Fill out isMember
int isMember(VirtualHeap VH, Dictionary D, int elem){
    // ...
}
