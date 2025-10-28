/*
"Ang Sistema ng Palengke"

Sa gitna ng Divisoria, ang pinakasikat na palengke sa Maynila, si Aling Nena ay nangangarap
na gawing digital ang kanyang tindahan ng prutas. Binigyan siya ng kanyang apo na si Carlo
ng isang lumang laptop at sinabi:
  "Lola, kailangan mo ng Synonym Chaining Dictionary para ma-track mo ang inventory mo nang mas mabilis!"

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
#define PRIME_SIZE (MAX / 2) // First half: prime area
#define EMPTY 0
#define USED 1
#define DELETED -1

// --- PRODUCT NODE STRUCTURE ---
typedef struct
{
    char productName[20]; // e.g., "Saba", "Mangga", "Dalandan"
    int quantity;         // stock count
    int link;             // hashValue of next synonym (-1 if none)
    int status;           // 0 = EMPTY, 1 = USED, -1 = DELETED
} ProductNode;

// --- PALENGKE DICTIONARY STRUCTURE ---
typedef struct
{
    ProductNode inventory[MAX];
    int avail; // points to next available slot in synonym area (starts at MAX - 1)
} PalengkeDict;

// --- HELPER FUNCTIONS ---
// Hash function based on product name
int hashProductName(const char *name)
{
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++)
        sum += name[i];
    return sum % PRIME_SIZE;
}

// Initialize the dictionary
void initPalengke(PalengkeDict *dict)
{

    for (int i = 0; i < PRIME_SIZE; i++)
    {
        dict->inventory[i].status = EMPTY;
        dict->inventory[i].quantity = 0;
    }

    // printf("%d\n\n", MAX);
    for (int i = MAX - 1; i >= PRIME_SIZE; i--)
    {
        dict->inventory[i].link = i - 1;
        dict->inventory[i].status = EMPTY;
        dict->inventory[i].quantity = 0;
    }

    dict->inventory[PRIME_SIZE].link = -1;
    dict->avail = MAX - 1;
    // printf("Avail: %d\n\n", dict->avail);
}

// --- CORE OPERATIONS ---
// Insert a product into the inventory
void insertProduct(PalengkeDict *dict, const char *name, int qty)
{
    int hashValue = hashProductName(name);
    // Case 1: Slot empty — insert directly
    if (dict->inventory[hashValue].status == EMPTY)
    {
        printf("Inserted home slot: %s at %d\n", name, hashValue);
        strcpy(dict->inventory[hashValue].productName, name);
        dict->inventory[hashValue].quantity = qty;
        dict->inventory[hashValue].status = USED;
        dict->inventory[hashValue].link = -1;
    }

    // Case 2: Same product — update quantity
    else if (strcmp(dict->inventory[hashValue].productName, name) == 0)
    {
        printf("Updated home slot: %s\n", name);
        dict->inventory[hashValue].quantity = qty;
    }

    // Case 3: Collision — traverse synonym chain
    else if (strcmp(dict->inventory[hashValue].productName, name) != 0)
    {
        int *trav;

        for (trav = &dict->inventory[hashValue].link; *trav != -1 && strcmp(dict->inventory[*trav].productName, name) != 0; trav = &dict->inventory[*trav].link)
        {
        }

        if (*trav != -1)
        {
            printf("Updated synonym slot: %s\n", name);
            dict->inventory[*trav].quantity = qty;
        }
        // Case 4: Need to insert in synonym area
        else
        {

            if (dict->avail != -1)
            {
                printf("Inserted in synonym slot: %s\n", name);
                int temp = dict->inventory[dict->avail].link;
                dict->inventory[dict->avail].link = dict->inventory[hashValue].link;
                dict->inventory[hashValue].link = dict->avail;

                strcpy(dict->inventory[dict->avail].productName, name);
                dict->inventory[dict->avail].quantity = qty;
                // Allocate from avail (decrement pointer)
                dict->avail = temp;
            }
        }
    }
}

// Search for a product and return its quantity (-1 if not found)
int searchProduct(PalengkeDict dict, const char *name)
{

    int hashValue = hashProductName(name);

    if (dict.inventory[hashValue].status != EMPTY)
    {
        if (strcmp(dict.inventory[hashValue].productName, name) == 0)
        {
            return dict.inventory[hashValue].quantity;
        }
        else
        {

            int trav;

            for (trav = dict.inventory[hashValue].link; trav != -1; trav = dict.inventory[trav].link)
            {

                if (strcmp(dict.inventory[trav].productName, name) == 0)
                {
                    return dict.inventory[trav].quantity;
                }
            }
        }

        return -1;
    }
}

// Delete a product from the inventory
void deleteProduct(PalengkeDict *dict, const char *name)
{
}

// --- DISPLAY FUNCTION ---
void displayPalengke(PalengkeDict dict)
{
    printf("\n=== ALING NENA'S INVENTORY ===\n");

    printf("\nPRIME AREA (Main Stall):\n");
    for (int i = 0; i < PRIME_SIZE; i++)
    {
        printf("[%2d] ", i);
        if (dict.inventory[i].status == EMPTY)
        {
            printf("EMPTY | link: -1\n");
        }
        else if (dict.inventory[i].status == DELETED)
        {
            printf("DELETED | link: %d\n", dict.inventory[i].link);
        }
        else
        {
            printf("%-10s (x%d) | link: %d\n",
                   dict.inventory[i].productName,
                   dict.inventory[i].quantity,
                   dict.inventory[i].link);
        }
    }

    printf("\nSYNONYM AREA (Extra Storage):\n");
    for (int i = MAX - 1; i > dict.avail; i--)
    {
        printf("[%2d] %-10s (x%d) | link: %d | Original Hash: %d\n",
               i,
               dict.inventory[i].productName,
               dict.inventory[i].quantity,
               dict.inventory[i].link,
               hashProductName(dict.inventory[i].productName));
    }
    printf("\nAvail pointer: %d\n", dict.avail);
}

// --- MAIN: Test Cases ---
int main()
{

    // printf("yo");
    PalengkeDict aling_nena;
    initPalengke(&aling_nena);

    printf("=== Test 1: Insert products into prime area ===\n");
    insertProduct(&aling_nena, "Saba", 50);
    insertProduct(&aling_nena, "Mangga", 30);
    insertProduct(&aling_nena, "Dalandan", 20);
    displayPalengke(aling_nena);

    printf("\n=== Test 2: Search for products ===\n");
    printf("Saba stock: %d (expected: 50)\n", searchProduct(aling_nena, "Saba"));
    printf("Mangga stock: %d (expected: 30)\n", searchProduct(aling_nena, "Mangga"));
    printf("Kamote stock: %d (expected: -1)\n", searchProduct(aling_nena, "Kamote"));

    printf("\n=== Test 3: Insert colliding products (synonym area) ===\n");
    insertProduct(&aling_nena, "Ubas", 15);
    insertProduct(&aling_nena, "Santol", 25);
    displayPalengke(aling_nena);

    printf("\n=== Test 4: Search in synonym chain ===\n");
    printf("Ubas stock: %d (expected: 15)\n", searchProduct(aling_nena, "Ubas"));
    printf("Santol stock: %d (expected: 25)\n", searchProduct(aling_nena, "Santol"));

    // printf("\n=== Test 5: Delete from prime area ===\n");
    // deleteProduct(&aling_nena, "Saba");
    // printf("Saba stock after delete: %d (expected: -1)\n", searchProduct(aling_nena, "Saba"));
    // displayPalengke(aling_nena);

    // printf("\n=== Test 6: Delete from synonym chain ===\n");
    // deleteProduct(&aling_nena, "Ubas");
    // printf("Ubas stock after delete: %d (expected: -1)\n", searchProduct(aling_nena, "Ubas"));
    // displayPalengke(aling_nena);

    // printf("\n=== Test 7: Insert duplicate ===\n");
    // insertProduct(&aling_nena, "Mangga", 40);
    // printf("Mangga stock: %d (expected: 40)\n", searchProduct(aling_nena, "Mangga"));

    // printf("\n=== Test 8: Fill up the synonym area ===\n");
    // insertProduct(&aling_nena, "Bayabas", 10);
    // insertProduct(&aling_nena, "Atis", 12);
    // insertProduct(&aling_nena, "Guyabano", 8);
    // insertProduct(&aling_nena, "Rambutan", 18);
    // insertProduct(&aling_nena, "Lanzones", 22);
    // displayPalengke(aling_nena);

    // printf("\n=== Test 9: Insert when synonym area is full ===\n");
    // insertProduct(&aling_nena, "Suha", 5);
    // printf("Suha stock: %d (expected: -1 if overflow)\n", searchProduct(aling_nena, "Suha"));

    return 0;
}
