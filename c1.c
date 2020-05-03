/*************************************************************************
	> File Name: c1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月02日 星期六 20时40分35秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int x,y,z,max;
    scanf("%d %d %d",&x,&y,&z);
    if(x>y){
        max=x;
    }
    else{
        max=y;
    }
    if(max<z){
        max=z;
    }
    printf("最大值为%d\n",max);
}
