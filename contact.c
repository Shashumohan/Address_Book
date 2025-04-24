#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sc) 
{
    // Sort contacts based on the chosen criteria
    char str[100];
    if(sc==1)
    {
        int j=0,res=0;     //using bubble sort technique.
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-1-i;j++)
            {
                res = strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
                if(res>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]= addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
    }
    if(sc==2)
    {
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-1-i;j++)
            {
                if((strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone))>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]= addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
    }
    if(sc==3)
    {
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-1-i;j++)
            {
                if((strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email))>0)
                {
                    Contact temp = addressBook->contacts[j];
                    addressBook->contacts[j]= addressBook->contacts[j+1];
                    addressBook->contacts[j+1] = temp;
                }
            }
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)   
    {
        printf("%d.%s\t\t%s\t\t%s\t\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }   
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


int validate_name(char *s)
{
    int len = 0;
    while(s[len]!='\0')      
    { 
        if(!(s[len] == ' ' || isalpha(s[len])))     //if the character is not alphabetic or space print error message and return 1.
        {
            printf("Inavlid name please enter again\n");
            return 1;
        }
        len++;
    }
    if(len>0)     
    {
        return 0;
    }
    else     // length of the name cant be zero.
    {
        return 1;
    }    
}

int validate_number(char *n)
{
    int len = 0;
    while(n[len]!='\0')      // runnimg the loop upto null character.
    {
        if(!(isdigit(n[len])))     //checking if number contains only digits or not
        {
            printf("Invalid number Enter again\n");      // if any character is found print error and return 1. 
            return 1;
        }
        len++;
    }
    if(len!=10)         //checks wheather the number contains 10 digits or not
    {
        printf("Invalid number Enter again\n");
        return 1;      
    }
    return 0;    // return 0 when number is valid.
}

int validate_mailid(char *m)
{
    int len=0;
    if(!(isalpha(m[len])))        //first character should be alphabet
    {
        printf("Invalid mailid\n");
        return 1;
    }
    int count_at =0;
    int count_dot = 0;
    while(m[len]!='\0')       
    {
        if(m[len]==' ')         //checks if the id contains space or not 
        {
            printf("Invalid mail id\n");
            return 1;            // if space is available return 1.
        }
        if(m[len]=='@')      // checks the mail id shouls contain only 1 @ character.
        {
            count_at++;
        }
        else if(m[len]=='.')    // checks the mail id shouls contain atleast 1 '.' character.
        {
            count_dot++;
        }
        len++;
    }
    
    if(count_at != 1 || count_dot<1)
    {
        printf("Invalid email id\n");
        return 1;
    }

    return 0;
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char str[100];
    printf("Enter the name\n");
    int res=0;      // A variable to collect the return value from the validate function.
    int count=0;    // To keep if all the attributs is validated.
    do
    {
        scanf(" %[^\n]",str);
        /*checking the space is available infront of the name and skipping the spaces if 
        it encountered before the name.*/
        int i=0,j=0; 
        while(str[i] == ' ')
        {
            i++;
        }
        if(i!=0)  /*if space is available shift the name to the left side by nuber of space available before name.*/
        {
            while(str[j]!='\0')
            {
                str[j] = str[j+i]; 
                j++;
            }
        }
        res = validate_name(str);
        if(!res)      /*copying the name to the structure if the name is correct*/
        {
            for(int k=0;k<addressBook->contactCount;k++)
            {
                if(!(strcmp(str,addressBook->contacts[k].name)))
                {
                    printf("Contact is already present\ncheck for the mobile number\n");
                }
            }
            count++;  
        }
    }while(res!=0);   // running the loop till the user enter correct name.

    printf("Enter the mobile number\n");
    char num[20];
    do
    {
        scanf(" %[^\n]",num);
        res = validate_number(num);
        if(!res)
        {
            for(int k=0;k<addressBook->contactCount;k++)
            {
                if(!(strcmp(num,addressBook->contacts[k].phone)))
                {
                    printf("phone number is already available\ncontact not stored\n");
                    return;
                }
            }
            count++;
        }
    }while(res!=0);

    printf("Enter the mail id\n");

    char mailid[50];
    do
    {
        scanf(" %[^\n]",mailid);
        res = validate_mailid(mailid);
        if(!res)
        {
            int flag =0;
            for(int k=0;k<addressBook->contactCount;k++)
            {
                if(!(strcmp(mailid,addressBook->contacts[k].email)))
                {
                    printf("mail is already taken\n");
                    flag =1;
                    break;
                }
            }
            if(!flag)
            {
                count++;
            }
        }
    }while(res!=0);

    if(count == 3)    // storing the contact details if all the information is valid.
    {
        strcpy(addressBook->contacts[addressBook->contactCount].name,str);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,num);
        strcpy(addressBook->contacts[addressBook->contactCount].email,mailid);
        addressBook->contactCount++;
        printf("Contact is successfully updated\n");
    }
    else
    {
        printf("Contact is not stored\n");
    }
}

int compare_name(AddressBook *addressBook,char *str)
{
    int flag=0,d=1;
    for(int k=0;k<addressBook->contactCount;k++)
    {
        if(!(strcmp(str,addressBook->contacts[k].name)))
        {
            printf("%d.Contact deatails\n",d);
            printf("Name : %s\n",addressBook->contacts[k].name);
            printf("Phone no : %s\n",addressBook->contacts[k].phone);
            printf("Mail ID : %s\n",addressBook->contacts[k].email);
            d++;
            flag = 1;
        }
    }
    return flag;
}

int compare_phone(AddressBook *addressBook,char *str)
{
    int d=1;
    for(int k=0;k<addressBook->contactCount;k++)
    {
        if(!(strcmp(str,addressBook->contacts[k].phone)))
        {
            printf("%d.Contact deatails\n",d);
            printf("Name : %s\n",addressBook->contacts[k].name);
            printf("Phone no : %s\n",addressBook->contacts[k].phone);
            printf("Mail ID : %s\n",addressBook->contacts[k].email);
            d++;
            return 1;
        }
    }
    return 0;
}

int compare_email(AddressBook *addressBook,char *str)
{
    int d=1;
    for(int k=0;k<addressBook->contactCount;k++)
    {
        if(!(strcmp(str,addressBook->contacts[k].email)))
        {
            printf("%d.Contact deatails\n",d);
            printf("Name : %s\n",addressBook->contacts[k].name);
            printf("Phone no : %s\n",addressBook->contacts[k].phone);
            printf("Mail ID : %s\n",addressBook->contacts[k].email);
            d++;
            return 1;
        }
    }
    return 0;
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    char str[50];
    int c;
    do
    {
        printf("Enter the choice for search\n1.Name\n2.conatct\n3.mailid\n");
        scanf("%d",&c);
        getchar();
        int res =0;
        if(c==1)
        {
            do
            {
                printf("Enter the name\n");
                /*checking the space is available infront of the name and skipping the spaces if 
                it encountered before the name.*/
                scanf("%[^\n]",str);
                res = validate_name(str);
                if(!res)
                {
                    int flag = compare_name(addressBook,str);
                    if(!flag)
                    {
                        printf("Contact details not available\n");
                        return 1;
                    }
                }
                
            }while(res!=0);
            return 0;
        }
        else if(c==2)
        {
            do
            {
                printf("Enter the phone number\n");
                scanf("%[^\n]",str);
                res = validate_number(str);
                if(!res)
                {
                    int flag = compare_phone(addressBook,str);
                    if(!flag)
                    {
                        printf("Contact details not available\n");
                        return 1;
                    }
                }
            }while(res!=0);
            return 0;
        }
        else if(c==3)
        {
            do
            {
                printf("Enter the mail ID\n");
                scanf("%[^\n]",str);
                res = validate_mailid(str);
                if(!res)
                {
                    int flag=compare_email(addressBook,str);
                    if(!flag)
                    {
                        printf("Contact details not available\n");
                        return 1;
                    }
                }
            }while(res!=0);
            return 0;
        }
        else
        {
            printf("Inavlid choice\n");
            return 1;
        }
    }while(c<=3 && c>=1);
}

void editContact(AddressBook *addressBook)
{
    char str_search[50];
    char str[50];
    int arr[100];  //To store the indices of matching contacts.
    int arrcount=0;

    printf("What would you like to use to search for the contact to edit?\n");
    printf("1. Name\n2. Phone\n3. Email ID\n");
    int search;
    scanf("%d",&search);
    getchar();

    switch(search)
    {
        case 1:
            printf("Enter the name to search: ");
            break;
        case 2:
            printf("Enter the phone number to search: ");
            break;
        case 3:
            printf("Enter the email ID to search: ");
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    scanf("%[^\n]",str_search);
    getchar();

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if ((search == 1 && strcmp(addressBook->contacts[i].name, str_search) == 0) ||
            (search == 2 && strcmp(addressBook->contacts[i].phone, str_search) == 0) ||
            (search == 3 && strcmp(addressBook->contacts[i].email, str_search) == 0))
        {
            arr[arrcount++]=i;
        }
    }
    int index;
    if(arrcount==0)
    {
        printf("No Contact found.\n");
        return;
    }
    else if(arrcount==1)
    {
        index=arr[0];
        printf("Contact found:\n");
        printf("Name: %s, Phone: %s, Email: %s\n",
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);
    }
    else
    {
        printf("Multiple contact found:\n");
        for(int i=0;i<arrcount;i++)
        {
            int si=arr[i];
            printf("[%d] Name: %s, Phone: %s, Email: %s\n", i+1,
               addressBook->contacts[si].name,
               addressBook->contacts[si].phone,
               addressBook->contacts[si].email);
        }
        printf("Select the contact number that need to edit (1-%d): ",arrcount);
        int choice;
        scanf(" %d",&choice);
        getchar();

        if(choice<1 || choice>arrcount)
        {
            printf("Invalid choice");
            return ;
        }

        index = arr[choice-1];
    }

    printf("What would you like to edit?\n");
    printf("1. Name\n2. Phone\n3. Email ID\n");
    int edit;
    scanf("%d",&edit);
    getchar();
    int res;
    if(edit==1)
    {
        printf("Enter the new name: ");
        do
        {
            scanf(" %[^\n]",str);
            int i=0,j=0; 
            while(str[i] == ' ')
            {
                i++;
            }
            if(i!=0)  /*if space is available shift the name to the left side by nuber of space available before name.*/
            {
                while(str[j]!='\0')
                {
                    str[j] = str[j+i]; 
                    j++;
                }
            }
            res = validate_name(str);
            if(!res)
            {
                strcpy(addressBook->contacts[index].name,str);
                printf("Name is edited Successfully.\n");   
            }
        }while(res!=0);
    }
    else if(edit==2)
    {
        printf("Enter the new phone number: ");
        do
        {
            scanf(" %[^\n]",str);
            res = validate_number(str);
            if(!res)
            {
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].phone,str) == 0 && i!=index)
                    {
                        printf("Error: Phone number already exits for another contact.\n");
                        return;
                    }
                }
                strcpy(addressBook->contacts[index].phone,str);
                printf("Phone number is edited successfully.\n");
            }
        }while(res!=0);
    }
    else if(edit == 3)
    {
        printf("Enter the new Mail ID: ");
        do
        {
            scanf(" %[^\n]",str);
            res = validate_mailid(str);
            if(!res)
            {
                for(int i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].email,str) == 0 && i!=index)
                    {
                        printf("Error: mail id already exits for another contact.\n");
                        return;
                    }
                }
                strcpy(addressBook->contacts[index].email,str);
                printf("mail id is edited successfully.\n");
            }
        }while(res!=0);
    }
    else
    {
        printf("Invalid choice\n");
        return;
    }
}



void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    char str_search[50];
    char str[50];
    int arr[100];
    int arrcount =0;

    printf("What would you like to use to search for the contact to delete?\n");
    printf("1. Name\n2. Phone\n3. Email ID\n");
    int search;
    scanf("%d",&search);
    getchar();

    switch(search)
    {
        case 1:
            printf("Enter the name to search: ");
            break;
        case 2:
            printf("Enter the phone number to search: ");
            break;
        case 3:
            printf("Enter the email ID to search: ");
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    scanf("%[^\n]",str_search);
    getchar();

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if ((search == 1 && strcmp(addressBook->contacts[i].name, str_search) == 0) ||
            (search == 2 && strcmp(addressBook->contacts[i].phone, str_search) == 0) ||
            (search == 3 && strcmp(addressBook->contacts[i].email, str_search) == 0))
        {
            arr[arrcount++]=i;
        }
    }
    int index;
    if(arrcount==0)
    {
        printf("No Contact found.\n");
        return;
    }
    else if(arrcount==1)
    {
        index=arr[0];
        printf("Contact found:\n");
        printf("Name: %s, Phone: %s, Email: %s\n",
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);
    }
    else
    {
        printf("Multiple contact found:\n");
        for(int i=0;i<arrcount;i++)
        {
            int si = arr[i];
            printf("[%d] Name: %s, Phone: %s, Email: %s\n", i+1,
               addressBook->contacts[si].name,
               addressBook->contacts[si].phone,
               addressBook->contacts[si].email);
        }
        printf("Select the contact details that need to deleted (1-%d): ",arrcount);
        int choice;
        scanf(" %d",&choice);
        getchar();

        if(choice<1 || choice>arrcount)
        {
            printf("Invalid choice");
            return ;
        }

        index = arr[choice-1];
    }

    for(int i=index;i<addressBook->contactCount;i++)
    {
        strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
        strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
        strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
    }
    addressBook->contactCount--;

    printf("Contact is deleted successfully.\n");

}
