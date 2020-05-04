/*************************************************************************
	> File Name: c3.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月02日 星期六 20时41分04秒
 ************************************************************************/

#include<stdio.h>
int f(int a)
{
    for(int i=2;i<a;i++){
        if(a%i==0){
            return 0;
        }
    }
    return 1;    
}
int main()
{
    int a;
    scanf("%d",&a);
    if(f(a)){
        printf("%d是素数\n",a);
    }
    else{
        printf("%d不是素数\n",a);
    }
}
