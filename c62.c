/*************************************************************************
	> File Name: c62.c
	> Author: 
	> Mail: 
	> Created Time: 2020年06月19日 星期五 21时06分27秒
 ************************************************************************/

#include<stdio.h>
void copy_string(char *s1,char*s2);
int main()
{
	char s1[100],s2[100];
	printf("请输入s1:");
	gets(s1);
	printf("请输入s2:");
	gets(s2);
	char *a=s1;
	char *b=s2;
	copy_string(a,b);
	printf("s1=%s\ns2=%s\n",s1,s2);
}
void copy_string(char *s1,char *s2)
{
	for(;*s1!='\0';s1++,s2++)
	{
		*s2=*s1;
	}
	*s2='\0';
}
