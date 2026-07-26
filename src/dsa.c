#include "../include/banking.h"
#include "../include/utils.h"

#define MAX_CUSTOMERS 500

//==================================================
// Load Customers
//==================================================

int loadCustomers(Customer customers[])
{
    FILE *file;
    int count = 0;

    file = fopen("../data/customer.dat", "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&customers[count], sizeof(Customer), 1, file))
    {
        count++;
    }

    fclose(file);

    return count;
}



//==================================================
// DSA Menu
//==================================================

void dsaMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========== Analytics & Search ==========\n");

        printf("\n1. Search Customer (Linear Search)");
        printf("\n2. Search Customer (Binary Search)");
        printf("\n3. Sort By Name");
        printf("\n4. Sort By Balance");
        printf("\n5. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                linearSearchCustomer();
                break;

            case 2:
                binarySearchCustomer();
                break;

            case 3:
                sortCustomersByName();
                break;

            case 4:
                sortCustomersByBalance();
                break;

            case 5:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while(choice != 5);
}



//==================================================
// Linear Search
//==================================================

void linearSearchCustomer()
{
    Customer customers[MAX_CUSTOMERS];

    int count = loadCustomers(customers);

    int accountNumber;
    int i;

    clearScreen();

    printf("\n========== Search Customer(Linear Search) ==========\n");

    printf("\nEnter Account Number : ");
    scanf("%d", &accountNumber);

    for(i = 0; i < count; i++)
    {
        if(customers[i].accountNumber == accountNumber)
        {
            displayCustomer(customers[i]);

            pauseScreen();
            return;
        }
    }

    printf("\nCustomer Not Found.");

    pauseScreen();
}



//==================================================
// Binary Search
//==================================================

void binarySearchCustomer()
{
    Customer customers[MAX_CUSTOMERS];

    int count = loadCustomers(customers);

    int i, j;
    Customer temp;

    // Sort by Account Number

    for(i = 0; i < count - 1; i++)
    {
        for(j = 0; j < count - i - 1; j++)
        {
            if(customers[j].accountNumber >
               customers[j + 1].accountNumber)
            {
                temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }

    int accountNumber;

    printf("\nEnter Account Number : ");
    scanf("%d",&accountNumber);

    int low = 0;
    int high = count - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(customers[mid].accountNumber == accountNumber)
        {
            displayCustomer(customers[mid]);

            pauseScreen();
            return;
        }

        if(customers[mid].accountNumber < accountNumber)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    printf("\nCustomer Not Found.");

    pauseScreen();
}



//==================================================
// Sort By Name
//==================================================

void sortCustomersByName()
{
    Customer customers[MAX_CUSTOMERS];

    int count = loadCustomers(customers);

    int i, j;

    Customer temp;

    for(i = 0; i < count - 1; i++)
    {
        for(j = 0; j < count - i - 1; j++)
        {
            if(strcmp(customers[j].name,
                      customers[j + 1].name) > 0)
            {
                temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }

    clearScreen();

    printf("\n========== Customers Sorted By Name ==========\n");

    for(i = 0; i < count; i++)
    {
        displayCustomer(customers[i]);
    }

    pauseScreen();
}



//==================================================
// Sort By Balance
//==================================================

void sortCustomersByBalance()
{
    Customer customers[MAX_CUSTOMERS];

    int count = loadCustomers(customers);

    int i, j;

    Customer temp;

    for(i = 0; i < count - 1; i++)
    {
        for(j = 0; j < count - i - 1; j++)
        {
            if(customers[j].balance <
               customers[j + 1].balance)
            {
                temp = customers[j];
                customers[j] = customers[j + 1];
                customers[j + 1] = temp;
            }
        }
    }

    clearScreen();

    printf("\n========== Customers Sorted By Balance ==========\n");

    for(i = 0; i < count; i++)
    {
        displayCustomer(customers[i]);
    }

    pauseScreen();
}