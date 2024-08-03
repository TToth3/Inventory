//Code goes here
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

/* Tyler's Code*/

int readInvetory(){
    
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

        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }
        else if(choice == 1){
            printf("\e[1;1H\e[2J");
            Pointer = Pointer->nextItem;
            printf("\nRecords:\n");
            printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }
        else if(choice == 2){
            printf("\e[1;1H\e[2J");
            Pointer = Pointer->prevItem;
            printf("\nRecords:\n");
            printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);

        }
        else if(choice == 0){
            printf("\e[1;1H\e[2J");
        }

        else{
            printf("\nNo Records Found\n");
        }

    }
    

}


int updateInventory(){
    printf("\e[1;1H\e[2J");
    printf("");

}

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
            //WIP
        }
        else if(choice == 3){
            readInvetory();
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





