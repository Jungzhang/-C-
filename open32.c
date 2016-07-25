/*************************************************************************
	> File Name: test.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月17日 星期日 10时32分42秒
	> Description: 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char buf;
    int fd = open("./win10.iso", O_RDWR);

    if (fd < 0) {
        perror("Open Error : ");
        return EXIT_FAILURE;
    }

    if (lseek(fd, 0, SEEK_END) < 0) {
        perror("First lseek Error : ");
        close(fd);
        return EXIT_FAILURE;
    }

    if (write(fd, "X", 1) < 0) {
        perror("Write Error : ");
        close(fd);
        return EXIT_FAILURE;
    }

    if (lseek(fd, -1, SEEK_END) < 0) {
        perror("Second lseek Error : ");
        close(fd);
        return EXIT_FAILURE;
    }

    if (read(fd, &buf, 1) == 0) {
        printf("未读到任何信息\n");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("%c\n", buf);

    close(fd);

    return EXIT_SUCCESS;
}
