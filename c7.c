/*************************************************************************
	> File Name: c7.c
	> Author: 
	> Mail: 
	> Created Time: 2020年06月15日 星期一 23时56分42秒
 ************************************************************************/
#include <stdio.h>
typedef struct student
{
	long studentID;      	 /*学号*/
	char studentName[10];	/*姓名*/ 
	char studentSex;		/*性别*/ 
	int score[3];			/*三门课的成绩*/ 
}STUDENT;
void Input(STUDENT stu[],int n,int m);  /*声明输入函数*/ 
void Aver(STUDENT stu[],float aver[],int n,int m);	/*声明计算平均数函数*/ 
void Print(STUDENT stu[],float aver[],int n,int m);	/*声明输出函数*/ 
int main()
{
	float aver[5]; 	/*定义平均数变量类型*/ 
	STUDENT stu[5];		/*定义结构体变量stu[i]*/
	Input(stu,5,3); 	/*调用输入函数*/
	Aver(stu,aver,5,3);		/*调用计算平均数函数*/
	Print(stu,aver,5,3);	/*调用输出函数*/
	return 0;
}
void Input(STUDENT stu[],int n,int m)
{
	int i,j;
	/*利用循环输入5个学生的信息*/
	for(i=0;i<n;i++)
	{
		printf("请输入第%d个学生的学号、姓名、性别(用M或F表示)、成绩：\n",i+1); /*提示用户使用键盘输入信息*/
		scanf("%ld %s %c",&stu[i].studentID,stu[i].studentName,&stu[i].studentSex);
		/*利用循环将学生成绩输入stu.score[i]数组*/ 
		for(j=0;j<m;j++)
		{
			scanf("%d",&stu[i].score[j]);
		}
	}
} 
void Aver(STUDENT stu[],float aver[],int n,int m)
{
	int i,j,sum[n];
	for(i=0;i<n;i++)
	{
		sum[i]=0;/*初始化sum[i]为0*/
		/*计算三科成绩总分*/ 
		for(j=0;j<m;j++)
		{
			sum[i]=sum[i]+stu[i].score[j];
		}
		aver[i]=(float)sum[i]/m;/*计算平均分*/ 
	}
}
/**输出学生信息*/
void Print(STUDENT stu[],float aver[],int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		printf("%10ld%8s%3c",stu[i].studentID,
							stu[i].studentName,
							stu[i].studentSex);
		for(j=0;j<m;j++)
		{
			printf("%4d",stu[i].score[j]);
		}
		printf("%6.1f\n",aver[i]);
	}
}
