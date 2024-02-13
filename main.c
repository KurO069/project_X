#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/colors.h"
#include "modules/dataStructures.h"
#include "modules/electricity.h"
#include "modules/water.h"
#include "modules/tax.h"
#include "modules/call.h"
#include "modules/userHandeling.h"
int _UID = 0;
int home()
{
    system("cls");
    struct user _user = viewDetails(_UID);
    printf(" %s ", _user._email);
    printf("\n\n");
    printf("-------------------------");
    printf(BLUE"\n 1. ENERGY METER");
    printf("\n 2. WATER WATCH");
    printf("\n 3. TAX MASTER");
    printf("\n 4. CALL TALLY"RESET);
    printf(DARK_RED"\n\n 0. EXIT "RESET);
    printf("\n-------------------------");
    char _ch;
    printf("\n\n CHOICE => ");
    _ch = getch();
    switch (_ch)
    {
    case '1':
        system("cls");
        calcElec(_UID);
        break;
    case '2':
        system("cls");
        calcWater(_UID);
        break;
    case '3':
        system("cls");
        calcTax(_UID);
        break;
    case '4':
        system("cls");
        calcCall(_UID);
        break;
    case '0':
        exit(0);

    default:
        home();
    }
    home();
}
int screen()
{
    while (_UID == 0)
    {
        system("cls");
        printf(DARK_RED"\tWELCOME TO X\n"RESET);
        printf("\n-------------------------");

        printf(GUTTER_GREY"\n 1.LOGIN"RESET);
        printf(GREEN"\n 2.SIGN UP"RESET);
        printf(DARK_RED"\n\n 0.EXIT"RESET);
        printf("\n-------------------------");

        char _ch;
        printf("\n CHOICE => ");
        _ch = getch();
        switch (_ch)
        {
        case '1':
            system("cls");
            _UID = login();
            break;
        case '2':
            system("cls");
            _UID = createUser();
            break;
        case '0':
            exit(0);
        default:
            screen();
        }
    }

    home();
}

int main()
{
    screen();
    return 0;
}