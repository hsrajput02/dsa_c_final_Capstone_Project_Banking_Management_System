#include "../include/banking.h"
#include "../include/utils.h"

//==================================================
// Employee Login
//==================================================

void employeeLogin()
{
    FILE *file;

    Employee employee;

    int employeeId;
    char password[30];

    int found = 0;

    clearScreen();

    printf("\n========================================");
    printf("\n          EMPLOYEE LOGIN");
    printf("\n========================================");

    printf("\n\nEmployee ID : ");
    scanf("%d", &employeeId);

    printf("Password : ");
    scanf("%s", password);

    file = fopen("../data/employee.dat", "rb");

    if (file == NULL)
    {
        printf("\nEmployee Records Not Found.");
        pauseScreen();
        return;
    }

    while (fread(&employee, sizeof(Employee), 1, file))
    {
        if (employee.employeeId == employeeId &&
            strcmp(employee.password, password) == 0)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf("\n\nLogin Successful.");
        pauseScreen();

        employeeMenu();
    }
    else
    {
        printf("\nInvalid Employee ID or Password.");
        pauseScreen();
    }
}



//==================================================
// Employee Dashboard
//==================================================

void employeeMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========================================");
        printf("\n          EMPLOYEE DASHBOARD");
        printf("\n========================================");

        printf("\n1. Create Customer Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Search Customer");
        printf("\n5. View All Customers");
        printf("\n6. Logout");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                searchAccount();
                break;

            case 5:
                viewAccounts();
                break;

            case 6:
                printf("\nLogging Out...");
                pauseScreen();
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while (choice != 6);
}