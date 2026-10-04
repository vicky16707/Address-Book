#include "contact.h"      // Header file containing structure and function declarations
#include <stdio.h>        // Standard input/output functions
#include <string.h>       // String handling functions
#include <ctype.h>        // Character validation functions

// Function : search_contact

int search_contact(const AddressBook *addressbook, int match[])
{
    int count = 0;      // Stores number of matching contacts
    int option;         // Stores user's search option

    // Display search menu
    printf("\n------Choose by what to search------\n1.Search by name\n2.Search by Mobile number\n3.Search by Email id\n4.EXIT\n");

    // Read a valid menu option
    do
    {
        printf("Enter option: ");

        // Validate numeric input
        if(scanf("%d", &option) != 1)
        {
            printf("Invalid input\n");

            // Clear invalid characters from input buffer
            while(getchar() != '\n');

            option = 0;
            continue;
        }

        // Validate option range
        if(option < 1 || option > 4)
        {
            printf("Invalid option\n");
        }

    } while(option < 1 || option > 4);

    // Exit search menu
    if(option == 4)
        return -1;

    switch(option)
    {
        // Search by Name
        case 1:
        {
            char na[20];

            // Read name from user
            printf("Enter name to search : ");
            scanf(" %[^\n]", na);

            // Compare entered name with every contact
            for(int i = 0; i < addressbook->contact_count; i++)
            {
                // Prefix matching using strncmp()
                if(strncmp(addressbook->contact_details[i].Name,
                           na,
                           strlen(na)) == 0)
                {
                    // Store matched contact index
                    match[count++] = i;
                }
            }
            break;
        }

        // Search by Mobile Number
        case 2:
        {
            char num[20];

            // Read mobile number
            printf("Enter number to search : ");
            scanf("%10s", num);

            // Compare with every stored contact
            for(int i = 0; i < addressbook->contact_count; i++)
            {
                if(strncmp(addressbook->contact_details[i].Mobile_number,
                           num,
                           strlen(num)) == 0)
                {
                    match[count++] = i;
                }
            }
            break;
        }

        // Search by Email ID
        case 3:
        {
            char mail[50];

            // Read email ID
            printf("Enter mail id to search : ");
            scanf("%49s", mail);

            // Compare with every stored email
            for(int i = 0; i < addressbook->contact_count; i++)
            {
                if(strncmp(addressbook->contact_details[i].Mail_ID,
                           mail,
                           strlen(mail)) == 0)
                {
                    match[count++] = i;
                }
            }
            break;
        }
    }

    // Return total number of matched contacts
    return count;
}

// Function : edit_name

void edit_name(AddressBook *addressbook, int idex)
{
    char name[20];

    // Repeat until a valid name is entered
    while(1)
    {
        int valid = 1;

        // Read new name
        printf("Enter new Name : ");
        scanf(" %19[^\n]", name);

        // Validate each character
        for(int i = 0; name[i] != '\0'; i++)
        {
            // Only alphabets and spaces are allowed
            if(!isalpha(name[i]) && name[i] != ' ')
            {
                valid = 0;
                break;
            }
        }

        // Reject empty string
        if(strlen(name) == 0)
            valid = 0;

        int only_spaces = 1;

        // Check whether input contains only spaces
        for(int i = 0; name[i]; i++)
        {
            if(name[i] != ' ')
                only_spaces = 0;
        }

        // Reject names containing only spaces
        if(only_spaces)
            valid = 0;

        if(valid)
        {
            // Update contact name
            strcpy(addressbook->contact_details[idex].Name, name);

            printf("Valid Name Updated\n");
            break;
        }

        printf("Invalid Name\n");
    }
}

void edit_mobile(AddressBook *addressbook, int idex)
{
    char Mobile_number[11];

    // Repeat until a valid mobile number is entered
    while(1)
    {
        int valid = 1;
        int duplicate = 0;

        // Read the new mobile number
        printf("Enter new Mobile Number : ");
        scanf("%10s", Mobile_number);

        // Check whether the mobile number contains exactly 10 digits
        if(strlen(Mobile_number) != 10)
        {
            valid = 0;
        }

        // Verify that all characters are digits
        for(int i = 0; Mobile_number[i] != '\0'; i++)
        {
            if(!isdigit(Mobile_number[i]))
            {
                valid = 0;
                break;
            }
        }

        // Check whether the mobile number already exists
        if(valid)
        {
            for(int j = 0; j < addressbook->contact_count; j++)
            {
                // Ignore the current contact while checking duplicates
                if(j != idex &&
                   strcmp(addressbook->contact_details[j].Mobile_number,
                          Mobile_number) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
        }

        // Display message if duplicate mobile number is found
        if(duplicate)
        {
            printf("Mobile Number already exists\n");
            continue;
        }

        // Display message if the entered mobile number is invalid
        if(!valid)
        {
            printf("Invalid Mobile Number\n");
            continue;
        }

        // Update the mobile number of the selected contact
        strcpy(addressbook->contact_details[idex].Mobile_number,
               Mobile_number);

        // Display success message
        printf("Valid Mobile Number Updated\n");
        break;
    }
}

void edit_mail(AddressBook *addressbook, int idex)
{
    char mail[50];

    // Repeat until a valid email ID is entered
    while(1)
    {
        int valid = 1, duplicate = 0;
        int at = 0, at_pos = -1;

        // Read the new email ID
        printf("Enter Mail: ");
        scanf("%49s", mail);

        // Find the length of the entered email
        int len = strlen(mail);

        // Count the number of '@' symbols and store its position
        for(int i = 0; i < len; i++)
        {
            if(mail[i] == '@')
            {
                at++;
                at_pos = i;
            }
        }

        // Email must contain exactly one '@'
        if(at != 1)
            valid = 0;

        // '@' should not be the first or last character
        if(at_pos <= 0 || at_pos >= len - 1)
            valid = 0;

        // Check whether '@' is present
        if(at_pos == -1)
            valid = 0;

        int dot = 0;

        // Check whether a '.' exists after '@'
        for(int i = at_pos + 1; i < len; i++)
        {
            if(mail[i] == '.')
            {
                dot = 1;
                break;
            }
        }

        // Mark email invalid if '.' is not found
        if(!dot)
            valid = 0;

        // Check whether the email ID already exists
        for(int i = 0; i < addressbook->contact_count; i++)
        {
            // Ignore the current contact while checking duplicates
            if(i != idex && strcmp(addressbook->contact_details[i].Mail_ID, mail) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        // Display message if duplicate email is found
        if(duplicate)
        {
            printf("Duplicate mail\n");
            continue;
        }

        // Update the email if it is valid
        if(valid)
        {
            strcpy(addressbook->contact_details[idex].Mail_ID, mail);
            printf("Mail Updated\n");
            break;
        }

        // Display error message for invalid email
        printf("Invalid Mail\n");
    }
}

void create_contact(AddressBook *addressbook)
{
    // Check whether the address book has reached its maximum capacity
    if(addressbook->contact_count >= 100)
    {
        printf("Full\n");
        return;
    }

    // Store the index where the new contact will be added
    int idx = addressbook->contact_count;

    // Temporary variables to store user input
    char name[20];
    char mobile[11];
    char Mail_ID[50];

    /* ---------------- NAME ---------------- */

    // Read and validate the contact name
    while(1)
    {
        printf("Name: ");
        scanf(" %19[^\n]", name);

        int valid = 1;

        // Check whether the name contains only alphabets and spaces
        for(int i = 0; name[i]; i++)
        {
            if(!isalpha(name[i]) && name[i] != ' ')
            {
                valid = 0;
                break;
            }
        }

        // Accept the name only if it is valid and not empty
        if(valid && strlen(name) > 0)
            break;

        printf("Invalid name\n");
    }

    /* ---------------- MOBILE ---------------- */

    // Read and validate the mobile number
    while(1)
    {
        int valid = 1;
        int duplicate = 0;

        printf("Enter Mobile Number: ");
        scanf("%10s", mobile);

        // Mobile number must contain exactly 10 digits
        if(strlen(mobile) != 10)
            valid = 0;

        // Verify that every character is a digit
        for(int i = 0; mobile[i]; i++)
        {
            if(!isdigit(mobile[i]))
            {
                valid = 0;
                break;
            }
        }

        // Check whether the mobile number already exists
        if(valid)
        {
            for(int j = 0; j < addressbook->contact_count; j++)
            {
                if(strcmp(addressbook->contact_details[j].Mobile_number, mobile) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
        }

        // Reject duplicate mobile numbers
        if(duplicate)
        {
            printf("Mobile already exists\n");
            continue;
        }

        // Accept the mobile number if it is valid
        if(valid)
            break;

        printf("Invalid Mobile Number\n");
    }

    /* ---------------- EMAIL ---------------- */

    // Read and validate the email address
    while(1)
    {
        int valid = 1;
        int duplicate = 0;
        int at = 0, at_pos = -1;

        printf("Enter Mail: ");
        scanf("%49s", Mail_ID);

        // Find the length of the email
        int len = strlen(Mail_ID);

        // Count the number of '@' symbols and record its position
        for(int i = 0; i < len; i++)
        {
            if(Mail_ID[i] == '@')
            {
                at++;
                at_pos = i;
            }
        }

        // Email should contain exactly one '@'
        if(at != 1)
            valid = 0;

        // '@' should not be the first or last character
        if(at_pos <= 0 || at_pos >= len - 1)
            valid = 0;

        int dot = 0;

        // Check whether '.' appears after '@'
        for(int i = at_pos + 1; i < len; i++)
        {
            if(Mail_ID[i] == '.')
            {
                dot = 1;
                break;
            }
        }

        // Mark email invalid if '.' is not found
        if(!dot)
            valid = 0;

        // Check whether the email already exists
        if(valid)
        {
            for(int i = 0; i < addressbook->contact_count; i++)
            {
                if(strcmp(addressbook->contact_details[i].Mail_ID, Mail_ID) == 0)
                {
                    duplicate = 1;
                    break;
                }
            }
        }

        // Reject duplicate email IDs
        if(duplicate)
        {
            printf("Duplicate mail\n");
            continue;
        }

        // Accept the email if it is valid
        if(valid)
            break;

        printf("Invalid Mail\n");
    }

    /* ---------------- STORE DATA ---------------- */

    // Store the validated contact details in the address book
    strcpy(addressbook->contact_details[idx].Name, name);
    strcpy(addressbook->contact_details[idx].Mobile_number, mobile);
    strcpy(addressbook->contact_details[idx].Mail_ID, Mail_ID);

    // Increase the contact count
    addressbook->contact_count++;

    // Save the updated contacts to the file
    save_contacts(addressbook);

    // Display success message
    printf("Contact saved\n");
}

void list_contacts(AddressBook *addressbook)
{
    // Check whether any contacts are available
    if(addressbook->contact_count == 0)
    {
        printf("\n\n=========No Contacts Available=========\n");
        return;
    }

    // Display the table header
    printf("\n-----------------------------------------------------\n");
    printf("S.No  Name           Mobile Number     Mail ID\n");
    printf("-----------------------------------------------------\n");

    // Display all contacts one by one
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf("%-6d%-16s%-17s%-20s\n",
               i + 1,
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID);
    }
}

void search_contacts(AddressBook *addressbook)
{
    // Array to store matching contact indexes
    int match[100], count;

    while(1)
    {
        // Search for matching contacts
        count = search_contact(addressbook, match);

        // Return if user selects EXIT
        if(count == -1)
        {
            return;
        }

        // If no contacts are found, search again
        if(count == 0)
        {
            printf("Contact not found\n");
            continue;
        }

        // Exit loop when matching contacts are found
        break;
    }

    // Display heading for matching contacts
    printf("\nMatching Contacts\n");

    // Display all matching contacts
    for(int i = 0; i < count; i++)
    {
        // Get the actual contact index
        int idex = match[i];

        // Print contact details
        printf("%d. %-15s %-15s %-20s\n",
               idex + 1,
               addressbook->contact_details[idex].Name,
               addressbook->contact_details[idex].Mobile_number,
               addressbook->contact_details[idex].Mail_ID);
    }
}

void edit_contact(AddressBook *addressbook)
{
    // Array to store the matching contact indexes
    int match[100],choice;

    // Search for the required contact
    int count = search_contact(addressbook, match);
    
    // Return if no matching contact is found
    if(count <= 0)
    {
        printf("No contact\n");
        return;
    }

    // Display all matching contacts
    for(int i = 0; i < count; i++)
    {
        int idex = match[i];

        printf("%d. %-15s %-15s %-20s\n",i + 1,addressbook->contact_details[idex].Name
            ,addressbook->contact_details[idex].Mobile_number,addressbook->contact_details[idex].Mail_ID);
    }

    // Read a valid contact selection from the user
    while(1)
    {
        printf("Select contact to edit : ");   

        // Validate integer input
        if(scanf("%d", &choice) != 1)
        {
            printf(" →→→→→Invalid input←←←←←\n");

            // Clear the input buffer
            while(getchar() != '\n');

            continue;
        }

        // Check whether the selected option is within range
        if(choice < 1 || choice > count)
        {
            printf("Invalid selection\n");
            continue;
        }

        break;
        
    }

    // Get the actual index of the selected contact
    int idex = match[choice - 1];

    int option;

    // Display edit menu
    printf("\n1.Edit Name\n2.Edit Mobile Number\n3.Edit Mail ID\n4.Edit All\n5.EXIT\n");
    
    // Read a valid edit option
    do
    {
        printf("Enter option : ");

        // Validate integer input
        if(scanf("%d",&option) != 1)
        {
            printf("Invalid input\n");

            // Clear the input buffer
            while(getchar() != '\n');

            option = 0;
        }

    }while(option < 1 || option > 5);

    // Perform the selected edit operation
    switch(option)
    {
        case 1:
        {
            // Edit only the contact name
            edit_name(addressbook, idex);
            break;
        }

        case 2:
        {
            // Edit only the mobile number
            edit_mobile(addressbook, idex);
            break;
        }

        case 3:
        {
            // Edit only the email ID
            edit_mail(addressbook, idex);
            break;
        }

        case 4:
        {
            // Edit all contact details
            edit_name(addressbook, idex);
            edit_mobile(addressbook, idex);
            edit_mail(addressbook, idex);
            break;
        }

        case 5:
        {
            // Exit without editing
            return;
        }
        
    }

    // Save the updated contact details into the file
    save_contacts(addressbook);

    // Display success message
    printf("Contact updated successfully\n");
}

void delete_contact(AddressBook *addressbook)
{
    // Array to store matching contact indexes
    int match[100];

    // Search for the contact to delete
    int count = search_contact(addressbook, match);

    // Return if no matching contact is found
    if(count <= 0)
    {
        printf("Contact not found\n");
        return;
    }

    // Display all matching contacts
    for(int i = 0; i < count; i++)
    {
        int index = match[i];

        printf("%d. %-15s %-15s %-20s\n",i + 1,addressbook->contact_details[index].Name
            ,addressbook->contact_details[index].Mobile_number,addressbook->contact_details[index].Mail_ID);
    }

    int choice;

    // Read a valid contact selection
    while(1)
    {
        printf("Select contact to delete : ");

        // Validate integer input
        if(scanf("%d",&choice) != 1)
        {
            printf("Invalid input\n");

            // Clear the input buffer
            while(getchar() != '\n');

            continue;
        }

        // Check whether the selected contact is within range
        if(choice < 1 || choice > count)
        {
            printf("Invalid selection\n");
            continue;
        }

        break;
    }

    // Get the actual contact index to delete
    int index = match[choice - 1];

    // Shift all contacts one position to the left
    for(int i = index; i < addressbook->contact_count - 1; i++)
    {
        addressbook->contact_details[i] =addressbook->contact_details[i + 1];
    }

    // Reduce the total number of contacts
    addressbook->contact_count--;

    // Save the updated contact list
    save_contacts(addressbook);

    // Display success message
    printf("Contact deleted successfully\n");
}

void save_contacts(AddressBook *addressbook)
{
    FILE *fp = fopen("contacts.csv", "w");   //opening in write mode

    if(fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }
    fprintf(fp, "#%d\n", addressbook->contact_count);
    for(int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID);
    }

    fclose(fp);
}

void load_contacts(AddressBook *addressbook)
{
    // Open the contacts file in read mode
    FILE *fp = fopen("contacts.csv", "r");   //opening in read mode

    // Check whether the file exists
    if(fp == NULL)             //fopen return null when the acces is denied or wrong path or file not found
    {
        // Initialize contact count to zero
        addressbook->contact_count = 0;

        // Create a new contacts file with zero contacts
        save_contacts(addressbook);       // creates file with #0

        return;
    }

    // Read the total number of contacts from the first line
    if(fscanf(fp, "#%d\n",&addressbook->contact_count) != 1)
    {
        // Reset contact count if the file format is invalid
        addressbook->contact_count = 0;

        // Close the file before returning
        fclose(fp);

        return;
    }

    // Prevent reading beyond the maximum capacity
    if(addressbook->contact_count > 100) // it only works when the file is corrupted or program crashes
    {
        addressbook->contact_count = 100;
    }

    // Read each contact from the file
    for(int i = 0; i < addressbook->contact_count; i++)
    {
        // Read Name, Mobile Number and Mail ID separated by commas
        if(fscanf(fp,"%19[^,],%10[^,],%49[^\n]\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID) != 3)
        {
            // Stop reading if any record is incomplete
            addressbook->contact_count = i;

            break;
        }
    }

    // Close the file after reading
    fclose(fp);
}