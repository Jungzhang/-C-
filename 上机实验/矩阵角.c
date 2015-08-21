#include <stdio.h>

void func(int arr[5][5])
{
	int val = arr[0][0],i,j,x = 0,y = 0;
	for (i = 0;i < 5;i++)
		for (j = 0;j < 5;j++)
			if(val < arr[i][j])
			
}

int main(void)
{
	int a[5][5] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	int i,j;
	func(a);
	for(i = 0;i < 5;i++){
		for(j = 0;j < 5;j++)
			printf("%d\t",a[i][j]);
		printf("\n");
	}

	return 0;
}
