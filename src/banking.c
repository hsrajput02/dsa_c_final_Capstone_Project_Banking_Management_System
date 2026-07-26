#include "../include/banking.h"
#include "../include/utils.h"

#define CUSTOMER_FILE "../data/customer.dat"
#define EMPLOYEE_FILE "../data/employee.dat"
#define TRANSACTION_FILE "../data/transaction.dat"



//==================================================
// Customer File Handling
//==================================================

// Save Customer

void saveCustomer(Customer customer)
{
    FILE *file;

    file = fopen(CUSTOMER_FILE, "ab");

    if (file == NULL)
    {
        printf("\nUnable to Open Customer File.\n");
        return;
    }

    fwrite(&customer, sizeof(Customer), 1, file);

    fclose(file);
}



// Total Customers

int totalCustomers()
{
    FILE *file;
    Customer customer;
    int count = 0;

    file = fopen(CUSTOMER_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&customer, sizeof(Customer), 1, file))
    {
        count++;
    }

    fclose(file);

    return count;
}



// Generate Account Number

int generateAccountNumber()
{
    return 1001 + totalCustomers();
}



// Display Customer

void displayCustomer(Customer customer)
{
    printf("\n--------------------------------------------\n");

    printf("Account Number : %d\n", customer.accountNumber);
    printf("Name           : %s\n", customer.name);
    printf("Father Name    : %s\n", customer.fatherName);
    printf("Gender         : %s\n", customer.gender);
    printf("Age            : %d\n", customer.age);
    printf("Mobile         : %s\n", customer.mobile);
    printf("Email          : %s\n", customer.email);
    printf("Address        : %s\n", customer.address);
    printf("Aadhaar        : %s\n", customer.aadhaar);
    printf("PAN            : %s\n", customer.pan);
    printf("Account Type   : %s\n", customer.accountType);
    printf("Balance        : %.2f\n", customer.balance);

    printf("Status         : ");

    if (customer.status == ACTIVE)
        printf("Active\n");
    else
        printf("Frozen\n");

    printf("KYC            : ");

    if (customer.kycVerified)
        printf("Verified\n");
    else
        printf("Pending\n");
}



// Find Customer

int findCustomer(int accountNumber, Customer *customer)
{
    FILE *file;

    file = fopen(CUSTOMER_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(customer, sizeof(Customer), 1, file))
    {
        if (customer->accountNumber == accountNumber)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}



// Update Customer

void updateCustomer(Customer customer)
{
    FILE *file;
    FILE *temp;

    Customer current;

    file = fopen(CUSTOMER_FILE, "rb");

    temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL)
    {
        printf("\nFile Error.\n");
        return;
    }

    while (fread(&current, sizeof(Customer), 1, file))
    {
        if (current.accountNumber == customer.accountNumber)
        {
            fwrite(&customer, sizeof(Customer), 1, temp);
        }
        else
        {
            fwrite(&current, sizeof(Customer), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(CUSTOMER_FILE);

    rename("temp.dat", CUSTOMER_FILE);
}

//==================================================
// Customer Management
//==================================================

// Customer Menu

void accountMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========== Customer Management ==========\n");

        printf("\n1. Create Account");
        printf("\n2. View All Accounts");
        printf("\n3. Search Account");
        printf("\n4. Update Account");
        printf("\n5. Delete Account");
        printf("\n6. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                viewAccounts();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                updateAccount();
                break;

            case 5:
                deleteAccount();
                break;

            case 6:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while (choice != 6);
}



// Create Account

void createAccount()
{
    Customer customer;

    clearScreen();

    printf("\n========== Create Account ==========\n");

    customer.accountNumber = generateAccountNumber();

    printf("Customer Name : ");
    scanf(" %[^\n]", customer.name);

    printf("Father Name : ");
    scanf(" %[^\n]", customer.fatherName);

    printf("Gender : ");
    scanf("%s", customer.gender);

    printf("Age : ");
    scanf("%d", &customer.age);

    printf("Mobile : ");
    scanf("%s", customer.mobile);

    printf("Email : ");
    scanf("%s", customer.email);

    printf("Address : ");
    scanf(" %[^\n]", customer.address);

    printf("Aadhaar : ");
    scanf("%s", customer.aadhaar);

    printf("PAN : ");
    scanf("%s", customer.pan);

    printf("Account Type (Saving/Current) : ");
    scanf("%s", customer.accountType);

    printf("Initial Deposit : ");
    scanf("%f", &customer.balance);

    printf("Set 4 Digit PIN : ");
    scanf("%d", &customer.pin);

    customer.status = ACTIVE;
    customer.kycVerified = 1;

    saveCustomer(customer);

    printf("\n--------------------------------");
    printf("\nAccount Created Successfully");
    printf("\nAccount Number : %d", customer.accountNumber);
    printf("\n--------------------------------");

    pauseScreen();
}



// View All Accounts

void viewAccounts()
{
    FILE *file;

    Customer customer;

    int found = 0;

    clearScreen();

    file = fopen(CUSTOMER_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo Customer Records Found.");
        pauseScreen();
        return;
    }

    while (fread(&customer, sizeof(Customer), 1, file))
    {
        displayCustomer(customer);
        found = 1;
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo Accounts Available.");
    }

    pauseScreen();
}



// Search Account

void searchAccount()
{
    Customer customer;

    int accountNumber;

    clearScreen();

    printf("\n========== Search Account ==========\n");

    printf("Enter Account Number : ");
    scanf("%d", &accountNumber);

    if (findCustomer(accountNumber, &customer))
    {
        displayCustomer(customer);
    }
    else
    {
        printf("\nAccount Not Found.");
    }

    pauseScreen();
}



// Update Account

void updateAccount()
{
    Customer customer;

    clearScreen();

    int accountNumber;

    printf("\n========== Update Account ==========\n");

    printf("Enter Account Number : ");
    scanf("%d", &accountNumber);

    if (!findCustomer(accountNumber, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    printf("\nLeave unchanged values by entering new data carefully.\n\n");

    printf("Mobile : ");
    scanf("%s", customer.mobile);

    printf("Email : ");
    scanf("%s", customer.email);

    printf("Address : ");
    scanf(" %[^\n]", customer.address);

    updateCustomer(customer);

    printf("\nAccount Updated Successfully.");

    pauseScreen();
}



// Delete Account

void deleteAccount()
{
    FILE *file;
    FILE *temp;

    Customer customer;

    int accountNumber;
    int found = 0;

    clearScreen();

    printf("\n========== Delete Account ==========\n");

    printf("Enter Account Number : ");
    scanf("%d", &accountNumber);

    file = fopen(CUSTOMER_FILE, "rb");
    temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL)
    {
        printf("\nFile Error.");
        pauseScreen();
        return;
    }

    while (fread(&customer, sizeof(Customer), 1, file))
    {
        if (customer.accountNumber == accountNumber)
        {
            found = 1;
        }
        else
        {
            fwrite(&customer, sizeof(Customer), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(CUSTOMER_FILE);
    rename("temp.dat", CUSTOMER_FILE);

    if (found)
    {
        printf("\nAccount Deleted Successfully.");
    }
    else
    {
        printf("\nAccount Not Found.");
    }

    pauseScreen();
}

//==================================================
// Employee File Handling
//==================================================


void employeeManagement()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========== Employee Management ==========\n");

        printf("\n1. Add Employee");
        printf("\n2. View Employees");
        printf("\n3. Search Employee");
        printf("\n4. Update Employee");
        printf("\n5. Delete Employee");
        printf("\n6. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                viewEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                updateEmployee();
                break;

            case 5:
                deleteEmployee();
                break;

            case 6:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while(choice != 6);
}

// Save Employee

void saveEmployee(Employee employee)
{
    FILE *file;

    file = fopen(EMPLOYEE_FILE, "ab");

    if (file == NULL)
    {
        printf("\nUnable to Open Employee File.\n");
        return;
    }

    fwrite(&employee, sizeof(Employee), 1, file);

    fclose(file);
}



// Total Employees

int totalEmployees()
{
    FILE *file;
    Employee employee;
    int count = 0;

    file = fopen(EMPLOYEE_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&employee, sizeof(Employee), 1, file))
    {
        count++;
    }

    fclose(file);

    return count;
}



// Generate Employee ID

int generateEmployeeId()
{
    return 2001 + totalEmployees();
}



// Display Employee

void displayEmployee(Employee employee)
{
    printf("\n---------------------------------------\n");

    printf("Employee ID : %d\n", employee.employeeId);
    printf("Name        : %s\n", employee.name);
    printf("Designation : %s\n", employee.designation);
    printf("Mobile      : %s\n", employee.mobile);
}



// Find Employee

int findEmployee(int employeeId, Employee *employee)
{
    FILE *file;

    file = fopen(EMPLOYEE_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(employee, sizeof(Employee), 1, file))
    {
        if (employee->employeeId == employeeId)
        {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    return 0;
}



// Update Employee

void updateEmployeeRecord(Employee employee)
{
    FILE *file;
    FILE *temp;

    Employee current;

    file = fopen(EMPLOYEE_FILE, "rb");
    temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL)
    {
        printf("\nFile Error.\n");
        return;
    }

    while (fread(&current, sizeof(Employee), 1, file))
    {
        if (current.employeeId == employee.employeeId)
        {
            fwrite(&employee, sizeof(Employee), 1, temp);
        }
        else
        {
            fwrite(&current, sizeof(Employee), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(EMPLOYEE_FILE);
    rename("temp.dat", EMPLOYEE_FILE);
}



//==================================================
// Employee CRUD
//==================================================

// Add Employee

void addEmployee()
{
    Employee employee;

    clearScreen();

    printf("\n========== Add Employee ==========\n");

    employee.employeeId = generateEmployeeId();

    printf("Employee Name : ");
    scanf(" %[^\n]", employee.name);

    printf("Designation : ");
    scanf(" %[^\n]", employee.designation);

    printf("Mobile : ");
    scanf("%s", employee.mobile);

    printf("Password : ");
    scanf("%s", employee.password);

    saveEmployee(employee);

    printf("\nEmployee Added Successfully.");
    printf("\nEmployee ID : %d", employee.employeeId);

    pauseScreen();
}



// View Employees

void viewEmployees()
{
    FILE *file;

    Employee employee;

    int found = 0;

    clearScreen();

    file = fopen(EMPLOYEE_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo Employee Records Found.");
        pauseScreen();
        return;
    }

    while (fread(&employee, sizeof(Employee), 1, file))
    {
        displayEmployee(employee);
        found = 1;
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo Employees Available.");
    }

    pauseScreen();
}



// Search Employee

void searchEmployee()
{
    Employee employee;

    int employeeId;

    clearScreen();

    printf("\n========== Search Employee ==========\n");

    printf("Enter Employee ID : ");
    scanf("%d", &employeeId);

    if (findEmployee(employeeId, &employee))
    {
        displayEmployee(employee);
    }
    else
    {
        printf("\nEmployee Not Found.");
    }

    pauseScreen();
}



// Update Employee

void updateEmployee()
{
    Employee employee;

    int employeeId;

    clearScreen();

    printf("\n========== Update Employee ==========\n");

    printf("Enter Employee ID : ");
    scanf("%d", &employeeId);

    if (!findEmployee(employeeId, &employee))
    {
        printf("\nEmployee Not Found.");
        pauseScreen();
        return;
    }

    printf("Name : ");
    scanf(" %[^\n]", employee.name);

    printf("Designation : ");
    scanf(" %[^\n]", employee.designation);

    printf("Mobile : ");
    scanf("%s", employee.mobile);

    printf("Password : ");
    scanf("%s", employee.password);

    updateEmployeeRecord(employee);

    printf("\nEmployee Updated Successfully.");

    pauseScreen();
}



// Delete Employee

void deleteEmployee()
{
    FILE *file;
    FILE *temp;

    Employee employee;

    int employeeId;
    int found = 0;

    clearScreen();

    printf("\n========== Delete Employee ==========\n");

    printf("Enter Employee ID : ");
    scanf("%d", &employeeId);

    file = fopen(EMPLOYEE_FILE, "rb");
    temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL)
    {
        printf("\nFile Error.");
        pauseScreen();
        return;
    }

    while (fread(&employee, sizeof(Employee), 1, file))
    {
        if (employee.employeeId == employeeId)
        {
            found = 1;
        }
        else
        {
            fwrite(&employee, sizeof(Employee), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(EMPLOYEE_FILE);
    rename("temp.dat", EMPLOYEE_FILE);

    if (found)
    {
        printf("\nEmployee Deleted Successfully.");
    }
    else
    {
        printf("\nEmployee Not Found.");
    }

    pauseScreen();
}


//==================================================
// Transaction File Handling
//==================================================

// Total Transactions

int totalTransactions()
{
    FILE *file;
    Transaction transaction;
    int count = 0;

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    while (fread(&transaction, sizeof(Transaction), 1, file))
    {
        count++;
    }

    fclose(file);

    return count;
}



// Generate Transaction ID

int generateTransactionId()
{
    return 5001 + totalTransactions();
}



// Save Transaction

void saveTransaction(int accountNumber, char type[], float amount, float balance)
{
    FILE *file;

    Transaction transaction;

    file = fopen(TRANSACTION_FILE, "ab");

    if (file == NULL)
    {
        return;
    }

    transaction.transactionId = generateTransactionId();

    transaction.accountNumber = accountNumber;

    strcpy(transaction.type, type);

    transaction.amount = amount;

    transaction.balance = balance;

    strcpy(transaction.date, __DATE__);

    fwrite(&transaction, sizeof(Transaction), 1, file);

    fclose(file);
}



// View Transaction History

void viewTransactionHistory(int accountNumber)
{
    FILE *file;

    Transaction transaction;

    int found = 0;

    file = fopen(TRANSACTION_FILE, "rb");

    if (file == NULL)
    {
        printf("\nNo Transaction History Available.\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("%-8s %-12s %-12s %-12s %-12s\n",
           "ID",
           "Type",
           "Amount",
           "Balance",
           "Date");

    printf("===============================================================\n");

    while (fread(&transaction, sizeof(Transaction), 1, file))
    {
        if (transaction.accountNumber == accountNumber)
        {
            printf("%-8d %-12s %-12.2f %-12.2f %-12s\n",
                   transaction.transactionId,
                   transaction.type,
                   transaction.amount,
                   transaction.balance,
                   transaction.date);

            found = 1;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo Transactions Found.\n");
    }
}



//==================================================
// Banking Transactions
//==================================================

// Deposit Money

void depositMoney()
{
    Customer customer;

    int accountNumber;

    float amount;

    clearScreen();

    printf("\n========== Deposit Money ==========\n");

    printf("Enter Account Number : ");
    scanf("%d", &accountNumber);

    if (!findCustomer(accountNumber, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    if (customer.status == FROZEN)
    {
        printf("\nAccount is Frozen.");
        pauseScreen();
        return;
    }

    printf("Enter Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\nInvalid Amount.");
        pauseScreen();
        return;
    }

    customer.balance += amount;

    updateCustomer(customer);

    saveTransaction(
        customer.accountNumber,
        "Deposit",
        amount,
        customer.balance
    );

    printf("\nDeposit Successful.");

    printf("\nAvailable Balance : %.2f", customer.balance);

    pauseScreen();
}



// Withdraw Money

void withdrawMoney()
{
    Customer customer;

    int accountNumber;

    float amount;

    clearScreen();

    printf("\n========== Withdraw Money ==========\n");

    printf("Enter Account Number : ");
    scanf("%d", &accountNumber);

    if (!findCustomer(accountNumber, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    if (customer.status == FROZEN)
    {
        printf("\nAccount is Frozen.");
        pauseScreen();
        return;
    }

    printf("Enter Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\nInvalid Amount.");
        pauseScreen();
        return;
    }

    if (amount > customer.balance)
    {
        printf("\nInsufficient Balance.");
        pauseScreen();
        return;
    }

    customer.balance -= amount;

    updateCustomer(customer);

    saveTransaction(
        customer.accountNumber,
        "Withdraw",
        amount,
        customer.balance
    );

    printf("\nWithdrawal Successful.");

    printf("\nAvailable Balance : %.2f", customer.balance);

    pauseScreen();
}

//==================================================
// Customer Banking Services
//==================================================

// Transfer Money

void transferMoney()
{
    Customer sender;
    Customer receiver;

    int receiverAccount;
    float amount;

    clearScreen();

    printf("\n========== Transfer Money ==========\n");

    if (!findCustomer(currentCustomer, &sender))
    {
        printf("\nCustomer Not Found.");
        pauseScreen();
        return;
    }

    if (sender.status == FROZEN)
    {
        printf("\nYour Account is Frozen.");
        pauseScreen();
        return;
    }

    printf("Receiver Account Number : ");
    scanf("%d", &receiverAccount);

    if (!findCustomer(receiverAccount, &receiver))
    {
        printf("\nReceiver Account Not Found.");
        pauseScreen();
        return;
    }

    if (receiver.status == FROZEN)
    {
        printf("\nReceiver Account is Frozen.");
        pauseScreen();
        return;
    }

    if (receiver.accountNumber == sender.accountNumber)
    {
        printf("\nCannot Transfer To Same Account.");
        pauseScreen();
        return;
    }

    printf("Enter Amount : ");
    scanf("%f", &amount);

    if (amount <= 0)
    {
        printf("\nInvalid Amount.");
        pauseScreen();
        return;
    }

    if (amount > sender.balance)
    {
        printf("\nInsufficient Balance.");
        pauseScreen();
        return;
    }

    sender.balance -= amount;
    receiver.balance += amount;

    updateCustomer(sender);
    updateCustomer(receiver);

    saveTransaction(
        sender.accountNumber,
        "Transfer",
        amount,
        sender.balance
    );

    saveTransaction(
        receiver.accountNumber,
        "Received",
        amount,
        receiver.balance
    );

    printf("\nTransfer Successful.");
    printf("\nAvailable Balance : %.2f", sender.balance);

    pauseScreen();
}



// Balance Inquiry

void balanceInquiry()
{
    Customer customer;

    clearScreen();

    if (!findCustomer(currentCustomer, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    printf("\n========== Balance Inquiry ==========\n");

    printf("\nAccount Number : %d", customer.accountNumber);
    printf("\nCustomer Name  : %s", customer.name);
    printf("\nBalance        : %.2f", customer.balance);

    pauseScreen();
}



// Change PIN

void changePin()
{
    Customer customer;

    int oldPin;
    int newPin;

    clearScreen();

    if (!findCustomer(currentCustomer, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    printf("\n========== Change PIN ==========\n");

    printf("Enter Current PIN : ");
    scanf("%d", &oldPin);

    if (oldPin != customer.pin)
    {
        printf("\nIncorrect PIN.");
        pauseScreen();
        return;
    }

    printf("Enter New PIN : ");
    scanf("%d", &newPin);

    if (newPin < 1000 || newPin > 9999)
    {
        printf("\nPIN Must Be 4 Digits.");
        pauseScreen();
        return;
    }

    if (newPin == oldPin)
    {
        printf("\nNew PIN Cannot Be Same As Current PIN.");
        pauseScreen();
        return;
    }

    customer.pin = newPin;

    updateCustomer(customer);

    printf("\nPIN Changed Successfully.");

    pauseScreen();
}



// Mini Statement

void miniStatement()
{
    Customer customer;

    clearScreen();

    if (!findCustomer(currentCustomer, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    printf("\n========== Mini Statement ==========\n");

    printf("\nAccount Number : %d", customer.accountNumber);
    printf("\nCustomer Name  : %s", customer.name);
    printf("\nCurrent Balance: %.2f\n", customer.balance);

    printf("\n-----------------------------------------------\n");

    viewTransactionHistory(currentCustomer);

    pauseScreen();
}

//==================================================
// Reports & Statistics
//==================================================

// Reports Menu

void reportsMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========== Reports ==========\n");

        printf("\n1. Total Customers");
        printf("\n2. Total Employees");
        printf("\n3. Total Bank Balance");
        printf("\n4. Active Accounts");
        printf("\n5. Frozen Accounts");
        printf("\n6. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                totalCustomersReport();
                break;

            case 2:
                totalEmployeesReport();
                break;

            case 3:
                totalBankBalance();
                break;

            case 4:
                activeAccountsReport();
                break;

            case 5:
                frozenAccountsReport();
                break;

            case 6:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while(choice != 6);
}



// Total Customers

void totalCustomersReport()
{
    clearScreen();

    printf("\n========== Total Customers ==========\n");

    printf("\nTotal Customers : %d", totalCustomers());

    pauseScreen();
}



// Total Employees

void totalEmployeesReport()
{
    clearScreen();

    printf("\n========== Total Employees ==========\n");

    printf("\nTotal Employees : %d", totalEmployees());

    pauseScreen();
}



// Total Bank Balance

void totalBankBalance()
{
    FILE *file;

    Customer customer;

    float total = 0;

    file = fopen(CUSTOMER_FILE, "rb");

    if(file == NULL)
    {
        printf("\nNo Records Found.");
        pauseScreen();
        return;
    }

    while(fread(&customer, sizeof(Customer), 1, file))
    {
        total += customer.balance;
    }

    fclose(file);

    clearScreen();

    printf("\n========== Total Bank Balance ==========\n");

    printf("\nTotal Balance : %.2f", total);

    pauseScreen();
}



// Active Accounts

void activeAccountsReport()
{
    FILE *file;

    Customer customer;

    int count = 0;

    file = fopen(CUSTOMER_FILE, "rb");

    if(file == NULL)
    {
        printf("\nNo Records Found.");
        pauseScreen();
        return;
    }

    while(fread(&customer, sizeof(Customer), 1, file))
    {
        if(customer.status == ACTIVE)
        {
            count++;
        }
    }

    fclose(file);

    clearScreen();

    printf("\n========== Active Accounts ==========\n");

    printf("\nTotal Active Accounts : %d", count);

    pauseScreen();
}



// Frozen Accounts

void frozenAccountsReport()
{
    FILE *file;

    Customer customer;

    int count = 0;

    file = fopen(CUSTOMER_FILE, "rb");

    if(file == NULL)
    {
        printf("\nNo Records Found.");
        pauseScreen();
        return;
    }

    while(fread(&customer, sizeof(Customer), 1, file))
    {
        if(customer.status == FROZEN)
        {
            count++;
        }
    }

    fclose(file);

    clearScreen();

    printf("\n========== Frozen Accounts ==========\n");

    printf("\nTotal Frozen Accounts : %d", count);

    pauseScreen();
}