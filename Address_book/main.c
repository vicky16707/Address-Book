
#include"contact.h"
/* Structure declaration */
int main()
{
    // Variable and structre defintion 
    int option;
    AddressBook addressbook;
    // Load contacts from file when program starts 
    addressbook.contact_count = 0;        // initialize

    load_contacts(&addressbook);           // load file data
       
    while (1)
    {
        printf("\n=========Address book menu=========\n"); /* Give a prompt message for a user */
        printf(" 1.Add contact\n 2.search contact\n 3.Edit contact\n 4.Delete contact\n 5.Display contact\n 6.Exit\n");
        printf("  Enter the option : ");

        if(scanf("%d", &option) != 1)
        {
            printf(" →→→→→Invalid input←←←←←\n");
            while(getchar() != '\n');
            continue;
        }
        switch (option) // Based on choosed option 
        {
        case 1:
        {
            create_contact(&addressbook);//create contact function call
            break;
        }
        case 2:
        {
            search_contacts(&addressbook);//search contact function call
            break;
        }
        case 3:

            edit_contact(&addressbook);//edit contact function call
            break;

        case 4:
        {
            delete_contact(&addressbook);//delete contact function call
            break;
        }
        case 5:
        {
            printf("\n==================    CONTACT LILST    ==================\n");
            list_contacts(&addressbook);                     //list contact function call
            break;
        }
        case 6:
            printf("Exit\n");
            return 0;

        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}
