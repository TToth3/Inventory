/* Baseline code*/
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>

#define FILE_NAME "Inventory.txt"
#define TOTAL_SALES "Total_Sales.txt"

struct Inventory{
    int ID;
    char Name[20];
    float Cost;
    int Stock;
    struct Inventory* nextItem;
    struct Inventory* prevItem;};
typedef struct Inventory Items;

//Global variables
char buffer[1024];
Items* Tail = NULL;
Items* Head = NULL;
Items* Pointer = NULL;
Items* newItem = NULL;
int count = 0;
FILE* file_ptr;

void printInventory(){
    printf("\e[1;1H\e[2J");
        Pointer = Head;
        if(Pointer != NULL){
            printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
            while(Pointer->nextItem != NULL){
                Pointer = Pointer->nextItem;
                printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
            }
        }

        else{
            printf("\nNo Inventory\n");
        }
}


int ReadFile(){

    //Variables used to store lines of data from the file
    int a;
    char b[99];
    float c;
    int d;

    //Opens the file in read mode
    file_ptr = fopen("Inventory.txt", "r");
    //Scans the file and preps variables 

    
    fscanf(file_ptr, "%d %f %s %d", &a, &c, b, &d);

    while(!feof(file_ptr)){
        //Counting how many nodes have been added to properly track ID numbers
        count++;
        //Creates initial and new nodes
        newItem = malloc(sizeof(Items));
        if(count == 1){
            Head = newItem;
            newItem->nextItem = NULL;
        }
        else{

            newItem->nextItem = Head;
            newItem->prevItem = NULL;
            Tail = newItem->nextItem;
            Tail->prevItem = newItem;
            Head = newItem;
        }

        //Sets the node vaiables to equal their file counterparts
        newItem->ID = a;
        newItem->Cost = c;
        //Had to get creative to get a string to copy
        strcpy(newItem->Name, b);
        newItem->Stock = d;
        //Gets next set of file Data
        fscanf(file_ptr, "%d %f %s %d", &a, &c, b, &d);
    }
    //Closes file
    fclose(file_ptr);
}

/*///////////////////
Adrian's Functions
//////////////////*/



typedef struct Item {
    char name[100];
    int quantity;
    float unit_Price;
    struct Item *next;
} Items;

#define FILE_NAME "Inventory.txt"


int main() {
    Items *head = NULL;
    int choice;

    load_FromFile(&head);

    do {
        printf("Main Menu\n");
        printf("1. Add an item\n");
        printf("2. View current inventory\n");
        printf("3. Find an item\n");
        printf("4. Purchase an item\n");
        printf("5. Alter an item\n");
        printf("6. Remove an item\n");
        printf("7. Quit...\n"); 
        printf("Pick an option: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) { // Add an item
            add_Item(&head);
        } else if (choice == 2) { // View Inventory
            view_Inventory(head);
        } else if (choice == 3) { // Find an item
            char name[100];
            printf("Enter item: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            Items *item = find_Item(head, name);
            if (item) {
                printf("Item found: %s, Quantity: %d, Price: %.2f\n", item->name, item->quantity, item->unit_Price);
            } else {
                printf("Item not found.\n");
            }
        } else if (choice == 4) { // Purchase an item
            purchase_Item(head);
        } else if (choice == 5) { // Alter an item
            alter_Item(head);
        } else if (choice == 6) { // Remove an item
            remove_Item(&head);
        } else if (choice == 7) { // Quit
            save_ToFile(head);
            free_List(head);
            printf("Exiting...\n");
        } else {
            printf("Choose a number between 1 and 7.\n");
        }

        printf("Press any key to continue...");
        getch();
    } while (choice != 7);

    return 0;
}
*/
void add_Item(Items **head) {
    Items *newItem = (Items *)malloc(sizeof(Items));
    if (!newItem) {
        printf("Full\n");
        return;
    }

    getchar();

    printf("Enter item name: ");
    fgets(newItem->name, sizeof(newItem->name), stdin);
    newItem->name[strcspn(newItem->name, "\n")] = '\0';

    printf("Enter quantity: ");
    scanf("%d", &newItem->quantity);
    getchar(); 

    printf("Enter item price: ");
    scanf("%f", &newItem->unit_Price);
    getchar(); 

    newItem->next = *head;
    *head = newItem;
    save_ToFile(*head);
}

void view_Inventory(Items *head) {
    Items *current = head;
    float totalValue = 0.0; 

    if (!current) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("Inventory:\n");
    while (current) {
        printf("Item: %s, Quantity: %d, Price: %.2f\n", current->name, current->quantity, current->unit_Price);
        totalValue += current->quantity * current->unit_Price;
        current = current->next;
    }
    printf("Total Value: %.2f\n", totalValue); // Total amount of sales not implemented
}

Items* find_Item(Items *head, const char *name) {
    Items *current = head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void purchase_Item(Items *head) {
    char name[100];
    int quantity;
    printf("Enter item name to purchase: "); 
// I think this above could be done better. Maybe make it case insensitive? 
// Maybe a separate value that each item is assigned when added. Accidentally duplicating items in the inventory list isn't optimal for
// any of the establish functions.
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    Items *item = find_Item(head, name);
    if (item) {
        printf("Enter quantity to purchase: ");
        scanf("%d", &quantity);
        getchar(); 

        if (quantity <= item->quantity) {
            item->quantity -= quantity;
            printf("Purchased %d of %s. Remaining quantity: %d\n", quantity, item->name, item->quantity);
            save_ToFile(head);
        } else {
            printf("Not enough in stock.\n");
        }
    } else {
        printf("Item not found.\n");
    }
}

void alter_Item(Items *head) {
    char name[100];
    Items *item;
    
    printf("Enter the name of the item to alter: "); //Need to also be able to alter the name of the item.
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    item = find_Item(head, name);
    if (item) {
        int newQuantity;
        float newPrice;
        
        printf("Item found: %s, Quantity: %d, Price: %.2f\n", item->name, item->quantity, item->unit_Price);
        
        printf("Enter new quantity (or -1 to keep current): ");
        scanf("%d", &newQuantity);
        getchar(); 
        
        if (newQuantity != -1) {
            item->quantity = newQuantity;
        }

        printf("Enter new price (or -1 to keep current): "); 
        //Originally was set at 0. But -1 was a better choice. Since 0 can be a valid stock quantity
        //while negative numbers shouldn't be.
        scanf("%f", &newPrice);
        getchar(); 

        if (newPrice != -1.0) {
            item->unit_Price = newPrice;
        }
        
        printf("Item updated: %s, Quantity: %d, Price: %.2f\n", item->name, item->quantity, item->unit_Price);
        save_ToFile(head);
    } else {
        printf("Item not found.\n");
    }
}

void remove_Item(Items **head) {
    char name[100];
    printf("Enter the name of the item to remove: "); // Same issue as with Alter Items. Inadvertant Item duplication from user input.
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    Items *current = *head;
    Items *previous = NULL;

    while (current && strcmp(current->name, name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current) {
        if (previous) {
            previous->next = current->next;
        } else {
            *head = current->next;
        }
        free(current);
        printf("Item %s removed successfully.\n", name);
        save_ToFile(*head);
    } else {
        printf("Item not found.\n");
    }
}

void save_ToFile(Items *head) {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    Items *current = head;
    while (current) {
        fprintf(file, "%s\n%d\n%.2f\n", current->name, current->quantity, current->unit_Price);
        current = current->next;
    }

    fclose(file);
}

void load_FromFile(Items **head) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("File not found. Opening a new one.\n");
        return;
    }

    Items *current = NULL;
    while (!feof(file)) {
        Items *newItem = (Items *)malloc(sizeof(Items));
        if (!newItem) {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }

        if (fgets(newItem->name, sizeof(newItem->name), file)) {
            newItem->name[strcspn(newItem->name, "\n")] = '\0';
            if (fscanf(file, "%d %f ", &newItem->quantity, &newItem->unit_Price) == 2) {
                newItem->next = *head;
                *head = newItem;
            } else {
                free(newItem);
                break;
            }
        } else {
            free(newItem);
            break;
        }
    }

    fclose(file);
}






/* Tyler's Functions*/


void purchaseItem();
void totalCosts(double totalSales);
    int ID;
    int quantity;
    double itemCost;
    double totalSales = 0;
    Items *Pointer = Head;
    
    file_ptr = fopen("Total_Sales.txt")
    
    if(Pointer == NULL) {
        printf("Out of Stock");
    else 
        printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
        printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
    }

    while(Pointer != NULL) {
        Pointer = Pointer->nextItem;
        printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        Pointer = Pointer->nextItem;
    }

        printf("What would you like to purchase: ");
        scanf("%d", &ID);
        
        Pointer = Head;
        while(Pointer != NULL && Pointer->ID != ID) {
            Pointer = Pointer->nextItem;
        }
        if (Pointer == NULL) {
            printf("Item does not exist");

        else
            printf("How many do you want to purchase: ");
            scanf("%d", quantity);
        }
        if (quantity > Pointer->Stock) {
            printf("Not enough in stock");
            else {
                itemCost = Pointer->Cost * quantity
                totalSales += itemCost;
                Pointer->Stock -= quantity
                
        fprintf(file_ptr, "%d %.2f %s %d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }

}
// End of Purchase
// Needs testing

void readInvetory(){

    /* Feel free to comment out this code and work on it */


    printf("\e[1;1H\e[2J");
    Pointer = Head;
    int choice = 1;
    printf("\nRecords:\n");
    printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
    printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
    while(choice != 0){
        
        printf("\nWhat would you like to do?\n1. View next record\n2. View previous Record\n0. Quit\nChoice: ");
        scanf("%d", &choice);
        char* str = fgets(buffer, sizeof(buffer), stdin);

        //Input validation
        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }

        //Scrolls Pointer up list
        else if(choice == 1){
            printf("\e[1;1H\e[2J");
            Pointer = Pointer->nextItem;
            printf("\nRecords:\n");
            printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }

        //Scrolls pointer down list
        else if(choice == 2){
            printf("\e[1;1H\e[2J");
            Pointer = Pointer->prevItem;
            printf("\nRecords:\n");
            printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);

        }

        //Clears screen
        else if(choice == 0){
            printf("\e[1;1H\e[2J");
        }

        else{
            printf("\nNo Records Found\n");
        }

    }
    

}

void editItem(){
    
}
//End of editItem()

// Function complete (until bug testing)
void removeItem(){
    int choice;
    int check = 1;
    Items* temp = NULL;

    printf("\e[1;1H\e[2J");
    printInventory();

    printf("\nPlease enter the ID of the item you'd like to Remove: ");
    scanf("%d", &choice);

    char* str = fgets(buffer, sizeof(buffer), stdin);

    if(strlen(str) != 1){
        printf("\nYou did not enter a Valid ID, Please try again\n");
    }

    else{
        Pointer = Head;
        while(Pointer->ID != choice && Pointer->nextItem != NULL){
            Pointer = Pointer->nextItem;
        }
        
        if(Pointer->ID == choice){
            if(Pointer->prevItem == NULL){
                temp = Pointer->nextItem;
                Head = temp;
                temp->prevItem = NULL;
            }
            else if(Pointer->nextItem == NULL){
                temp = Pointer->prevItem;
                temp->nextItem = NULL;
            }
            
            else{
            temp = Pointer->prevItem;
            temp->nextItem = Pointer->nextItem;
            temp = Pointer->nextItem;
            temp->prevItem = Pointer->prevItem;
            }
        }
        else{
            printf("\nItem Not found\n");
        }
    }
}
//End of removeItem()

// Function complete (until bug testing)
// May add item duplicate check 
void addInvetory(){
    printf("\e[1;1H\e[2J");
    int choice = 1;
    file_ptr = fopen("Inventory.txt", "a");
    
    while(choice != 0){
        printf("\nEnter '0' to stop adding Items\nOr enter any other number to continue: ");
        scanf("%d", &choice);
        char* str = fgets(buffer, sizeof(buffer), stdin);
        
        if(strlen(str) != 1){
            choice = 1;
        }

        if(choice != 0){
            count++;
            newItem = malloc(sizeof(Items));
            if(count == 1){
                Head = newItem;
                newItem->nextItem = NULL;
            }

            else{
            newItem->nextItem = Head;
            newItem->prevItem = NULL;
            Tail = newItem->nextItem;
            Tail->prevItem = newItem;
            Head = newItem;
            }
            
            printf("\nPlease Enter Item %d's Name, Cost and how many we have: ", count);
            scanf("%s%f%d", newItem->Name, &newItem->Cost, &newItem->Stock);
            
            //Adds ID values
            newItem->ID = count;

            char* str = fgets(buffer, sizeof(buffer), stdin);

            //Adds new items to the file
            fprintf(file_ptr, "%d %.2f %s %d\n", count, newItem->Cost, newItem->Name, newItem->Stock);
            
            //Input validation
            if(strlen(str) != 1){
                printf("\nYou did not enter a valid balance and/or stock for %s, We will set the incorrect value(s) to 0\nPlease edit these values later\n", newItem->Name);
                //Not perfect since both will fail if the Cost does, but it can catch errors on stock and leave cost unaffected.
                if(isdigit(newItem->Cost) == 0){
                    newItem->Cost = 0;
                }
                if(isdigit(newItem->Stock) == 0){
                    newItem->Stock = 0;
                }
                
            }
        }
    }
    fclose(file_ptr);
}
//End of AddInventory()


void updateInventory(){

    int choice = 0;
    printf("\e[1;1H\e[2J");
    while(choice != 4){
        printf("What would you like to do?\n\n1. Add Item\n2. Remove Item\n3. Edit Item\n4. Back\nChoice: ");
        scanf("%d", &choice);
        char* str = fgets(buffer, sizeof(buffer), stdin);
        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }
        else if(choice == 1){
            addInvetory();
        }
        else if(choice == 2){
            removeItem();
        }
        else if(choice == 3){
            //WIP
        }
        else if(choice == 4){
            printf("\e[1;1H\e[2J");
        }
    }
}
//End of updateInventory()


/*///////////////// 
    MAIN BODY 
/////////////////*/

int main(){
    
    file_ptr = fopen("Inventory.txt", "a");
    fclose(file_ptr);
    ReadFile();

    int choice;

    while(choice != 4){
        printf("\e[1;1H\e[2J");
        printf("\nWhat Would you like to do?\n\n1. Edit Inventory\n2. Make a Purchase\n3. View Records\n4. Exit\nChoice: ");
        scanf("%d",&choice);

        char* str = fgets(buffer, sizeof(buffer), stdin);

        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }
        else if(choice == 1){
            updateInventory();
        }
        else if(choice == 2){
            purchaseItem();
            
        }
        else if(choice == 3){
            readInvetory();

            /*Still needs proper record printing*/
        }
        else if(choice == 4){
            printf("Thanks for using the program!");
            sleep(2);
        }
        else{
            printf("Something has gone wrong, please try again.");
        }
    }

}