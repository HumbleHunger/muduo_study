/*************************************************************************
	> File Name: c6.c
	> Author: 
	> Mail: 
	> Created Time: 2020年06月15日 星期一 07时51分17秒
 ************************************************************************/
#include <stdio.h>
#include <string.h>
void sort(char *p_s1, char *p_s2);
int main()
{
	char s1[100], s2[100], s3[100];
	char *p_s1=s1,*p_s2=s2,*p_s3=s3;
	printf("请随意输入三个字符串：\n");
	gets(s1);
	gets(s2);
	gets(s3);
	sort(p_s1, p_s2);
	sort(p_s1, p_s3);
	sort(p_s2, p_s3);
	printf("按照由小到大的顺序输出如下：\n%s\t%s\t%s\t", p_s1, p_s2, p_s3);
	return 0;
}

void sort(char *p_s1, char *p_s2)
{
	char temp[100];
	if(strcmp(p_s1,p_s2)>0)
	{
		strcpy(temp, p_s1);
		strcpy(p_s1, p_s2);
		strcpy(p_s2, temp);
	}
}
