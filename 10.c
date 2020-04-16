/*************************************************************************
	> File Name: 10.c
	> Author: 
	> Mail: 
	> Created Time: 2020年04月16日 星期四 20时01分17秒
 ************************************************************************/

#include <stdio.h>

int Square(int i)

{

	return i * i;

}

int main()

{

	int i = 0;

	i = Square(i);

	for ( ; i<3; i++)

	{

		static int i = 1;

		i += Square(i);

		printf("%d,", i);

	}

	printf("%d\n", i);

	return 0;

}
