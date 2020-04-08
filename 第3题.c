#include <stdio.h> 
void main()
{
    int x,y;
	printf("ÇëÊäÈëxµÄÖµ");
	scanf("%d",&x);
	if(x<0){
		printf("y=%d",2*x+1);
	} else if(x==0){
		printf("y=%d",0);
	}else{
		printf("y=%d",2*x-1);
	}

} 
