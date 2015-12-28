/*************************************************************************
	> File Name: Huffman.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月25日 星期五 19时13分40秒
	> Description: 哈夫曼树的操作
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

#include "Huffman.h"
#include "Common.h"

//初始化哈夫曼树
HuffmanTreeNode *InitHuffmanTree(void)
{
    int i;
    
    HuffmanTreeNode *HuffmanTree;
    HuffmanTree = (HuffmanTreeNode *)malloc(sizeof(HuffmanTreeNode) * NODEMAX);
    
    if (HuffmanTree == NULL) {
        return NULL;
    }

    for (i = 0; i < NODEMAX; i++) {
        HuffmanTree[i].weight = 0;
        HuffmanTree[i].parent = -1;
        HuffmanTree[i].LChild = -1;
        HuffmanTree[i].RChild = -1;
    }

    return HuffmanTree;
}

//创建哈夫曼树
int CreatHuffmanTree(HuffmanTreeNode *HuffmanTree, int *weight, int *count)
{
    int FirstMin, SecondMin;
    int i;
    int LeafCount = 0;      // 文件中实际有的字符个数

    assert(HuffmanTree);    //断言函数,保证传进来的数组拥有合法地址

    // 标记实际存在的结点并统计实际存在的结点个数
    for (i = 0; i < LEAFMAX; i++) {
        HuffmanTree[i].weight = weight[i];
        if (weight[i] != 0) {
            LeafCount++;
        }
    }

    for (i = LEAFMAX; i < LEAFMAX + LeafCount - 1; i++) {
        if (SelectNode(HuffmanTree, &FirstMin, &SecondMin, i) == 0) {
            return 0;
        }
        HuffmanTree[i].weight = HuffmanTree[FirstMin].weight + HuffmanTree[SecondMin].weight;
        HuffmanTree[i].LChild = FirstMin;
        HuffmanTree[i].RChild = SecondMin;
        HuffmanTree[FirstMin].parent = i;
        HuffmanTree[SecondMin].parent = i;
    }

    *count = i - 1;

    return 1;
}

//获得哈夫曼编码,Huffman树的极端情况层次只有255层
int CreatHuffmanCode(HuffmanTreeNode *HuffmanTree, char HuffmanCode[LEAFMAX][CODEMAXSIZE])
{
    int i, j, cursor;
    char CodeTemp[CODEMAXSIZE];
    
    assert(HuffmanCode);    //确保传进来的指针有效

    for (i = 0; i < LEAFMAX; i++) {
        if (HuffmanTree[i].weight != 0) {
            j = i;
            cursor = CODEMAXSIZE - 1;
            CodeTemp[cursor] = '\0';
            cursor--;
            
            while (HuffmanTree[j].parent > -1) {
                assert(!(cursor < 0));     //断言函数,保证程序的安全性(如果超过255层则表示程序出错)
                if (j == HuffmanTree[HuffmanTree[j].parent].LChild){
                    CodeTemp[cursor] = '0';
                } else if (j == HuffmanTree[HuffmanTree[j].parent].RChild) {
                    CodeTemp[cursor] = '1';
                } else {
                    return 0;
                }
                cursor--;
                j = HuffmanTree[j].parent;
            }
            strcpy(HuffmanCode[i], CodeTemp + cursor + 1);
        }
    }

    return 1;
}

