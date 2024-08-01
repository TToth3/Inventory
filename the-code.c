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
    struct Inventory* nextItem;};
typedef struct Inventory Items;

//Global variables
char buffer[1024];

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

int updateInventory(){

}






int main{
    


}





