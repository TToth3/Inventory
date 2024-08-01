#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Inventory {
    int ID;
    char Name[50];
    float Cost;
    int Stock;
    struct Inventory* nextItem;
};

typedef struct Inventory Items;

Items* Head = NULL;
Items* Pointer = NULL;
Items* newItem = NULL;
int count = 0;
FILE* file_ptr;

int ReadFile() {
    int a;
    float c;
    int d;
    char b[50];

    file_ptr = fopen("Inventory.txt.rtf", "r");
    if (file_ptr == NULL) {
    }

    while (fscanf(file_ptr, "%d %f %s %d", &a, &c, b, &d) == 4) {
        count++;
        newItem = (Items*)malloc(sizeof(Items));
        if (newItem == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file_ptr);
            return -1;
        }
        newItem->ID = a;
        newItem->Cost = c;
        strcpy(newItem->Name, b);
        newItem->Stock = d;
        newItem->nextItem = NULL;

        if (Head == NULL) {
            Head = newItem;
        } else {
            Pointer = Head;
            while (Pointer->nextItem != NULL) {
                Pointer = Pointer->nextItem;
            }
            Pointer->nextItem = newItem;
        }
    }

    fclose(file_ptr);
    return 0;
}

void add_Item() {
    newItem = (Items*)malloc(sizeof(Items));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter item ID: ");
    scanf("%d", &newItem->ID);
    printf("Enter item name: ");
    scanf("%s", newItem->Name);
    printf("Enter item cost: ");
    scanf("%f", &newItem->Cost);
    printf("Enter item stock: ");
    scanf("%d", &newItem->Stock);
    newItem->nextItem = NULL;

    if (Head == NULL) {
        Head = newItem;
    } else {
        Pointer = Head;
        while (Pointer->nextItem != NULL) {
            Pointer = Pointer->nextItem;
        }
        Pointer->nextItem = newItem;
    }
    count++;
    printf("Item added successfully.\n");
}

void rem_Item() {
    int id;
    printf("Enter the item to remove: ");
    scanf("%d", &id);

    Items *prev = NULL, *current = Head;
    while (current != NULL && current->ID != id) {
        prev = current;
        current = current->nextItem;
    }

    if (current == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (prev == NULL) {
        Head = current->nextItem;
    } else {
        prev->nextItem = current->nextItem;
    }
    free(current);
    count--;
    printf("Item removed successfully.\n");
}

void alt_Item() {
    int id;
    printf("Enter the item to alter: ");
    scanf("%d", &id);

    Items *current = Head;
    while (current != NULL && current->ID != id) {
        current = current->nextItem;
    }

    if (current == NULL) {
        printf("Item not found.\n");
        return;
    }

    printf("Enter new cost (current: %.2f): ", current->Cost);
    scanf("%f", &current->Cost);
    printf("Enter new stock (current: %d): ", current->Stock);
    scanf("%d", &current->Stock);

    printf("Item updated successfully.\n");
}

void disp_Items() {
    if (Head == NULL) {
        printf("No items in inventory.\n");
        return;
    }

    printf("\nCurrent Inventory:\n");
    Items *current = Head;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Cost: $%.2f, Stock: %d\n",
               current->ID, current->Name, current->Cost, current->Stock);
        current = current->nextItem;
    }
}

int main() {
    int choice = 0;
    if (ReadFile() == -1) {
        return -1;
    }

    while (1) {
        printf("\nOptions:\n");
        printf("1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Alter Item\n");
        printf("4. Display Items\n");
        printf("5. Quit\n");
        printf("Select Action: ");
        scanf("%d", &choice);

        if (choice == 1) {
            add_Item();
        } else if (choice == 2) {
            rem_Item();
        } else if (choice == 3) {
            alt_Item();
        } else if (choice == 4) {
            disp_Items();
        } else if (choice == 5) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid option. Please select a valid action.\n");
        }
    }

    // Free allocated memory
    Items* temp;
    while (Head != NULL) {
        temp = Head;
        Head = Head->nextItem;
        free(temp);
    }

    return 0;
}
