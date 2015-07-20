#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
/*	pid_t pid;
	pid = vfork();

	switch(pid)
	{
		case 0:
			printf("子程序中!\n");	exit(0);
		case -1:
			printf("ERROR\n");
		default:
			printf("父进程中!\n");
	}
*/
printf("helloworld!\n");
	return 0;
}
