/*************************************************************************
	> File Name: 6.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月05日 星期日 19时45分59秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int a,sum,sum_all;
    a=sum=sum_all=0;
    for(int i=1;i<=13;i++){
        for(int j=0;j<23;j++){
            scanf("%d",&a);
            sum+=a;
        }
        printf("第%d个输入地累计确诊数为%d\n",i,sum);
        sum_all+=sum;
    }
    printf("13个输入地累计确诊总个数为%d\n",sum_all);
    return 0;
}
