#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item {
    char name[20];
    float price;
    int quantity;
    struct item* next;
};

typedef struct item Item;

void add_Item(Item** head); //Essential to Part One //
void rem_Item(Item** head); // Essential to Part one //
void alt_Item(Item* head); //Essential to Part One //
void disp_Items(Item* head); // Weak Part Three //
void free_List(Item* head);

int main() {
    int choice = 0;
    Item* head = NULL;

    while (1) { 
        printf("\nOptions:\n");
        printf("1. Add Item\t");
        printf("2. Remove Item\t");
        printf("3. Alter Item\t");
        printf("4. Quit\n");
        printf("5.Save and Quit\n\n"); //Not implemented. Since Part specifies the Add, Remove and Alter portions I focused on that. Also can't output things to text documents yet... //
        printf("Select Action: ");
        scanf("%d", &choice);


    // Tried to use "case" but I was still messing it up so used an IF-Else instead
        if (choice == 1) {
            add_Item(&head);
        } else if (choice == 2) {
            rem_Item(&head);
        } else if (choice == 3) {
            alt_Item(head);
        } else if (choice == 4) {
            printf("Exiting...\n");
            break; // I want to add a way to save this output using option 6 before here. //
        } else {
                printf("Wrong, wrong, wrong, wrong. Wrong, wrong, wrong, wrong. You're wrong. You're wrong. You're Wrong...\n");
        // ^^^ Scrubs meme ^^^  Can be replaced with soemthing more appropriate///
        }

        if (choice != 4) {
            disp_Items(head);
        }
    }

    free_List(head);
    return 0;
}

void add_Item(Item** head) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter item name: ");
    scanf("%s", newItem->name);
    printf("Enter item price: ");
    scanf("%f", &newItem->price);
    printf("Enter item quantity: ");
    scanf("%d", &newItem->quantity);

    newItem->next = *head;
    *head = newItem;
    printf("Item added successfully.\n");
}

void rem_Item(Item** head) {
    char name[20];
    printf("Enter the name of the item to remove: ");
    scanf("%s", name);

    Item *current = *head, *previous = NULL;

    while (current != NULL && strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Item removed successfully.\n");
}

void alt_Item(Item* head) {
    char name[20];
    printf("Enter the name of the item to alter: ");
    scanf("%s", name);

    Item* current = head;

    while (current != NULL && strcmp(current->name, name) != 0) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Item not found.\n");
        return;
    }

    printf("Enter new price (current: %.2f): ", current->price);
    scanf("%f", &current->price);
    printf("Enter new quantity (current: %d): ", current->quantity);
    scanf("%d", &current->quantity);

    printf("Item updated successfully.\n");
}

void disp_Items(Item* head) {
    Item* current = head;

    printf("\nCurrent Inventory:\n");
    while (current != NULL) {
        printf("Name: %s, Price: $%.2f, Quantity: %d\n", current->name, current->price, current->quantity);
        current = current->next;
    }
}

void free_List(Item* head) {
    Item* current = head;
    Item* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
//Enter code here
