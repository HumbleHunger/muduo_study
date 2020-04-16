/*************************************************************************
	> File Name: 11.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月16日 星期四 20时03分39秒
 ************************************************************************/

#include<stdio.h>
int max(int x,int y)
{
    if(x>y){
        return x;
    }
    else{
        return y;
    }
}
int main()
{
    int x,y;
    scanf("%d %d",&x,&y);
    printf("%d\n",max(x,y));
}
