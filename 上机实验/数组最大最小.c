#include <stdio.h>

int max,min,x1,y1,x2,y2;

void cmp(int a[4][4])
{
	int i,j;
	max = a[0][0];min = a[0][0];
	for (i = 0;i < 4;i++)
		for (j = 0;j < 4;j++)
		{
			if(max < a[i][j])
			{max = a[i][j];x1 = i;y1 = j;}
		}
	for (i = 0;i < 4;i++)
        for (j = 0;j < 4;j++)
        {
            if(min > a[i][j])
            {min = a[i][j];x2 = i;y2 = j;}
        }

}

int main(void)
{
	int a[4][4] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	cmp(a);
	printf("max = %d,\t下标:(%d,%d)\nmin = %d,\t下标:(%d,%d)\n",max,x1,y1,min,x2,y2);

	return 0;
}
