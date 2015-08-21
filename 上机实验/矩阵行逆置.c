#include <stdio.h>

void juzhen(int (*arr)[4],int m)
{
	int temp,i,j;
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < (m / 2); j++)
		{
			temp = arr[i][j];arr[i][j] = arr[i][m - j -1];arr[i][m-j-1] = temp;
		}
	}
}

int main(void)
{
	int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}},i,j;
	juzhen(a,4);
	for(i = 0;i < 3;i++){
		for(j = 0; j < 4; j++)
		{
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}

	return 0;
}
