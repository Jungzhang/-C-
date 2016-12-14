/*************************************************************************
	> File Name: sloth.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年12月12日 星期一 21时53分02秒
	> Description: 一个简单的JSON库试水
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <math.h>

#include "sloth.h"

#define EXPECT(c, ch) assert(*c->json == (ch))
#define ISDIGIT(ch) ('0' <= (ch) && (ch) <= '9')
#define ISDIGIT1TO9(ch) ('1' <= (ch) && (ch) <= '9')

typedef struct {
    const char *json;
}sloth_context;

//空白
static void sloth_parse_whitespace(sloth_context *c)
{
    const char *p = c->json;

    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
        ++p;
    }
    c->json = p;
}

//分析true
static int sloth_parse_true(sloth_context *c, sloth_value *v)
{
    EXPECT(c, 't');
    c->json++;

    if (c->json[0] != 'r' || c->json[1] != 'u' || c->json[2] != 'e') {
        return SLOTH_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = SLOTH_TRUE;

    return SLOTH_PARSE_OK;
}

//分析false
static int sloth_parse_false(sloth_context *c, sloth_value *v)
{
    EXPECT(c, 'f');
    c->json++;

    if (c->json[0] != 'a' || c->json[1] != 'l' || c->json[2] != 's' || c->json[3] != 'e') {
        return SLOTH_PARSE_INVALID_VALUE;
    }
    c->json += 4;
    v->type = SLOTH_FALSE;

    return SLOTH_PARSE_OK;
}

//分析null
static int sloth_parse_null(sloth_context *c, sloth_value *v)
{
    EXPECT(c, 'n');
    c->json++;

    if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l') {
        return SLOTH_PARSE_INVALID_VALUE;
    }
    c->json += 3;
    v->type = SLOTH_NULL;

    return SLOTH_PARSE_OK;
}

//分析数字
static int sloth_parse_number(sloth_context *c, sloth_value *v)
{
    const char *p = c->json;

    if (*p == '-') {
        ++p;
    }
    
    if (*p == '0') {
        ++p;
    } else {
        if (!ISDIGIT1TO9(*p)) {
            return SLOTH_PARSE_INVALID_VALUE;
        }
        for (++p; ISDIGIT(*p); ++p);
    }

    if (*p == '.') {
        ++p;
        if (!ISDIGIT(*p)) {
            return SLOTH_PARSE_INVALID_VALUE;
        }
        for (++p; ISDIGIT(*p); ++p);
    }

    if (*p == 'e' || *p == 'E') {
        ++p;
        if (*p == '+' || *p == '-') {
            ++p;
        }
        if (!ISDIGIT(*p)) {
            return SLOTH_PARSE_INVALID_VALUE;
        }
        for (++p; ISDIGIT(*p); ++p);
    }

    errno = 0;
    v->number = strtod(c->json, NULL);

    if (errno == ERANGE && (v->number == HUGE_VAL || v->number == -HUGE_VAL)) {
        v->number = 0;
        return SLOTH_NUMBER_OUT_OF_REANGE;
    }

    //此处不可用strtod的返回的end指针,因为json中没有0x,但是该函数可正常解析0x系列
    c->json = p;
    v->type = SLOTH_NUMBER;

    return SLOTH_PARSE_OK;
}

//通过不同的首字母调用不同的解析进行解析操作
static int sloth_parse_value(sloth_context *c, sloth_value *v)
{
    switch (*c->json) {
        case 'n' : return sloth_parse_null(c, v);
        case 't' : return sloth_parse_true(c, v);
        case 'f' : return sloth_parse_false(c, v);
        case '\0' : return SLOTH_PARSE_EXPECT_VALUE;
        default : return sloth_parse_number(c, v);
    }
}

//解析JSON的对外接口
int sloth_parse(sloth_value *root, const char *json)
{
    assert(root != NULL);
    int ret;
    sloth_context c;
    c.json = json;
    root->type = SLOTH_NULL;
    sloth_parse_whitespace(&c);
    //只有解析成功之后才有肯能去检查空格之后还有没有非空格值
    if ((ret = sloth_parse_value(&c, root)) == SLOTH_PARSE_OK) {
        sloth_parse_whitespace(&c);
        if (*c.json != '\0') {
            root->type = SLOTH_NULL;
            ret = SLOTH_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    
    return ret;
}

//获取类型
sloth_type sloth_get_type(const sloth_value *v)
{
    assert(v != NULL);
    return v->type;
}

//获取数字
double sloth_get_number(const sloth_value *v)
{
    assert(v != NULL && v->type == SLOTH_NUMBER);

    return v->number;
}
