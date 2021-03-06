/*************************************************************************
	> File Name: Huffman.c
	> Author: jungzhang
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年11月26日 星期四 20时12分39秒
	> Description:  哈夫曼树,静态三叉链表
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;          //哈夫曼树的叶子结点个数
int SIZE;       //哈夫曼树的存储池大小

//判断某个字符是否在数组中
int IsExist(char data[], char tar)
{
    int i;
    for (i = 0; data[i] != '\0'; i++){
        if (data[i] == tar){
            return 1;
        }
    }

    return 0;
}

//扫描字符串,得到权值和叶子结点
void ScanStr(char str[], char data[], int weight[])
{
    int i, j, k = 0;

    for (i = 0; i < strlen(str); i++){
        if (!IsExist(data, str[i]))
            data[k] = str[i];
        else {
            continue;
        }
        for (j = 0; j < strlen(str); j++){
            if (str[j] == data[k])
                weight[k]++;
        }
        k++;
    }
    N = strlen(data);
    SIZE = 2 * N - 1;
}

//哈夫曼树的存储结构
typedef struct Huffman{
    char data;
    int weight;
    int parent, LChid, RChid;
}Huffman;

//初始化哈夫曼树
Huffman *InitTree(char data[], int weight[])
{
    Huffman *root;
    int i;

    root = (Huffman *)malloc(sizeof(Huffman) * SIZE);  //分配存储池

    for (i = 0; i < N; i++){
        root[i].data = data[i];      //将叶子结点放入存储池的前端,并将他们的双亲和孩子结点都置为无效
        root[i].weight = weight[i];
        root[i].parent = -1;
        root[i].LChid = -1;
        root[i].RChid = -1;
    }

    for (i; i < SIZE; i++){    //将存储池中剩余的结点都初始化为未使用状态
        root[i].data = '\0';
        root[i].weight = 0;
        root[i].parent = -1; 
        root[i].LChid = -1;
        root[i].RChid = -1;    
    }
    
    return root;
}

//从root中选取两个权值最小的结点,b中存储的是次小值下标,a中存储的是最小值下标
void SelectNode(Huffman *root, int *a, int *b)
{
    int i;

    for (i = 0; root[i].weight != 0 && root[i].parent != -1; i++);  //找到数组中下标从0开始的第一个未建树结点下标
    *a = i;     *b = i;         //将该下标作为初始值
    
    //后两个if语句防止了当第一个未建树的权值是最小值时返回的a,b全为最小值情况的发生
    for (i = 0; root[i].weight != 0; i++){  //遍历所有存储池中已使用的元素
        if (root[i].parent == -1 && root[i].weight <= root[*a].weight){  //如果遍历到的元素权值比最小值小
            *b = *a;    *a = i;     //将最小值作为次小值(下标),并将该值作为最小值(下标)
        }
        else if (*a == *b && root[i].parent == -1){   //如果a,b值相同表明还未进行次小值比较,将此时的值暂且作为次小值
            *b = i;
        }  //如果遍历到的元素权值比次小值小,并且确定已进行次小值的比较
        else if (root[i].parent == -1 && root[i].weight <= root[*b].weight && *a != *b){  
            *b = i;  //将该值作为次小值
        }
    }
}

//创建哈夫曼树
int CreatHuffmanTree(Huffman *root)
{
    int i;
    int a, b;

    if (!root)
        return 0;

    for (i = N; i < SIZE; i++){
        SelectNode(root, &a, &b);
        root[i].weight = root[a].weight + root[b].weight;
        root[i].LChid = a;
        root[i].RChid = b;
        root[a].parent = i;
        root[b].parent = i;
    }

    return 1;
}

//计算WPL
int CalculateWPL(Huffman *root)
{
    int i, j, count = 0;
    int wpl = 0;

    for (i = 0; i < N; i++){
        count = 0;
        for (j = i; root[j].parent != -1; j = root[j].parent){
            count++;
        }
        wpl = wpl + count * root[i].weight;
    }

    return wpl;
}

//获取哈夫曼编码
void GetHuffmanCode(Huffman *root, char code[100][100])
{
    int i,j,k;
    for (i = 0; i < N; i++){
        k = N - 1;
        for (j = i; root[j].parent != -1; j = root[j].parent){
            if (j == root[root[j].parent].LChid) {
                code[i][k] = '0';
            } 
            else if (j == root[root[j].parent].RChid) {
                code[i][k] = '1';
            }
            k--;
        }
    }
}

//得到某个字符的哈夫曼编码数组的下标
int GetCodeVal(char tar, char data[])
{
    int i;
    for (i = 0; i < N; i++){
        if (data[i] == tar){
            return i;
        }
    }

    return -1;
}

//对字符串进行编码输出
void StrToCode(char str[], char data[], char code[100][100])
{
    int i, j, len, tar;
    len = strlen(str);
    for (i = 0; i < len; i++){
        tar = GetCodeVal(str[i], data);
        if (tar == -1){
            printf("ERROR!\n");
            exit(-1);
        }
        for (j = 0; j < N; j++){
            if (code[tar][j] != '\0'){
                printf("%c",code[tar][j]);
            }
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char data[100] = {0}, str[1000];
    char code[100][100] = {0};
    int weight[100] = {0};
    Huffman *root;
    int i,j;

    scanf("%s", str);
    ScanStr(str, data, weight);
    setbuf(stdin, NULL);
    root = InitTree(data, weight);
    CreatHuffmanTree(root);
    GetHuffmanCode(root, code);

    //输出哈夫曼编码
    for (i = 0; i < N; i++){
        printf("%c : ", root[i].data);
        for (j = 0; j < N; j++){
            if (code[i][j] != '\0'){
                printf("%c", code[i][j]);
            }
        }
        printf("\n");
    }

    StrToCode(str, data, code);

    printf("WPL = %d\n", CalculateWPL(root));
    
    return 0;
}
