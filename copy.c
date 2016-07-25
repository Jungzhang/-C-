/*************************************************************************
	> File Name: copy.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月19日 星期二 22时13分02秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s old new\n", argv[0]);
        return EXIT_FAILURE;
    }

    inputFd = open(argv[1], O_RDONLY);

    if (inputFd < 0) {
        perror("Open");
        return EXIT_FAILURE;
    }

    outputFd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
                    | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (outputFd < 0) {
        perror("Open");
        return EXIT_FAILURE;
    }

    while((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            printf("复制失败!\n");
        }
    }

    close(outputFd);
    close(inputFd);

    return EXIT_SUCCESS;
}
