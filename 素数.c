#include <stdio.h>
void main()
{
	int a[100];
	int i,j;
	int c=0;
	for(i=0;i<100;i++){
		a[i]=i+1;
	}
	for(i=0;i<100;i++){
		printf("%d",a[i]);
	}
	printf("\n\n");
	for(i=0;i<100;i++){
	c=abc(a,i,c);
	if(c==0){printf("%d\t",a[i]);
		
		}c=0;
	}
}
int abc(int a[],int i,int c)
{
	int j;
		for(j=2;j<a[i];j++){
			
		if(a[i]%j==0){
			c=1;
			break;
	}
		}return c;
}
