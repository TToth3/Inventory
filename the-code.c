/* Baseline code*/
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>

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
float totalSales;
float totalUnsold;

void printInventory(){
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

int searchName(char search[99]){
    int check = 0;
    Pointer = Head;
    while((check == 0) && (strcmp(search,Pointer->Name) != 0)){
        Pointer = Pointer->nextItem;
        if(Pointer->nextItem == NULL){
            check = 1;
        }
    }
    if(strcmp(search,Pointer->Name) == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int ReadFile(){

    //Variables used to store lines of data from the file
    int a;
    char b[99];
    float c;
    int d;
    Items* temp;

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
    file_ptr = fopen("Total_Sales.txt","r");
    fscanf(file_ptr,"%f", &totalSales);
    fclose(file_ptr);
}

void purchaseItem() {
    char Name[99];
    int quantity;
    int check;
    float itemCost;
    Pointer = Head;
    int buyLoop = 1;
    
    file_ptr = fopen("Total_Sales.txt", "w");
    
    if(Pointer == NULL) {
        printf("\nNo Items In Inventory\n");
        return;
    }

    else{
        buyLoop = 1;
        printf("\e[1;1H\e[2J");
        while((strcmp(Name,"Exit") != 0) && (strcmp(Name,"exit") != 0)){
            printInventory();
            printf("\nPlease enter the name of what would you like to purchase\nOr Enter 'Exit' to leave\n: ");
            scanf("%s", &Name);
            if((strcmp(Name,"Exit") != 0) || (strcmp(Name,"exit") != 0)){
                printf("\e[1;1H\e[2J");
            }
            else{
                check = searchName(Name);
                if(check == 1){
                    printf("\nHow many do you want to purchase: ");
                    scanf("%d", &quantity);
                    if (quantity > Pointer->Stock) {
                        printf("\nNot enough in stock\n");
                    }
                    else {
                        itemCost = Pointer->Cost * quantity;
                        totalSales += itemCost;
                        Pointer->Stock -= quantity;
                        fprintf(file_ptr, "%.2f", totalSales);
                    }
                }
                else{
                    printf("Item Not Found");
                }
            }
        }
    }
}   

// End of purchaseItem()


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
    int choice;
    int edit;
    char name[99];
    int stock;
    float price;
    int test;
    int loop = 1;
    int loop2 = 1;
    Items* temp = NULL;

    printf("\e[1;1H\e[2J");
    printInventory();

    printf("\nPlease enter the ID of the item you'd like to Edit: ");
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
            while(loop2 == 1){
                printf("\e[1;1H\e[2J");
                printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
                printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
                printf("\nWhat would you like to edit?\n\n1. Name\n2. Price\n3. Stock\n4. Exit\nChoice: ");
                scanf("%d", &edit);

                char* str = fgets(buffer, sizeof(buffer), stdin);

                if(strlen(str) != 1){
                    printf("\nYou did not enter a Valid ID, Please try again\n");
                }

                else if(edit == 1){
                    while(loop == 1){
                        printf("\nPlease enter the new name: ");
                        scanf("%s", name);
                        test = searchName(name);
                        if(test == 0){
                            strcpy(Pointer->Name, name);
                            loop = 0;
                        }
                        else{
                            printf("\nThere is already and item with that name\n");
                        }
                    }

                }
                else if(edit == 2){
                    while(loop == 1){
                        printf("\nPlease enter the new Price: ");
                        scanf("%f", &price);
                        char* str = fgets(buffer, sizeof(buffer), stdin);

                        if(strlen(str) != 1){
                            printf("\nYou did not enter a Valid ID, Please try again\n");
                        }
                        else{
                            Pointer->Cost = price;
                            loop = 0;
                        }
                    }
                }
                else if(edit == 3){
                    while(loop == 1){
                        printf("\nPlease enter the new Stock: ");
                        scanf("%d", &stock);
                        char* str = fgets(buffer, sizeof(buffer), stdin);

                        if(strlen(str) != 1){
                            printf("\nYou did not enter a Valid ID, Please try again\n");
                        }
                        else{
                            Pointer->Stock = stock;
                            loop = 0;
                        }
                    }
                    
                }
                else if(edit == 4){
                    loop2 = 0;
                }
                else{
                    printf("\nSomething went wrong\n");
                }
            }
        }
    }
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
            editItem();
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
    file_ptr = fopen("Total_Sales.txt", "a");
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
            //Saves the running data to the file so edits stick
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
            printf("Thanks for using the program!");
            sleep(2);
        }
        else{
            printf("Something has gone wrong, please try again.");
        }
    }

}
