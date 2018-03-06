#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#endif // GAME_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "getInput.h"

#define PI 3.14159265359
#define SCREENX 73 //width of screen
#define SCREENY 20 //height of screen
#define TOP 4 //top spacing
#define LEFT 3 //left spacing

/*-------function prototypes------*/
void start(int player);
void town(void);
int building(int x, int index);
void charPosition(int *x, int *y, int player);
void printLife(int hit, int player, char name[]);
void details(char p1[], char p2[]);
void gotoxy(int x, int y);
void request(float *ang, float *vel, int player);
void calcAngVel(float *ang, float *vel);
void calcAngVel(float *ang, float *vel);
void message(char text[], int x, int y);
float toRad(float deg);
float height(float vel, float ang, float dist);
void printScreen(void);
void printChar1(int x, int y);
void printChar2(int x, int y);
int star(int charX, int charY, float ang, float vel, int player, int char2X, int char2Y);
void clearStar(int charX, int charY, float ang, float vel, int player);
/*--------------------------------*/

//Global variables
int charHeight=6;
int charWidth=5;

float g=9.8; //value of acceleration due to gravity
int totalLife=3;

float len; //total length in meter equivalent of SCREENX
float unit; //length equivalent to one character

int bHeight[6]; //array of height of buildings
int bWidth=12; //width of buildings

int tmpAng=0, tmpVel=0;

void start(int player)
//start of game
//If single player, player=1. Else 2.
{
    system("cls");
    float ang, vel; //angle and velocity for projectile
    float ang2=0, vel2=0;

    printScreen();
    char p1[10], p2[10]; //names of players
    int n;
    details(p1, p2);

    int hit1=0,hit2=0;
    int turn=0;
    while(hit1<totalLife && hit2<totalLife)
    {
        srand(time(0));
        len = 250+rand()%300;

        system("cls");
        printScreen();
        town();

        int x1,y1;
        charPosition(&x1,&y1,1);
        printChar1(x1,y1);

        int x2,y2;
        charPosition(&x2,&y2,2);
        printChar2(x2,y2);

        printLife(hit1, 1, p1);
        printLife(hit2, 2, p2);
        vel2=0, ang2=0;

        int index=0;
        int tmp=turn;
        while (index==0){
            if (turn%2==0){
                request(&ang, &vel, 1);
                int result=star(x1,y1,ang, vel,1, x2, y2);
                clearStar(x1,y1,ang, vel,1);
                turn++;
                if (result==1){
                    message("Exact Hit", SCREENX/2, 2);
                    ++hit2;
                    ++index;
                    continue;
                }
            } else {
                if (player==2)
                    request(&ang, &vel, 2);
                else
                {
                     calcAngVel(&ang2, &vel2);
                     ang=ang2; vel=vel2;
                }

                int result=star(x2,y2,ang, vel,2, x1, y1);
                clearStar(x2,y2,ang, vel,2);
                turn++;
                if (result==1){
                    message("Exact Hit", SCREENX/2, 2);
                    ++hit1;
                    ++index;
                }
            }
            if (turn>=(tmp+10)){
                message("Draw", SCREENX/2, 2);
                break;
            }
        }
    }
    printLife(hit1, 1, p1);
    printLife(hit2, 2, p2);

    if (hit2>hit1){
        gotoxy(SCREENX/2, SCREENY/2);
        printf("Congratultion");
        gotoxy(SCREENX/2, SCREENY/2+1);
        printf("Ninja %s wins", p1);
        write(p1, p2, 1, hit1, hit2, totalLife);
    } else {
        gotoxy(SCREENX/2, SCREENY/2);
        printf("Congratultion");
        gotoxy(SCREENX/2, SCREENY/2+1);
        printf("Ninja %s wins", p2);
        write(p1, p2, 2, hit1, hit2, totalLife);
    }

    gotoxy(SCREENX/2,2);
    printf("Replay? (y/n)");
    char a;
    do
    {
        a=getch();
    } while (a!='y' && a!='n');
    if (a=='y')
        getMenu();
    else
        ;
}
void town(void)
{
    int x,i;
    srand(time(0));
    for (x=(LEFT+1), i=0; x<(LEFT+SCREENX); x+=bWidth, i++)
        bHeight[i]=building(x,i); //print building and save its height in array h
}

int building(int x, int index)
//Print building with random height
{
    int height=rand()%10+3;//randomly generated height

    //limiting height of first and last building to less than 8
    if (index==0 || index==5)
        height>8?(height-=(height%8)):height;

    //limiting height of second and second last building to less than 10
    if (index==1 || index==4)
        height>10?(height-=(height%10)):height;

    int i,j;
    int y=TOP+SCREENY-height;

    gotoxy(x,y);
    printf("%c", 201);
    for (i=1;i<bWidth-1;i++){
        gotoxy(x+i,y);
        printf("=");
    }
    gotoxy(x+bWidth-1,y);
    printf("%c\n",187);

    for (i=x+1;i<x+bWidth-1;i++){
        if (i%2==0){
            gotoxy(i, y+1);
            printf("%c", 222);
            gotoxy(i, y+2);
            printf("%c", 222);
        }
        gotoxy(i,y+3);
        printf("%c", 196);
    }

    for (j=1;j<height;j++){
        gotoxy(x,y+j);
        printf("%c",186);
        gotoxy(x+bWidth-1,y+j);
        printf("%c",186);
    }
    return height;
}

void charPosition(int *x, int *y, int player)
{
    srand(time(0));
    if (player==1)
        *x=LEFT+1+(rand()%2)*bWidth+rand()%6;
    else
        *x=LEFT+SCREENX-(rand()%2)*bWidth-rand()%6-6;

    int j;
    if ((float)*x/bWidth!=(int)*x/bWidth)
        j=(*x/bWidth);
    else
        j=(*x/bWidth)-1;

    *y=TOP+SCREENY-charHeight-bHeight[j];
}


void printLife(int hit, int player, char name[])
{
    int x;
    (player==1)?(x=LEFT+1):(x=LEFT+SCREENX-15);
    gotoxy(x,1);
    printf("Ninja %s", name);
    gotoxy(x,2);
    printf("Life : %3d", totalLife-hit);
}

void details(char p1[], char p2[])
{
    int x= SCREENX/2-8, j=2;

    gotoxy(x, TOP+j);
    printf("Enter player's name");
    gotoxy(x, TOP+(++j));
    printf("-------------------");

    gotoxy(x, TOP+(j+=2));
    printf("Player 1 : ");
    charWord(p1);

    gotoxy(x, TOP+(++j));
    printf("Player 2 : ");
    charWord(p2);

    gotoxy(x-=4, TOP+(j+=3));
    printf("How much do you want to play?!");
    gotoxy(x, TOP+(++j));
    printf("------------------------------");
    gotoxy(x+5, TOP+(++j));
    printf("Number of lives : ");
    totalLife = intNum(1,1);

    gotoxy(x-=1, TOP+(j+=3));
    printf("Get Ready to play the NINJA GAME");
    gotoxy(x, TOP+(++j));
    printf("--------------------------------");

    j++;
    int i;
    for (i=3; i>0; i--){
        gotoxy(x+15, TOP+j);
        printf("\a%d", i);
        Sleep(1000);
        FlushConsoleInputBuffer( GetStdHandle( STD_INPUT_HANDLE ) );
        gotoxy(x+15, TOP+j);
        printf(" ");
    }
}

void gotoxy(int x, int y)
//Set cursor position to x,y
{
    COORD coord={0,0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void request(float *ang, float *vel, int player)
/*player= 1 or 2*/
{
    int x;
    if (player==1){
        x=LEFT+2;
    }else{
        x=LEFT+SCREENX-16;
    }

    float deg;
    gotoxy(x, TOP+1);
    printf("Angle: ");
    deg=floatNum(2,10);
    (player==1)?(*ang= toRad(deg)):(*ang=PI-toRad(deg));

    gotoxy(x, TOP+2);
    printf("Velocity: ");
    *vel=floatNum(3,10);

    gotoxy(x+strlen("Angle: "), TOP+1);
    printf("      ");
    gotoxy(x+strlen("Velocity: "), TOP+2);
    printf("      ");

}

void calcAngVel(float *ang, float *vel)
{
    int x=LEFT+SCREENX-16;

    static float deg;

    gotoxy(x, TOP+1);
    printf("Angle: ");
    Sleep(rand()%3*1000+rand()%10*100);

    srand(time(0));
    if (*ang==0)
        deg=rand()%10+30;
    else if (tmpAng>0)
        deg+=(5+rand()%3);
    else if (tmpAng<0)
        deg-=(5+rand()%3);
    else;

    printf("%3.2f", deg);
    *ang=PI-toRad(deg);

    gotoxy(x, TOP+2);
    printf("Velocity: ");
    Sleep(rand()%3*1000+rand()%10*100);

    if (*vel==0)
        *vel=rand()%10+35;
    else if (tmpVel>0)
        *vel+=((5+rand()%3))*tmpVel;
    else if (tmpVel<0)
        *vel-=((5+rand()%3)*tmpVel);
    else;

    printf("%3.2f", *vel);
    Sleep(1000);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

    gotoxy(x+strlen("Angle: "), TOP+1);
    printf("      ");
    gotoxy(x+strlen("Velocity: "), TOP+2);
    printf("      ");
}

void message(char text[], int x, int y)//text and display position
{
    gotoxy(x,y);
    printf("%s", text);
    Sleep(3000);
    FlushConsoleInputBuffer( GetStdHandle( STD_INPUT_HANDLE ) );
    gotoxy(x,y);
    int i;
    for (i=0;i<strlen(text);i++)
        printf(" ");
}

float toRad(float deg)
//convert deg into radian
{
    float rad = (deg*PI)/180;
    return rad;
}

float height(float vel, float ang, float dist)
//claculate height of projectile
{
    float h=(float) dist*tan(ang)-(g*pow(dist, 2))/(2*pow(vel, 2)*pow(cos(ang),2));
    return h;
}

void printScreen(void)
{
    int i,j;
    char chSide=179, chTop=196;

    for (i=LEFT+1; i<LEFT+SCREENX;i++){
        gotoxy(i,TOP-1);
        printf("%c", chTop);
    }
    for (i=LEFT+1; i<LEFT+SCREENX;i++){
        gotoxy(i,TOP+SCREENY);
        printf("%c", chTop);
    }
    for (j=TOP; j<TOP+SCREENY; j++){
        gotoxy(LEFT, j);
        printf("%c", chSide);
    }
    for (j=TOP; j<TOP+SCREENY; j++){
        gotoxy(LEFT+SCREENX, j);
        printf("%c", chSide);
    }
}

void printChar1(int x, int y)
{
    gotoxy(x+1,y++);
    printf("__");
    gotoxy(x,y++);
    printf("|@@");
    gotoxy(x,y++);
    printf("|_-)");
    gotoxy(x,y++);
    printf("|\\\\|\\");
    gotoxy(x,y++);
    printf("| \\|");
    gotoxy(x,y);
    printf("|m|m");
}

void printChar2(int x, int y)
{
    gotoxy(x+2,y++);
    printf("__");
    gotoxy(x+2,y++);
    printf("@@|");
    gotoxy(x+1,y++);
    printf("<-_)");
    gotoxy(x,y++);
    printf("/|  |");
    gotoxy(x+1,y++);
    printf("|  |");
    gotoxy(x+1,y);
    printf("m|m|");
}

int star(int charX, int charY, float ang, float vel, int player, int char2X, int char2Y)
{
    int starBegin, starEnd;
    if (player==1){
        starBegin=charX+charWidth;//5=>char width +1
        starEnd=LEFT+SCREENX-1;
    } else {
        starBegin=charX-1;
        starEnd=LEFT+1;
    }

    unit=len/SCREENX;
    int x,y,y1;
    float h, h1;

    for (x=starBegin; (player==1)?(x<starEnd):(x>starEnd);)
    {
        tmpAng=0;
        h = height(vel, ang, (float) (x-charX)*unit);
        y = (charY+3)-roundf(h/unit);

        if (y<=TOP||y>=TOP+SCREENY){
            message("Target Missed", (SCREENX/2),2);
            if (player==2 && y<=TOP)
                tmpAng=-1;
            return 0;
            break;
        } else if (y>=(TOP+SCREENY-bHeight[x/bWidth])){
            message("Target Missed", (SCREENX/2),2);
            return 0;
            break;
        }


        int index=0,j=1;
        float dist;
        do{
            (player==1)?(dist=x-charX+j):(dist=x-charX-j);
            h1 = height(vel, ang, (float) dist*unit);
            y1 = (charY+3)-roundf(h1/unit);
            index+=1;
            j++;
        }while(y==y1 && j<60);

        dist=x-charX-j;
        h1 = height(vel, ang, (float) dist*unit);
        y1 = (charY+3)-roundf(h1/unit);

        if (tmpAng>=0)
        {
            if (x<char2X)
                tmpVel=-1;
            else if (x>(char2X+(char2Y-char2X)/2))
                tmpVel=3;
            else if (x>(char2X+(char2Y-char2X)/3))
                tmpVel=2;
            else if (x>(char2X))
                tmpVel=1;
        } else {
            tmpVel=0;
        }


        if (player==2 && y>=(TOP+SCREENY-bHeight[x/bWidth]))
        {
            if (y1>y)
                tmpAng=1;
            else
                tmpAng=0;
        }


        if (player==1)
            x+=index/2;
        else
            x-=index/2;

        gotoxy(x,y);
        printf("*");
        Sleep(150);
        gotoxy(x,y);
        printf(".");

        if (x<=(char2X+charWidth) && x>=char2X){
            if (y<=(char2Y+charHeight) && y>=char2Y){
                return 1;
                break;
            }
        }

        if (index==1){
            if (player==1)
                x++;
            else
                x--;
        } else {
            if (player==1)
                x+=index/2;
            else
                x-=index/2;
        }
    }
}

void clearStar(int charX, int charY, float ang, float vel, int player)
{
    int starBegin, starEnd;
    if (player==1){
        starBegin=charX+charWidth;//4=>char width +1
        starEnd=LEFT+SCREENX-1;
    } else {
        starBegin=charX-1;
        starEnd=LEFT+1;
    }

    unit=len/SCREENX;
    int x,y;
    float h;

    for (x=starBegin; (player==1)?(x<starEnd):(x>starEnd);)
    {
        h = height(vel, ang, (float) (x-charX)*unit);
        y = (charY+3)-roundf(h/unit);

        if (y<=TOP||y>=TOP+SCREENY){
            break;
        } else if (y>=(TOP+SCREENY-bHeight[x/bWidth])){
            break;
        }

        gotoxy(x,y);
        printf(" ");
        (player==1)?x++:x--;
    }
}

