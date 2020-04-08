#include <stdio.h> 
int max(int a[]);
void main()
{
	int i,b; 
	int a[2];
	printf("请输入两个数\n");
	for(i=0;i<2;i++){
		scanf("%d",&a[i]);
	} 
	b=max(a);
	printf("%d",b);
 } 
int max(int a[])
{
	int *p=a;
	if(p[0]>p[1]){
		return(p[0]);
	}else{
		return(p[1]);
	}
}
