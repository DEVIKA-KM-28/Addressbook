#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include <string.h>

void saveContactsToFile(AddressBook *addressBook)
{
 
    FILE *fptr=fopen("contacts.csv","w");  // Open the file in write mode

    if(fptr==NULL)
    {
        printf("file not opened");     // Print error if file could not be opened
    }

    fprintf(fptr,"%d\n",addressBook->contactCount);     

    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Write each contact's name, phone, and email in CSV format

    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(fptr);    // Close the file after writing
    printf("Contacts saved successfully\n");
    exit(0);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("contacts.csv","r");     // Open the file in read mode

    if(fptr==NULL)
    {
        printf("file opening failed for reading\n");
        //addressBook->contactCount=0;
        return;
    }

    //read contacts from first line

    fscanf(fptr,"%d\n",&addressBook->contactCount);
    //fseek(fptr,1,SEEK_CUR);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        // Read each contact's name, phone, and email from CSV format

        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);    // Close the file after reading

    printf("contacts loaded successfully");


}
