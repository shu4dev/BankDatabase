/*****************************************************************
//
//NAME:        Chien-Hua Shu
//
//HOMEWORK:    project1
//
//CLASS:       ICS212
//
//INSTRUCTOR:  Ravi Narayan
//
//DATE:        Mar 24, 2023
//
//FILE:        record.h
//
//DESCRIPTION: This file contains a struct that will be used as
//             the main datatype that store in the database
*****************************************************************/

struct record
{
    int            accountno;
    char           name[30];
    char           address[50];
    struct record* next;
};
