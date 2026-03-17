#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("1.sort by name\n2.sort by phone\n3.sort by email\n");

    printf("Enter your choice:\n");

    int choice;
    scanf("%d",&choice);
    
    switch(choice)
    {
        case 1:

        for(int i=0;i<(addressBook->contactCount-1);i++)
        {
            for(int j=0;j<(addressBook->contactCount-i-1);j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)   //if first contact name comes after second,swap them
                {
                    Contact temp=addressBook->contacts[j];  
                    addressBook->contacts[j]=addressBook->contacts[j+1];                  
                    addressBook->contacts[j+1]=temp;
                }
                
            }
        }
        break;

        case 2:
        for(int i=0;i<(addressBook->contactCount-1);i++)
        {
            for(int j=0;j<(addressBook->contactCount-i-1);j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0) // If the first number is greater than the second,swap them
                {
                      Contact temp=addressBook->contacts[j];
                      addressBook->contacts[j]=addressBook->contacts[j+1];
                      addressBook->contacts[j+1]=temp;
                }
                
            }
        }
        break;

        case 3:
        for(int i=0;i<(addressBook->contactCount-1);i++)
        {
            for(int j=0;j<(addressBook->contactCount-i-1);j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)  // If first string comes after second alphabetically,swap them
                {
                      Contact temp=addressBook->contacts[j];
                      addressBook->contacts[j]=addressBook->contacts[j+1];
                      addressBook->contacts[j+1]=temp;
                }
                
            }
        }
        break;

        default:
        printf("Invalid choice\n");
        return;
        
    }
    printf("\n%s%23s%15s%30s\n","Index","Name","Phone","Email"); 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%d%28s%15s%30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
 {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    printf("Enter the details to create a contact:\n");

    printf("Enter the Name:\n");

    char str_name[50];
    getchar();       //to clear leftover line in buffer
    scanf("%[^\n]",str_name);

    if(validatename(str_name))
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name,str_name);  //copying new name to addressBook
    }
    else
    {
        printf("Enter only alphabets");
        return;
    }
    
    printf("Enter the phone number:\n");
    char str_phone[11];
    scanf("%s",str_phone);
   
    if(validatephone(str_phone,addressBook))
    {
        strcpy(addressBook->contacts[addressBook->contactCount].phone,str_phone);   //copying new phone number to addressBook
    }
    else
    {
        printf("Enter only 10 digits");
        return;
    }

    printf("Enter the email:\n");
    char str_email[50]; 
    scanf("%s",str_email);
   
    if(validateemail(str_email, addressBook))
    {
        strcpy(addressBook->contacts[addressBook->contactCount].email,str_email);    //copying new gmail to addressBook
        printf("Contact created successfully");
    }
    else
    {
        printf("Error! Enter valid email id");
        return;
    }

    addressBook->contactCount++;     //extra one contact added so increase contactCount
    
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    printf("1.Search by name\n2.Search by phone\n3.Search by email\n");
    printf("Enter your choice\n");
     
    int choice;
    scanf("%d",&choice);
    int found=0;
  
    switch(choice)
    {

    case 1:
    
      printf("Enter the name:\n");
      char name[50];
      getchar();
      scanf(" %[^\n]",name);
      found=0;

        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcasecmp(addressBook->contacts[i].name,name) == 0)   // Compare names case-insensitively
            {
                //Contact found, display details

                printf("Found at index %d.\n",i+1);
                printf("Name:%s\n",addressBook->contacts[i].name);
                printf("Phone:%s\n",addressBook->contacts[i].phone);
                printf("email:%s\n",addressBook->contacts[i].email);
                found = 1;
                return i+1; //to return index value (i+1) because index start from 0 but we want sl.no from 1
            }
        }
        if(found == 0)
        {
        printf("Name Not found\n");
        return 0;
        }
        break;
    
    case 2:
        
        printf("Enter the phone number:\n");
        char phone[20];
        //getchar();
        scanf("%s",phone);
        found=0;

        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,phone) == 0) // Compare phone numbers
            {
                //Contact found, display details

                printf("Found at index %d.\n",i+1);
                printf("Name:%s\n",addressBook->contacts[i].name);
                printf("Phone:%s\n",addressBook->contacts[i].phone);
                printf("email:%s\n",addressBook->contacts[i].email);
                found = 1;
                return i+1; //to return index value (i+1) because index start from 0 but we want sl.no from 1
            }
        }
        if(found == 0)
        {
        printf("Phone number Not found\n");
        return 0;
        }
        break;

    case 3:

        printf("Enter the email:\n");
        char email[50];
        scanf("%s",email);
        found = 0;
//printf("count -> %d\n", addressBook -> contactCount);
    for (int i=0;i<addressBook->contactCount;i++)
    {
       // printf("addre -> %s\nemail -> %s\n",addressBook->contacts[i].email,email);
        if(strncmp(addressBook->contacts[i].email,email, strlen(email)) ==0)  //compare emails 
        {
            //Contact found, display details

            printf("Found at Index : %d\n", i + 1);  
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            found = 1;
            return i + 1;    //to return index value (i+1) because index start from 0 but we want sl.no from 1
        }
    }

    if (found == 0)
    {
        printf("Email Not found\n");
        return 0;   
    }
    break;

    default:
    
        printf("Invalid choice\n");
        return 0;
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int ret=searchContact(addressBook);    //to edit first we have to search the contact so here we calling searchContact function

    if(ret == 0)
    {
          return;  //exit from function
    }
    
    int index = ret - 1;

    printf("Enter what you want to edit:\n 1.Name\n 2.Phone\n 3.email\n");
    printf("Enter your choice\n");

    int choice;
    scanf("%d",&choice);
    //getchar();

    switch(choice)
      
    {
        case 1:
        
        printf("Enter the new name:\n");
        char temp1[50]; 
        getchar();
        scanf(" %[^\n]",temp1);

        if(validatename(temp1))    // Validate the entered name
      {
        strcpy(addressBook->contacts[index].name,temp1);  // If valid, update the name
      }
     else
      {
        printf("Enter only alphabets:\n");
        return;
      }
     break;

       case 2: 
        
        printf("Enter the new phone number:\n");
        char temp2[50];
        scanf("%s",temp2);

        if(validatephone(temp2,addressBook))    // Validate the entered phone number
      {
        strcpy(addressBook->contacts[index].phone,temp2);    // If valid, update the phone number
      }
     else
      {
        printf("Enter only 10 digits\n");
        return;
      }
     break;

    case 3:

    printf("Enter the new email:\n");
    char temp3[50];
    scanf("%s",temp3);
 
    if(validateemail(temp3,addressBook))  // Validate the entered email
    {
        strcpy(addressBook->contacts[index].email,temp3);  // If valid, update the contact's email
    }
    else
    {
        printf("Enter valid email id\n");
        return; 
    }
    break;

        default:
        printf("Invalid choice\n");
        return;
    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    int ret=searchContact(addressBook);    //ret gives index+1 of the found contact or 0 if not found

    if(ret == 0)
    {
        return;         //no contact was found function exits without deleting
    }

    int index = ret - 1;
    // 1-based position returned by searchContact into a 0-based index

    printf("Deleting contact: %s,%s,%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);

    for(int i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1]; //shifting of contacts after deleting to fill the gap of deleted contact
    }
    addressBook->contactCount--; 
    printf("Contact Deleted successfully");
     
}

