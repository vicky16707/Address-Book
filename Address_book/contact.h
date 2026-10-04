#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>

// Structures for the Fields
typedef struct Contact_data
{
    char Name[20];
    char Mobile_number[11];
    char Mail_ID[50];

}Contacts;

// Structures foe the Contact deatils
typedef struct AddressBook_Data
{                                      
    Contacts contact_details[100];      // Array of structures for the Fields sturucture
    int contact_count;                   // To keep the track no of contact count
}AddressBook;

/* Function declarations */

void create_contact(AddressBook *);
void list_contacts(AddressBook *);
void search_contacts(AddressBook *);
void edit_contact(AddressBook *);
void delete_contact(AddressBook *);
void save_contacts(AddressBook *);
void load_contacts(AddressBook *);
void edit_name(AddressBook *addressbook, int idex);
void edit_mobile(AddressBook *addressbook, int idex);
void edit_mail(AddressBook *addressbook, int idex);

#endif
// CONTACT_H
// CONTACT_H