/*************************************************************************
	> File Name: 13.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月16日 星期四 20时20分41秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
int hour,minute,second;
void Update()
{
    second++;
    if(second==60)
    {
        second=0;
        minute++;
    }
    if(minute==60)
    {
        minute=0;
        hour++;
    }
    if(hour==24)
    {
        hour=0;
    }
}
void Display()
{
    printf("%2d:%2d:%2d\n",hour,minute,second);
}
void Delay()
{
    int t;
    sleep(1);
}
int main()
{
    int i;
    hour=minute=second=0;
    for(;;)
    {
        Update();
        Display();
        Delay();
    }
    return 0;
}
