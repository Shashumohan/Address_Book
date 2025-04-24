#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp;
    fp=fopen("addressbook.csv","w");
    if(fp == NULL)
    {
        printf("invalid Address\n");
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    printf("Contacts Saved to addressbook\n");
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    int *num = &addressBook->contactCount;
    FILE *fp;
    fp = fopen("addressbook.csv","r");
    if(fp==NULL)
    {
        printf("Invalid Address");
        return;
    }
    int i=0;
    while(fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email)!=EOF)
    {
        i++;
    }
    *num = i;
    fclose(fp);
    printf("Contacts loaded from addressbook\n");
}
