/*
Filipino Flavor Story: "Ang Sistema ng Palengke"

Sa gitna ng Divisoria, ang pinakasikat na palengke sa Maynila, si Aling Nena ay nangangarap 
na gawing digital ang kanyang tindahan ng prutas. Binigyan siya ng kanyang apo na si Carlo 
ng isang lumang laptop at sinabi: "Lola, kailangan mo ng Synonym Chaining Dictionary para 
ma-track mo ang inventory mo nang mas mabilis!"

Ang sistema ay may dalawang bahagi:
1. Prime Area - para sa mga pangunahing produkto (saba, mangga, dalandan, atbp.)
2. Synonym Area - para sa mga karagdagang produkto na may parehong hash value (collision handling)

Kailangan ni Carlo na i-implement ang tatlong pangunahing operations:
- INSERT: Magdagdag ng produkto (at ang dami nito)
- DELETE: Alisin ang produkto kapag ubos na
- SEARCH: Hanapin kung meron pang stock

Matulungan kaya ni Carlo si Aling Nena bago mag-closing time ng palengke?


*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 20
#define PRIME_SIZE (MAX/2)  // First half: prime area
#define DELETED -1
#define EMPTY -2

// --- PRODUCT NODE STRUCTURE ---
typedef struct {
    char productName[20];  // e.g., "Saba", "Mangga", "Dalandan"
    int quantity;          // stock count
    int link;
} ProductNode;

// --- PALENGKE DICTIONARY STRUCTURE ---
typedef struct {
    ProductNode inventory[MAX];
    int avail;  // points to the next available slot in synonym area
} PalenkeDict;

// --- Helper Functions (provided) ---
// Hash function based on product name
int hashProductName(const char *name) {
    int sum = 0, i = 0;
    while (name[i] != '\0') {
        sum += name[i];
        i++;
    }
    return (sum % PRIME_SIZE);
}

// Initialize the dictionary
void initPalengke(PalenkeDict *dict) {
    // Initialize prime area
    

    // then initialize synonym area
    
}

// Display the dictionary
void displayPalengke(PalenkeDict dict) {
    printf("\n=== ALING NENA'S INVENTORY ===\n");
    printf("\nPRIME AREA (Main Stall):\n");
    for (int i = 0; i < PRIME_SIZE; i++) {
        printf("[%d] ", i);
        if (dict.inventory[i].quantity == EMPTY) {
            printf("EMPTY | link: -1\n");
        } else if (dict.inventory[i].quantity == DELETED) {
            printf("DELETED | link: %d\n", dict.inventory[i].link);
        } else {
            printf("%s (x%d) | link: %d\n", 
                   dict.inventory[i].productName, 
                   dict.inventory[i].quantity, 
                   dict.inventory[i].link);
        }
    }
    
    printf("\nSYNONYM AREA (Extra Storage):\n");
    for (int i = MAX - 1; i > dict.avail; i--) {
        printf("[%d] %s (x%d) | link: %d | Original Hash: %d\n", 
               i, 
               dict.inventory[i].productName, 
               dict.inventory[i].quantity, 
               dict.inventory[i].link,
               hashProductName(dict.inventory[i].productName));
    }
    printf("\nAvail pointer: %d\n", dict.avail);
}

// --- TODO: Implement these functions ---

// Insert a product into the inventory
void insertProduct(PalenkeDict *dict, const char *name, int qty); // TODO

// Search for a product and return its quantity (-1 if not found)
int searchProduct(PalenkeDict dict, const char *name); // TODO

// Delete a product from the inventory
void deleteProduct(PalenkeDict *dict, const char *name); // TODO

// --- MAIN: Test Cases ---
int main() {
    PalenkeDict aling_nena;
    initPalengke(&aling_nena);
    
    printf("=== Test 1: Insert products into prime area ===\n");
    insertProduct(&aling_nena, "Saba", 50);      // Expected: hash to prime area
    insertProduct(&aling_nena, "Mangga", 30);    // Expected: hash to prime area
    insertProduct(&aling_nena, "Dalandan", 20);  // Expected: hash to prime area
    displayPalengke(aling_nena);
    
    printf("\n=== Test 2: Search for products ===\n");
    printf("Saba stock: %d (expected: 50)\n", searchProduct(aling_nena, "Saba"));           // Expected: 50
    printf("Mangga stock: %d (expected: 30)\n", searchProduct(aling_nena, "Mangga"));       // Expected: 30
    printf("Kamote stock: %d (expected: -1)\n", searchProduct(aling_nena, "Kamote"));       // Expected: -1 (not found)
    
    printf("\n=== Test 3: Insert colliding products (synonym area) ===\n");
    insertProduct(&aling_nena, "Ubas", 15);      // May collide, goes to synonym area
    insertProduct(&aling_nena, "Santol", 25);    // May collide, goes to synonym area
    displayPalengke(aling_nena);
    
    printf("\n=== Test 4: Search in synonym chain ===\n");
    printf("Ubas stock: %d (expected: 15)\n", searchProduct(aling_nena, "Ubas"));           // Expected: 15
    printf("Santol stock: %d (expected: 25)\n", searchProduct(aling_nena, "Santol"));       // Expected: 25
    
    printf("\n=== Test 5: Delete from prime area ===\n");
    deleteProduct(&aling_nena, "Saba");
    printf("Saba stock after delete: %d (expected: -1)\n", searchProduct(aling_nena, "Saba")); // Expected: -1
    displayPalengke(aling_nena);
    
    printf("\n=== Test 6: Delete from synonym chain ===\n");
    deleteProduct(&aling_nena, "Ubas");
    printf("Ubas stock after delete: %d (expected: -1)\n", searchProduct(aling_nena, "Ubas")); // Expected: -1
    displayPalengke(aling_nena);
    
    printf("\n=== Test 7: Insert duplicate ===\n");
    insertProduct(&aling_nena, "Mangga", 40);    // Expected: update quantity or reject
    printf("Mangga stock: %d (expected: 30 or 40 depending on implementation)\n", searchProduct(aling_nena, "Mangga"));
    
    printf("\n=== Test 8: Fill up the synonym area ===\n");
    insertProduct(&aling_nena, "Bayabas", 10);
    insertProduct(&aling_nena, "Atis", 12);
    insertProduct(&aling_nena, "Guyabano", 8);
    insertProduct(&aling_nena, "Rambutan", 18);
    insertProduct(&aling_nena, "Lanzones", 22);
    displayPalengke(aling_nena);
    
    printf("\n=== Test 9: Insert when synonym area is full ===\n");
    insertProduct(&aling_nena, "Suha", 5);       // Expected: should fail or not insert if full
    printf("Suha stock: %d (expected: -1 if overflow)\n", searchProduct(aling_nena, "Suha"));
    
    return 0;
}
