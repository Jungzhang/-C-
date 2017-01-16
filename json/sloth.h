/*************************************************************************
	> File Name: sloth.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年12月12日 星期一 21时51分34秒
    > Description: 试水一个简单的JSON库
 ************************************************************************/
#ifndef _JSON_SLOTH_H
#define _JSON_SLOTH_H

//设置为null
#define sloth_set_null(v) sloth_free(v)

//初始化
#define sloth_init(v) do{(v)->type = SLOTH_NULL;}while(0)

//JSON中的数据类型
typedef enum {
    SLOTH_NULL,
    SLOTH_FALSE,
    SLOTH_TRUE,
    SLOTH_NUMBER,
    SLOTH_STRING,
    SLOTH_ARRAY,
    SLOTH_OBJECT
} sloth_type;

//JSON对象的数据类型
typedef struct {
    union {
        struct {char *s; size_t len;}str;
        double number;
    }u;
    sloth_type type;
} sloth_value;

//返回值定义
enum {
    //正确,无错误
    SLOTH_PARSE_OK = 0,
    //传入的json字符串只包含空白字符
    SLOTH_PARSE_EXPECT_VALUE,
    //如果传入的字符串中包含非法字符
    SLOTH_PARSE_INVALID_VALUE,
    //若一个字符之后,在空白之后还有其他字符
    SLOTH_PARSE_ROOT_NOT_SINGULAR,
    //数字越界
    SLOTH_NUMBER_OUT_OF_REANGE,
    //缺少引号
    SLOTH_PARSE_MISS_QUOTATION_MARK,
    //转义字符出现不合法字符
    SLOTH_PARSE_INVALID_STRING_ESCAPE,
    //无效的字符
    SLOTH_PARSE_INVALID_STRING_CHAR,
    //解析不合法的十六进制数字
    SLOTH_PARSE_INVALID_UNICODE_HEX,
    //不正确的代理对
    SLOTH_PARSE_INVALID_UNICODE_SURROGATE
};

//传入JSON字符串
//将其解析为JSON对象
//存于传入的JSON对象指针为根节点的JSON树中
int sloth_parse(sloth_value *root, const char *json);

//获取类型
sloth_type sloth_get_type(const sloth_value *v);

//获取数字
double sloth_get_number(const sloth_value *v);
//设置数字
void sloth_set_number(sloth_value *v, double n);

//设置字符串
void sloth_set_string(sloth_value *v, const char *s, size_t len);
//获取字符串
const char *sloth_get_string(const sloth_value *v);
//获取字符串长度
size_t sloth_get_string_length(const sloth_value *v);

//释放字符串空间
void sloth_free(sloth_value *v);

//获取boolean
int sloth_get_boolean(const sloth_value *v);
//设置boolean
void sloth_set_boolean(sloth_value *v, int b);

#endif
