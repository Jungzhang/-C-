/*************************************************************************
	> File Name: openR.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月20日 星期三 08时03分22秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;

    if (close(STDIN_FILENO) == -1) {
        perror("Close");
        return EXIT_FAILURE;
    }

    fd = open("openR.c", O_RDONLY);

    if (fd < 0) {
        perror("Open");
        return EXIT_FAILURE;
    }

    printf("fd = %d\n", fd);

    close(fd);

    return EXIT_SUCCESS;
}
