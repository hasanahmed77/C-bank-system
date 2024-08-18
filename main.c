#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[30];
    int accountNumber;
    char password[10];
    int amount;
} Account;

Account createAccount(char name[], char passsowrd[]);

int main()
{
    Account Muhammmad = createAccount("Muhammad", "12345");

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
