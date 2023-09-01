/*****************************************************************
//
//  NAME:        Chien-Hua Shu
//
//  HOMEWORK:    project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 27, 2023
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   This is the database.c file that contains all the operation
//   of database
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
extern int debugmode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   add record to database with the input from 
//                 user interface
//
//  Parameters:    start   (struct record**) : The address of the
//                                             pointer to the first
//                                             record store in the heap
//                 accnum  (int) :             The account number entered
//                                             By user
//                 name    (char[]) :          The name entered By user
//                 address (char[]) :          The address entered By user
//
//  Return values:  N/A
//
****************************************************************/

void addRecord(struct record **start, int accnum, char name[], char address[])
{
    struct record *PointerRecord;
    struct record *PrePointer;
    struct record *insertion;
    int Biggestaccno = 0;
    insertion = (struct record*) malloc(sizeof(struct record));
    PointerRecord = *start;
    PrePointer = NULL;
    if (*start != NULL)
    {
        Biggestaccno = PointerRecord->accountno;
        if (accnum <= Biggestaccno)
        {
            insertion->next = PointerRecord;
            *start = insertion;
        }
        else
        {
            while (PointerRecord->next != NULL && accnum > Biggestaccno)
            {
                PrePointer = PointerRecord;
                PointerRecord = PointerRecord->next;
                Biggestaccno = PointerRecord->accountno;
            }
            if (accnum > Biggestaccno)
            {
                PointerRecord->next = insertion;
                insertion->next = NULL;
            }
            else
            {
                insertion->next = PointerRecord;
                PrePointer->next = insertion;
            }
        }
        insertion->accountno = accnum;
        strcpy(insertion->name, name);
        strcpy(insertion->address, address);
        if (debugmode == 1)
        {
            printf("\n\n\n (debug) called addRecord function\n");
            printf("The function takes parameter struct ");
            printf("record **start, int accnum, char name[], char[]\n");
            printf("The function add a record with following value\n");
            printf("account number: %d\n", insertion->accountno);
            printf("name: %s\n", insertion->name);
            printf("the address is: %s\n", insertion->address);
            printf("the next is: %p\n", (void*) insertion->next);
        }
    }
    else
    {
        *start = malloc(sizeof(struct record));
        (*start)->accountno = accnum;
        strcpy((*start)->name, name);
        strcpy((*start)->address, address);
        (*start)->next = NULL;
        if (debugmode == 1)
        {
            printf("\n\n\n (debug) called addRecord function\n");
            printf("The function takes parameter struct record **start,");
            printf("int accnum, char name[], char[]\n");
            printf("The function add a record with following value\n");
            printf("account number: %d\n", (*start)->accountno);
            printf("name: %s\n", (*start)->name);
            printf("the address is: %s\n", (*start)->address);
            printf("the next is : %p\n", (void*) (*start)->next);
        }
    }
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   print all records that is stored in the database 
//
//  Parameters:    start   (struct record*) :  pointer to the first
//                                             record store in the heap
//
//  Return values:  N/A
//
****************************************************************/

void printAllRecords(struct record *start)
{
    int count = 0;
    struct record *PointerRecord;
    PointerRecord = start;
    while (PointerRecord != NULL)
    {
        count++;
        printf("\n\nThe account number is : %d\n", PointerRecord->accountno);
        printf("The name is : %s\n", PointerRecord->name);
        printf("The address is : %s\n", PointerRecord->address);
        PointerRecord = PointerRecord->next;
    }
    if (count == 0)
    {
        printf("NO record in the database yet\n");
    }
    if (debugmode == 1)
    {
        printf("\n\n\ncalled printAllRecords\n");
        printf("the function has parameter struct record *start\n");
        printf("the loop run %d times \n", count);
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   add record to database with the input from 
//                 user interface
//
//  Parameters:    start   (struct record*) :  pointer to the first
//                                             record store in the heap    
//                 accnum  (int) :             The account number entered
//                                             By user
//  Return values:  count (int) : the amount of records found
//                                -1 no records found
//
****************************************************************/

int findRecord(struct record *start, int accnum)
{
    int count = -1;
    struct record *PointerRecord;
    PointerRecord = start;
    if (PointerRecord == NULL)
    {
        count = -1;
    }
    else
    {
        while (PointerRecord != NULL)
        {
            if (accnum == PointerRecord->accountno)
            {
                count++;
                printf("\n\nThe account number is : %d\n", PointerRecord->accountno);
                printf("The name is : %s\n", PointerRecord->name);
                printf("The address is : %s\n", PointerRecord->address);
            }
            PointerRecord = PointerRecord->next;
        }
    }
    if (count == -1)
    {
        printf("NOT RECORD FOUND");
    }
    if (debugmode == 1)
    {
        printf("\n\n\n (debug) called findRecord function\n");
        printf("the function take parameter struct record");
        printf("*start %p and int accnum %d\n", (void*)start, accnum);
        printf("the function found %d records (no record if -1)", count);
    }
    return count;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   delete record from the database
//
//  Parameters:    start   (struct record**) : The address of the
//                                             pointer to the first
//                                             record store in the heap
//                 accnum  (int) :             The account number entered
//                                             By user
//
//  Return values:  result (int) : 0 success
//                                -1 not records deleted
****************************************************************/

int deleteRecord(struct record **start, int accnum)
{
    struct record *PointerRecord;
    struct record *PrePointer;
    int result = 0;
    int target = 0;
    int count = 0;
    PointerRecord = *start;
    PrePointer = NULL;
    if (*start != NULL)
    {
        target = PointerRecord->accountno;
        if (accnum <  target)
        {
            result = -1;
        }
        else
        {
            while (PointerRecord != NULL)
            {
                target = PointerRecord->accountno;
                if (accnum == target)
                {
                    count++;
                    if (PrePointer == NULL)
                    {
                        *start = PointerRecord->next;
                        if (debugmode == 1)
                        {
                            printf("\n\n\n (debug) delete the record with following information\n");
                            printf("account number: %d\n", PointerRecord->accountno);
                            printf("name: %s\n", PointerRecord->name);
                            printf("address: %s\n", PointerRecord->address);
                        }
                        free(PointerRecord);
                        PointerRecord = *start;
                    }
                    else if (PointerRecord->next == NULL)
                    {
                        PrePointer->next = NULL;
                        if (debugmode == 1)
                        {
                            printf("delete the record with following information\n");
                            printf("account number: %d\n", PointerRecord->accountno);
                            printf("name: %s\n", PointerRecord->name);
                            printf("address: %s\n", PointerRecord->address);
                        }
                        free(PointerRecord);
                        PointerRecord = PrePointer;
                    }
                    else
                    {
                        PrePointer->next = PointerRecord->next;
                        if (debugmode == 1)
                        {
                            printf("delete the record with following information\n");
                            printf("account number: %d\n", PointerRecord->accountno);
                            printf("name: %s\n", PointerRecord->name);
                            printf("address: %s\n", PointerRecord->address);
                        }
                        free(PointerRecord);
                        PointerRecord = PrePointer;
                    }
                    printf("\n The record is successfully deleted\n");
                }
                else
                {
                    PrePointer = PointerRecord;
                    PointerRecord = PointerRecord->next;
                }
            }
        }
    }
    else
    {
        result = -1;
    }
    if (count == 0)
    {
        printf("No record delete because the account number is not found\n");
    }
    return result;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   write all the records from database 
//                 to database.txt
//
//  Parameters:    start   (struct record*) : pointer to the first
//                                            record store in the heap                   
//                 filename (char[]) :         The file name of the file 
//                                             that the program want to write in
//  Return values:  result (int) : 0 success
//                                -1 fail
****************************************************************/

int writefile(struct record *start, char filename[])
{
    FILE *file;
    struct record *PointerRecord;
    int result;
    PointerRecord = start;
    file = fopen(filename, "w");
    fclose(file);
    file = fopen(filename, "w");
    if (file == NULL)
    {
        result = -1;
    }
    else
    {
        while (PointerRecord != NULL)
        {
            fprintf(file, "%d", PointerRecord->accountno);
            fputs("\n", file);
            fprintf(file, "%s", PointerRecord->name);
            fputs("\n", file);
            fprintf(file, "%s", PointerRecord->address);
            fputs("\n", file);
            if (debugmode == 1)
            {
                printf("\n\n\n (debug) called writefile function\n");
                printf("record with following infomation has written in the file\n");
                printf("account number: %d\n", PointerRecord->accountno);
                printf("name: %s\n", PointerRecord->name);
                printf("address: %s\n", PointerRecord->address);
            }
            PointerRecord = PointerRecord->next;
        }
        result = 0;
    }
    fclose(file);
    return result;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   read all the records from the file 
//                 to database
//
//  Parameters:    start   (struct record**) : The address of the
//                                             pointer to the first
//                                             record store in the heap
//                 filename (char[]) :         The file name the program
//                                             read from
//  Return values:  result (int) : 0 success
//                                -1 fail
****************************************************************/

int readfile(struct record **start, char filename[])
{
    FILE *file;
    struct record *PointerRecord;
    struct record *PrePointer;
    int result = 0;
    int accnum = 0;
    int i = 0;
    int ii = 0;
    char name[30];
    int ai = 0;
    char address[50];
    char temp[80];
    char ctemp;
    char chr;
    char count = 0;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        result = -1;
    }
    else
    {
        PointerRecord = malloc(sizeof(struct record));
        PointerRecord->next = NULL;
        while (fscanf(file, "%d", &accnum) != EOF)
        {
            PointerRecord->next = malloc(sizeof(struct record));
            count++;
            ai = 0;
            ii = 0;
            PointerRecord->accountno = accnum;
            accnum = 0;
            fgets(temp, 80, file);
            while (ii < 30)
            {
                chr = fgetc(file);
                if (chr == '\n')
                {
                    name[ii] = '\0';
                    ii = 30;
                }
                else
                {
                    name[ii] = chr;
                    ii++;
                }
            }
            strcpy(PointerRecord->name, name);
            while (ai < 50)
            {
                ctemp = fgetc(file);
                if (ai == 0)
                {
                    address[ai] = ctemp;
                    ai++;
                }
                else
                {
                    if (ctemp == '\n' && address[ai - 1] == '\n')
                    {
                        address[ai] = '\0';
                        ai = 50;
                    }
                    else
                    {
                        address[ai] = ctemp;
                        ai++;
                    }
                }
            }
            strcpy(PointerRecord->address, address);
            if (i == 0)
            {
                *start = PointerRecord;
                i++;
            }
            if (debugmode == 1)
            {
                printf("\n\n\n (debug) called readfile function\n");
                printf("record with following infomation has read from the file\n");
                printf("account number: %d\n", PointerRecord->accountno);
                printf("name: %s\n", PointerRecord->name);
                printf("address: %s\n", PointerRecord->address);
            }
            PrePointer = PointerRecord;
            PointerRecord = PointerRecord->next;
        }
        free(PointerRecord->next);
        if (PrePointer != NULL)
        {
            free(PrePointer->next);
            PrePointer->next = NULL;
        }
        result = 0;
        fclose(file);
    }
    return result;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   deallocate all the heap spaces that are used
//                 in this program
//
//  Parameters:    start   (struct record**) : The address of the
//                                             pointer to the first
//                                             record store in the heap
//  
//  Return values: N/A
****************************************************************/

void cleanup(struct record **start)
{
    struct record *PrePointer;
    int count = 0;
    while (*start != NULL)
    {
        count++;
        PrePointer = *start;
        *start = (*start)->next;
        free(PrePointer);
    }
    if (debugmode == 1)
    {
        printf("\n\n\n (debug) called cleanup function\n");
        printf("%d heap space are deallocated\n", count);
    }
}
