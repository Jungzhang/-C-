/*************************************************************************
	> File Name: fileHoll.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月20日 星期三 08时38分29秒
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

    if ((fd = open("tar.txt", O_RDWR)) < 0) {
        perror("Open Old");
        return EXIT_FAILURE;
    }

    if (lseek(fd, 1000, SEEK_END) < 0) {
        perror("lseek");
        close(fd);
        return EXIT_FAILURE;
    }

    if ((write(fd, "I", 1)) != 1) {
        perror("Write");
    }

    close(fd);

    return EXIT_SUCCESS;
}
