/*************************************************************************
	> File Name: Graph_List.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org  or  zhanggen.jung@gmail.com
	> Created Time: 2015年12月05日 星期六 13时57分02秒
	> Description: 图的一些操作,邻接表版
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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

//DFS(递归)
void DFS_R(GRAPH *graph, int ver, int visited[])
{
    side *pTemp = graph->v[ver].pFirst->pNext;
    printf("%c", graph->v[ver].data);
    visited[ver] = 1;
    
    while (pTemp){
        
        if (!visited[pTemp->pos]){           //如果没有被访问过
            DFS_R(graph, pTemp->pos, visited);          //DFS该结点
        }
        
        pTemp = pTemp->pNext;
    }
}

//DFS(非递归)
void DFS(GRAPH *graph, int ver, int visited[])
{
    side *pTemp;
    STACK *stack = InitStack();
    
    printf("%c", graph->v[ver].data);
    visited[ver] = 1;
    PushStack(stack, ver);

    while (!IsEmpty(stack)) {
        pTemp = graph->v[ver].pFirst->pNext;
        
        while (pTemp) {
            if (!visited[pTemp->pos]) {
                printf("%c", graph->v[pTemp->pos].data);
                visited[pTemp->pos] = 1;
                PushStack(stack, pTemp->pos);
                pTemp = graph->v[pTemp->pos].pFirst;
            }
            pTemp = pTemp->pNext;
        }
        
        PopStack(stack, &ver);
        
        if (!IsEmpty(stack)) {
            PopStack(stack, &ver);
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
    Queue *q = InitQueue();
    side *pTemp;
    
    printf("%c", graph->v[ver].data);
    visited[ver] = 1;
    InQueue(q, ver);
    
    while (!QIsEmpty(q)) {
        
        OutQueue(q, &ver);
        pTemp = graph->v[ver].pFirst->pNext;
        
        while (pTemp) {
            
            if (!visited[pTemp->pos]) {
                printf("%c", graph->v[pTemp->pos].data);
                visited[pTemp->pos] = 1;
                InQueue(q, pTemp->pos);
            }
            pTemp = pTemp->pNext;
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
            BFS(graph, 0, visited);
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

//Dijkstra算法,dist是start点到其他点的距离,path是start到其他各点的最短路径
void Dijkstra(GRAPH *graph, int start, int dist[], int **path)
{
    int i, j, mindist, minpos;
    int *visited = (int *)malloc(sizeof(int) *graph->len);
    side *pTemp;

    //初始化
    for (i = 0; i < graph->len; ++i) {
        
        if (i != start) {
            dist[i] = INT_MAX;
        } else {
            dist[i] = 0;
        }
        
        path[i][0] = -1;  //加上一个最短路径的结束标志
        visited[i] = 0;
    }

    //算法核心
    for (j = 0; j < graph->len; ++j) {
        
        mindist = INT_MAX;
        
        //选择最小值路径的下标和最小值
        for (i = 0; i < graph->len; ++i) {
            if (!visited[i] && dist[i] < mindist) {
                minpos = i;
                mindist = dist[i];
            }
        }
        
        visited[minpos] = 1;  //将最小值的点置为已获得最小路径
        pTemp = graph->v[minpos].pFirst->pNext;  //选择最小值的第一个邻接点
        
        while (pTemp) {
            i = pTemp->pos;  //选择最小值点的邻接点
            //如果该点没有被加入,并且最小值加上该点的权值小于原记录的路径长度
            if (!visited[i] && dist[i] > dist[minpos] + pTemp->weight) { 
                //将路径长度改为新的路径长度
                dist[i] = pTemp->weight + dist[minpos];
                for (j = 0; path[minpos][j] != -1; ++j) {
                    path[i][j] = path[minpos][j];   //将最小值的路径拷贝给本结点
                }
                path[i][j] = minpos;
                path[i][j + 1] = -1;    //因为是以-1作为路径结束的标志,因此必须将其置为-1
            }
            pTemp = pTemp->pNext; //选择最小值点的下一个邻接点
        }
    }

    free(visited);
}

//floyd求最短路径


int main(int argc, char *argv[])
{
    int i, j, in_degree, out_degree, total;
    int *dist, **path;
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
    
    dist = (int *)malloc(sizeof(int) * graph->len);
    path = (int **)malloc(sizeof(int *) * graph->len);

    for (i = 0; i < graph->len; ++i) {
        path[i] = (int *)malloc(sizeof(int) * graph->len);
    }
    
    Dijkstra(graph, 3, dist, path);

    for (i = 0; i < graph->len; ++i) {
        if (dist[i] == INT_MAX) {
            printf("%c无可到达的路径\n", graph->v[i].data);
        } else {
            printf("%c:\t%d\t经过的结点是：", graph->v[i].data, dist[i]);
            for (j = 0; path[i][j] != -1; ++j) {
                printf("%c", graph->v[path[i][j]].data);
            }
            printf("%c\n", graph->v[i].data);
        }
    }
    
    return 0;
}
