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
            fprintf(stderr, "%s:%d: expect: " format " actual:" format "\n", __FILE__, __LINE__, expect, actual); \
            main_ret = EXIT_FAILURE;    \
        }\
    }while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == actual, expect, actual, "%d")

//测试null
static void test_parse_null()
{
    sloth_value v;
    v.type = SLOTH_TRUE;
    EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, "null"));
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));
}

//测试为零个或多个空格
static void test_parse_expect()
{
    sloth_value v;
    v.type = SLOTH_TRUE;
    EXPECT_EQ_INT(SLOTH_PARSE_EXPECT_VALUE, sloth_parse(&v, " "));
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));

    EXPECT_EQ_INT(SLOTH_PARSE_EXPECT_VALUE, sloth_parse(&v, ""));
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));
}

//测试空白之后还有字符
static void test_parse_singular()
{
    sloth_value v;
    v.type = SLOTH_TRUE;
    EXPECT_EQ_INT(SLOTH_PARSE_ROOT_NOT_SINGULAR, sloth_parse(&v, "null n"));
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));
}

//测试含有非法字符
static void test_parse_invalid()
{
    sloth_value v;
    v.type = SLOTH_TRUE;
    EXPECT_EQ_INT(SLOTH_PARSE_INVALID_VALUE, sloth_parse(&v, "asd"));
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));
}

//测试true
static void test_parse_true()
{
    sloth_value v;
    v.type = SLOTH_FALSE;
    EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, "true"));
    EXPECT_EQ_INT(SLOTH_TRUE, sloth_get_type(&v));
}

//测试false
static void test_parse_false()
{
    sloth_value v;
    v.type = SLOTH_FALSE;
    EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, "false"));
    EXPECT_EQ_INT(SLOTH_FALSE, sloth_get_type(&v));
}

static void test_parse()
{
    test_parse_null();
    test_parse_expect();
    test_parse_singular();
    test_parse_invalid();
    test_parse_true();
    test_parse_false();
}

int main(int argc, char *argv[])
{
    test_parse();
    printf("%d  %d  (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);

    return main_ret;
}
