# Smart Banking Management System (SBMS)

## Overview

Smart Banking Management System (SBMS) is a console-based banking application developed in C. It allows administrators, employees, and customers to perform various banking operations using a menu-driven interface. The project stores records using binary files and demonstrates the use of Data Structures and Algorithms.

## Features

### Administrator
- Secure login
- Customer management
- Employee management
- Reports and statistics
- DSA module (Search, Sort, Linked List, Queue)

### Employee
- Secure login
- Create customer account
- Deposit money
- Withdraw money
- Search customer
- View customer records

### Customer
- Secure login
- Balance inquiry
- Deposit money
- Withdraw money
- Transfer money
- Mini statement
- Change PIN

### Reports
- Total customers
- Total employees
- Total bank balance
- Active accounts
- Frozen accounts

### DSA Concepts
- Binary Search
- Bubble Sort by Name
- Bubble Sort by Balance
- Linked List (dynamic customer record traversal)
- Queue (FIFO customer service request handling)

## Technologies Used

- Language: C
- Compiler: GCC
- File Handling: Binary Files
- Platform: Windows
- IDE: Visual Studio Code

## Project Structure

```
SBMS/
│
├──data/
|   ├── customer.dat
|   ├── employee.dat
|   └── transaction.dat
|
├── include/
│   ├── banking.h
│   └── utils.h
│
├── src/
│   ├── main.c
│   ├── admin.c
│   ├── employee.c
│   ├── customer.c
│   ├── banking.c
│   ├── dsa.c
│   └── utils.c
|
├── outputs/
|       ├── Main-Menu.png
        ├── Admin_Dashboard.png
│       ├── Customer_Dashboard.png
│       ├── Employee_Dashboard.png
│       ├── Cust_Account_Details.png
        ├── cust_management.png
│       ├── Emp_mangement.png
│       ├── Services&Request.png
│       ├── Mini_Statement.png
│       └── Reports&statics.png
|
├── ppts/
|    └──SBMS_Presentation.pptx
│
├── reports/
|    └──SBMS_Project_Report.docx
|
├── README.md
|
└──
```

## How to Compile

Open the terminal inside the `src` folder and run:

```bash
gcc main.c admin.c employee.c customer.c banking.c dsa.c utils.c -o main
```

## How to Run

```bash
./main
```

For Windows PowerShell:

```powershell
.\main.exe
```

## Modules

- Admin Module
- Employee Module
- Customer Module
- Banking Module
- Reports Module
- DSA Module
- Utility Module

## Data Structures Used

- Structures
- Arrays
- Binary File Handling
- Binary Search
- Bubble Sort
- Linked List (singly linked list of customer records)
- Queue (linked-list based FIFO queue for service requests)


## Future Enhancements

- Password encryption
- Interest calculation
- Loan management
- Online banking
- ATM services
- Database integration
- Graphical User Interface

## Developed By

Harpal Singh Lodhi

B.Tech CSE Student

Smart Banking Management System (SBMS)

Summer Training Capstone Project