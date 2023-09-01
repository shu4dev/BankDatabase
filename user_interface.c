/******************************************************************
//
//  NAME:        Chien-Hua Shu
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        Mar 24, 2023
//
//  FILE:        user_interface.c 
//
//  DESCRIPTION:
//               This is the user_interface file that interact with
                 user and do whatever user wants to do in the database
******************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"
#include "record.h"
int debugmode = 0;

/******************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   A function that will collect user
//                 address that will be used in database.
//
//  Parameters:    input (char[]): array that store the address
//                 len (int):      the length of the array 
//                 
//                 
//  Return values: N/A
******************************************************************/

void getaddress(char input[], int len)
{
    int clear;
    int i = 0;
    for (clear = 0; clear < len; clear ++)
    {
        input[clear] = '\0';
    }
    printf("\n\nWarning!! please don't type more than 50 charcters ");
    printf("otherwise it will not be record\n");
    printf("Hit enter again once done\n");
    printf("please enter the address: ");
    while (i < len)
    {
        char temp = fgetc(stdin);
        if (i == 0)
        {
            input[i] = temp;
            i++;
        }
        else
        {
            if (temp == '\n' && input[i-1] == '\n')
            {
                i = len;
            }
            else
            {
                input[i] = temp;
                i++;
            }
        }
    }
    if (debugmode == 1)
    {
        printf("\n\n\n (debug) Calliing getaddress Function\n");
        printf("getaddress has char input[] and int len\n");
        printf("getaddress store %s in the input[]", input);
    }
}

/******************************************************************
//
//  Function name: getAccountNum 
//
//  DESCRIPTION:   A function that gets the acount of the user that 
//                 will be stored in database
//
//  Parameters:    address (int*): the address where store account
//                 number 
//
//  Return values: N/A
******************************************************************/

void getAccountNum(int* address)
{
    int accountno = 0;
    int ReturnVal = 0;
    char temp[80];
    printf("Warning!! the account number must be positve\n");
    printf("and only contains number\n");
    printf("Please enter the account number: ");
    ReturnVal = scanf("%d", &accountno);
    fgets(temp, 80, stdin);
    while (ReturnVal != 1 || accountno < 0 || temp[0] != '\n')
    {
        printf("the account number must be positive and only contains numbers\n");
        printf("Please enter again: ");
        ReturnVal = scanf("%d", &accountno);
        fgets(temp, 80, stdin);
    }
    *address = accountno;
    if (debugmode == 1)
    {
        printf("\n\n\n (debug) Called getAccountNum Function\n");
        printf("getAccountNum has parameter int* address\n");
        printf("the function stores %d int the parameter int* address\n", *address);
    }
}

/******************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A function where print introduction of this program 
//                 collect all the information needed and interact with 
//                 database 
//  Parameters:    argc (int) the amount of commond 
//                 argv (char*[]) a char array of commonds
//
//  Return values: 0 success
                  -1 fail
******************************************************************/

int main(int argc, char *argv[])
{
    char name[30];
    char temp[80];
    char address[50];
    char user_input[20];
    int EndOfLoop = 1;
    int i = 0;
    int check = 0;
    int AccountNumber = 0;
    struct record *start = NULL;
    if (argc <= 2)
    {
        if (argc == 2)
        {
            if (strcmp(argv[1], "debug") == 0)
            {
                debugmode = 1;
                check = 1;
            }
        }
        else
        {
            check = 1;
        }
    }
    if (check == 1)
    {
        readfile(&start, "database.txt");
        printf("\n\nAloha, welome to Aloha bank this program is designed");
        printf("to interact with database\n\n");
        do
        {
            i = 0;
            printf("\n\n\nPlease select one of the options from the menu\n");
            printf("\nadd:      To add a new record in the database\n");
            printf("\nprintall: To print all records in the database\n");
            printf("\nfind:     Find record(s) with a specified account number\n");
            printf("\ndelete:   To delete existing record(s) from the database using");
            printf("\n          the account number as a key\n");
            printf("\nquit:     Quit the program\n");
            printf("Enter one of the option: ");
            scanf("%s", user_input);
            if (strncmp(user_input, "add", strlen(user_input)) == 0)
            {
                fgets(temp, 80, stdin);
                getAccountNum(&AccountNumber);
                printf("\nWarning!! please don't type more than 30 charcters");
                printf(" otherwise it will not be record\n");
                printf("please type your name: ");
                while (i < 50)
                {
                    char chr = fgetc(stdin);
                    if (chr  == '\n')
                    {
                        name[i] = '\0';
                        i = 50;
                    }
                    else
                    {
                        name[i] = chr;
                        i++;
                    }
                }
                getaddress(address, 50);
                addRecord(&start, AccountNumber, name, address);
                printf("\nThe record is successfully added\n");
            }
            else if (strncmp(user_input, "printall", strlen(user_input)) == 0)
            {
                fgets(temp, 80, stdin);
                printAllRecords(start);
            }
            else if (strncmp(user_input, "find", strlen(user_input)) == 0)
            {
                fgets(temp, 80, stdin);
                getAccountNum(&AccountNumber);
                findRecord(start, AccountNumber);
            }
            else if (strncmp(user_input, "delete", strlen(user_input)) == 0)
            {
                fgets(temp, 80, stdin);
                getAccountNum(&AccountNumber);
                deleteRecord(&start, AccountNumber);
            }
            else if (strncmp(user_input, "quit", strlen(user_input)) == 0)
            {
                fgets(temp, 80, stdin);
                EndOfLoop = 0;
            }
            else
            {
                printf("\noption doesn't existed, please enter a option from the menu\n");
                fgets(temp, 80, stdin);
            }
        }
        while (EndOfLoop == 1);
    }
    else
    {
        printf("Invalid commond-line argument\n");
    }
    writefile(start, "database.txt");
    cleanup(&start);
    return 0;
}
