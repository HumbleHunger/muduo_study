/*************************************************************************
	> File Name: c4.c
	> Author: 
	> Mail: 
	> Created Time: 2020年05月04日 星期一 19时36分34秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    while(1){
        printf("1.加密\n2.解密\n");
        int chose;
        scanf("%d",&chose);
        if(chose==1){
            printf("输入加密前的密码(只能由小写字母构成且不能超过10位)");
            char a[11];
            scanf("%s",a);
            for(int i=0;i<10;i++){
                if(a[i]==0){
                    break;
                }
                a[i]=a[i]+3;
                if(a[i]>122){
                    a[i]=a[i]-26;
                }
            }
            printf("加密后的密码为%s\n",a);
        }else if(chose==2){
            printf("输入加密后的密码(只能由小写字母构成且不能超过10位)");
            char a[11];
            scanf("%s",a);
            for(int i=0;i<10;i++){
                if(a[i]==0){
                    break;
                }
                a[i]=a[i]-3;
                if(a[i]<97){
                    a[i]=a[i]+26;
                }
            }
            printf("解密后的密码为%s\n",a);
        }else{
            printf("请输入正确的选项\n");
        }
    }
}
