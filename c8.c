/*************************************************************************
	> File Name: c8.c
	> Author: 
	> Mail: 
	> Created Time: 2020年06月17日 星期三 07时56分06秒
 ************************************************************************/
#include<stdio.h>
#include<string.h>
int main()
{
        int i,a=3;
        char b[50];
        FILE *p1;
        printf("输入明文");
        gets(b);
        for(i=0;i<strlen(b);i++)
        {
        	b[i]=b[i]+a;
            if(b[i]>122){
                b[i]=b[i]-26;
            }
        }
        p1=fopen("1","w");
        fputs(b,p1);
        fclose(p1);
        for(i=0;i<strlen(b);i++)
        {
            b[i]=b[i]-a;
            if(b[i]<97){
                b[i]=b[i]+26;
            }
        }
        p1=fopen("2","w");
        fputs(b,p1);
        fclose(p1);
}
