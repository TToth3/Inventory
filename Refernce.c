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
    struct Inventory* nextItem;};
typedef struct Inventory Items;

//Global variables
char buffer[1024];

Items* Head = NULL;
Items* Pointer = NULL;
Items* newItem = NULL;
int count = 0;
FILE* file_ptr;



//Reads and creates list
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

//Adds Nodes to the list and file (just a slightly modified version of Module 11)
int addInvetory(){
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

int readInvetory(){
    
    printf("\e[1;1H\e[2J");
    Pointer = Head;
    if(Pointer != NULL){
        printf("\nRecords:\n");
        printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
        printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        while(Pointer->nextItem != NULL){
            Pointer = Pointer->nextItem;
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }
    }
    else{
        printf("\nNo Records Found\n");
    }

}

int searchInventory(){

    char search[99];
    int check = 0;
    printf("Please enter the name of the item you'd like to find (case sensitive)\n: ");
    scanf("%s", search);

    Pointer = Head;
    while((check == 0) && (strcmp(search,Pointer->Name) != 0)){
        Pointer = Pointer->nextItem;
        if(Pointer->nextItem == NULL){
            check = 1;
        }
    }

    if(strcmp(search,Pointer->Name) == 0){
        printf("\nID:\tCost:\tName:\tStock:\n----------------------------\n");
        printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
    }
    else{
        printf("\n%s was not found. Either its not it the list or the spelling didnt match.\nPlease Try Again.\n",search);
    }
}

int purchaseItem(){

    int choice;
    int check;

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

    printf("\nPlease enter the ID of the item you'd like to purchase: ");
    scanf("%d", &choice);

    Pointer = Head;
    while(Pointer->ID != choice){
        Pointer = Pointer->nextItem;
        if(Pointer->nextItem == NULL){
            check = 1;
        }
    }

    if(Pointer->ID == choice){
        printf("\nID:\tCost:\tName:\tStock:\n----------------------------\n");
        printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        printf("\nHow Mant would you like to buy: ");

    }
    else{
        printf("\nwas not found. Either its not it the list or the spelling didnt match.\nPlease Try Again.\n");
    }
}

int main(){
    file_ptr = fopen("Inventory.txt", "a");
    fclose(file_ptr);
    ReadFile();
    int choice;
    printf("\e[1;1H\e[2J");

    while(choice != 5){
        printf("\nWhat would you like to do?\n1. Add Item to Invetory\n2. View Inventory\n3. Find an Item in inventory\n4. Purchase an Item\n5. Exit\nChoice: ");
        scanf("%d", &choice);
        char* str = fgets(buffer, sizeof(buffer), stdin);

        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }
        else if(choice == 1){
            addInvetory();
        }
        else if(choice == 2){
            readInvetory();
        }
        else if(choice == 3){
            searchInventory();
        }
        else if(choice == 4){
            purchaseItem();
        }
        else if(choice == 5){
            printf("\nThanks for shopping!\n");
            sleep(2);
        }
        else{
            printf("An Error occured, Please try again");
        }
    }
}