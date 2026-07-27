#ifndef BANKING_H
#define BANKING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

#define ACTIVE 1
#define FROZEN 0

// ---------------------------
// Structures
// ---------------------------

typedef struct
{
    int accountNumber;

    char name[50];
    char fatherName[50];
    char gender[10];

    int age;

    char mobile[15];
    char email[50];
    char address[100];

    char aadhaar[20];
    char pan[20];

    char accountType[20];

    int pin;

    float balance;

    int status;
    int kycVerified;

} Customer;

typedef struct
{
    int employeeId;

    char name[50];

    char designation[50];

    char mobile[15];

    char password[30];

} Employee;

typedef struct
{
    int transactionId;

    int accountNumber;

    char type[20];

    float amount;

    float balance;

    char date[20];

} Transaction;

// ---------------------------
// Global Variable
// ---------------------------

extern int currentCustomer;

// ---------------------------
// Main Menu
// ---------------------------

void adminLogin();
void adminMenu();

void employeeLogin();
void employeeMenu();

void customerLogin();
void customerMenu();

void aboutProject();

// ---------------------------
// Customer Management
// ---------------------------

void accountMenu();

void createAccount();
void viewAccounts();
void searchAccount();
void updateAccount();
void deleteAccount();

// ---------------------------
// Employee Management
// ---------------------------

void employeeManagement();

void addEmployee();
void viewEmployees();
void searchEmployee();
void updateEmployee();
void deleteEmployee();

// ---------------------------
// Transactions
// ---------------------------

void depositMoney();
void withdrawMoney();

void transferMoney();

void balanceInquiry();

void miniStatement();

void changePin();

// ---------------------------
// File Handling
// ---------------------------

void saveCustomer(Customer customer);

int totalCustomers();

int generateAccountNumber();

void displayCustomer(Customer customer);

int findCustomer(int accountNumber, Customer *customer);

void updateCustomer(Customer customer);

void saveEmployee(Employee employee);

int generateEmployeeId();

void displayEmployee(Employee employee);

void saveTransaction(
    int accountNumber,
    char type[],
    float amount,
    float balance
);

int totalTransactions();
int generateTransactionId();

void viewTransactionHistory(int accountNumber);

int findEmployee(int employeeId, Employee *employee);
void updateEmployeeRecord(Employee employee);

int totalEmployees();

// ---------------------------
// Reports
// ---------------------------

void reportsMenu();

void totalCustomersReport();

void totalEmployeesReport();

void totalBankBalance();

void activeAccountsReport();

void frozenAccountsReport();

// ---------------------------
// DSA
// ---------------------------

void dsaMenu();

void linearSearchCustomer();

void binarySearchCustomer();

void sortCustomersByName();

void sortCustomersByBalance();

void linkedListMenu();

void queueMenu();

// ---------------------------
// Utility
// ---------------------------

void clearScreen();

void pauseScreen();

void mainMenu();

#endif