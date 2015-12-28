/*************************************************************************
> File Name: Function.c
> Author: Jung
> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
> Created Time: 2015年12月27日 星期日 13时51分49秒
> Description:
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Common.h"
#include "Huffman.h"
#include "Function.h"

//压缩函数
int Compression(char SourceFileName[], char TarFileName[])
{
    int weight[LEAFMAX], ch, i, num, count = 0;
    HuffmanTreeNode *HuffmanTree;
    char HuffmanCode[LEAFMAX][CODEMAXSIZE], StrNum[9], TempFileName[256] = {0,0};
    FILE *SourceFileFp, *TarFileFp;
    FILE *TempFileFp;

    assert(SourceFileName);     //断言函数,确保传进来的各个数组地址合法
    assert(TarFileName);
    strcpy(TempFileName, TarFileName);
    strcat(TempFileName, ".tmp");

    if (GetWeight(weight, SourceFileName) == 0) {
        printf("权值统计失败!\n");
        return 0;
    }

    if ((HuffmanTree = InitHuffmanTree()) == NULL) {
        printf("HuffmanTree初始化失败!\n");
        return 0;
    } 
    if (CreatHuffmanTree(HuffmanTree, weight, &i) == 0) {
        printf("HuffmanTree创建失败!\n");
        return 0;
    }
    if (CreatHuffmanCode(HuffmanTree, HuffmanCode) == 0) {
        printf("HuffmanCode创建失败!\n");
        return 0;
    }

    if ((SourceFileFp = fopen(SourceFileName, "rb")) == NULL) {
        printf("源文件打开失败!\n");
        return 0;
    }
    if ((TempFileFp = fopen(TempFileName, "wb+")) == NULL) {
        printf("临时文件打开失败!\n");
        return 0;
    }
    if ((TarFileFp = fopen(TarFileName, "wb")) == NULL) {
        printf("目标文件打开失败!\n");
        return 0;
    }

    while ((ch = fgetc(SourceFileFp)) != EOF) {
        fwrite(HuffmanCode[ch], strlen(HuffmanCode[ch]), 1, TempFileFp);
    }

    fseek(TempFileFp, 0, SEEK_SET);

    fwrite(weight, sizeof(weight), 1, TarFileFp);
    fwrite(&count, sizeof(int), 1, TarFileFp);

    while ((count = fread(StrNum, sizeof(char), 8, TempFileFp)) == 8) {
        StrNum[8] = '\0';
        num = StrToChar(StrNum);
        fputc(num, TarFileFp);
    }

    fseek(TarFileFp, sizeof(weight), SEEK_SET);
    fwrite(&count, sizeof(int), 1, TarFileFp);
    fseek(TarFileFp, 0, SEEK_END);

    i = count;
    if (count > 0) {
        while(i < 8) {
            StrNum[i] = '0';
            i++;
        }
        StrNum[8] = '\0';
        num = StrToChar(StrNum);
        fputc(num, TarFileFp);
        CharToStr(num, StrNum);
    }

    printf("压缩率：%lf%%\n", ((double)ftell(TarFileFp)) / ftell(SourceFileFp) * 100);

    fclose(TarFileFp);
    fclose(TempFileFp);
    fclose(SourceFileFp);
    remove(TempFileName);

    return 1;
}

//解压缩函数
int Decompression(char *SourceFileName, char *TarFileName)
{
    int weight[LEAFMAX], ch, root, i, count, temp;
    char TempFileName[256] = {0,0}, StrNum[9];
    FILE *SourceFileFp, *TarFileFp, *TempFileFp;
    HuffmanTreeNode *HuffmanTree;
    unsigned long FileEnd, FileLength = 1027;

    if ((SourceFileFp = fopen(SourceFileName, "rb")) == NULL) {
        printf("打开源文件失败");
        return 0;
    }
    if (fread(weight, sizeof(weight), 1, SourceFileFp) != 1) {
        printf("读取源文件压缩信息失败!\n");
        return 0;
    }
    if (fread(&count, sizeof(int), 1, SourceFileFp) != 1) {
        printf("读取源文件压缩信息失败!\n");
        return 0;
    }
    if ((HuffmanTree = InitHuffmanTree()) == NULL) {
        printf("HuffmanTree初始化失败!\n");
        return 0;
    }
    if (CreatHuffmanTree(HuffmanTree, weight, &root) == 0) {
        printf("HuffmanTree创建失败!\n");
        return 0;
    }

    if (HuffmanTree[root].parent != -1) {
        printf("HuffmanTree根结点获取失败!\n");
        fclose(SourceFileFp);
        return 0;
    }

    strcpy(TempFileName, TarFileName);
    strcat(TempFileName, ".tmp");

    if ((TempFileFp = fopen(TempFileName, "wb+")) == NULL) {
        printf("临时文件打开失败!\n");
        return 0;
    }

    if ((TarFileFp = fopen(TarFileName, "wb")) == NULL) {
        printf("打开目标文件失败!\n");
        return 0;
    }

    fseek(SourceFileFp, 0, SEEK_END);
    FileEnd = ftell(SourceFileFp);
    fseek(SourceFileFp, 1028, SEEK_SET);

    while ((temp = fgetc(SourceFileFp)) != EOF && FileLength < FileEnd - 2) {
        FileLength++;
        CharToStr(temp, StrNum);
        fwrite(StrNum, strlen(StrNum), 1, TempFileFp);
    }

    CharToStr(temp, StrNum);

    if (count != 0) {
        StrNum[count] = '\0';
    }
    fwrite(StrNum, strlen(StrNum), 1, TempFileFp);

    fseek(TempFileFp, 0, SEEK_SET);
    
    while (1) {
        i = root;
        
        while (HuffmanTree[i].LChild != -1 && (ch = fgetc(TempFileFp)) != EOF) {
            if (ch == '0') {
                i = HuffmanTree[i].LChild;
            } else if (ch == '1') {
                i = HuffmanTree[i].RChild;
            }
        }
        
        if (ch == EOF) {
            break;
        }
        fputc(i, TarFileFp);
    }

    fclose(SourceFileFp);
    fclose(TempFileFp);
    fclose(TarFileFp);
    remove(TempFileName);

    return 1;
}

