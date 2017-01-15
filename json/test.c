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
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == actual, expect, actual, "%.17g")
#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")

//测试解析的基方法
#define TEST_PARSE_BASE(json, type_sloth)     \
    do { \
        sloth_value v; \
        v.type = SLOTH_TRUE;   \
        EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, json));    \
        EXPECT_EQ_INT(type_sloth, sloth_get_type(&v));     \
    } while(0)

//测试错误的基方法
#define TEST_ERROR_BASE(json, test_type) \
    do {    \
        sloth_value v; \
        v.type = SLOTH_TRUE;    \
        EXPECT_EQ_INT(test_type, sloth_parse(&v, json));    \
        EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));  \
    }while(0)

//数字测试基方法
#define TEST_NUMBER_BASE(num, json) \
    do {    \
        sloth_value v;  \
        sloth_init(&v);     \
        EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, json));   \
        EXPECT_EQ_INT(SLOTH_NUMBER, sloth_get_type(&v)); \
        EXPECT_EQ_DOUBLE(num, sloth_get_number(&v));   \
    }while(0)

//测试null
static void test_parse_null()
{
    TEST_PARSE_BASE("null", SLOTH_NULL);
}

//测试为零个或多个空格
static void test_parse_expect()
{
    TEST_ERROR_BASE(" ", SLOTH_PARSE_EXPECT_VALUE);
    TEST_ERROR_BASE("", SLOTH_PARSE_EXPECT_VALUE);
}

//测试空白之后还有字符
static void test_parse_singular()
{
    TEST_ERROR_BASE("null n", SLOTH_PARSE_ROOT_NOT_SINGULAR);
    TEST_ERROR_BASE("0x123", SLOTH_PARSE_ROOT_NOT_SINGULAR);
    TEST_ERROR_BASE("0x0", SLOTH_PARSE_ROOT_NOT_SINGULAR);
    TEST_ERROR_BASE("012", SLOTH_PARSE_ROOT_NOT_SINGULAR);
}

//测试含有非法字符
static void test_parse_invalid()
{
    TEST_ERROR_BASE("asd", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("+0", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("+1", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("1.", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("INF", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("inf", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE(".1", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("e1", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("NAN", SLOTH_PARSE_INVALID_VALUE);
    TEST_ERROR_BASE("nan", SLOTH_PARSE_INVALID_VALUE);
}

//测试true
static void test_parse_true()
{
    TEST_PARSE_BASE("true", SLOTH_TRUE);
}

//测试false
static void test_parse_false()
{
    TEST_PARSE_BASE("false", SLOTH_FALSE);
}

//测试数字
static void test_parse_number()
{
    TEST_NUMBER_BASE(0.0, "0");
    TEST_NUMBER_BASE(0.0, "0.0");
    TEST_NUMBER_BASE(-1.0, "-1");
    TEST_NUMBER_BASE(1.0, "1");
    TEST_NUMBER_BASE(1.5, "1.5");
    TEST_NUMBER_BASE(-1.5, "-1.5");
    TEST_NUMBER_BASE(0.012, "0.012");
    TEST_NUMBER_BASE(-0.012, "-0.012");
    TEST_NUMBER_BASE(1E9, "1E9");
    TEST_NUMBER_BASE(-1E9, "-1E9");
    TEST_NUMBER_BASE(1E+9, "1E+9");
    TEST_NUMBER_BASE(-1E+9, "-1E+9");
    TEST_NUMBER_BASE(1E-9, "1E-9");
    TEST_NUMBER_BASE(-1E-9, "-1E-9");
    TEST_NUMBER_BASE(1e9, "1e9");
    TEST_NUMBER_BASE(-1e9, "-1e9");
    TEST_NUMBER_BASE(1e9, "1e9");
    TEST_NUMBER_BASE(1e9, "1e9");
    TEST_NUMBER_BASE(1e9, "1e9");
    TEST_NUMBER_BASE(1e9, "1e9");
    TEST_NUMBER_BASE(1e9, "1e9");
    TEST_NUMBER_BASE(3.1415926, "3.1415926");
    TEST_NUMBER_BASE(-3.1415926, "-3.1415926");
    TEST_NUMBER_BASE(0.0, "1e-10000");
    TEST_NUMBER_BASE(1.0000000000000002, "1.0000000000000002");
    TEST_NUMBER_BASE( 4.9406564584124654e-324, "4.9406564584124654e-324" );
    TEST_NUMBER_BASE(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    TEST_NUMBER_BASE( 2.2250738585072009e-308, "2.2250738585072009e-308" );
    TEST_NUMBER_BASE(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    TEST_NUMBER_BASE( 2.2250738585072014e-308, "2.2250738585072014e-308" );
    TEST_NUMBER_BASE(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    TEST_NUMBER_BASE( 1.7976931348623157e+308, "1.7976931348623157e+308" );
    TEST_NUMBER_BASE(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

//测试字符串的基方法
#define TEST_STRING(expect, json) \
    do { \
        sloth_value v;  \
        sloth_init(&v);     \
        EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, json));\
        EXPECT_EQ_INT(SLOTH_STRING, sloth_get_type(&v));\
        EXPECT_EQ_STRING(expect, sloth_get_string(&v), sloth_get_string_length(&v));\
        sloth_free(&v);\
    }while(0)

static void test_parse_string() {
    TEST_STRING("", "\"\"");
    TEST_STRING("Hello", "\"Hello\"");
    TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
    TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
}

//测试数字越界
static void test_parse_out_of_reange()
{
    TEST_ERROR_BASE("1e400", SLOTH_NUMBER_OUT_OF_REANGE);
    TEST_ERROR_BASE("-1e400", SLOTH_NUMBER_OUT_OF_REANGE);
}

static void test_parse()
{
    test_parse_null();
    test_parse_expect();
    test_parse_singular();
    test_parse_invalid();
    test_parse_true();
    test_parse_false();
    test_parse_number();
    test_parse_out_of_reange();
}

int main(int argc, char *argv[])
{
    test_parse();
    printf("%d  %d  (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);

    return main_ret;
}
