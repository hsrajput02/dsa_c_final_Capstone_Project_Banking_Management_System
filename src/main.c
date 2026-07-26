#include "../include/banking.h"
#include "../include/utils.h"

int main()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n==================================================\n");
        printf("      SMART BANKING MANAGEMENT SYSTEM (SBMS)\n");
        printf("==================================================\n");

        printf("\n1. Administrator Login");
        printf("\n2. Employee Login");
        printf("\n3. Customer Login");
        printf("\n4. About Project");
        printf("\n5. Exit");

        printf("\n\nEnter Your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                adminLogin();
                break;

            case 2:
                employeeLogin();
                break;

            case 3:
                customerLogin();
                break;

            case 4:
                clearScreen();

                printf("\n=========================================\n");
                printf("        SMART BANKING MANAGEMENT SYSTEM\n");
                printf("=========================================\n");

                printf("\nProject Name : SBMS");
                printf("\nDeveloped Using : C Language");
                printf("\nConcepts Used :");
                printf("\n  - Structures");
                printf("\n  - File Handling");
                printf("\n  - Functions");
                printf("\n  - Searching");
                printf("\n  - Sorting");
                printf("\n  - Stack");
                printf("\n  - Queue");
                printf("\n  - Linked List");

                printf("\n\nModules:");
                printf("\n  * Administrator");
                printf("\n  * Employee");
                printf("\n  * Customer");
                printf("\n  * Banking Transactions");
                printf("\n  * Reports");
                printf("\n  * DSA");

                printf("\n\nVersion : 1.0");

                pauseScreen();
                break;

            case 5:
                clearScreen();

                printf("\n=========================================\n");
                printf(" Thank You For Using SBMS");
                printf("\n=========================================\n\n");

                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    }
    while (choice != 5);

    return 0;
}