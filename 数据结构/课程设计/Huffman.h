/*************************************************************************
	> File Name: Huffman.h
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月25日 星期五 19时14分33秒
	> Description:  哈夫曼树的操作接口
 ************************************************************************/
#ifndef _HUFFMAN_H
#define _HUFFMAN_H

#include "Common.h"

//初始化哈夫曼树
HuffmanTreeNode *InitHuffmanTree(void);

//创建哈夫曼树
int CreatHuffmanTree(HuffmanTreeNode *HuffmanTree, int *weight, int *count);

//获得哈夫曼编码
int CreatHuffmanCode(HuffmanTreeNode *HuffmanTree, char HuffmanCode[LEAFMAX][CODEMAXSIZE]);

#endif
