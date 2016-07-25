/*************************************************************************
	> File Name: Common.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月25日 星期五 22时49分40秒
	> Description:
 ************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <math.h>

#include "Common.h"

//统计文件中字符出现的次数,得到频率数组weight[]
int GetWeight(int *weight, char *SourceName)
{
    int i;
    int ch;
    FILE *source;

    for (i = 0; i < LEAFMAX; i++) {
        weight[i] = 0;
    }

    if ((source = fopen(SourceName, "rb")) == NULL) {
        return 0;
    }

    while ((ch = fgetc(source)) != EOF) {
        if (ch > 255 || ch < 0) {
            printf("不能识别的字符\n");
            return 0;
        }
        weight[ch]++;
    }

    fclose(source);

    return 1;
}

//在weight数组中选择两个最小值的下标
int SelectNode(HuffmanTreeNode *HuffmanTree, int *FristMin, int *SecondMin, int length)
{
    int i;
    int WeightMin = INT_MAX, WeightSecondMin = INT_MAX;

    *SecondMin = -1;
    *FristMin = -1;

    for (i = 0; i < length; i++) {
        //如果本结点确实存在于文件中(weight!=0),且未建树(parent==-1)
        if (HuffmanTree[i].weight != 0 && HuffmanTree[i].parent == -1) {
            if (HuffmanTree[i].weight < WeightMin) {
                WeightSecondMin = WeightMin;
                WeightMin = HuffmanTree[i].weight;
                *SecondMin = *FristMin;
                *FristMin = i;
            } else if (HuffmanTree[i].weight < WeightSecondMin) {
                WeightSecondMin = HuffmanTree[i].weight;
                *SecondMin = i;
            }
        }
    }

    if (*SecondMin == -1 || *FristMin == -1) {
        return 0;
    }

    return 1;
}

//程序使用说明
void Instruction(char *name)
{
    printf("使用方法：\n");
    printf("\t%s -功能参数 -s(source) 源文件 -t(target) 压缩后的文件名\n\n", name);
    printf("功能参数说明：\n");
    printf("\t-c(compression)：压缩文件\n");
    printf("\t-d(decompression)：解压缩文件\n\n");
}

//把二进制字符串转化为一个char
int StrToChar(char *StrNum)
{
    int i = 7;
    int num = 0;

    while (i >= 0) {
        num += pow(2, (7 - i)) * (StrNum[i] - 48);
        --i;
    }

    return num;
}

//把一个char转化为二进制
void CharToStr(int ch, char *StrNum)
{
    int i;

    for (i = 0; i < 8; i++){
        StrNum[i] = '0';
    }

    StrNum[i] = '\0';
    i--;

    while (ch) {
        StrNum[i] += ch % 2;
        ch /= 2;
        --i;
    }

}
