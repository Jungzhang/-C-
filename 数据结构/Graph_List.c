/*************************************************************************
	> File Name: Graph_List.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月05日 星期六 13时57分02秒
	> Description: 图的一些操作,邻接表版
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "GraphStack.h"
#include "GraphQueue.h"

#define MAXSIZE 88

//图的关系边定义
typedef struct side{
    int pos;
    int weight;
    struct side *pNext;
}side;

//图的顶点数组定义
typedef struct vertex{
    char data;
    side *pFirst;
}vertex;

//图的数据结构定义
typedef struct graph{
    vertex v[MAXSIZE];
    int len;
}GRAPH;

//初始化图
GRAPH *InitGraph(void)
{
    char data;
    GRAPH *graph;
    graph = (GRAPH *)malloc(sizeof(GRAPH));
    graph->len = 0;
    
//    printf("请输入顶点数据：");
    data = getchar();

    while (data != '\n'){
        graph->v[graph->len].data = data;
        graph->v[graph->len].pFirst = (side *)malloc(sizeof(side));
        graph->v[graph->len].pFirst->pNext = NULL;
        graph->len++;
        data = getchar();
    }

    return graph;
}

//通过字符找到data数组位置
void SearcPos(GRAPH *graph, char start, char end, int *posStart, int *posEnd)
{
    int i;

    *posStart = 0, *posEnd = 0;
    for (i = 0; i < graph->len; i++) {
        if (graph->v[i].data == start) {
            *posStart = i;
        } else if (graph->v[i].data == end) {
            *posEnd = i;
        }
    }
}

//向链表中有序插入某结点
void InsertList(side *pHead, side *pNew)
{
    side *pTemp = pHead;
    while(pTemp->pNext) {
        if (pTemp->pNext->pos > pNew->pos){
            break;
        }
        pTemp = pTemp->pNext;
    }
    pNew->pNext = pTemp->pNext;
    pTemp->pNext = pNew;
}

//创建图
void CreatGraph(GRAPH *graph)
{
    char start, end;
    int weight, posStart, posEnd, i;
    side *pNew;

    while(1){
 //       printf("请输入图的关系集合(start end weight,如：a b 30)输入#结束输入：");
        scanf("%c", &start);
        if (start == '#'){
            break;
        }
        scanf(" %c %d", &end, &weight);     
        getchar();  //清除输入缓存区
        SearcPos(graph, start, end, &posStart, &posEnd);
        if (graph->v[posStart].data != start || graph->v[posEnd].data != end){
            printf("关系输入有误,现在退出!\n"); 
            exit(-1);
        }
        pNew = (side *)malloc(sizeof(side));
        pNew->pos = posEnd;
        pNew->weight = weight;
        InsertList(graph->v[posStart].pFirst, pNew);
    }
}

//取出图graph中ver(出度结点)的下一个结点
int AdjVex(GRAPH *graph, int ver, int visit)
{
    side *pTemp = graph->v[ver].pFirst->pNext;

    //如果访问的结点是第一个结点则返回第一个相邻的结点
    if (ver == visit && pTemp){
        return pTemp->pos;
    }
    
    for (pTemp; pTemp != NULL && pTemp->pos != visit; pTemp = pTemp->pNext);
    
    if (pTemp == NULL)      //如果未找到visit结点则就不存在下一个结点,即返回-1
        return -1;

    if (pTemp->pNext != NULL)   //如果找到visit结点并且下一个结点还存在就返回下一个结点的位置
        return pTemp->pNext->pos;
    else    //如果visit结点的下一个结点不存在就返回-1
        return -1;
}


//DFS(递归)
void DFS_R(GRAPH *graph, int ver, int visited[])
{
    int visit = ver;      //要访问的结点下标
    printf("%c", graph->v[visit].data);
    visited[visit] = 1;
    visit = AdjVex(graph, ver, visit);      //取出ver的下一个邻接点

    while (visit != -1){
        
        if (!visited[visit]){           //如果没有被访问过
            DFS_R(graph, visit, visited);          //DFS该结点
        }
        
        visit = AdjVex(graph, ver, visit);    //取出ver的下一个邻接点
    }
}

//DFS(非递归)
void DFS(GRAPH *graph, int ver, int visited[])
{
    int visit = ver;
    STACK *stack = InitStack();
    
    printf("%c", graph->v[visit].data);
    visited[visit] = 1;
    PushStack(stack, visit);

    while (!IsEmpty(stack)) {
        visit = AdjVex(graph, ver, visit);
        while (visit != -1) {
            if (!visited[visit]) {
                printf("%c", graph->v[visit].data);
                visited[visit] = 1;
                PushStack(stack, visit);
                ver = visit;  //将出度结点更改为新结点
                visit = AdjVex(graph, ver, visit);  //找到新出度结点的下一个邻接点
            } else {
                visit = AdjVex(graph, ver, visit);
            }
        }
        PopStack(stack, &visit);
        if (!IsEmpty(stack)){
            GetTop(stack, &ver);
        }
    }
}

//深搜遍历
void TraverseDFS(GRAPH *graph)
{
    int i;
    int visited[MAXSIZE] = {0,0,0};

    printf("递归：");

    for (i = 0; i < graph->len; i++){
        if (!visited[i]){
            DFS_R(graph, i, visited);
        }
    }

    printf("\n\n");

    for (i = 0; i < MAXSIZE && i <= graph->len; i++){
        visited[i] = 0;
    }

    printf("非递归：");

    for (i = 0; i < graph->len; i++){
        if (!visited[i]) {
            DFS(graph, i, visited);
        }
    }

    printf("\n");
}

//BFS
void BFS(GRAPH *graph, int ver, int visited[])
{
    int visit = ver;
    Queue *q = InitQueue();
    
    printf("%c", graph->v[ver].data);
    visited[visit] = 1;
    InQueue(q, visit);
    
    while (!QIsEmpty(q)) {
        
        OutQueue(q, &ver);
        visit = ver;
        visit = AdjVex(graph, ver, visit);
        
        while (visit != -1) {
            
            if (!visited[visit]) {
                printf("%c", graph->v[visit].data);
                visited[visit] = 1;
                InQueue(q, visit);
            }
            
            visit = AdjVex(graph, ver, visit);
        }
    }
}

//广搜遍历
void TraverseBFS(GRAPH *graph)
{
    int visited[MAXSIZE] = {0, 0, 0};
    int i;

    printf("广度优先搜索：");

    for (i = 0; i < graph->len; i++) {
        
        if (!visited[i]) {
            BFS(graph, i, visited);
        }       
    }

    printf("\n");

}

//计算图的度
void degree(GRAPH *graph, int ver, int *in_degree, int *out_degree, int *total)
{
    int i;
    side *pTemp;

    *in_degree = 0;
    *out_degree = 0;
    *total = 0;

    for (i = 0; i < graph->len; i++) {
        
        pTemp = graph->v[i].pFirst->pNext;

        while (pTemp) {
            
            if (i == ver) {
                ++(*out_degree);
            }
            
            if (pTemp->pos == ver) {
                ++(*in_degree);
            }
            pTemp = pTemp->pNext;
        }
    }

    (*total) = (*out_degree) + (*in_degree);
}

int main(int argc, char *argv[])
{
    int i, in_degree, out_degree, total;
    GRAPH *graph = InitGraph();
    CreatGraph(graph);
    printf("\n");
    TraverseDFS(graph);
    printf("\n");
    TraverseBFS(graph);

    printf("\n%10s%10s%10s%10s\n", "顶点", "入度", "出度", "总度");

    for (i = 0; i < graph->len; i++) {
        degree(graph, i, &in_degree, &out_degree, &total);
        printf("%6c%9d%8d%8d\n", graph->v[i].data, in_degree, out_degree, total);
    }
    
    return 0;
}
