/*************************************************************************
	> File Name: Common.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月25日 星期五 22时30分09秒
	> Description: 定义公共数据结构和声明函数
 ************************************************************************/
#ifndef _COMMON_H
#define _COMMON_H

#define LEAFMAX (256)           //叶子结点的最大个数(文件中出现的字符最大种类数)
#define NODEMAX (2 * LEAFMAX - 1)     //哈夫曼树所有结点的最大个数
#define CODEMAXSIZE (LEAFMAX - 1)     //哈夫曼树的最高层次只有(NODEMAX) / 2

typedef struct HuffmanTree{

    int weight;     //权值
    int parent;     //双亲结点的下标
    int LChild;     //左孩子
    int RChild;     //右孩子

}HuffmanTreeNode;

//统计文件中字符出现的次数,得到频率数组weight[]
int GetWeight(int *weight, char *SourceName);

//从数组中选取两个最小值的下标
int SelectNode(HuffmanTreeNode HuffmanTree[], int *FirstMin, int *SecondMin, int length);

//程序使用说明
void Instruction(char *name);

//把二进制字符串转为一个char
int StrToChar(char *StrNum);

//把一个char转化为二进制
void CharToStr(int ch, char *StrNum);

#endif
