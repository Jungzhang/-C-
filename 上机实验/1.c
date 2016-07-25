/*************************************************************************
	> File Name: 1.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月13日 星期三 13时55分20秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    while (1) {
        srand(time(NULL));
        printf("%d - %d\n", rand() % 10, rand() % 100);
        sleep(1);
    }

    return EXIT_SUCCESS;
}
