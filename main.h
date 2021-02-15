#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct appInfo
{
    int appID;
    int nRooms;
    char Date[10];
    int nAdults;
    int nKids;
    char Family[60];
    double monthRent;
}appInfo;

int *apartmentsCount;

appInfo **dynArr;
unsigned controlPoint = 0;
unsigned numA = 0, numF = 0;

void loadArr();
void printApartment();
void addApartment();
void writeToFile();
void feeCalc();
void elevatorSet();
void emptyApp();
void addInEmpty();

#endif // MAIN_H_INCLUDED
