#include<stdio.h>
#include<string.h>
#include "contact.h"
#include<ctype.h>

int validatename(char *name)
{
    int i = 0, flag = 0;
    while(name[i])
    {
        if((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] == ' '))
     
        {
            //character valid keep checking
        }
        else
        {
            flag = 1;  
        }
        i++;
    }
    if(flag == 0)     //name should be uppercase lowercase and space
    {
        return 1;
    }
    else
    {
        return 0;
    }
   
}

int validatephone(char *phone,AddressBook *addressBook)
{
    if(strlen(phone) != 10)           //length should be 10
    {
        printf("Phone number must be exactly 10 digits\n");
        return 0;
    }

    for(int i=0;phone[i] != '\0';i++)
    {
        if(phone[i] < '0' || phone[i] > '9')           //checking only digits are present
        {
            printf("Phone number must be contain only digits\n");
            return 0;
        }
    }

    for(int i=0;i<(addressBook->contactCount);i++)
    {
           if(strcmp(addressBook->contacts[i].phone,phone) == 0)    // checking duplicate or not
           {
            printf("Phone number already exists in addressbook\n");
            return 0;
           }

    }

    return 1;
    
}
int validateemail(char *email, AddressBook *addressBook)
{
    
    int check = 0;
    for (int i = 0; i < (addressBook->contactCount); i++)
    {
        if (strcmp(addressBook->contacts[i].email, email) == 0)  // checking duplicate or not
        {
            check = 1;
            break;
        }
    }
    if (check == 1)
    {
        return 0;
    }
   

    char *index1 = strchr(email, '@');   //checking whether it is containing only one @ or not
    if (index1 == NULL)
        return 0;

    char *index2 = strchr(email, '.');   //checking whether it is containing only one  . or not
    if (index2 == NULL)
        return 0;

    if (index2 < index1)  //check . present before @
        return 0;

    int Count = 0;
    for (int i = 0; email[i]; i++)
      {
        if (email[i] == '@')  //checking whether @ present more than once
      {
        Count++;
      }
    }

if (Count != 1) {
    return 0;               // Invalid: either 0 or more than 1 '@'
}

    for (int i = 0; email[i]; i++)
    {
        if ((email[i] >= 'a' && email[i] <= 'z') || (email[i] == '@') || (email[i] == '.') || (email[i]>=48 && email[i]<=57))
        {
            //keep checking for all character 
        }
        else
        {
            return 0;
        }
    }
    if ( isalnum(*(index1 - 1)) && isalnum(*(index1 + 1)) )    
   {                                                               //before and after @ and . alphanumeric should be present 
        if ( isalnum(*(index2 - 1)) && isalnum(*(index2 + 1)) )
        {
            return 1;
       }
        else
          return 0;
   }
   else
       return 0;
}