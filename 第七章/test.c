/*************************************************************************
	> File Name: test.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月23日 星期六 19时51分27秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("aaaaaa\n");
    abort();
    printf("bbbbbbb\n");


    return EXIT_SUCCESS;
}
