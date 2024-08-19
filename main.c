#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER 256
#define MAX_NAME 30
#define MAX_PASSWORD 10
#define THIRD_LETTER_DB 2

typedef struct
{
    char name[MAX_NAME];
    int accountNumber;
    char password[MAX_PASSWORD];
    int amount;
} Account;

Account createAccount(char name[], char passsowrd[]);
int login(int *accountNumber, int *amount, char name[], char password[]);

int main()
{
    int userInput, isLoggedIn;
    int accountNumber = 0, amount = 0;
    char name[MAX_NAME], password[MAX_PASSWORD];

    printf("Welcome to The Bank!\n");
    printf("1. Login\n2. Create an account\n");
    printf("Choose 1 or 2: ");
    scanf("%d", &userInput);

    if (userInput == 1)
    {
        isLoggedIn = login(&accountNumber, &amount, name, password);
    }
    else if (userInput == 2)
    {
        printf("Cannot create accounts yet!\n");
    }
    else
    {
        printf("Invalid input!");
    }

    if (isLoggedIn)
    {
        printf("LOGGED FROM MAIN@\n");
        printf("%s\n", name);
        printf("%d\n", amount);
        printf("%d\n", accountNumber);
    }

    return 0;
}

Account createAccount(char name[], char password[])
{
    Account account;

    strcpy(account.name, name);
    account.accountNumber = 0;
    strcpy(account.password, password);
    account.amount = 0;

    FILE *pF = fopen("db.txt", "a");

    fprintf(pF, "NAME=%s PASSWORD=%s ACCOUNT=%d, AMOUNT=%d\n", account.name, account.password, account.accountNumber, account.amount);

    fclose(pF);

    return account;
}

int login(int *accountNumber, int *amount, char name[], char password[])
{
    char buffer[MAX_BUFFER], bufferCopy[MAX_BUFFER], *token;
    char *pPasswordFromDB = NULL, *pAccountNumberFromBD = NULL, *pNamefromDB = NULL;

    printf("Account number: ");
    scanf("%d", accountNumber);

    printf("Password: ");
    scanf("%s", password);

    FILE *pF = fopen("db.txt", "r");

    while (fgets(buffer, MAX_BUFFER, pF) != NULL)
    {
        strcpy(bufferCopy, buffer);
        token = strtok(buffer, " ");

        // third letters of each word in DB are different
        while (token != NULL)
        {
            if (token[THIRD_LETTER_DB] == 'S')
                pPasswordFromDB = &token[9];
            else if (token[THIRD_LETTER_DB] == 'C')
                pAccountNumberFromBD = &token[8];
            else if (token[THIRD_LETTER_DB] == 'M')
                strcpy(name, &token[5]);
            else if (token[THIRD_LETTER_DB] == '0')
                *amount = atoi(token);

            token = strtok(NULL, " ");
        }

        if (strcmp(pPasswordFromDB, password) == 0 && atoi(pAccountNumberFromBD) == *accountNumber)
        {
            printf("logged in!\n");

            fclose(pF);

            return 1;
        }
    }

    printf("Wrong password or account number!\n");

    fclose(pF);

    return 0;
}
