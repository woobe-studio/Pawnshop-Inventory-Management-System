#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

// Pawnshop database structure
struct DATABASE {
    int ID;
    char NAME[20];
    char CATEGORY[20];
    char STATUS[20];
    float PRICE;
    float PRICE_WHEN_UNPAID;
    char PAWN_DATE[10];
};
struct DATABASE CURRENT_DB;

// Size of DATABASE
long int size = sizeof(CURRENT_DB);

// Cursor coordinates
COORD coord = { 0, 0 };

// Setting coordinates
void set_coordinate(int x, int y)
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

FILE *file, *temp_file;

// Function to add an item
void add_item()
{
    system("cls");
    fseek(file, 0, SEEK_END);
    char next_choice = 'Y';

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter unique ID: ");
        scanf("%d", &CURRENT_DB.ID);

        printf("\nEnter name: ");
        scanf("%s", CURRENT_DB.NAME);

        printf("\nEnter item category: ");
        scanf("%s", CURRENT_DB.CATEGORY);

        printf("\nEnter item status: ");
        scanf("%s", CURRENT_DB.STATUS);

        printf("\nEnter price: ");
        scanf("%f", &CURRENT_DB.PRICE);

        printf("\nEnter price when unpaid: ");
        scanf("%f", &CURRENT_DB.PRICE_WHEN_UNPAID);

        printf("\nEnter pawn date (DAY\\MONTH\\YEAR): ");
        scanf("%s", CURRENT_DB.PAWN_DATE);
        fwrite(&CURRENT_DB, size, 1, file);

        printf("\nDo you want to add another item (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to delete an item by name
void delete_item()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'Y';
    int once = 0;

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter the name of the item you want to delete (Remember, sold items cannot be deleted!)\n");
        printf("\nEnter name: ");
        scanf("%s", TEMP_NAME);

        temp_file = fopen("temp.txt", "wb");
        rewind(file);

        while (fread(&CURRENT_DB, size, 1, file) == 1)
        {
            if (strcmp(CURRENT_DB.NAME, TEMP_NAME) != 0)
            {
                fwrite(&CURRENT_DB, size, 1, temp_file);
            }
            else if(strcmp(CURRENT_DB.NAME, TEMP_NAME) == 0)
            {
                once += 1;
                if(strcmp(CURRENT_DB.STATUS,"SOLD") == 0)
                {
                    printf("\nItem cannot be deleted because it is already sold!\n");
                    fwrite(&CURRENT_DB, size, 1, temp_file);
                }
            }
        }
        if(once == 0)
            printf("\nItem with this name does not exist\n");
        fclose(file);
        fclose(temp_file);
        remove("data.txt");
        rename("temp.txt", "data.txt");
        file = fopen("data.txt", "rb+");

        printf("\nDo you want to delete something else (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to edit an item parameter by choice
void edit_item()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'Y';
    int edit_choice =  -1;
    int once = 0;

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter the name of the item you want to edit\n");
        printf("\nEnter name: ");
        scanf("%s", TEMP_NAME);
        printf("\n(Enter the number of what you want to edit in the item)\n");
        printf("\n\n\tCANCEL -> 0\n\tID -> 1\n\tNAME -> 2\n\tCATEGORY -> 3\n\tSTATUS -> 4\n\tPRICE -> 5\n\tPRICE WHEN UNPAID -> 6\n\tPAWN DATE -> 7\n");
        printf("\nEnter the number: ");
        scanf("%d",&edit_choice);
        while(edit_choice < 0 || edit_choice > 7)
        {
            printf("\nEnter the correct number: ");
            scanf("%d",&edit_choice);
        }
        if(edit_choice == 0)
            return;

        rewind(file);

        while (fread(&CURRENT_DB, size, 1, file) == 1) {
            if (strcmp(CURRENT_DB.NAME, TEMP_NAME) == 0)
            {
                once += 1;
                if(edit_choice == 1)
                {
                    printf("\nEnter new ID:");
                    scanf("%d", &CURRENT_DB.ID);
                }
                else if(edit_choice == 2)
                {
                    printf("\nEnter new name :");
                    scanf("%s", CURRENT_DB.NAME);
                }
                else if(edit_choice == 3)
                {
                    printf("\nEnter new category :");
                    scanf("%s", CURRENT_DB.CATEGORY);
                }
                else if(edit_choice == 4)
                {
                    printf("\nEnter new status :");
                    scanf("%s", CURRENT_DB.STATUS);
                }
                else if(edit_choice == 5)
                {
                    printf("\nEnter new price :");
                    scanf("%f", &CURRENT_DB.PRICE);
                }
                else if(edit_choice == 6)
                {
                    printf("\nEnter new price when unpaid :");
                    scanf("%f", &CURRENT_DB.PRICE_WHEN_UNPAID);
                }
                else if(edit_choice == 7)
                {
                    printf("\nEnter new pawn date :");
                    scanf("%s", CURRENT_DB.PAWN_DATE);
                }
                fseek(file, -size, SEEK_CUR);
                fwrite(&CURRENT_DB, size, 1, file);
                break;
            }
        }
        if(once == 0)
            printf("\nThe item with this name did not exist so nothing could be edited\n");
        printf("\nDo you want to edit something else (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to search by name
void search_by_name()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'Y';
    int once = 0;

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter the entire or beginning of the name of the item you want to find\n");
        printf("\nEnter name: ");
        scanf("%s", TEMP_NAME);
        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          STATUS\t\t\t         PRICE\t\t   PRICE WHEN UNPAID\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DB, size, 1, file) == 1)
        {
            if(contains(TEMP_NAME,CURRENT_DB.NAME) == 1)
            {
                once += 1;

                printf("\n");
                printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s",CURRENT_DB.ID, CURRENT_DB.NAME, CURRENT_DB.CATEGORY, CURRENT_DB.STATUS, CURRENT_DB.PRICE, CURRENT_DB.PRICE_WHEN_UNPAID,CURRENT_DB.PAWN_DATE);
                printf("\n");
            }
        }
        if(once == 0)
            printf("\nThe item with this name does not exist\n");
        printf("\nDo you want to search for something else (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to search by price range
void search_by_price_range()
{
    system("cls");
    float MIN = 0, MAX = 0;
    char next_choice = 'Y';
    int once = 0;

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter the price range in which you want to find items\n");
        printf("\nEnter MIN : ");
        scanf("%f", &MIN);
        while(MIN < 0)
        {
            printf("\nEnter the correct number : ");
            scanf("%f", &MIN);
        }
        printf("\nEnter MAX : ");
        scanf("%f", &MAX);
        while(MAX < 0)
        {
            printf("\nEnter the correct number : ");
            scanf("%f", &MAX);
        }
        if(MIN > MAX)
        {
            int TEMPORARY = MAX;
            MAX = MIN;
            MAX = TEMPORARY;
        }
        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          STATUS\t\t\t         PRICE\t\t   PRICE WHEN UNPAID\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DB, size, 1, file) == 1)
        {
            if(CURRENT_DB.PRICE >= MIN && CURRENT_DB.PRICE <= MAX)
            {
                once += 1;
                printf("\n");
                printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s",CURRENT_DB.ID, CURRENT_DB.NAME, CURRENT_DB.CATEGORY, CURRENT_DB.STATUS, CURRENT_DB.PRICE, CURRENT_DB.PRICE_WHEN_UNPAID,CURRENT_DB.PAWN_DATE);
                printf("\n");
            }
        }
        if(once == 0)
            printf("\nNo item with such price range exists\n");
        printf("\nDo you want to search for something else (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to search by ID
void search_by_id()
{
    system("cls");
    int TEMP_ID;
    char next_choice = 'Y';
    int once = 0;

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter the ID of the item you want to find\n");
        printf("\nEnter ID : ");
        scanf("%d", &TEMP_ID);
        rewind(file);
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          STATUS\t\t\t         PRICE\t\t   PRICE WHEN UNPAID\t\t  PAWN DATE");
        printf("\n");
        printf("===============================================================================================================================================================================================================");
        printf("\n");
        while (fread(&CURRENT_DB, size, 1, file) == 1)
        {
            if(CURRENT_DB.ID == TEMP_ID)
            {
                once += 1;
                printf("\n");
                printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s",CURRENT_DB.ID, CURRENT_DB.NAME, CURRENT_DB.CATEGORY, CURRENT_DB.STATUS, CURRENT_DB.PRICE, CURRENT_DB.PRICE_WHEN_UNPAID,CURRENT_DB.PAWN_DATE);
                printf("\n");
            }
        }
        if(once == 0)
            printf("\nItem with this ID does not exist\n");
        printf("\nDo you want to search for something else (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to show everything in a database
void show_all()
{
    system("cls");
    int once = 0;
    rewind(file);
    printf("\n");
    printf("===============================================================================================================================================================================================================");
    printf("\n");
    printf("\t       ID\t\t\t    NAME\t\t        CATEGORY\t\t          STATUS\t\t\t         PRICE\t\t   PRICE WHEN UNPAID\t\t  PAWN DATE");
    printf("\n");
    printf("===============================================================================================================================================================================================================");
    printf("\n");
    while (fread(&CURRENT_DB, size, 1, file) == 1)
    {
        once += 1;
        printf("\n");
        printf("%16d\t\t%16s\t\t%16s\t\t%16s\t\t%14.2f\t\t%14.2f\t\t\t%16s",CURRENT_DB.ID, CURRENT_DB.NAME, CURRENT_DB.CATEGORY, CURRENT_DB.STATUS, CURRENT_DB.PRICE, CURRENT_DB.PRICE_WHEN_UNPAID,CURRENT_DB.PAWN_DATE);
        printf("\n");
    }
    if(once == 0)
        printf("\nNo item found in the database\n");
    printf("\nPress any key to return to the main menu");
    fflush(stdin);
    getch();
    system("cls");
}

// Function to make a sale
void make_sale()
{
    system("cls");
    char TEMP_NAME[20];
    char next_choice = 'Y';
    int once = 0;

    while (next_choice == 'Y' || next_choice == 'y')
    {
        set_coordinate(30, 5);
        printf("\nEnter the name of the item that has been sold.\n");
        printf("\nEnter name: ");
        scanf("%s", TEMP_NAME);
        rewind(file);
        while (fread(&CURRENT_DB, size, 1, file) == 1)
        {
            if (strcmp(CURRENT_DB.NAME, TEMP_NAME) == 0)
            {
                once += 1;
                strcpy(CURRENT_DB.STATUS, "SOLD");
                fseek(file, -size, SEEK_CUR);
                fwrite(&CURRENT_DB, size, 1, file);
                break;
            }
        }
        if(once == 0)
            printf("\nNo item found with that name\n");
        printf("\nDo you want to sell something else (Type 'Y' if yes): ");
        fflush(stdin);
        next_choice = getche();
        system("cls");
    }
}

// Function to print out database in a text file
void print_in_file()
{
    system("cls");
    char print_choice;
    file = fopen("data.txt", "rb");
    temp_file = fopen("temp.txt", "wb");

    while (fread(&CURRENT_DB, size, 1, file) == 1)
    {
        fwrite(&CURRENT_DB, size, 1, temp_file);
    }
    fclose(file);
    fclose(temp_file);
    remove("data.txt");
    rename("temp.txt", "data.txt");

    printf("\nDo you want to print everything that was in the database in a text file (Type 'Y' if yes): ");
    fflush(stdin);
    print_choice = getche();

    if(print_choice == 'Y' || print_choice == 'y')
    {
        file = fopen("data.txt", "rb+");
        printf("\nFile printing is in process. Check your file after some time\n");
    }

    printf("\nPress any key to return to the main menu\n");
    fflush(stdin);
    getch();
    system("cls");
}

int main()
{
    int choice;
    file = fopen("data.txt", "rb+");
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0)
    {
        fclose(file);
        file = fopen("data.txt", "wb+");
    }

    while (1)
    {
        set_coordinate(30, 5);
        printf("\n\n\t Project of Pawnshop\n\n");
        printf("\t1. Add an item\n\n");
        printf("\t2. Delete an item\n\n");
        printf("\t3. Edit an item\n\n");
        printf("\t4. Search by name\n\n");
        printf("\t5. Search by price range\n\n");
        printf("\t6. Search by ID\n\n");
        printf("\t7. Show all\n\n");
        printf("\t8. Make a sale\n\n");
        printf("\t9. Print database\n\n");
        printf("\t10. Exit\n\n");

        printf("\n\n\t\tEnter your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add_item();
                break;

            case 2:
                delete_item();
                break;

            case 3:
                edit_item();
                break;

            case 4:
                search_by_name();
                break;

            case 5:
                search_by_price_range();
                break;

            case 6:
                search_by_id();
                break;

            case 7:
                show_all();
                break;

            case 8:
                make_sale();
                break;

            case 9:
                print_in_file();
                break;

            case 10:
                fclose(file);
                exit(0);
                break;

            default:
                printf("\n\n\tWrong choice entered\n\n");
                break;
        }
    }
    return 0;
}
