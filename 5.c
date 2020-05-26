/*************************************************************************
	> File Name: 5.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 13时37分57秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void jiami(char *my)
{
    char *a=(char *)malloc(101);
    memset(a,0,sizeof(a));
    printf("请输入明文\n");
    scanf("%s",a);
    char *b=(char *)malloc(strlen(a)+1);
    memset(b,0,sizeof(b));
    int j=0;
    for(int i=0;i<strlen(a);i++){
        b[i]=my[j++];
        if(j==strlen(my)){
            j=0;
        }
    }
    char *c=(char *)malloc(strlen(a)+1);
    memset(c,0,sizeof(c));
    for(int i=0;i<strlen(a);i++){
        c[i]=b[i]+a[i]-65;
        if(c[i]>90){
            c[i]=c[i]-26;
        }
    }
    printf("明文:%s\n密钥:%s\n密文:%s\n",a,b,c);
    free(a);
    free(b);
    free(c);
}
void jiemi(char *my)
{
    char *a=(char *)malloc(101);
    memset(a,0,sizeof(a));
    printf("请输入密文\n");
    scanf("%s",a);
    char *b=(char *)malloc(strlen(a)+1);
    memset(b,0,sizeof(b));
    int j=0;
    for(int i=0;i<strlen(a);i++){
        b[i]=my[j++];
        if(j==strlen(my)){
            j=0;
        }
    }
    char *c=(char *)malloc(strlen(a)+1);
    memset(c,0,sizeof(c));
    for(int i=0;i<strlen(a);i++){
        c[i]=a[i]-b[i]+65;
        if(c[i]<65){
            c[i]=c[i]+26;
        }
    }
    printf("密文:%s\n密钥:%s\n明文:%s\n",a,b,c);
    free(a);
    free(b);
    free(c);
}
int main()
{
    char *my=(char *)malloc(11);
    printf("请输入一个关键词\n");
    scanf("%s",my);
    while(1){
        printf("1.加密\n2.解密\n3.退出\n");
        int chose;
        scanf("%d",&chose);
        if(chose==1){
            jiami(my);
        }
        else if(chose==2){
            jiemi(my);
        }
        else{
            exit(0);
        }
    }
}
