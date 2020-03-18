/*************************************************************************
	> File Name: 3.1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月18日 星期三 22时36分56秒
 ************************************************************************/

#include<stdio.h>
int main(int argc,char **argv)
{
    int num;
    scanf("%d",&num);
    if(num<0){
        num=num*(-1);
    }
    int bai,shi,ge;
    bai=num/100;
    ge=num%10;
    shi=(num-bai*100)/10;
    printf("%d%d%d%%\n",ge,shi,bai);
}
