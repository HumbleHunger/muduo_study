/*************************************************************************
	> File Name: 3.4.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月22日 星期日 21时25分06秒
 ************************************************************************/
#include <stdio.h>
#include <math.h>
void main()
{
    double a,b,c,x1,x2,d;
    scanf("%lf,%lf,%lf",&a,&b,&c);
    d = sqrt(b*b-4*a*c);
    b=(-1)*b;
    x1=-(b+d)/2/a;
    x2=-(b-d)/2/a;
    printf("x1=%f\nx2=%f\n",x1,x2);
}
