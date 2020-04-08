#include <stdio.h> 
void main()
{
	int r,s,c;
	printf("请输入圆的半径");
	scanf("%d",&r); 
	if(r>=0){
		printf("圆的面积为%dΠ\n",r*r);
        printf("圆的周长为%dΠ",2*r);}
		else{
			printf("请输入正确的半径长度"); 
		}	
} 
