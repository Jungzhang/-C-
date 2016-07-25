/*************************************************************************
	> File Name: getopt.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2016年04月19日 星期二 14时39分16秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

extern int opterr;

int main(int argc, char *argv[])
{
    char opt;
    opterr = 0;

    while ((opt = getopt(argc, argv, "ABC")) != -1) {
        printf("%d\n",opt);
        switch(opt) {
        case 'A' :
            printf("%s\n", argv[2]);
            break;
        case 'B':
            printf("case B\n");
            break;
        case 'C':
            printf("case C\n");
            break;
        case 'D':
            printf("case D\n");
            break;
        default:
            printf("其他\n");
        }
    }
    
    return EXIT_SUCCESS;
}
