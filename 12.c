/*************************************************************************
	> File Name: 12.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月16日 星期四 20时08分40秒
 ************************************************************************/

#include<stdio.h>
int Fact(int n)
{
    int sum,cj;
    sum=0;
    for(int i=1;i<=n;i++){
        cj=1;
        for(int j=1;j<=i;j++){
            cj=cj*j;
        }
        sum+=cj;
    }
    return sum;
}
int main()
{
    int n;
    scanf("%d",&n);
    printf("%d\n",Fact(n));
}
