#include <stdio.h>
#include <string.h>

#define max_Items 25

struct item {
    char name[50];
    float price;
    int quantity;
};

typedef struct item Item;

void add_Item(Item inventory[], int *count);
void rem_Item(Item inventory[], int *count);
void alt_Item(Item inventory[], int count);
void disp_Items(Item inventory[], int count);

int main() {
    int choice = 0;
    Item inventory[max_Items];  
    int count = 0;              

    while (1) { 
        printf("\nOptions:\n");
        printf("1. Add Item\t");
        printf("2. Remove Item\t");
        printf("3. Alter Item\t");
        printf("4. Quit\n");
        printf("Select Action: ");
        scanf("%d", &choice);

        if (choice == 1) {
            add_Item(inventory, &count);
        } else if (choice == 2) {
            rem_Item(inventory, &count);
        } else if (choice == 3) {
            alt_Item(inventory, count);
        } else if (choice == 4) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Wrong, wrong, wrong, wrong. Wrong, wrong, wrong, wrong. You're wrong. You're wrong. You're Wrong...\n");
        }
    }

    return 0;
}

void add_Item(Item inventory[], int *count) {
    if (*count >= max_Items) {
        printf("Err\n");
        return;
    }

    printf("Enter item name: ");
    scanf("%s", inventory[*count].name);
    printf("Enter item price: ");
    scanf("%f", &inventory[*count].price);
    printf("Enter item quantity: ");
    scanf("%d", &inventory[*count].quantity);

    (*count)++;
    printf("Item added succesfully.\n");
}

void rem_Item(Item inventory[], int *count) {
    char name[20];
    printf("Enter the name of the item to remove: ");
    scanf("%s", name);

    int i, found = 0;
    for (i = 0; i < *count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found.\n");
        return;
    }

    for (int j = i; j < *count - 1; j++) {
        inventory[j] = inventory[j + 1];
    }
    (*count)--;
    printf("Item removed successfully.\n");
}

void alt_Item(Item inventory[], int count) {
    char name[20];
    printf("Enter the name of the item to alter: ");
    scanf("%s", name);

    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (strcmp(inventory[i].name, name) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found.\n");
        return;
    }

    printf("Enter new price (current: %.2f): ", inventory[i].price);
    scanf("%f", &inventory[i].price);
    printf("Enter new quantity (current: %d): ", inventory[i].quantity);
    scanf("%d", &inventory[i].quantity);

    printf("Item updated successfully.\n");
}

void disp_Items(Item inventory[], int count) {
    printf("\nCurrent Inventory:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Price: $%.2f, Quantity: %d\n", inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}
