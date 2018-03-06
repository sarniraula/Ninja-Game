#ifndef GETINPUT_H_INCLUDED
#define GETINPUT_H_INCLUDED

#endif // GETINPUT_H_INCLUDED

#include <stdio.h>
#include <conio.h>
#include <math.h>

//function prototypes
float floatNum (int length, int minimum);
int intNum (int length, int minimum);
char charWord (char letters[]);

//function declarations
float floatNum (int length, int minimum)
//take input of float numbers
{
    float num=0;
    char a;
    int index=0, currentLen=0,x;

    do
    {
        a=getch();
        if (a>=48 && a<=57){
            a-='0';
            if (index==0 && currentLen<length){
                printf("%d", a);
                num*=10;
                num+=a;
                currentLen++;
            }else if((index>0) && (index<3)){
                printf("%d", a);
                num+=pow(10, -index)*a;
                index++;
            }
        }else if(a=='.' && index==0) {
            printf("%c", a);
            index++;
        } else if (a==8) {
            if (index>1){
                printf("\b \b");
                x=pow(10,index-2);
                num=floor(num*x)/x;
                index--;
            } else if (index==1) {
                printf("\b \b");
                index--;
            } else if (currentLen>0){
                printf("\b \b");
                int tmp=num;
                tmp/=10;
                num = tmp;
                currentLen--;
            }
        }
    }while(a!='\r' || num<minimum);

    return num;
}

int intNum (int length, int minimum)
//take input of integer number
{
    int num=0, currentLen=0;
    char a;

    do
    {
        a=getch();
        if (a>=48 && a<=57 && currentLen<length){
            printf("%c", a);
            a-='0';
            num*=10;
            num+=a;
            currentLen++;
         } else if (a==8 && currentLen>0) {
            printf("\b \b");
            num/=10;
            currentLen--;
        }
    }while(a!='\r' || num<minimum);

    return num;
}

char charWord (char letters[])
//take string as input
{
    char a;
    int i=0;

    do
    {
        a=getch();
        if ((a>=65 && a<=90) || (a>=97 && a<=122)){
            printf("%c", a);
            letters[i++]=a;
            letters[i]=NULL;
         } else if (a==8 && i>0) {
            printf("\b \b");
            letters[--i]=NULL;
        }
    }while(a!='\r' || i==0);
}

