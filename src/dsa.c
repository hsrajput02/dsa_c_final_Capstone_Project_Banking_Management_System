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

        printf("\n========== Services ==========\n");

        printf("\n1. Search Customer");
        printf("\n2. Sort By Name");
        printf("\n3. Sort By Balance");
        printf("\n4. View Customers");
        printf("\n5. Service Requests");
        printf("\n6. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                binarySearchCustomer();
                break;

            case 2:
                sortCustomersByName();
                break;

            case 3:
                sortCustomersByBalance();
                break;

            case 4:
                linkedListMenu();
                break;

            case 5:
                queueMenu();
                break;

            case 6:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while(choice != 6);
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

//==================================================
// Linked List - Customer Records
//==================================================

typedef struct CustomerNode
{
    Customer data;
    struct CustomerNode *next;
} CustomerNode;

CustomerNode* buildCustomerLinkedList(int *count)
{
    FILE *file;
    Customer customer;
    CustomerNode *head = NULL;
    CustomerNode *tail = NULL;
    CustomerNode *newNode;

    *count = 0;

    file = fopen("../data/customer.dat", "rb");

    if(file == NULL)
    {
        return NULL;
    }

    while(fread(&customer, sizeof(Customer), 1, file))
    {
        newNode = (CustomerNode *)malloc(sizeof(CustomerNode));

        if(newNode == NULL)
        {
            break;
        }

        newNode->data = customer;
        newNode->next = NULL;

        if(head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        (*count)++;
    }

    fclose(file);

    return head;
}

void freeCustomerLinkedList(CustomerNode *head)
{
    CustomerNode *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void displayCustomersLinkedList()
{
    int count = 0;
    CustomerNode *head;
    CustomerNode *current;

    clearScreen();

    printf("\n========== Customers ==========\n");

    head = buildCustomerLinkedList(&count);

    if(head == NULL)
    {
        printf("\nNo Customer Records Found.");
        pauseScreen();
        return;
    }

    current = head;

    while(current != NULL)
    {
        displayCustomer(current->data);
        current = current->next;
    }

    printf("\nTotal Customers : %d\n", count);

    freeCustomerLinkedList(head);

    pauseScreen();
}

void linkedListMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========== Linked List Module ==========\n");

        printf("\n1. View All Customers");
        printf("\n2. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                displayCustomersLinkedList();
                break;

            case 2:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while(choice != 2);
}



//==================================================
// Queue - Customer Service Requests
//==================================================

typedef struct
{
    int requestId;
    int accountNumber;
    char customerName[50];
    char requestType[50];
} ServiceRequest;

typedef struct QueueNode
{
    ServiceRequest data;
    struct QueueNode *next;
} QueueNode;

typedef struct
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

int generateRequestId()
{
    FILE *file;
    ServiceRequest request;
    int count = 0;

    file = fopen("../data/queue.dat", "rb");

    if(file == NULL)
    {
        return 5001;
    }

    while(fread(&request, sizeof(ServiceRequest), 1, file))
    {
        count++;
    }

    fclose(file);

    return 5001 + count;
}

void enqueueRequest(Queue *q, ServiceRequest request)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));

    if(newNode == NULL)
    {
        return;
    }

    newNode->data = request;
    newNode->next = NULL;

    if(q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeueRequest(Queue *q, ServiceRequest *out)
{
    QueueNode *temp;

    if(q->front == NULL)
    {
        return 0;
    }

    temp = q->front;
    *out = temp->data;

    q->front = q->front->next;

    if(q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);

    return 1;
}

void displayQueue(Queue *q)
{
    QueueNode *current = q->front;
    int found = 0;

    printf("\n--------------------------------------------------------------\n");
    printf("%-8s %-10s %-22s %-15s\n", "ReqID", "AccNo", "Name", "Request Type");
    printf("----------------------------------------------------------------\n");

    while(current != NULL)
    {
        printf("%-8d %-10d %-22s %-15s\n",
               current->data.requestId,
               current->data.accountNumber,
               current->data.customerName,
               current->data.requestType);

        current = current->next;
        found = 1;
    }

    if(!found)
    {
        printf("\nQueue is Empty.\n");
    }
}

void freeQueue(Queue *q)
{
    QueueNode *current = q->front;
    QueueNode *temp;

    while(current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }

    q->front = NULL;
    q->rear = NULL;
}

Queue loadQueue()
{
    Queue q;
    FILE *file;
    ServiceRequest request;

    q.front = NULL;
    q.rear = NULL;

    file = fopen("../data/queue.dat", "rb");

    if(file == NULL)
    {
        return q;
    }

    while(fread(&request, sizeof(ServiceRequest), 1, file))
    {
        enqueueRequest(&q, request);
    }

    fclose(file);

    return q;
}

void saveQueue(Queue *q)
{
    FILE *file;
    QueueNode *current;

    file = fopen("../data/queue.dat", "wb");

    if(file == NULL)
    {
        return;
    }

    current = q->front;

    while(current != NULL)
    {
        fwrite(&current->data, sizeof(ServiceRequest), 1, file);
        current = current->next;
    }

    fclose(file);
}

void addServiceRequest()
{
    Queue q;
    ServiceRequest request;
    Customer customer;

    clearScreen();

    printf("\n========== Add Service Request ==========\n");

    printf("\nEnter Account Number : ");
    scanf("%d", &request.accountNumber);

    if(!findCustomer(request.accountNumber, &customer))
    {
        printf("\nAccount Not Found.");
        pauseScreen();
        return;
    }

    strcpy(request.customerName, customer.name);

    printf("Enter Request Type (e.g. Cheque Book / Statement / Card) : ");
    scanf(" %49[^\n]", request.requestType);

    request.requestId = generateRequestId();

    q = loadQueue();
    enqueueRequest(&q, request);
    saveQueue(&q);
    freeQueue(&q);

    printf("\nRequest Added Successfully. Request ID : %d\n", request.requestId);

    pauseScreen();
}

void viewServiceQueue()
{
    Queue q;

    clearScreen();

    printf("\n========== Service Request ==========\n");

    q = loadQueue();
    displayQueue(&q);
    freeQueue(&q);

    pauseScreen();
}

void processServiceRequest()
{
    Queue q;
    ServiceRequest processed;

    clearScreen();

    printf("\n========== Process Next Request ==========\n");

    q = loadQueue();

    if(!dequeueRequest(&q, &processed))
    {
        printf("\nQueue is Empty. No Requests to Process.");
    }
    else
    {
        saveQueue(&q);

        printf("\nProcessed Request:\n");
        printf("Request ID    : %d\n", processed.requestId);
        printf("Account No    : %d\n", processed.accountNumber);
        printf("Customer Name : %s\n", processed.customerName);
        printf("Request Type  : %s\n", processed.requestType);
    }

    freeQueue(&q);

    pauseScreen();
}

void queueMenu()
{
    int choice;

    do
    {
        clearScreen();

        printf("\n========== Service Requests ==========\n");

        printf("\n1. Add Request");
        printf("\n2. View Requests");
        printf("\n3. Process Next Request)");
        printf("\n4. Back");

        printf("\n\nEnter Choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addServiceRequest();
                break;

            case 2:
                viewServiceQueue();
                break;

            case 3:
                processServiceRequest();
                break;

            case 4:
                break;

            default:
                printf("\nInvalid Choice.");
                pauseScreen();
        }

    } while(choice != 4);
}