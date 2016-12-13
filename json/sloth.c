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

#include "sloth.h"

#define EXPECT(c, ch) assert(*c->json == (ch))

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

static int sloth_parse_value(sloth_context *c, sloth_value *v)
{
    switch (*c->json) {
        case 'n' : return sloth_parse_null(c, v);
        case 't' : return sloth_parse_true(c, v);
        case 'f' : return sloth_parse_false(c, v);
        case '\0' : return SLOTH_PARSE_EXPECT_VALUE;
        default : return SLOTH_PARSE_INVALID_VALUE;
    }
}

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
            ret = SLOTH_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    
    return ret;
}


sloth_type sloth_get_type(const sloth_value *v)
{
    assert(v != NULL);
    return v->type;
}
