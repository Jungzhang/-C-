/*************************************************************************
	> File Name: Main.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月25日 星期五 19时19分22秒
	> Description:  主程序
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#include "Huffman.h"
#include "Common.h"
#include "Function.h"

int main(int argc, char *argv[])
{
    int source = 0, target = 0, funcsion = 0, i;
    clock_t start, end;

    if (argc < 6) {
        printf("\n程序参数输入有误!\n\n");
        Instruction(argv[0]);
        return EXIT_FAILURE;
    }

    start = clock();

    //参数解析
    for (i = 1; i < 6; ++i) {
        if (!strcmp(argv[i], "-c")) {
            funcsion = i;
        } else if (!strcmp(argv[i], "-s")) {
            if (i != 5) {
                source = i + 1;
            } else {
                printf("参数输入有误!\n\n");
                Instruction(argv[0]);
                return EXIT_FAILURE;
            }
        } else if (!strcmp(argv[i], "-t")) {
            if (i != 5) {
                target = i + 1;
            } else {
                printf("参数输入有误!\n\n");
                return EXIT_FAILURE;
            }
        } else if (!strcmp(argv[i], "-d")) {
            funcsion = i;
        }
    }
    if ((!strcmp(argv[funcsion], "-c")) && source != 0 && target != 0) {
        if (Compression(argv[source], argv[target]) == 0) {
            printf("压缩失败!\n");
            return EXIT_FAILURE;
        } else {
            end = clock();
            printf("压缩时间：%lf秒\n\n",((double)end - start) / CLOCKS_PER_SEC);
        }
    } else if ((!strcmp(argv[funcsion], "-d")) && source != 0 && target != 0) {
        if (Decompression(argv[source], argv[target]) == 0) {
            printf("解压缩失败!\n");
            return EXIT_FAILURE;
        } else {
            end = clock();
            printf("解压成功!\n");
            printf("解压缩时间：%lf秒\n\n",((double)end - start) / CLOCKS_PER_SEC);
        }
    } else {
        printf("命令错误!\n");
        Instruction(argv[0]);
    }

    
    return EXIT_SUCCESS;
}
