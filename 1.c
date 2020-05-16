/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月30日 星期四 21时22分33秒
 ************************************************************************/
#include <stdio.h>
int main()
{
char msg,ct;
printf("please input a key between 0~25:\n");
printf("key=");
else
{
break;
}
}
printf("\n");

printf("Enter a ciphertext:\n");

for(i=0;;i++)
{
     scanf("%c",&ct);
     if((('a'<=ct)&&(ct<='z'))||(('A'<=ct)&&(ct<='Z')))
     {
     msg=ct-key;
     printf("%c",msg);
}
else if(ct==' ')
{
printf("%c",ct);
}
else
break;
}
printf("\n");
}
