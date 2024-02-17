#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR_LEN 100
#define MAX_ARR_LEN 4000
#define COLUMN_WIDTH 8

/*
AOL Project
Reynard Amadeus Joshua
2702339702

Write 4 functions:
a. Display : display function
b. SelectRow : search function
c. SortBy : mergeSort function
d. Export : xport function

*/

typedef struct
{
    char location[MAX_STR_LEN];
    char city[MAX_STR_LEN];
    long long int price;
    int room;
    int bathroom;
    int carPark;
    char type[MAX_STR_LEN];
    char furnish[MAX_STR_LEN];
} Property;

typedef enum
{
    ASCENDING,
    DESCENDING
} Order;

enum MenuOptions
{
    DISPLAY,
    SELECT,
    SORT,
    EXPORT,
    EXIT
};

Property properties[MAX_ARR_LEN];
char columns[COLUMN_WIDTH][MAX_STR_LEN];
int n = 0;

void display(int, int);

int strcasecmp(const char *s1, const char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        char c1 = tolower(*s1);
        char c2 = tolower(*s2);

        if (c1 != c2)
        {
            return c1 - c2;
        }

        s1++;
        s2++;
    }

    return tolower(*s1) - tolower(*s2);
}
int findColumnIdx(char column[])
{
    int result;
    for (int i = 0; i < COLUMN_WIDTH; i++)
    {
        if (strcmp(columns[i], column) == 0)
        {
            return i;
        }
    }
    return -1;
}

Order stringToOrder(char str[])
{
    if (strcasecmp(str, "Ascending") == 0)
    {
        return ASCENDING;
    }
    else if (strcasecmp(str, "Descending") == 0)
    {
        return DESCENDING;
    }
    else
    {
        // Handle unrecognized string
        return ASCENDING;
    }
}

void merge(int left, int mid, int right, char column[], Order order)
{
    int i = left, j = mid + 1, k = left;
    Property temp[MAX_ARR_LEN];

    int columnIdx = findColumnIdx(column);

    while (i <= mid && j <= right)
    {
        int comparisonResult;
        switch (columnIdx)
        {
        case 0:
            comparisonResult = strcmp(properties[i].location, properties[j].location);
            break;
        case 1:
            comparisonResult = strcmp(properties[i].city, properties[j].city);
            break;

        case 2:
            comparisonResult = properties[i].price - properties[j].price;
            break;

        case 3:
            comparisonResult = properties[i].room - properties[j].room;
            break;

        case 4:
            comparisonResult = properties[i].bathroom - properties[j].bathroom;
            break;

        case 5:
            comparisonResult = properties[i].carPark - properties[j].carPark;
            break;

        case 6:
            comparisonResult = strcmp(properties[i].type, properties[j].type);
            break;

        case 7:
            comparisonResult = strcmp(properties[i].furnish, properties[j].furnish);
            break;

        default:
            break;
        }
        if (order == ASCENDING)
        {
            if (comparisonResult <= 0)
            {
                temp[k++] = properties[i++];
            }
            else
            {
                temp[k++] = properties[j++];
            }
        }
        else
        {
            if (comparisonResult > 0)
            {
                temp[k++] = properties[i++];
            }
            else
            {
                temp[k++] = properties[j++];
            }
        }
    }

    while (i <= mid)
    {
        temp[k++] = properties[i++];
    }
    while (j <= right)
    {
        temp[k++] = properties[j++];
    }
    for (int i = left; i < k; i++)
    {
        properties[i] = temp[i];
    }
}

void mergeSort(int left, int right, char column[], Order Order)
{
    int mid = left + (right - left) / 2;
    if (left < right)
    {
        mergeSort(left, mid, column, Order);
        mergeSort(mid + 1, right, column, Order);
        merge(left, mid, right, column, Order);
    }
}

void search(char column[], char key[], int left, int right)
{
    int columnIdx = findColumnIdx(column);
    int leftmost = -1;
    int rightmost = -1;

    int tempLeft = left;
    int tempRight = right;
    int comparisonResult;
    // Find the leftmost occurrence
    while (tempLeft <= tempRight)
    {
        int mid = tempLeft + (tempRight - tempLeft) / 2;
        switch (columnIdx)
        {
        case 0:
            comparisonResult = strcmp(key, properties[mid].location);
            break;
        case 1:
            comparisonResult = strcmp(key, properties[mid].city);
            break;

        case 2:
            comparisonResult = atoi(key) - properties[mid].price;
            break;

        case 3:
            comparisonResult = atoi(key) - properties[mid].room;
            break;

        case 4:
            comparisonResult = atoi(key) - properties[mid].bathroom;
            break;

        case 5:
            comparisonResult = atoi(key) - properties[mid].carPark;
            break;

        case 6:
            comparisonResult = strcmp(key, properties[mid].type);
            break;

        case 7:
            comparisonResult = strcmp(key, properties[mid].furnish);
            break;

        default:
            break;
        }

        if (comparisonResult == 0)
        {
            leftmost = mid;
            tempRight = mid - 1; // Continue searching in the left subarray
        }
        else if (comparisonResult < 0)
        {
            tempRight = mid - 1;
        }
        else
        {
            tempLeft = mid + 1;
        }
    }

    // Find the rightmost occurrence
    tempLeft = left;
    tempRight = right;

    while (tempLeft <= tempRight)
    {
        int mid = tempLeft + (tempRight - tempLeft) / 2;
        switch (columnIdx)
        {
        case 0:
            comparisonResult = strcmp(key, properties[mid].location);
            break;
        case 1:
            comparisonResult = strcmp(key, properties[mid].city);
            break;

        case 2:
            comparisonResult = atoi(key) - properties[mid].price;
            break;

        case 3:
            comparisonResult = atoi(key) - properties[mid].room;
            break;

        case 4:
            comparisonResult = atoi(key) - properties[mid].bathroom;
            break;

        case 5:
            comparisonResult = atoi(key) - properties[mid].carPark;
            break;

        case 6:
            comparisonResult = strcmp(key, properties[mid].type);
            break;

        case 7:
            comparisonResult = strcmp(key, properties[mid].furnish);
            break;

        default:
            break;
        }

        if (comparisonResult == 0)
        {
            rightmost = mid;
            tempLeft = mid + 1; // Continue searching in the right subarray
        }
        else if (comparisonResult < 0)
        {
            tempRight = mid - 1;
        }
        else
        {
            tempLeft = mid + 1;
        }
    }

    // Check if the key is found at least once
    if (leftmost != -1)
    {
        display(leftmost, rightmost);
    }
    else
    {
        printf("Not Found!\n");
    }
}

void readFile()
{
    FILE *fp;
    fp = fopen("file.csv", "r");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }
    int i = 0;
    fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6], columns[7]);
    while (fscanf(fp, "%[^,],%[^,],%lld,%d,%d,%d,%[^,],%[^\n]\n", properties[i].location, properties[i].city, &properties[i].price, &properties[i].room, &properties[i].bathroom, &properties[i].carPark, properties[i].type, properties[i].furnish) == 8)
    {
        i++;
    }
    n = i;
    fclose(fp);
}
void display(int initialIndex, int finalIndex)
{
    for (int i = 0; i < 101; i++)
    {

        printf("-");
    }
    puts("");

    printf("|%-20s|%-20s|%-10s|%-5s|%-9s|%-8s|%-9s|%-11s|\n", columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6], columns[7]);
    for (int i = 0; i < 101; i++)
    {
        if (i == 0 || i == 21 || i == 42 || i == 53 || i == 59 || i == 69 || i == 78 || i == 88 || i == 100)
        {
            printf("|");
        }
        else
        {
            printf("-");
        }
    }
    puts("");

    for (int i = initialIndex; i <= finalIndex; i++)
    {
        printf("|%-20s|%-20s|%-10lld|%-5d|%-9d|%-8d|%-9s|%-11s|\n", properties[i].location, properties[i].city, properties[i].price, properties[i].room, properties[i].bathroom, properties[i].carPark, properties[i].type, properties[i].furnish);
    }
    for (int i = 0; i < 101; i++)
    {
        printf("-");
    }
    puts("");
}
void xport(char fileName[])
{
    int length = strlen(fileName);
    if (length >= 4 && strcmp(fileName + length - 4, ".csv") == 0)
    {
        // String already ends with ".csv", no need to concatenate
    }
    else
    {
        // Concatenate ".csv" to the string
        strcat(fileName, ".csv");
    }
    FILE *fp;
    fp = fopen(fileName, "w");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s,%s,%s\n", columns[0], columns[1], columns[2], columns[3], columns[4], columns[5], columns[6], columns[7]);
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%s,%s,%lld,%d,%d,%d,%s,%s\n", properties[i].location, properties[i].city, properties[i].price, properties[i].room, properties[i].bathroom, properties[i].carPark, properties[i].type, properties[i].furnish);
    }
    fclose(fp);
    printf("Data successfully written to file %s!\n", fileName);
}

// Menu related functions
void displayMenu()
{
    puts("What do you want to do?");
    puts("1. Display Data");
    puts("2. Search Data");
    puts("3. Sort Data");
    puts("4. Export Data");
    puts("5. Exit");
}

enum MenuOptions getValidChoice()
{
    int userInput;
    while (1)
    {
        printf("Enter your choice (1-5): ");
        if (scanf("%d", &userInput) != 1)
        {
            // Invalid input, clear the input buffer
            while (getchar() != '\n')
                ;
            printf("Invalid input. Please enter a number between 1 and 5.\n");
        }
        else if (userInput < 1 || userInput > 5)
        {
            // Input out of range
            printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
        else
        {
            // Valid input, break out of the loop
            break;
        }
    }
    return (enum MenuOptions)(userInput - 1); // Map user input to enum
}

int main(int argc, char const *argv[])
{
    readFile();

    char input[MAX_STR_LEN];
    enum MenuOptions choice;

    do
    {
        // Display menu
        displayMenu();
        // Get user input
        choice = getValidChoice();
        system("cls");
        // Process the chosen option
        switch (choice)
        {
        case DISPLAY:
            // Display
            int rows;
            printf("Number of rows to be displayed:");
            scanf("%d", &rows);
            getchar();
            if (rows > n)
            {
                rows = n;
            }

            display(0, rows - 1);
            puts("\n");
            system("pause");
            break;
        case SELECT:
            // Search
            char column[MAX_STR_LEN], target[MAX_STR_LEN];
            printf("Choose Column[Location 1/Location 2/Price/Rooms/Bathrooms/CarParks/Type/Furnish]:");
            scanf("%[^\n]", column);
            getchar();
            printf("What data do you want to find:");
            scanf("%[^\n]", target);
            getchar();

            mergeSort(0, n - 1, column, ASCENDING);
            search(column, target, 0, n - 1);
            system("pause");
            break;
        case SORT:
            // Sortby
            char orderStr[MAX_STR_LEN];
            Order order;
            printf("Enter column name to sort by[Location 1/Location 2/Price/Rooms/Bathrooms/CarParks/Type/Furnish]:");
            scanf("%[^\n]", column);
            getchar();
            printf("Order by[Ascending/Descending]:");
            scanf("%[^\n]", orderStr);
            getchar();
            order = stringToOrder(orderStr);
            mergeSort(0, n - 1, column, order);
            display(0, 9);
            puts("\n");
            system("pause");
            break;
        case EXPORT:
            // Export
            printf("File name: ");
            char fileName[MAX_STR_LEN];
            scanf("%[^\n]", fileName);
            getchar();
            xport(fileName);
            system("pause");
            break;
        default:
            break;
        }
        system("cls");
    } while (choice != 5);

    return 0;
}
