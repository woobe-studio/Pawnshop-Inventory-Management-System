#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

// Structure for the pawnshop database
struct DATABASE
{
    int ID;
    char NAME[20];
    char CATEGORY[20];
    char CONDITION[20];
    float PRICE;
    float UNPAID_PRICE;
    char PAWN_DATE[10];
};
struct DATABASE CURRENT_DATABASE;

// Size of the DATABASE structure
long int size = sizeof(CURRENT_DATABASE);

// Cursor coordinates
COORD coord = {0, 0};

// Set cursor position
void set_cursor_position(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord);
}

bool contains(const char *start, const char *word)
{
    return strncmp(start, word, strlen(start)) == 0;
}
FILE *file, *temporary_file;

// Function to add an item
void add_item()
{
    system("cls");
    fseek(file, 0, SEEK_END);
    char next_choice = 'T';

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter a unique ID: ");
        scanf("%d", &CURRENT_DATABASE.ID);

        printf("\nEnter the name: ");
        scanf("%s", CURRENT_DATABASE.NAME);

        printf("\nEnter the item category: ");
        scanf("%s", CURRENT_DATABASE.CATEGORY);

        printf("\nEnter the item condition: ");
        scanf("%s", CURRENT_DATABASE.CONDITION);

        printf("\nEnter the price: ");
        scanf("%f", &CURRENT_DATABASE.PRICE);

        printf("\nEnter the price when unpaid: ");
        scanf("%f", &CURRENT_DATABASE.UNPAID_PRICE);

        printf("\nEnter the pawn date (DAY\\MONTH\\YEAR): ");
        scanf("%s", CURRENT_DATABASE.PAWN_DATE);
        fwrite(&CURRENT_DATABASE, size, 1, file);

        printf("\nDo you want to add something else? (Type 'T' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}
// Function that removes an item by name
void remove_item()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'T';
    int was_once = 0;

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter the name of the item you want to remove (remember that sold items cannot be deleted!)\n");
        printf("\nEnter the name: ");
        scanf("%s", TEMP_NAME);

        temporary_file = fopen("temp.txt", "wb");
        rewind(file);

        while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
        {
            if (strcmp(CURRENT_DATABASE.NAME, TEMP_NAME) != 0)
            {
                fwrite(&CURRENT_DATABASE, size, 1, temporary_file);
            }
            else if (strcmp(CURRENT_DATABASE.NAME, TEMP_NAME) == 0)
            {
                was_once += 1;
                if (strcmp(CURRENT_DATABASE.CONDITION, "SOLD") == 0)
                {
                    printf("\nThe item cannot be deleted because it has already been sold!\n");
                    fwrite(&CURRENT_DATABASE, size, 1, temporary_file);
                }
            }
        }
        if (was_once == 0)
            printf("\nThe item with this name does not exist.\n");
        fclose(file);
        fclose(temporary_file);
        remove("data.txt");
        rename("temp.txt", "data.txt");
        file = fopen("data.txt", "rb+");

        printf("\nDo you want to remove something else? (Type 'T' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function that edits an item's parameter based on user choice
void edit_item()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'T';
    int edit_choice = -1;
    int was_once = 0;

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter the name of the item you want to edit\n");
        printf("\nEnter the name: ");
        scanf("%s", TEMP_NAME);
        printf("\n(Enter the number corresponding to what you want to edit in the item):\n");
        printf("\n\tCANCEL -> 0\n\tID -> 1\n\tNAME -> 2\n\tCATEGORY -> 3\n\tCONDITION -> 4\n\tPRICE -> 5\n\tUNPAID PRICE -> 6\n\tPAWN DATE -> 7\n");
        printf("\nEnter the number: ");
        scanf("%d", &edit_choice);
        while (edit_choice < 0 || edit_choice > 7)
        {
            printf("\nEnter a valid number: ");
            scanf("%d", &edit_choice);
        }
        if (edit_choice == 0)
            return;

        rewind(file);

        while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
        {
            if (strcmp(CURRENT_DATABASE.NAME, TEMP_NAME) == 0)
            {
                was_once += 1;
                if (edit_choice == 1)
                {
                    printf("\nEnter the new ID:");
                    scanf("%d", &CURRENT_DATABASE.ID);
                }
                else if (edit_choice == 2)
                {
                    printf("\nEnter the new name:");
                    scanf("%s", CURRENT_DATABASE.NAME);
                }
                else if (edit_choice == 3)
                {
                    printf("\nEnter the new category:");
                    scanf("%s", CURRENT_DATABASE.CATEGORY);
                }
                else if (edit_choice == 4)
                {
                    printf("\nEnter the new condition:");
                    scanf("%s", CURRENT_DATABASE.CONDITION);
                }
                else if (edit_choice == 5)
                {
                    printf("\nEnter the new price:");
                    scanf("%f", &CURRENT_DATABASE.PRICE);
                }
                else if (edit_choice == 6)
                {
                    printf("\nEnter the new unpaid price:");
                    scanf("%f", &CURRENT_DATABASE.UNPAID_PRICE);
                }
                else if (edit_choice == 7)
                {
                    printf("\nEnter the new pawn date (DAY\\MONTH\\YEAR):");
                    scanf("%s", CURRENT_DATABASE.PAWN_DATE);
                }
            }
            fwrite(&CURRENT_DATABASE, size, 1, file);
        }
        if (was_once == 0)
            printf("\nThe item with this name does not exist.\n");
        printf("\nDo you want to edit something else? (Type 'T' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function that searches for an item by name
void search_by_name()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'T';
    int was_once = 0;

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter the entire or the beginning of the item name you want to find\n");
        printf("\nEnter the name: ");
        scanf("%s", TEMP_NAME);
        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          CONDITION\t\t\t         PRICE\t\t   UNPAID PRICE\t\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
        {
            if (contains(TEMP_NAME, CURRENT_DATABASE.NAME) == 1)
            {
                was_once += 1;

                printf("\n");
                printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                printf("\n");
            }
        }
        if (was_once == 0)
            printf("\nThe item with this name does not exist.\n");
        printf("\nDo you want to search for something else? (Type 'T' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// This function searches within a price range
void search_by_price_range()
{
    system("cls");
    float _MIN = 0, _MAX = 0;
    char next_choice = 'T';
    int found_once = 0;

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter the price range for the items you want to find:\n");
        printf("\nEnter MIN: ");
        scanf("%f", &_MIN);
        while (_MIN < 0)
        {
            printf("\nEnter a valid number: ");
            scanf("%f", &_MIN);
        }
        printf("\nEnter MAX: ");
        scanf("%f", &_MAX);
        while (_MAX < 0)
        {
            printf("\nEnter a valid number: ");
            scanf("%f", &_MAX);
        }
        if (_MIN > _MAX)
        {
            int temporary = _MAX;
            _MAX = _MIN;
            _MIN = temporary;
        }
        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          CONDITION\t\t\t         PRICE\t\t   UNPAID PRICE\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
        {
            int price = CURRENT_DATABASE.PRICE;
            if (price >= _MIN && price <= _MAX)
            {
                found_once += 1;

                printf("\n");
                printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                printf("\n");
            }
        }
        if (found_once == 0)
            printf("\nNo items exist within this price range.\n");
        printf("\nDo you want to search for something else? (Type 'T' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function displays items from a given category
void display_items_from_category()
{
    system("cls");
    char next_choice = 'T';
    int edit_choice = -1;
    int was_once = 0;

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter the number of what you want to see in the category:\n");
        printf("\n\tCANCEL -> 0\n\tTOY -> 1\n\tFURNITURE -> 2\n\tDECORATION -> 3\n\tDEVICE -> 4\n\tTOOL -> 5\n");
        printf("\nEnter a number: ");
        scanf("%d", &edit_choice);
        while (edit_choice < 0 || edit_choice > 5)
        {
            printf("\nEnter a valid number: ");
            scanf("%d", &edit_choice);
        }
        if (edit_choice == 0)
            return;

        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          STATUS\t\t\t         PRICE\t\t   UNPAID PRICE\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
        {
            if (edit_choice == 1)
            {
                if (strcmp(CURRENT_DATABASE.CATEGORY, "TOY") == 0)
                {
                    was_once += 1;
                    printf("\n");
                    printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                    printf("\n");
                }
            }
            else if (edit_choice == 2)
            {
                if (strcmp(CURRENT_DATABASE.CATEGORY, "FURNITURE") == 0)
                {
                    was_once += 1;
                    printf("\n");
                    printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                    printf("\n");
                }
            }
            else if (edit_choice == 3)
            {
                if (strcmp(CURRENT_DATABASE.CATEGORY, "DECORATION") == 0)
                {
                    was_once += 1;
                    printf("\n");
                    printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                    printf("\n");
                }
            }
            else if (edit_choice == 4)
            {
                if (strcmp(CURRENT_DATABASE.CATEGORY, "DEVICE") == 0)
                {
                    was_once += 1;
                    printf("\n");
                    printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                    printf("\n");
                }
            }
            else if (edit_choice == 5)
            {
                if (strcmp(CURRENT_DATABASE.CATEGORY, "TOOL") == 0)
                {
                    was_once += 1;
                    printf("\n");
                    printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                    printf("\n");
                }
            }
        }
        if (was_once == 0)
            printf("\nTHERE IS NO ITEM IN THIS CATEGORY\n");
        printf("\nDO YOU WANT TO SEARCH STH ELSE ? (ENTER 'T' IF YES) : ");
        next_choice = getche();
        system("cls");
    }
}
// This function searches by pawn date
void search_by_pawn_date()
{
    system("cls");
    char TEMP_DATE[10];
    char next_choice = 'T';
    int found_once = 0;

    while (next_choice == 'T' || next_choice == 't')
    {
        set_cursor_position(30, 5);
        printf("\nEnter the pawn date you want to find:\n");
        printf("\nEnter pawn date: ");
        scanf("%s", TEMP_DATE);
        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          CONDITION\t\t\t         PRICE\t\t   UNPAID PRICE\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
        {

            if (contains(TEMP_DATE, CURRENT_DATABASE.PAWN_DATE) == 1)
            {
                found_once += 1;

                printf("\n");
                printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
                printf("\n");
            }
        }
        if (found_once == 0)
            printf("\nNo item with this pawn date exists.\n");
        printf("\nDo you want to search for something else? (Type 'T' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

void display_items()
{
    system("cls");
    set_cursor_position(30, 5);
    rewind(file);

    printf("\n");
    printf("===============================================================================================================================================================================================================");
    printf("\n");
    printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          CONDITION\t\t\t         PRICE\t\t   UNPAID PRICE\t\t  PAWN DATE");
    printf("\n");
    printf("===============================================================================================================================================================================================================");
    printf("\n");

    while (fread(&CURRENT_DATABASE, size, 1, file) == 1)
    {
        printf("\n");
        printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s", CURRENT_DATABASE.ID, CURRENT_DATABASE.NAME, CURRENT_DATABASE.CATEGORY, CURRENT_DATABASE.CONDITION, CURRENT_DATABASE.PRICE, CURRENT_DATABASE.UNPAID_PRICE, CURRENT_DATABASE.PAWN_DATE);
    }

    printf("\n\n\n\t");
    system("pause");
}

int main()
{
    int choice;

    file = fopen("data.txt", "rb+");

    if (file == NULL)
    {
        file = fopen("data.txt", "wb+");
        if (file == NULL)
        {
            printf("\nUnable to open the file...");
            exit(1);
        }
    }

    system("Color 8E");
    system("pause");

    while (1)
    {
        system("cls");
        set_cursor_position(30, 10);
        printf("\n1. ADD ITEM\n");
        set_cursor_position(30, 12);
        printf("\n2. EDIT ITEM\n");
        set_cursor_position(30, 14);
        printf("\n3. DISPLAY ITEMS\n");
        set_cursor_position(30, 16);
        printf("\n4. SEARCH BY NAME\n");
        set_cursor_position(30, 18);
        printf("\n5. SEARCH BY PRICE RANGE\n");
        set_cursor_position(30, 20);
        printf("\n6. SEARCH BY PAWN DATE\n");
        set_cursor_position(30, 22);
        printf("\n7. DISPLAY ITEMS BY CATEGORY\n");
        set_cursor_position(30, 24);
        printf("\n8. DELETE ITEM\n");
        set_cursor_position(30, 26);
        printf("\n9. EXIT\n");
        set_cursor_position(30, 28);
        printf("\nYOUR CHOICE...\n");
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            add_item();
            break;
        case 2:
            edit_item();
            break;
        case 3:
            display_items();
            break;
        case 4:
            search_by_name();
            break;
        case 5:
            search_by_price_range();
            break;
        case 6:
            search_by_pawn_date();
            break;
        case 7:
            display_items_from_category();
            break;
        case 8:
            remove_item();
            break;
        case 9:
            fclose(file);
            exit(0);
            break;
        default:
            printf("\nINVALID CHOICE...\n");
        }
    }
    return 0;
}
