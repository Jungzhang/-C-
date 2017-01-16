/*************************************************************************
	> File Name: test1.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年12月12日 星期一 21时53分27秒
	> Description: 测试
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sloth.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")
#define EXPECT_EQ_STRING(expect, actual, alength) \
    EXPECT_EQ_BASE(sizeof(expect) - 1 == alength && memcmp(expect, actual, alength) == 0, expect, actual, "%s")
#define EXPECT_TRUE(actual) EXPECT_EQ_BASE((actual) != 0, "true", "false", "%s")
#define EXPECT_FALSE(actual) EXPECT_EQ_BASE((actual) == 0, "false", "true", "%s")

static void test_parse_null() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_boolean(&v, 0);
    EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, "null"));
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));
    sloth_free(&v);
}

static void test_parse_true() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_boolean(&v, 0);
    EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, "true"));
    EXPECT_EQ_INT(SLOTH_TRUE, sloth_get_type(&v));
    sloth_free(&v);
}

static void test_parse_false() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_boolean(&v, 1);
    EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, "false"));
    EXPECT_EQ_INT(SLOTH_FALSE, sloth_get_type(&v));
    sloth_free(&v);
}

#define TEST_NUMBER(expect, json)\
    do {\
        sloth_value v;\
        sloth_init(&v);\
        EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, json));\
        EXPECT_EQ_INT(SLOTH_NUMBER, sloth_get_type(&v));\
        EXPECT_EQ_DOUBLE(expect, sloth_get_number(&v));\
        sloth_free(&v);\
    } while(0)

static void test_parse_number() {
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    TEST_NUMBER(0.0, "1e-10000"); 

    TEST_NUMBER(1.0000000000000002, "1.0000000000000002"); 
    TEST_NUMBER( 4.9406564584124654e-324, "4.9406564584124654e-324"); 
    TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    TEST_NUMBER( 2.2250738585072009e-308, "2.2250738585072009e-308");  
    TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    TEST_NUMBER( 2.2250738585072014e-308, "2.2250738585072014e-308");  
    TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    TEST_NUMBER( 1.7976931348623157e+308, "1.7976931348623157e+308");  
    TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

#define TEST_STRING(expect, json)\
    do {\
        sloth_value v;\
        sloth_init(&v);\
        EXPECT_EQ_INT(SLOTH_PARSE_OK, sloth_parse(&v, json));\
        EXPECT_EQ_INT(SLOTH_STRING, sloth_get_type(&v));\
        EXPECT_EQ_STRING(expect, sloth_get_string(&v), sloth_get_string_length(&v));\
        sloth_free(&v);\
    } while(0)

static void test_parse_string() {
    TEST_STRING("", "\"\"");
    TEST_STRING("Hello", "\"Hello\"");
    TEST_STRING("Hello\nWorld", "\"Hello\\nWorld\"");
    TEST_STRING("\" \\ / \b \f \n \r \t", "\"\\\" \\\\ \\/ \\b \\f \\n \\r \\t\"");
    TEST_STRING("\x24", "\"\\u0024\"");         /* Dollar sign U+0024 */
    TEST_STRING("\xC2\xA2", "\"\\u00A2\"");     /* Cents sign U+00A2 */
    TEST_STRING("\xE2\x82\xAC", "\"\\u20AC\""); /* Euro sign U+20AC */
    TEST_STRING("\xF0\x9D\x84\x9E", "\"\\uD834\\uDD1E\"");  /* G clef sign U+1D11E */
    TEST_STRING("\xF0\x9D\x84\x9E", "\"\\ud834\\udd1e\"");  /* G clef sign U+1D11E */
}

#define TEST_ERROR(error, json)\
    do {\
        sloth_value v;\
        sloth_init(&v);\
        v.type = SLOTH_FALSE;\
        EXPECT_EQ_INT(error, sloth_parse(&v, json));\
        EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));\
        sloth_free(&v);\
    } while(0)


static void test_parse_invalid_unicode_hex() {
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u0\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u01\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u012\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u/000\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\uG000\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u0G00\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u0/00\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u00G0\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u000/\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u000G\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_HEX, "\"\\u 123\"");
}

static void test_parse_invalid_unicode_surrogate() {
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uDBFF\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\\\\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uDBFF\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_UNICODE_SURROGATE, "\"\\uD800\\uE000\"");
}

static void test_parse_expect_value() {
    TEST_ERROR(SLOTH_PARSE_EXPECT_VALUE, "");
    TEST_ERROR(SLOTH_PARSE_EXPECT_VALUE, " ");
}

static void test_parse_invalid_value() {
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "nul");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "?");

    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "+0");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "+1");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, ".123");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "1.");  
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "INF");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "inf");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "NAN");
    TEST_ERROR(SLOTH_PARSE_INVALID_VALUE, "nan");
}

static void test_parse_root_not_singular() {
    TEST_ERROR(SLOTH_PARSE_ROOT_NOT_SINGULAR, "null x");

    TEST_ERROR(SLOTH_PARSE_ROOT_NOT_SINGULAR, "0123");
    TEST_ERROR(SLOTH_PARSE_ROOT_NOT_SINGULAR, "0x0");
    TEST_ERROR(SLOTH_PARSE_ROOT_NOT_SINGULAR, "0x123");
}

static void test_parse_number_too_big() {
    TEST_ERROR(SLOTH_NUMBER_OUT_OF_REANGE, "1e309");
    TEST_ERROR(SLOTH_NUMBER_OUT_OF_REANGE, "-1e309");
}

static void test_parse_missing_quotation_mark() {
    TEST_ERROR(SLOTH_PARSE_MISS_QUOTATION_MARK, "\"");
    TEST_ERROR(SLOTH_PARSE_MISS_QUOTATION_MARK, "\"abc");
}

//转义字符失败
static void test_parse_invalid_string_escape() {
    TEST_ERROR(SLOTH_PARSE_INVALID_STRING_ESCAPE, "\"\\v\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_STRING_ESCAPE, "\"\\'\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_STRING_ESCAPE, "\"\\0\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_STRING_ESCAPE, "\"\\x12\"");
}

static void test_parse_invalid_string_char() {
    TEST_ERROR(SLOTH_PARSE_INVALID_STRING_CHAR, "\"\x01\"");
    TEST_ERROR(SLOTH_PARSE_INVALID_STRING_CHAR, "\"\x1F\"");
}

static void test_access_null() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_string(&v, "a", 1);
    sloth_set_null(&v);
    EXPECT_EQ_INT(SLOTH_NULL, sloth_get_type(&v));
    sloth_free(&v);
}

static void test_access_boolean() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_string(&v, "a", 1);
    sloth_set_boolean(&v, 1);
    EXPECT_TRUE(sloth_get_boolean(&v));
    sloth_set_boolean(&v, 0);
    EXPECT_FALSE(sloth_get_boolean(&v));
    sloth_free(&v);
}

static void test_access_number() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_string(&v, "a", 1);
    sloth_set_number(&v, 1234.5);
    EXPECT_EQ_DOUBLE(1234.5, sloth_get_number(&v));
    sloth_free(&v);
}

static void test_access_string() {
    sloth_value v;
    sloth_init(&v);
    sloth_set_string(&v, "", 0);
    EXPECT_EQ_STRING("", sloth_get_string(&v), sloth_get_string_length(&v));
    sloth_set_string(&v, "Hello", 5);
    EXPECT_EQ_STRING("Hello", sloth_get_string(&v), sloth_get_string_length(&v));
    sloth_free(&v);
}

static void test_parse() {
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_number();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
    test_parse_number_too_big();
    test_parse_missing_quotation_mark();
    test_parse_invalid_string_escape();
    test_parse_invalid_string_char();
    test_parse_string();
    test_parse_invalid_unicode_hex();
    test_parse_invalid_unicode_surrogate();

    test_access_null();
    test_access_boolean();
    test_access_number();
    test_access_string();
}

int main(int argc, char *argv[]) 
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
