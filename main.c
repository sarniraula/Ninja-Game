#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "game.h"

void displayTxt(char title[],int x, int y );
void getMenu(void);
void chooseMenu(int a);

int main(void)
{
    printScreen();
    displayTxt("title.txt", 17, TOP+4);
    Sleep(3000);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    getMenu();

    return 0;
}


void displayTxt(char title[],int x, int y )
//display text from file title[]
{
    char ch, file_name[25];
    FILE *fptr;

    if((fptr = fopen(title,"r")) == NULL )
    {
        perror("Error while opening the file.\n");
        exit(1);
    }

    int j=x;
    while( ( ch = fgetc(fptr) ) != EOF )
    {
        gotoxy(j,y);
        if (ch=='\n')
        {
            y++;
            j=x;
        }
        else
        {
          printf("%c",ch);
          j++;
        }
    }

    fclose(fptr);
}

void getMenu(void)
//Display menu item
{
    system("cls");
    printScreen();
    displayTxt("Heading.txt", 23, TOP+2);
    int x=31, y=TOP+11;
    gotoxy(x,y);
    printf("1: Single Player");
    gotoxy(x,y+=2);
    printf("2: Multi Player");
    gotoxy(x,y+=2);
    printf("3: Exit");

    int a;
    do
    {
        a=getch()-'0';
    }while(a<1 || a>3);

    chooseMenu(a);
}

void chooseMenu(int a)
//choose menu items
{
    switch(a)
    {
        case 1:
            start(1);
            break;
        case 2:
            start(2);
            break;
        case 3:
            break;
    }
}
