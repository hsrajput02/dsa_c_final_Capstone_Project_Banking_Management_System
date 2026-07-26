#include "../include/banking.h"
#include "../include/utils.h"

// Store logged-in customer account number
int currentCustomer = 0;

//==================================================
// Customer Login
//==================================================

void customerLogin()
{
    FILE *file;

    Customer customer;

    int accountNumber;
    int pin;

    int found = 0;

    clearScreen();

    printf("\n========================================");
    printf("\n          CUSTOMER LOGIN");
    printf("\n========================================");

    printf("\n\nAccount Number : ");
    scanf("%d", &accountNumber);

    printf("PIN : ");
    scanf("%d", &pin);

    file = fopen("../data/customer.dat", "rb");

    if (file == NULL)
    {
        printf("\nCustomer Records Not Found.");
        pauseScreen();
        return;
    }

    while (fread(&customer, sizeof(Customer), 1, file))
    {
        if (customer.accountNumber == accountNumber &&
            customer.pin == pin)
        {
            found = 1;
            currentCustomer = customer.accountNumber;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nInvalid Account Number or PIN.");
        pauseScreen();
        return;
    }

    if (customer.status == FROZEN)
    {
        printf("\nYour Account is Frozen.");
        pauseScreen();
        return;
    }

    printf("\nLogin Successful.");

    pauseScreen();

    customerMenu();
}



//==================================================
// Customer Dashboard
//==================================================

void customerMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========================================");
        printf("\n          CUSTOMER DASHBOARD");
        printf("\n========================================");

        printf("\n1. Balance Inquiry");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Transfer Money");
        printf("\n5. Mini Statement");
        printf("\n6. Change PIN");
        printf("\n7. Logout");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                balanceInquiry();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                transferMoney();
                break;

            case 5:
                miniStatement();
                break;

            case 6:
                changePin();
                break;

            case 7:
                currentCustomer = 0;
                printf("\nLogging Out...");
                pauseScreen();
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while (choice != 7);
}