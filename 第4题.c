#include <stdio.h> 
void main()
{
	int a[4]; 
	int i,j;
	printf("请输入四个整数\n"); 
	for(i=0;i<4;i++){
		scanf("%d",&a[i]);
	}
	int b=a[0];
	for(j=1;j<4;j++){
		if(b>a[j]){
			b=a[j];
		}
	}printf("%d",b);
 } 
