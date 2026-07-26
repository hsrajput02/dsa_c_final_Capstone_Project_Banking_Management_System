#include "../include/banking.h"
#include "../include/utils.h"

//==================================================
// Administrator Login
//==================================================

void adminLogin()
{
    char username[30];
    char password[30];

    clearScreen();

    printf("\n========================================");
    printf("\n         ADMINISTRATOR LOGIN");
    printf("\n========================================");

    printf("\n\nUsername : ");
    scanf("%s", username);

    printf("Password : ");
    scanf("%s", password);

    if(strcmp(username, ADMIN_USERNAME) == 0 &&
       strcmp(password, ADMIN_PASSWORD) == 0)
    {
        printf("\n\nLogin Successful.");

        pauseScreen();

        adminMenu();
    }
    else
    {
        printf("\n\nInvalid Username or Password.");

        pauseScreen();
    }
}



//==================================================
// Administrator Dashboard
//==================================================

void adminMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========================================");
        printf("\n          ADMIN DASHBOARD");
        printf("\n========================================");

        printf("\n1. Customer Management");
        printf("\n2. Employee Management");
        printf("\n3. Reports & Statistics");
        printf("\n4. Analytics & Search");
        printf("\n5. Logout");

        printf("\n\nEnter Choice : ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                accountMenu();
                break;

            case 2:
                employeeManagement();
                break;

            case 3:
                reportsMenu();
                break;

            case 4:
                dsaMenu();
                break;

            case 5:
                printf("\nLogging Out...");
                pauseScreen();
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    }while(choice != 5);
}