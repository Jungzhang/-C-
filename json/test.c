/*************************************************************************
	> File Name: test.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年12月12日 星期一 21时53分27秒
	> Description: 测试
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sloth.h"

static int main_ret = EXIT_SUCCESS;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {    \
        ++test_count; \
        if (equality) { \
            ++test_pass; \
        } else { \
            fprintf(stderr, "%s:%d: expect: " format " actual:" format "\n", __FILE__, __LINE__, expect, actual)\
            main_ret = EXIT_FAILURE;    \
        }\
    }while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == actual, expect, actual, "%d")

static void ()

int main(int argc, char *argv[])
{

    return main_ret;
}
