/*************************************************************************
	> File Name: sloth.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年12月12日 星期一 21时51分34秒
    > Description: 试水一个简单的JSON库
 ************************************************************************/
#ifndef _JSON_SLOTH_H
#define _JSON_SLOTH_H

//JSON中的数据类型
typedef enum {
    SLOTH_NULL,
    SLOTH_FALSE,
    SLOTH_TRUE,
    SLOTH_NUMBER,
    SLOTH_SIRING,
    SLOTH_ARRAY,
    SLOTH_OBJECT
} sloth_type;

//JSON对象的数据类型
typedef struct {
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
    SLOTH_PARSE_ROOT_NOT_SINGULAR
};

//传入JSON字符串
//将其解析为JSON对象
//存于传入的JSON对象指针为根节点的JSON树中
int sloth_parse(sloth_value *root, const char *json);

//获取结果
sloth_type sloth_get_type(const sloth_value *v);

#endif
