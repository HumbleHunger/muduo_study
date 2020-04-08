#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int n;
	struct node *next;
} Node;
void main()
{
	Node *head,*pre,*now;
	head=NULL;
	int num;
	do{
		scanf("%d",&num);
		if(num != -1){
			now=(Node*)malloc(sizeof(Node));
			if(head == NULL){
				head=now;
			}else{
				pre->next = now;
			}now->n=num;
			now->next=NULL;
			pre=now;
		}
	}while(num != -1);
	now=head;
	while(now != NULL){
		printf("%d  ",now->n);
		now=now->next;
	}
	now=head;
	while(now != NULL){
		pre=now;
		free(now);
		now=pre->next;
	}
	
 } 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
