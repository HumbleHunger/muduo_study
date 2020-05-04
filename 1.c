/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月30日 星期四 21时22分33秒
 ************************************************************************/
#include <stdio.h>
int main()
{
int i,key;
char msg,ct;
printf("please input a key between 0~25:\n");
printf("key=");
scanf("%d",&key);
printf("Enter a message:\n");
scanf("%c",&msg);
for(i=0;;i++)
    {
     scanf("%c",&msg);
     if((('a'<=msg)&&(msg<='z'))||(('A'<=msg)&&(msg<='Z')))
     {
     ct=msg+key;
     printf("%c",ct);
}
else if(msg==' ')
{
printf("%c",msg);
}
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
