/*************************************************************************
	> File Name: exec.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月21日 星期四 17时01分02秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    int fd = open("Text.txt", O_RDWR, 0664);

    char *cmd[] = {NULL};

    int flag = fcntl(fd, F_GETFD);
    if (fcntl(fd, F_SETFD, FD_CLOEXEC | flag) < 0) {
        perror("fcntl");
    }

    pid_t id = fork();

    if (id < 0) {
        printf("失败\n");
    }else if (id == 0) {
        if (execv("./child", cmd) < 0) {
            perror("ERROR");
        }
    } else {
        sleep(2);
        printf("父进程\n");
        if (write(fd, "aaa", 3) != 3) {
            perror("write");
        }
    }

    wait(NULL);
    close(fd);

    return EXIT_SUCCESS;
}
