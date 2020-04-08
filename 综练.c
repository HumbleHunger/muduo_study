#include <stdio.h>
void main()
{
	int a;
	for(;;){
	printf("1打印矩形\n2打印倒三角形\n3打印99乘法表\n请输入您的选项\n");
	scanf("%d",&a);
	if(a==1){
		int a,b,c,d;
	printf("请输入矩形的行数");
	scanf("%d",&c); 
	printf("请输入矩形的列数");
	scanf("%d",&d);
	for(a=1;a<=c;a++){
		for(b=1;b<=d;b++){
			printf("*");
		}printf("\n");
	}
}
    else if(a==2){
    	printf("行数");
    int a,b,c,d;
  
    scanf("%d",&a);
    d=a; 
    for(b=1;b<=a;b++){
    	for(c=1;c<=d;c++){
    		printf("*");
    		
		}printf("\n");
		d=d-1;
	}
	}
	else if(a==3){int a,c,b;
	c=1;
	for(a=1;a<=9;a++){
		for(b=1;b<=c;b++){
		
			printf("%d*%d=%d\t",b,c,b*c);
		}c++; 
		printf("\n");
		 
	}
	}else printf("输入错误\n"); 
	system("pause");
}
}
	

