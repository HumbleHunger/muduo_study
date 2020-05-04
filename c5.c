/*************************************************************************
	> File Name: c5.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月04日 星期一 20时28分46秒
 ************************************************************************/

#include <stdio.h>
int main(void)
{
    float original_amount, amount_with_tax;
    printf("Enter an amount: ");
    scanf("%f", &original_amount);
    amount_with_tax = original_amount * 1.05;
    printf("With tax added: $%.2f\n", amount_with_tax);
    return 0;
} 
