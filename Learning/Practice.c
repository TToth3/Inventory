
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
FILE* file_ptr
float totalSales

int ReadFile(){

    int a;
    char b[99];
    float c;
    int d;
    Items* temp;

    file_ptr = fopen("Inventory.txt", "r");
    fscanf(file_ptr, "%d %f %s %d", &a, &c, b, &d);

    while(!feof(file_ptr)){
        count++;
        
        newItem = malloc(sizeof(Items));
        if(count == 1){
            Tail = newItem;
            Head = newItem;
            newItem->nextItem = NULL;
        }
            
        else{

            newItem->nextItem = Head;
            newItem->prevItem = NULL;
            temp = newItem->nextItem;
            temp->prevItem = newItem;
            Head = newItem;
        }

        newItem->ID = a;
        newItem->Cost = c;
        strcpy(newItem->Name, b);
        newItem->Stock = d;

        fscanf(file_ptr, "%d %f %s %d", &a, &c, b, &d);
    }
    //Closes file
    fclose(file_ptr);
    file_ptr = fopen("Total_Sales.txt","r");
    fscanf(file_ptr,"%f", &totalSales);
    fclose(file_ptr);
}

void saveFile(){
    file_ptr = fopen("Inventory.txt", "w");
    Pointer = Tail;
    count = 1;
    fprintf(file_ptr, "%d %.2f %s %d\n", count, Pointer->Cost, Pointer->Name, Pointer->Stock);
    while(Pointer->prevItem != NULL){
        count++;
        Pointer = Pointer->prevItem;
        fprintf(file_ptr, "%d %.2f %s %d\n", count, Pointer->Cost, Pointer->Name, Pointer->Stock);
    }
    fclose(file_ptr);
}

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
            printf("\nTotal Sales: $%.2f\n", totalSales);
        }

        else{
            printf("\nNo Inventory\n");
        }
}


/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Use this file to practice refining your code in a semi-production state and work out the errors. Feel free to ask for advice.
Copy this onto your computer so that you can see the errors and run the code, some bugs dont show up visually.
If you need to add more inventory to continue testing, it will need to be done manually, as I have the update system disabled in here.
Everything else you would need to test and refine the code should already be in this file, if you think its missing something feel free to grab it.
There are roughly 10-13 Errors, 2-4 inefficiencies and 1 un-needed variable. All the other functions in this program can be used as tools to fix some of these
After that its refining the code to look or feel however you want.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/




void purchaseItem(double totalSales);
    int ID;
    int quantity;
    double itemCost;
    
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

/*
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Code Ends Here

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/





int main(){
    
    file_ptr = fopen("Inventory.txt", "a");
    fclose(file_ptr);
    file_ptr = fopen("Total_Sales.txt", "a");
    fclose(file_ptr);
    ReadFile();

    int choice;

    while(choice != 4){
        printf("\e[1;1H\e[2J");
        printf("\nWhat Would you like to do?\n\n1. Edit Inventory(disabled)\n2. Make a Purchase\n3. View Records\n4. Exit\nChoice: ");
        scanf("%d",&choice);

        char* str = fgets(buffer, sizeof(buffer), stdin);

        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }
        else if(choice == 1){
            printf("Disabled");
            //updateInventory();
        }
        else if(choice == 2){
            purchaseItem();
        }
        else if(choice == 3){
           printInventory();
        }
        else if(choice == 4){
            saveFile();
            printf("Thanks for using the program!");
            sleep(2);
        }
        else{
            printf("Something has gone wrong, please try again.");
        }
    }
    return 0;
}
