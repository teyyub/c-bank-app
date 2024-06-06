#include <stdio.h>
#include <stdlib.h>
#include "../include/customer.h"

void customerMenu(Customer *loggedInCustomer)
{
    int choice;
    while (1)
    {
        printf("\n=========== Customer Menu ===========\n");
        printf("1. Create Card\n");
        printf("2. Transfer Money\n");
        printf("3. List All Customers\n"); // New option
        printf("4. Logout\n");
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
            createCard(loggedInCustomer, initialBalance);
            break;
        }
        case 2:
        {
            char receiverUsername[MAX_USERNAME_LENGTH];
            double amount;
            printf("Enter receiver's username: ");
            scanf("%s", receiverUsername);
            printf("Enter amount to transfer: ");
            scanf("%lf", &amount);

            Customer customers[MAX_CUSTOMERS];
            int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);
            Customer *receiver = findCustomerByUsername(customers, numCustomers, receiverUsername);

            if (receiver != NULL)
            {
                transferMoney(loggedInCustomer, receiver, amount);
                saveCustomer(loggedInCustomer); // Update sender's info
                saveCustomer(receiver);         // Update receiver's info
            }
            else
            {
                printf("Receiver not found.\n");
            }
            break;
        }
        case 3: // New case
            listAllCustomers();
            break;
        case 4:
            return;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while (1) {
        printf("\n=====================\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("=====================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                registerCustomer(username, password);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                Customer* loggedInCustomer = loginCustomer(username, password);
                if (loggedInCustomer != NULL)
                {
                    customerMenu(loggedInCustomer);
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
