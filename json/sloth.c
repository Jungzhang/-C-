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
#include <string.h>

#include "sloth.h"

#ifndef SLOTH_INIT_STACK_SIZE
#define SLOTH_INIT_STACK_SIZE 256
#endif

#define EXPECT(c, ch) assert(*c->json == (ch))
#define ISDIGIT(ch) ('0' <= (ch) && (ch) <= '9')
#define ISDIGIT1TO9(ch) ('1' <= (ch) && (ch) <= '9')
#define SLOTH_INIT(v) do{(v)->type = SLOTH_NULL;}while(0)
#define PUTC(c, ch) do{*(char *)sloth_context_push(c, sizeof(char)) = (ch);}while(0)

//简化传参的数据结构
typedef struct {
    const char *json;
    char *stack;
    size_t size, top;
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

//设置boolean
void sloth_set_boolean(sloth_value *v, int b)
{
    sloth_free(v);
    v->type = b ? SLOTH_TRUE : SLOTH_FALSE;
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

//设置数字
void sloth_set_number(sloth_value *v, double number)
{
    assert(v != NULL);
    sloth_free(v);
    v->type = SLOTH_NUMBER;
    v->u.number = number;
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
    v->u.number = strtod(c->json, NULL);

    if (errno == ERANGE && (v->u.number == HUGE_VAL || v->u.number == -HUGE_VAL)) {
        v->u.number = 0;
        return SLOTH_NUMBER_OUT_OF_REANGE;
    }

    //此处不可用strtod的返回的end指针
    //因为json中没有0x,但是该函数可正常解析0x
    //所以当有0x时就会发生错误
    c->json = p;
    v->type = SLOTH_NUMBER;

    return SLOTH_PARSE_OK;
}

//释放字符串空间
void sloth_free(sloth_value *root)
{
    assert(root != NULL);
    if (root->type == SLOTH_STRING) {
        free(root->u.str.s);
    }
    //防止双重释放
    root->type = SLOTH_NULL;
}

//设置字符串
void sloth_set_string(sloth_value *root, const char *s, size_t len)
{
    assert(root != NULL && (s != NULL || len == 0));
    sloth_free(root);
    root->u.str.s = malloc(len + 1);
    memcpy(root->u.str.s, s, len);
    root->u.str.s[len] = '\0';
    root->u.str.len = len;
    root->type = SLOTH_STRING;
}

//暂存栈入栈操作
static void *sloth_context_push(sloth_context *c, size_t size)
{
    void *ret;
    assert(c != NULL && size > 0);
    
    //如果栈顶元素加上要入栈的长度超过当前栈的总大小
    //则需要对栈进行扩容操作
    if (c->top + size >= c->size) {
        //如果是未分配则
        if (c->size == 0) {
            c->size = SLOTH_INIT_STACK_SIZE;
        }
        while (c->top + size >= c->size) {
            c->size += c->size >> 1;
        }
        c->stack = (char *)realloc(c->stack, c->size);
    }
    
    ret = c->stack + c->top;
    c->top += size;
    
    return ret;
}

//暂存栈出栈操作
static void *sloth_context_pop(sloth_context *c, size_t size)
{
    assert(c != NULL && c->top >= size);
    return c->stack + (c->top -= size);
}

//返回错误码
#define STRING_ERROR(c, head, ret) do{(c)->top = head; return ret;}while(0)

//读取4位1６进制数
static const char *sloth_parse_hex4(const char *p, unsigned *u)
{
    int i;
    *u = 0;
    for (i = 0; i < 4; ++i) {
        char ch = *p++;
        *u <<= 4; //效果相当于 *u *= 16;
        if ('0' <= ch && ch <= '9') {
            *u |= ch - '0';  //效果相当于 *u += ch - '0';
        } else if ('A' <= ch && ch <= 'F') {
            *u |= ch - ('A' - 10);
        } else if ('a' <= ch && ch <= 'f') {
            *u |= ch - ('a' - 10);
        } else {
            return NULL;
        }
    }
    
    return p;
}

//utf-8编码
static void sloth_encode_utf8(sloth_context *c, unsigned u) 
{
    if (u <= 0x7F) { //码点7位
        //避免编译器的误判警告(unsigned -> char)
        PUTC(c, u & 0xFF);  
    } else if (u <= 0x7FF) { //11位码点
        PUTC(c, 0xc0 | ((u>>6) & 0xFF)); //字节2占5位,开始是110->0xc0
        PUTC(c, 0x80 | (u & 0x3F));      //字节1占6位,开始是10->0x80
    } else if (u <= 0xFFFF) { //16位码点
        PUTC(c, 0xE0 | ((u >> 12) & 0xFF));
        PUTC(c, 0x80 | ((u >> 6) & 0x3F));
        PUTC(c, 0x80 | (u & 0x3F));
    } else { //21位码点
        assert(u <= 0x10FFFF);
        PUTC(c, 0xF0 | ((u >> 18) & 0xFF));
        PUTC(c, 0x80 | ((u >> 12) & 0x3F));
        PUTC(c, 0x80 | ((u >> 6) & 0x3F));
        PUTC(c, 0x80 | (u & 0x3F));
    }
}
//解析字符串
static int sloth_parse_string(sloth_context *c, sloth_value *v)
{
    size_t head = c->top, len;
    const char *p;
    unsigned u, u1;
    
    EXPECT(c, '\"');    //判断json串的开头是不是"
    p = ++c->json;

    while(1) {
        char ch = *p++;
        switch (ch) {
            case '\"': {
                len = c->top - head;
                sloth_set_string(v, (const char *)sloth_context_pop(c, len), len);
                c->json = p;
                return SLOTH_PARSE_OK;
            }
            case '\\': {
                switch (*p++) {
                    case '\"': PUTC(c, '\"'); break;
                    case '\\': PUTC(c, '\\'); break;
                    case '/': PUTC(c, '/'); break;
                    case 'b': PUTC(c, '\b'); break;
                    case 'f': PUTC(c, '\f'); break;
                    case 'n': PUTC(c, '\n'); break;
                    case 'r': PUTC(c, '\r'); break;
                    case 't': PUTC(c, '\t'); break;
                    case 'u': {
                        //读取失败
                        if (!(p = sloth_parse_hex4(p, &u))) {
                            STRING_ERROR(c, head, SLOTH_PARSE_INVALID_UNICODE_HEX);
                        }
                        //代理对
                        if (u >= 0xD800 && u <= 0xDBFF) {
                            if (*p++ != '\\') {
                                STRING_ERROR(c, head, SLOTH_PARSE_INVALID_UNICODE_SURROGATE);
                            }
                            if (*p++ != 'u') {
                                STRING_ERROR(c, head, SLOTH_PARSE_INVALID_UNICODE_SURROGATE);
                            }
                            if (!(p = sloth_parse_hex4(p, &u1))) {
                                STRING_ERROR(c, head, SLOTH_PARSE_INVALID_UNICODE_HEX);
                            }
                            if (u1 < 0xDC00 || u1 > 0xDFFF) {
                                STRING_ERROR(c, head, SLOTH_PARSE_INVALID_UNICODE_SURROGATE);
                            }
                            u = (((u - 0xD800) << 10) | (u1 - 0xDC00)) + 0x10000;
                        }
                        sloth_encode_utf8(c, u);
                    }
                    default : {
                        STRING_ERROR(c, head, SLOTH_PARSE_INVALID_STRING_ESCAPE);
                    } 
                }
            } break;
            case '\0': {
                STRING_ERROR(c, head, SLOTH_PARSE_MISS_QUOTATION_MARK);
            }
            default : {
                //判断输入字符是否有非法字符(不可显示字符)
                if ((unsigned char)ch < 32) {
                    STRING_ERROR(c, head, SLOTH_PARSE_INVALID_STRING_CHAR);
                }
                PUTC(c, ch);
            }
        }
    }
}

//通过不同的首字母调用不同的解析进行解析操作
static int sloth_parse_value(sloth_context *c, sloth_value *v)
{
    switch (*c->json) {
        case 'n' : return sloth_parse_null(c, v);
        case 't' : return sloth_parse_true(c, v);
        case 'f' : return sloth_parse_false(c, v);
        case '\"': return sloth_parse_string(c, v);
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
    c.stack = NULL;
    c.size = c.top = 0;
    sloth_init(root);
    sloth_parse_whitespace(&c);

    //只有解析成功之后才有可能去检查空格之后还有没有非空格值
    if ((ret = sloth_parse_value(&c, root)) == SLOTH_PARSE_OK) {
        sloth_parse_whitespace(&c);
        if (*c.json != '\0') {
            root->type = SLOTH_NULL;
            ret = SLOTH_PARSE_ROOT_NOT_SINGULAR;
        }
    }
    assert(c.top == 0);
    free(c.stack);
    
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

    return v->u.number;
}

//获取字符串
const char *sloth_get_string(const sloth_value *v)
{
    assert(v->type == SLOTH_STRING && v->u.str.s != NULL);
    return v->u.str.s;
}

//获取字符串长度
size_t sloth_get_string_length(const sloth_value *v)
{
    assert(v->type == SLOTH_STRING && v->u.str.s != NULL);
    return v->u.str.len;
}

//获取boolean
int sloth_get_boolean(const sloth_value *v)
{
    assert(v != NULL && (v->type == SLOTH_TRUE || v->type == SLOTH_FALSE));
    return v->type == SLOTH_TRUE;
}

