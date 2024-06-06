#ifndef CUSTOMER_H
#define CUSTOMER_H

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_SURNAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define MAX_CUSTOMERS 100
#define CARD_LENGTH 16
#define MAX_CARDS 5
#define DATA_FILE "/Users/teyyub392/desktop/xazar/customers.dat"

typedef struct
{
    char cardNumber[CARD_LENGTH + 1];
    double balance;
} Card;

typedef struct
{
    int customer_id; // Unique ID for the customer
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char name[MAX_NAME_LENGTH];
    char surname[MAX_SURNAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    Card cards[MAX_CARDS];
    int cardCount; // Number of cards the customer has
    int isAdmin;
    // char cardNumber[CARD_LENGTH + 1]; // +1 for null-terminator
    // double balance;                   // Balance in the account
} Customer;

void listAllCustomers();
void generateCardNumber(char *cardNumber);
void saveCustomer(const Customer *customer);
int loadCustomers(Customer *customers, int maxCustomers);
// void registerCustomer(const char *username, const char *password);
void registerCustomer(const char *username, const char *password, const char *name, const char *surname, const char *phone, int isAdmin);
Customer *loginCustomer(const char *username, const char *password);
void transferMoney(Customer *sender, Customer *receiver, double amount);
void createCard(Customer *customer, double balance);
Customer *findCustomerByUsername(Customer *customers, int numCustomers, const char *username);
void printCustomer(const Customer *customer);
#endif // CUSTOMER_H
