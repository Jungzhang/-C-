/*************************************************************************
	> File Name: fork3.c
	> Author: 
	> Mail: 
	> Created Time: 2016年07月21日 星期四 17时41分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
    int pid;

    pid=fork();

    switch(pid)
    {
        case -1:
            perror("Process creation failed\n");
            exit(1);
        break;

        case 0:
            while(1)
            {
                fprintf(stderr, "A backgroud process,PID:%d,Parent PID:%d\n",getpid(),getppid());
                sleep(3);
            }
        break;

        default:
            sleep(1);
            printf("I am Parent Process,my pid is %d\n",getpid());
            exit (1);
    }

    return 0;
}
