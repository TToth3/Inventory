#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>

//Node Structure
struct Inventory{
    int ID;
    char Name[20];
    float Cost;
    int Stock;
    
    struct Inventory* nextItem;
    struct Inventory* prevItem;
};

//Node definintion 
typedef struct Inventory Items;


//Global variables
char buffer[1024];
Items* Tail = NULL;
Items* Head = NULL;
Items* Pointer = NULL;
Items* newItem = NULL;
int count = 0;
FILE* file_ptr;
float totalSales = 0;

//Start of printInventory()
void printInventory(){

    //start of node looping
    Pointer = Head;

    //Verifies that an inventory exists
    if(Pointer != NULL){

        //print the inventory information
        printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
        printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);

        //Loop through nodes
        while(Pointer->nextItem != NULL){
            Pointer = Pointer->nextItem;
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }
    }
    //no inventory found
    else{
        printf("\e[1;1H\e[2J");
        printf("\nNo Inventory\n");
    }
}
//End of printInventory()

//Start of saveFile()
void saveFile(){

    //Opens inventory.txt in write mode.
    file_ptr = fopen("Inventory.txt", "w");
    //Starts searching the nodes from the end to the front
    //This is for organizational purposes
    Pointer = Tail;

    //resets the ID counts incase of removed items
    count = 1;

    //Checks if there is an inventory (or in this case if there isnt one)
    if(Pointer == NULL){
        return;
    }

    //If there is an inventory
    else{

        //Write last node to file
        fprintf(file_ptr, "%d %.2f %s %d\n", count, Pointer->Cost, Pointer->Name, Pointer->Stock);

        //While there are still nodes to check
        while(Pointer->prevItem != NULL){
            //increase ID counter
            count++;
            //move to next item
            Pointer = Pointer->prevItem;
            //write to file
            fprintf(file_ptr, "%d %.2f %s %d\n", count, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }
    }
    //Save
    fclose(file_ptr);
}
//End of saveFile()

//Start of searchName()
//Gets input of name to search
int searchName(char search[99]){
    //Variables
    int check = 0;

    //Node loop
    Pointer = Head;
    //Checks search against the node's name
    while((check == 0) && (strcmp(search,Pointer->Name) != 0)){
        Pointer = Pointer->nextItem;
        //Ensures strcmp never compares NULL
        if(Pointer->nextItem == NULL){
            check = 1;
        }
    }
    //If the name is found
    if(strcmp(search,Pointer->Name) == 0){
        return 1;
    }
    //If the name is not found
    else{
        return 0;
    }
}
//End of searchName()

//Start of readFile()
int readFile(){

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
    //While not at the end of file
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
    //Closes Inventory file
    fclose(file_ptr);

    //Opens Total Sales Files
    file_ptr = fopen("Total_Sales.txt","r");
    //gets total sales
    fscanf(file_ptr,"%f", &totalSales);
    //Closes total sales file
    fclose(file_ptr);
}
//End of readFile()

//Start of purchaseItem()
void purchaseItem() {

    //Variables
    char Name[99];
    int quantity;
    int check;
    float itemCost;
    Pointer = Head;

    //Opens Total_Sales.txt in write
    file_ptr = fopen("Total_Sales.txt", "w");
    
    //Checks if there is not an inventory
    if(Pointer == NULL) {
        printf("\e[1;1H\e[2J");
        printf("\nNo Items In Inventory\n");
    }

    //if there is an inventory
    else{
        //Clear screen
        printf("\e[1;1H\e[2J");

        //ensures you dont want to exit
        while((strcmp(Name,"Exit") != 0) && (strcmp(Name,"exit") != 0)){
            
            //runs printInventory()
            printInventory();

            //Gets input
            printf("\nPlease enter the name of what would you like to purchase\nOr Enter 'Exit' to leave\n: ");
            scanf("%s", Name);

            //Makes sure its not exit
            if((strcmp(Name,"Exit") == 0) || (strcmp(Name,"exit") == 0)){
                printf("\e[1;1H\e[2J");
            }

            else{

                //Searches for item
                check = searchName(Name);

                //If item is found
                if(check == 1){

                    //Gets input
                    printf("\nHow many do you want to purchase: ");
                    scanf("%d", &quantity);

                    //Validates input
                    char* str = fgets(buffer, sizeof(buffer), stdin);
                    if(strlen(str) != 1){
                        printf("\nYou did not enter a Valid Amount, Please try again\n");
                    }

                    //check to see if order is more than the stock
                    else if (quantity > Pointer->Stock) {
                        printf("\nNot enough in stock\n");
                    }

                    //if stock is enough
                    else {
                        //gets order cost
                        itemCost = Pointer->Cost * quantity;
                        //adds order cost to total sales
                        totalSales += itemCost;
                        //reduces stock by order amount
                        Pointer->Stock -= quantity;
                    }
                }

                //If item wasnt found
                else{
                    printf("\nItem Not Found\n");
                }
            }
        }
    }
    fprintf(file_ptr, "%.2f", totalSales);
    fclose(file_ptr);
    saveFile();
}   
// End of purchaseItem()

//Start of findItem()
void findItem(){

    //Variables
    char Name[99];
    int check;
    Pointer = Head;

    //ensures inventory exists
    if(Pointer == NULL) {
        printf("\e[1;1H\e[2J");
        printf("\nNo Items In Inventory\n");
    }

    //if it does
    else{

        //gets input
        printf("What is the name of the item you are looking for: ");
        scanf("%s", Name);

        //searches for item
        check = searchName(Name);

        //if item is found
        if(check == 1){
            //print item inventory info
            printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
            printf("%d\t$%.2f\t%s\t%d\n", Pointer->ID, Pointer->Cost, Pointer->Name, Pointer->Stock);
        }

        //if item isnt found
        else{
            printf("\e[1;1H\e[2J");
            printf("\nItem Not Found\n");
        }
    }
}
//End of findItem()

//start of printSales
void printSales(){

    //variables
    float totalUnsold;
    Pointer = Head;

    //Check if inventory exists
    if(Pointer != NULL){
        //while it does exist loop through items
        while(Pointer != NULL){
            //unsold inventory is equal to item stock times its cost
            totalUnsold += Pointer->Cost * Pointer->Stock;
            Pointer = Pointer->nextItem;
        }

        //Print total unsold and total sold values
        printf("Total value of sold Items: $%.2f\nTotal Value of unsold stock: $%.2f\n", totalSales, totalUnsold);
    }

    //If no inventory exists
    else{
        
        //clear screen and print no unsold stock
        printf("\e[1;1H\e[2J");
        printf("\nNo Unsold Stock\n");

        //checks if we have sales in the past
        if(totalSales == 0){
            printf("\nNo Sales\n");
        }
    }
}
//End of printSales

//Start of reportInventory()
void reportInvetory(){
    //Variables + clear screen
    int choice;
    printf("\e[1;1H\e[2J");

    //Menu Loop
    while(choice != 4){

        //Print Menu and get input
        printf("\n1. View Inventory\n2. Find Item\n3. Sales Report\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        //Input validation
        char* str = fgets(buffer, sizeof(buffer), stdin);
        if(strlen(str) != 1){
            printf("\nYou did not enter a Valid ID, Please try again\n");
        }

        //Checks input for menu selection
        else if(choice == 1){
            printInventory();
        }
        //Checks input for menu selection
        else if(choice == 2){
            findItem();
        }
        //Checks input for menu selection
        else if(choice == 3){
            printSales();
        }
        //Checks input for menu selection
        else if(choice == 4){
            printf("\e[1;1H\e[2J");
        }
        //Catchall for unexpected failures
        else{
            printf("\nThe choice you entered was not valid\n");
        }
    }
}
//End of reportInventory()

//Start of editItem()
void editItem(){

    //Variables
    int choice;
    int edit;
    char name[99];
    int stock;
    float price;
    int test;
    int loop = 1;
    int loop2 = 1;
    Items* temp = NULL;
    Pointer = Head;

    //screen clear and check for inventory
    printf("\e[1;1H\e[2J");
    if(Pointer == NULL){
        printf("\nNo items in inventory\n");
    }

    //if there is an inventory
    else{
        //print inventory
        printInventory();

        //get input
        printf("\nPlease enter the ID of the item you'd like to Edit: ");
        scanf("%d", &choice);

        //validate input
        char* str = fgets(buffer, sizeof(buffer), stdin);
        if(strlen(str) != 1){
            printf("\nYou did not enter a Valid ID, Please try again\n");
        }

        //if input is good
        else{

            //Searches inventory for item to edit
            Pointer = Head;
            while(Pointer->ID != choice && Pointer->nextItem != NULL){
                Pointer = Pointer->nextItem;
            }
            
            //If item is found
            if(Pointer->ID == choice){
                //sets a placeholder for the pointer
                temp = Pointer;

                //Edit loop
                while(loop2 == 1){
                    loop = 1;

                    //Prints Item info
                    printf("\e[1;1H\e[2J");
                    printf("ID:\tCost:\tName:\tStock:\n----------------------------\n");
                    printf("%d\t$%.2f\t%s\t%d\n", temp->ID, temp->Cost, temp->Name, temp->Stock);

                    //Menu + get input
                    printf("\nWhat would you like to edit?\n\n1. Name\n2. Price\n3. Stock\n4. Exit\nChoice: ");
                    scanf("%d", &edit);

                    //Input validation
                    char* str = fgets(buffer, sizeof(buffer), stdin);
                    if(strlen(str) != 1){
                        printf("\nYou did not enter a Valid ID, Please try again\n");
                    }
                    
                    //Checks menu choice
                    else if(edit == 1){

                        //second edit loop
                        while(loop == 1){

                            //gets input
                            printf("\nPlease enter the new name: ");
                            scanf("%s", name);

                            //checks if name is already in inventory
                            test = searchName(name);

                            //if not then change name
                            if(test == 0){
                                strcpy(temp->Name, name);
                                loop = 0;
                            }

                            //if it is
                            else{
                                printf("\nThere is already and item with that name\n");
                            }
                        }

                    }

                    //Checks menu choice
                    else if(edit == 2){

                        //second edit loop
                        while(loop == 1){

                            //gets input
                            printf("\nPlease enter the new Price: ");
                            scanf("%f", &price);

                            //Validates input
                            char* str = fgets(buffer, sizeof(buffer), stdin);
                            if(strlen(str) != 1){
                                printf("\nYou did not enter a Valid ID, Please try again\n");
                            }

                            //if input is good change price
                            else{
                                temp->Cost = price;
                                loop = 0;
                            }
                        }
                    }

                    //Checks menu choice
                    else if(edit == 3){
                        while(loop == 1){

                            //gets input
                            printf("\nPlease enter the new Stock: ");
                            scanf("%d", &stock);

                            //Validates input
                            char* str = fgets(buffer, sizeof(buffer), stdin);
                            if(strlen(str) != 1){
                                printf("\nYou did not enter a Valid ID, Please try again\n");
                            }

                            //if input is good change stock
                            else{
                                temp->Stock = stock;
                                loop = 0;
                            }
                        }
                        
                    }

                    //Checks menu choice
                    else if(edit == 4){
                        loop2 = 0;
                    }

                    //Catchall for unexpected input
                    else{
                        printf("\nSomething went wrong\n");
                    }
                }
            }
        } 
    }
    //saves file
    saveFile();
}
//End of editItem()

//Start of removeItem()
void removeItem(){

    //Variables
    int choice;
    Items* temp = NULL;

    //clears screen
    printf("\e[1;1H\e[2J");

    //checks if inventory exists
    Pointer = Head;
    if(Pointer == NULL){
        printf("\e[1;1H\e[2J");
        printf("\nNo items in inventory");
    }

    //If it does
    else{

        //print inventory and get input
        printInventory();
        printf("\nPlease enter the ID of the item you'd like to Remove: ");
        scanf("%d", &choice);

        //Validate input
        char* str = fgets(buffer, sizeof(buffer), stdin);
        if(strlen(str) != 1){
            printf("\nYou did not enter a Valid ID, Please try again\n");
        }

        //if input is good
        else{

            //loop through nodes and check for ID
            Pointer = Head;
            while(Pointer->ID != choice && Pointer->nextItem != NULL){
                Pointer = Pointer->nextItem;
            }
            
            //If ID was found
            if(Pointer->ID == choice){

                //Checks if item is at the beginning of the inventory
                if(Pointer->prevItem == NULL){

                    //assigns temp to the next item
                    temp = Pointer->nextItem;
                    //reassigns head's possiton
                    Head = temp;
                    //Tells the next item that the previous one doesnt exist
                    temp->prevItem = NULL;
                }

                //checks if the item is in the end of the inventory
                else if(Pointer->nextItem == NULL){

                    //sets temp to the previous item
                    temp = Pointer->prevItem;
                    //reassigns tails possition
                    Tail = temp;
                    //tells the previous item that there is no next item
                    temp->nextItem = NULL;
                }
                
                //if item is in the middle of the inventory
                else{
                //temp becoms the previous item and tell that previous item that its next item is now one further down the line
                temp = Pointer->prevItem;
                temp->nextItem = Pointer->nextItem;

                //goes to the next item and tells it that its previous item is now one further back in the line
                temp = Pointer->nextItem;
                temp->prevItem = Pointer->prevItem;
                }                
            }

            //if ID wasnt found
            else{
                printf("\nItem Not found\n");
            }
        }
        //clears screen
        printf("\e[1;1H\e[2J");
    }
    //saves file
    saveFile();
}
//End of removeItem()

//Start of addInventory()
void addInvetory(){
    
    //Variables
    int choice = 1;
    char loop[10];
    Items* temp;
    file_ptr = fopen("Inventory.txt", "a");
    
    //Loop
    while(choice != 0){
        printf("\e[1;1H\e[2J");

        //Add Node code from module 11 with some changes
        if(choice != 0){
            count++;
            newItem = malloc(sizeof(Items));
            if(count == 1){
                //Assigns tail
                Tail = newItem;
                Head = newItem;
                newItem->nextItem = NULL;
            }

            else{
                
                //from Mod 11
                newItem->nextItem = Head;

                //assigns previous item
                newItem->prevItem = NULL;
                temp = newItem->nextItem;
                temp->prevItem = newItem;
        
                //from Mod 11
                Head = newItem;
            }
            
            //Gets input
            printf("\nPlease Enter Item %d's Name, Cost and how many we have: ", count);
            scanf("%s%f%d", newItem->Name, &newItem->Cost, &newItem->Stock);
            
            //Adds ID values
            newItem->ID = count;

            //Input validation
            char* str = fgets(buffer, sizeof(buffer), stdin);
            if(strlen(str) != 1){
                printf("\nYou did not enter a valid balance and/or stock for %s, We will set the incorrect value(s) to 0\nPlease edit these values later\n", newItem->Name);
                
                //checks for failed values
                //Not perfect since both will fail if the Cost does, but it can catch errors on stock and leave cost unaffected.
                if(isdigit(newItem->Cost) == 0){
                    newItem->Cost = 0;
                }
                if(isdigit(newItem->Stock) == 0){
                    newItem->Stock = 0;
                }
                
            }

            //Adds new items to the file
            fprintf(file_ptr, "%d %.2f %s %d\n", count, newItem->Cost, newItem->Name, newItem->Stock);
        }

        //Loop check
        printf("\nWould you like to add another? y/n\nChoice: ");
        scanf("%s", loop);
        if((strcmp(loop,"y") == 0) || (strcmp(loop,"Y") == 0) || (strcmp(loop,"yes") == 0) || (strcmp(loop,"Yes") == 0)){
            choice = 1;
        }
        else{
            choice = 0;
            printf("\e[1;1H\e[2J");
        }
    }
    //Closes file
    fclose(file_ptr);
}
//End of AddInventory()

//Start of updateInventory()
void updateInventory(){

    //Variable + clear screen
    int choice = 0;
    printf("\e[1;1H\e[2J");

    //Menu Loop
    while(choice != 4){

        //Get input
        printf("What would you like to do?\n\n1. Add Item\n2. Remove Item\n3. Edit Item\n4. Back\nChoice: ");
        scanf("%d", &choice);

        //input validation
        char* str = fgets(buffer, sizeof(buffer), stdin);
        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }

        //Checks menu selection
        else if(choice == 1){
            addInvetory();
        }
        //Checks menu selection
        else if(choice == 2){
            removeItem();
        }
        //Checks menu selection
        else if(choice == 3){
            editItem();
        }
        //Checks menu selection
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
    
    //opens both files to ensure they exist
    file_ptr = fopen("Inventory.txt", "a");
    fclose(file_ptr);
    file_ptr = fopen("Total_Sales.txt", "a");
    fclose(file_ptr);
    
    //gets file info and enters it into the running node list
    readFile();

    //variables and clear screen
    int choice;
    printf("\e[1;1H\e[2J");

    //Menu loop
    while(choice != 4){

        //Gets input
        printf("\nWhat Would you like to do?\n\n1. Edit Inventory\n2. Make a Purchase\n3. View Records\n4. Exit\nChoice: ");
        scanf("%d",&choice);

        //validates input
        char* str = fgets(buffer, sizeof(buffer), stdin);
        if(strlen(str) != 1){
            printf("\nYou did not enter a valid choice, Please try again.\n");
        }

        //Checks menu selection
        else if(choice == 1){
            updateInventory();
        }
        //Checks menu selection
        else if(choice == 2){
            purchaseItem();
        }
        //Checks menu selection
        else if(choice == 3){
            reportInvetory();
        }
        //Checks menu selection
        else if(choice == 4){
            //Saves the running data to the file so edits stick
            saveFile();
            printf("Thanks for using the program!");
            sleep(2);
        }

        //catchall for unexpected input
        else{
            printf("Something has gone wrong, please try again.");
        }
    }

}

//End of program
