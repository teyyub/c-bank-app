#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/customer.h"

void generateCardNumber(char *cardNumber)
{
    for (int i = 0; i < CARD_LENGTH; i++)
    {
        cardNumber[i] = '0' + rand() % 10; // Generate random digit
    }
    cardNumber[CARD_LENGTH] = '\0'; // Null-terminate the string
}

void generateUniqueID(int *id)
{
    // Use current timestamp as the initial value for the ID
    *id = (int)time(NULL) % 1000000;

    // Generate random numbers to fill in the remaining digits
    for (int i = 0; i < 6; i++)
    {
        *id = (*id * 10) + rand() % 10;
    }
}

void saveCustomer(const Customer *customer)
{
    FILE *file = fopen(DATA_FILE, "a");
    if (file == NULL)
    {
        file = fopen(DATA_FILE, "wb");
        if (file == NULL)
        {
            perror("Failed to create file");
            return;
        }
    }
    fwrite(customer, sizeof(Customer), 1, file);
    fclose(file);
}

int loadCustomers(Customer *customers, int maxCustomers)
{
    FILE *file = fopen(DATA_FILE, "rb");
    if (file == NULL)
    {
        return 0; // No data file exists yet
    }

    int count = 0;
    while (fread(&customers[count], sizeof(Customer), 1, file) && count < maxCustomers)
    {
        count++;
    }
    fclose(file);
    return count;
}

// void registerCustomer(const char *username, const char *password)
// {
//     Customer customers[MAX_CUSTOMERS];
//     int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);

//     if (numCustomers >= MAX_CUSTOMERS)
//     {
//         printf("Maximum number of customers reached.\n");
//         return;
//     }

//     for (int i = 0; i < numCustomers; i++)
//     {
//         if (strcmp(customers[i].username, username) == 0)
//         {
//             printf("Username already taken.\n");
//             return;
//         }
//     }

//     Customer newCustomer;
//     generateUniqueID(&(newCustomer.customer_id));
//     printf("Enter name: ");
//     scanf("%s", newCustomer.name);
//     printf("Enter surname: ");
//     scanf("%s", newCustomer.surname);
//     printf("Enter phone: ");
//     scanf("%s", newCustomer.phone);
//     strcpy(newCustomer.username, username);
//     strcpy(newCustomer.password, password);
//     saveCustomer(&newCustomer);
//     printf("Customer registered successfully. ID: %06d\n", newCustomer.customer_id);
//     //    printf("Customer registered successfully.\n");
// }

void registerCustomer(const char *username, const char *password, const char *name, const char *surname, const char *phone, int isAdmin)
{
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);

    if (numCustomers >= MAX_CUSTOMERS)
    {
        printf("Maximum number of customers reached.\n");
        return;
    }

    for (int i = 0; i < numCustomers; i++)
    {
        if (strcmp(customers[i].username, username) == 0)
        {
            printf("Username already taken.\n");
            return;
        }
    }

    Customer newCustomer;
    newCustomer.customer_id = numCustomers + 1;
    strcpy(newCustomer.username, username);
    strcpy(newCustomer.password, password);
    strcpy(newCustomer.name, name);
    strcpy(newCustomer.surname, surname);
    strcpy(newCustomer.phone, phone);
    newCustomer.cardCount = 0; // Initially, no cards
    newCustomer.isAdmin = isAdmin;

    saveCustomer(&newCustomer);
    printf("Customer registered successfully.\n");
}

Customer *loginCustomer(const char *username, const char *password)
{
    static Customer customers[MAX_CUSTOMERS];
    int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);

    for (int i = 0; i < numCustomers; i++)
    {
        if (strcmp(customers[i].username, username) == 0 && strcmp(customers[i].password, password) == 0)
        {
            printf("Login successful.\n");
            return &customers[i];
        }
    }
    printf("Login failed. Invalid username or password.\n");
    return NULL;
}

void createCard(Customer *customer, double initialBalance)
{
    if (customer->cardCount >= MAX_CARDS)
    {
        printf("Cannot create more cards for this customer.\n");
        return;
    }

    // Generate card number
    char cardNumber[CARD_LENGTH + 1]; // +1 for null-terminator
    generateCardNumber(cardNumber);

    strcpy(customer->cards[customer->cardCount].cardNumber, cardNumber);
    customer->cards[customer->cardCount].balance = initialBalance;
    customer->cardCount++;

    // Save the updated customer information
    saveCustomer(customer);

    // Assign the card number to the customer
    // strcpy(customer->cardNumber, cardNumber);

    // // Set the initial balance
    // customer->balance = initialBalance;

    printf("Card created successfully. Card number: %s\n", cardNumber);
}

void transferMoney(Customer *sender, Customer *receiver, double amount)
{
    // Check if the sender has sufficient balance
    // if (sender->balance < amount)
    // {
    //     printf("Insufficient balance for the transfer.\n");
    //     return;
    // }

    // Deduct the amount from the sender's balance
    // sender->balance -= amount;

    // Add the amount to the receiver's balance
    // receiver->balance += amount;

    if (sender->cards[0].balance < amount)
    { // Assuming the first card is used for simplicity
        printf("Insufficient balance.\n");
        return;
    }
    sender->cards[0].balance -= amount;
    receiver->cards[0].balance += amount;

    // Save updated customer information
    saveCustomer(sender);
    saveCustomer(receiver);

    printf("Transfer successful. $%.2f transferred from %s to %s.\n", amount, sender->username, receiver->username);
}

Customer *findCustomerByUsername(Customer *customers, int numCustomers, const char *username)
{
    for (int i = 0; i < numCustomers; i++)
    {
        if (strcmp(customers[i].username, username) == 0)
        {
            return &customers[i];
        }
    }
    return NULL;
}


void listAllCustomers()
{
    Customer customers[MAX_CUSTOMERS];
    int numCustomers = loadCustomers(customers, MAX_CUSTOMERS);

    if (numCustomers == 0)
    {
        printf("No customers found.\n");
        return;
    }

    printf("\n=========== List of All Customers ===========\n");
    for (int i = 0; i < numCustomers; i++)
    {
        printf("ID: %d\n", customers[i].customer_id);
        printf("Username: %s\n", customers[i].username);
        printf("Name: %s %s\n", customers[i].name, customers[i].surname);
        printf("Phone: %s\n", customers[i].phone);
        for (int j = 0; j < customers[i].cardCount; j++)
        {
            printf("  Card Number: %s, Balance: $%.2f\n", customers[i].cards[j].cardNumber, customers[i].cards[j].balance);
        }
        printf("--------------------------------------------\n");
    }
}

void printCustomer(const Customer *customer)
{
    if (customer)
    {
        printf("\nCustomer Details:\n");
        printf("Username: %s\n", customer->username);
        printf("Name: %s %s\n", customer->name, customer->surname);
        printf("Phone: %s\n", customer->phone);
        printf("Admin: %s\n", customer->isAdmin ? "Yes" : "No");
        for (int j = 0; j < customer->cardCount; j++)
        {
            printf("Card %d: %s, Balance: %.2f\n", j + 1, customer->cards[j].cardNumber, customer->cards[j].balance);
        }
    }
    else
    {
        printf("Customer not found.\n");
    }
}