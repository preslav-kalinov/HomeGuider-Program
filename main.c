#include "main.h"

int main()
{
    char option1[10];
    loadArr();

    do
    {
        printf("\t----------------------------------------------------------\n");
        printf("\tHOME-GUIDER COURSE WORK Group-36 Student #501219046\n");
        printf("\n\n\t\t1. Enter living people\n");
        printf("\t\t2. Entry fee calculation\n");
        printf("\t\t3. Elevator\n");
        printf("\t\t4. Mark apartment as empty\n");
        printf("\t\t5. Print data for an apartment\n");
        printf("\t\t6. Add people to an empty apartment\n");
        printf("\t\t7. Exit the home-guider\n");

        printf("\nEnter option: ");
        scanf("%s", option1);
        while(option1 < 1 && option1 > 7);
        system("cls");

        if(strcmp(option1, "1") == 0)
        {
            addApartment();
        }
        else if(strcmp(option1, "2") == 0)
        {
            feeCalc();
        }
        else if(strcmp(option1, "3") == 0)
        {
            elevatorSet();
        }
        else if(strcmp(option1, "4") == 0)
        {
            emptyApp();
        }
        else if(strcmp(option1, "5") == 0)
        {
            printApartment();
        }
        else if(strcmp(option1, "6") == 0)
        {
            addInEmpty();
        }
    }
    while(strcmp(option1, "7") != 0);
    free(apartmentsCount);
    free(dynArr);
    return 0;
}

void addApartment()
{
    appInfo temp;
    unsigned floor;
    printf("Please enter a floor number: ");
    scanf("%u", &floor);
    if(floor < 1 || floor > numF)
    {
        printf("Error: invalid floor number.\n");
        return;
    }
    if(apartmentsCount[floor - 1] + 1 > numA)
    {
        printf("Error: Too many apartments on the floor, please try another floor (from 1 to %d).\n", numF);
        return;
    }

    temp.appID = floor * 100 + apartmentsCount[floor - 1] + 1;
    printf("Enter number of rooms in apartment 1A%d: ", temp.appID);
    scanf("%d", &temp.nRooms);
    fflush(stdin);
    printf("Enter number of adults in apartment 1A%d: ", temp.appID);
    scanf("%d", &temp.nAdults);
    fflush(stdin);
    if(temp.nAdults > 0)
    {
        printf("Enter number of children in apartment 1A%d: ", temp.appID);
        scanf("%d", &temp.nKids);
        printf("Enter a family name in apartment 1A%d: ", temp.appID);
        scanf("%s", temp.Family);
        printf("Enter date of coming in apartment 1A%d: ", temp.appID);
        scanf("%s", temp.Date);
        printf("Enter rent amount in apartment 1A%d: ", temp.appID);
        scanf("%lf", &temp.monthRent);
        printf("\n\n");
    }
    else if(temp.nAdults <= 0)
    {
        temp.nKids = 0;
        strcpy(temp.Family, "");
        strcpy(temp.Date, "");
        temp.monthRent = 0.00;
    }

    dynArr[floor - 1][apartmentsCount[floor - 1]] = temp;
    apartmentsCount[floor - 1]++;
    writeToFile();
    controlPoint = 1;
}

void writeToFile()
{
    int i, j;
    FILE *fp;
    fp = fopen("apartments.bin", "wb");
    if(fp == NULL)
    {
        printf("Error: Can't write to file!\n");
        exit(2);
    }
    fwrite(&numF, sizeof(int), 1, fp);
    fwrite(&numA, sizeof(int), 1, fp);
    for(i = 0; i < numF; i++)
    {
        for(j = 0; j < numA; j++)
        {
            if(apartmentsCount[i] >= j + 1)
                fwrite(&dynArr[i][j], sizeof(appInfo), 1, fp);
        }
    }

    fclose(fp);
}

void loadArr()
{
    appInfo data;
    FILE *fp;
    int i, j, q;
    fp = fopen("apartments.bin", "rb");
    if(fp == NULL)
    {
        printf("Warning: Can't load the file with data!\n\n");
        printf("Please enter floors of the apartment building: ");
        scanf("%u", &numF);
        printf("Please enter number of apartments on each floor: ");
        scanf("%u", &numA);
        apartmentsCount = (int *) calloc(numF, sizeof(int));
        dynArr = (appInfo**) malloc(sizeof(appInfo*)*numF);
        if(dynArr == NULL || apartmentsCount == NULL)
        {
            printf("Error: Cannot dynamically allocate memory, exiting...\n\n");
            fclose(fp);
            free(apartmentsCount);
            free(dynArr);
            exit(1);
        }
        for(q = 0; q < numF; q++)
        {
            dynArr[q] = (appInfo*) malloc(sizeof(appInfo)*numA);
            if(dynArr[q] == NULL)
            {
                printf("Error: Cannot dynamically allocate memory, exiting...\n\n");
                fclose(fp);
                free(dynArr);
                exit(2);
            }
        }
        return;
    }
    fread(&numF, 1, sizeof(int), fp);
    fread(&numA, 1, sizeof(int), fp);
    apartmentsCount = (int *) calloc(numF, sizeof(int));
    dynArr = (appInfo**) malloc(sizeof(appInfo*)*numF);
    if(dynArr == NULL || apartmentsCount == NULL)
    {
        printf("Error: Cannot dynamically allocate memory, exiting...\n\n");
        fclose(fp);
        free(apartmentsCount);
        free(dynArr);
        exit(1);
    }
    for(q = 0; q < numF; q++)
    {
        dynArr[q] = (appInfo*) malloc(sizeof(appInfo)*numA);
        if(dynArr[q] == NULL)
        {
            printf("Error: Cannot dynamically allocate memory, exiting...\n\n");
            fclose(fp);
            free(dynArr);
            exit(2);
        }
    }
    for(i = 0; i < numF; i++)
    {
        for(j = 0; j < numA; j++)
        {
            if(fread(&data, sizeof(appInfo), 1, fp) != 1)
            {
                fclose(fp);
                break;
            }
            printf("%d\n", data.appID);
            dynArr[i][j] = data;
            apartmentsCount[i]++;
        }
    }
    controlPoint = 1;
    fclose(fp);
}

void printApartment()
{
    int appID, i, j;
    if(!controlPoint)
    {
        printf("No apartments available.\n\n");
        return;
    }

    printf("Please enter apartment ID: ");
    scanf("%d", &appID);

    for(i = 0; i < numF; i++)
    {
        for(j = 0; j < numA; j++)
        {
            if(dynArr[i][j].appID == appID)
            {
                printf("Apartment 1A%d:\n", dynArr[i][j].appID);
                printf("\tNumber of rooms: %d\n", dynArr[i][j].nRooms);
                printf("\tNumber of adults: %d\n", dynArr[i][j].nAdults);
                printf("\tNumber of kids: %d\n", dynArr[i][j].nKids);
                printf("\tFamily name: %s\n", dynArr[i][j].Family);
                printf("\tDate of coming: %s\n", dynArr[i][j].Date);
                printf("\tMonthly rent: %.2lf\n\n", dynArr[i][j].monthRent);
                return;
            }
        }
    }

    printf("Error: Apartment not found.\n");
}

void feeCalc()
{
    int appID, i, j, tax=0;

    printf("Please enter apartment ID: ");
    scanf("%d", &appID);

     for(i = 0; i < numF; i++)
    {
        for(j = 0; j < numA; j++)
        {
            if(dynArr[i][j].appID == appID)
            {
                if(i<2)
                {
                     tax = (dynArr[i][j].nAdults*3) + dynArr[i][j].nKids;
                }
                else
                    tax = (dynArr[i][j].nAdults*5) + (dynArr[i][j].nKids*3);
                if(tax>0)
                {
                    printf("Tax of the apartament %d is %d BGN \n", dynArr[i][j].appID, tax);
                    return;
                }
                else
                {
                    printf("Apartament %d is empty \n", dynArr[i][j].appID);
                    return;
                }
            }
        }
    }

    printf("Error: Apartment not found!\n");
}

void elevatorSet()
{
    int i, j;
    unsigned elevator = 0;
    int maxPeople = 0;
    int *numPeople;
    numPeople = (int *) calloc(numF, sizeof(int));
    if(numPeople == NULL)
    {
        printf("Error: Cannot dynamically allocate memory, exiting...\n\n");
        exit(3);
    }
    for(i = 0; i < numF; i++)
        for(j = 0; j < numA; j++)
            if(apartmentsCount[i] >= j + 1)
                numPeople[i] += dynArr[i][j].nAdults + dynArr[i][j].nKids;

    for(i = 2; i < numF - 1; i++)
    {
        if((numPeople[i] + numPeople[i - 1] + numPeople[i + 1]) >= maxPeople)
        {
            elevator = i + 1;
            maxPeople = numPeople[i] + numPeople[i - 1] + numPeople[i + 1];
        }
    }

    if(elevator >= 0 && elevator <= 1)
        elevator = 3;
    else if(maxPeople == 0)
        elevator = 1;
    printf("Elevator's best floor: %u\n" , elevator);
    free(numPeople);
}

void emptyApp()
{
    int appID, i, j;

    printf("Enter ID on the apartment you want to empty: ");
    scanf("%d", &appID);

    for(i = 0; i < numF; i++)
    {
        for(j = 0; j < numA; j++)
        {
            if(apartmentsCount[i] >= j + 1)

                if(dynArr[i][j].appID == appID && dynArr[i][j].nAdults!=0)
                {
                    dynArr[i][j].nAdults=0;
                    dynArr[i][j].nKids=0;
                    strcpy(dynArr[i][j].Family, "0");
                    strcpy(dynArr[i][j].Date,"00.00.0000");
                    dynArr[i][j].monthRent=0.0;

                    printf("Done!\n");
                    writeToFile();
                    return;
                }
        }
    }
    printf("Error: Apartment is already empty!\n");
}

void addInEmpty()
{
    int appID, i, j, numF1;
    printf("Enter the floor, where you want to add people: ");
    scanf("%u", &numF1);
    if(numF1>=1 && numF1<=numF)
    {
        printf("Enter the ID of the apartment: ");
        scanf("%d", &appID);

        for(i = 0; i < numF; i++)
        {
            for(j = 0; j < numA; j++)
            {
                if(dynArr[i][j].appID == appID)
                {
                    if((dynArr[i][j].nAdults)==0)
                    {
                        printf("Enter number of adults in apartment 1A%d: ", dynArr[i][j].appID);
                        scanf("%d", &dynArr[i][j].nAdults);
                        fflush(stdin);
                        if(dynArr[i][j].nAdults > 0)
                        {
                            printf("Enter number of children in apartment 1A%d: ", dynArr[i][j].appID);
                            scanf("%d", &dynArr[i][j].nKids);
                            printf("Enter a family name in apartment 1A%d: ", dynArr[i][j].appID);
                            scanf("%s", dynArr[i][j].Family);
                            printf("Enter date of coming in apartment 1A%d: ", dynArr[i][j].appID);
                            scanf("%s", dynArr[i][j].Date);
                            printf("Enter rent amount in apartment 1A%d: ", dynArr[i][j].appID);
                            scanf("%lf", &dynArr[i][j].monthRent);
                            printf("\n\n");
                        }

                            else if(dynArr[i][j].nAdults <= 0)
                            {
                                dynArr[i][j].nKids = 0;
                                strcpy(dynArr[i][j].Family, "");
                                strcpy(dynArr[i][j].Date, "");
                                dynArr[i][j].monthRent = 0.00;
                            }
                            writeToFile();
                            return;
                    }
                    else
                    {
                       printf("Apartment is not empty!\n");
                       return;
                    }
                }
            }
        }
    }
    else
    {
        printf("Error: Not an existing floor!\n");
        return;
    }
    printf("Apartment not found!\n");
    return;
}










