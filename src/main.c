#include <stdio.h>
#include <stdlib.h>
#include "../include/customer.h"

void adminMenu()
{
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH]; 

    while (1)
    {
        printf("\n=========== Admin Menu ===========\n");
        printf("1. Register Customer\n");
        printf("2. Create Card for Customer\n");
        printf("3. List All Customers\n"); 
        printf("4. Transfer Money Between Cards\n");
        printf("5. Logout\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter surname: ");
            scanf("%s", surname);
            printf("Enter phone: ");
            scanf("%s", phone);
            registerCustomer(username, password, name, surname, phone, 0);
            break;
        case 2:
        {
            printf("Enter username of customer to create card: ");
            scanf("%s", username);
            Customer customers[MAX_CUSTOMERS];
            int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);
            Customer *customer = findCustomerByUsername(customers, numCustomers, username);

            if (customer != NULL)
            {
                double initialBalance;
                printf("Enter initial balance: ");
                scanf("%lf", &initialBalance);
                createCard(customer, initialBalance);
            }
            else
            {
                printf("Customer not found.\n");
            }
            break;
        }
        case 3:
            listAllCustomers();
            break;
         
        case 4:{
            char receiverUsername[MAX_USERNAME_LENGTH];
            char senderUsername[MAX_USERNAME_LENGTH];
            double amount;

            printf("Enter username of sender: ");
            scanf("%s", senderUsername); 


            printf("Enter username of receiver: ");
            scanf("%s", receiverUsername);
            printf("Enter amount to transfer: ");
            scanf("%lf", &amount);


               

            Customer customers[MAX_CUSTOMERS];
            int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);

            Customer *sender= findCustomerByUsername(customers, numCustomers, senderUsername);

            printCustomer(sender);

            Customer *receiver = findCustomerByUsername(customers, numCustomers, receiverUsername);

            if (receiver != NULL)
            {
                transferMoney(sender, receiver, amount);
            }
            else
            {
                printf("Receiver not found.\n");
            }
        
            break;
        }
        case 5:
            return; // Logout
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void customerMenu(Customer *customer)
{
    int choice;

    while (1)
    {
        printf("\n=========== Customer Menu ===========\n");
        printf("1. Create Card\n");
        printf("2. Transfer Money\n");
        printf("3. Logout\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            double initialBalance;
            printf("Enter initial balance: ");
            scanf("%lf", &initialBalance);
            createCard(customer, initialBalance);
            break;
        }
        case 2:
        {
            char receiverUsername[MAX_USERNAME_LENGTH];
            double amount;
            printf("Enter username of receiver: ");
            scanf("%s", receiverUsername);
            printf("Enter amount to transfer: ");
            scanf("%lf", &amount);

            Customer customers[MAX_CUSTOMERS];
            int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);
            Customer *receiver = findCustomerByUsername(customers, numCustomers, receiverUsername);

            if (receiver != NULL)
            {
                transferMoney(customer, receiver, amount);
            }
            else
            {
                printf("Receiver not found.\n");
            }
            break;
        }
        case 3:
            return; // Logout
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int main()
{
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];

    while (1)
    {
        printf("\n=====================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("=====================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter surname: ");
            scanf("%s", surname);
            printf("Enter phone: ");
            scanf("%s", phone);
            registerCustomer(username, password, name, surname, phone, 1);
            break;
        case 2:
        {
            printf("Enter username: ");
            scanf("%s", username);
            printf("Enter password: ");
            scanf("%s", password);
            Customer *loggedInCustomer = loginCustomer(username, password);
            if (loggedInCustomer != NULL)
            {
                if (loggedInCustomer->isAdmin)
                {
                    adminMenu();
                }
                else
                {
                    customerMenu(loggedInCustomer);
                }
            }
            break;
        }
        case 3:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
