/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-10-29 19:51
 * Filename	 : BiTree.c
 * Description	 : 二叉树相关操作
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "BiTree.h"
#include <string.h>

//树的创建
BiTree *CreatTree(void)
{
	char ch;
	BiTree *NewChid;
	ch = getchar();
	
	if (ch == '#'){
		return NULL;
	}
	else{
		NewChid = (BiTree *)malloc(sizeof(BiTree));
		NewChid->data = ch;
		NewChid->LChid = CreatTree();
		NewChid->RChid = CreatTree();
	}
	return NewChid;
}

//输入树的先序序列和中序序列,创建一棵二叉树
BiTree *PreCreat(char pre[], char in[], int pre_start, int in_start, int len)
{
    BiTree *root;
    int m = 0;

    if (len <= 0){
        return NULL;
    }

    root = (BiTree *)malloc(sizeof(BiTree));
    root->data = pre[pre_start];
    while(in[m] != '\0'  && in[m] != pre[pre_start]){
        m++;
    }
    root->LChid = PreCreat(pre, in, pre_start + 1, in_start, m - in_start);
    root->RChid = PreCreat(pre, in, pre_start + 1 + (m - in_start), m + 1, len - (m - in_start) - 1);

    return root;
}

//输入树的后序序列和中序序列，创建一棵二叉树
BiTree *PostCreat(char post[], char in[], int post_end, int in_start, int len)
{
    BiTree *root;
    int m = 0;

    if (len <= 0){
        return NULL;
    }
    root = (BiTree *)malloc(sizeof(BiTree));
    root->data = post[post_end];
    while(in[m] != '\0' && in[m] != post[post_end]){
        m++;
    }
    //创建左子树
    root->LChid = PostCreat(post, in, post_end - 1 - (len - (m - in_start) - 1), in_start, m - in_start);
    root->RChid = PostCreat(post, in, post_end - 1, m + 1, len - (m - in_start) - 1);
    
    return root;
}

//树的先序遍历(递归)
void PreOrder(BiTree *root)
{
	if (root == NULL)
		return ;
	printf("%c", root->data);
	PreOrder(root->LChid);
	PreOrder(root->RChid);
}

//树的非递归遍历(先序)
void Pre_Order(BiTree *root)
{
	STACK *s = InitStack();
	BiTree *temp = root;

	while (temp != NULL || !IsEmpty(s)) {
	    if (temp != NULL){
            PushStack(s, temp);
            printf("%c", temp->data);
            temp = temp->LChid;
        }
        else {
            PopStack(s, &temp);
            temp = temp->RChid;
        }
	}
	DestroyStack(s);
}

//树的中序遍历(递归)
void InOrder(BiTree *root)
{
	if (root == NULL)
		return ;
	InOrder(root->LChid);
	printf("%c", root->data);
	InOrder(root->RChid);
}

//树的非递归遍历(中序)
void In_Order(BiTree *root)
{
	STACK *s = InitStack();
	BiTree *temp = root;
	while(temp != NULL || !IsEmpty(s)){
		if (temp != NULL){
			PushStack(s,temp);
			temp = temp->LChid;
		}
		else{
			PopStack(s, &temp);
			printf("%c", temp->data);
			temp = temp->RChid;
		}
	}
	DestroyStack(s);
}

//树的后序遍历(递归)
void PostOrder(BiTree *root)
{
	if (root == NULL)
		return ;
	PostOrder(root->LChid);
	PostOrder(root->RChid);
	printf("%c", root->data);
}

//树的非递归遍历(后序)
void Post_Order(BiTree *root)
{
	STACK *s = InitStack();
	BiTree *temp = root, *visited;
	while(temp != NULL || !IsEmpty(s)){
		if (temp != NULL){
			PushStack(s, temp);
			temp = temp->LChid;
		}
		else {
			GetTop(s, &temp);
			if (temp->RChid == NULL || visited == temp->RChid) {
				PopStack(s, &temp);
				printf("%c", temp->data);
				visited = temp;	temp = NULL;
			}
			else {
				temp = temp->RChid;
			}
		}
	}
}

//统计叶子节点个数,并输出叶子节点
void LeafCount(BiTree *root, int *count)
{
	if (root == NULL)
		return ;
	LeafCount(root->LChid, count);
	LeafCount(root->RChid, count);
	if (root->LChid == NULL && root->RChid == NULL){
		printf("%c", root->data);
		(*count)++;
	}
}

//求二叉树高
void BiTreeDepth(BiTree *root, int h, int *depth)
{
	if (root != NULL){
		if (h > *depth)
			*depth = h;
		BiTreeDepth(root->LChid, h + 1, depth);
		BiTreeDepth(root->RChid, h + 1, depth);
	}
}
//求树叶子结点的路径
void PrePath(BiTree *root, char path[], int len)
{
	int i;
	if (root == NULL)
		return ;
	if (root->LChid == NULL && root->RChid == NULL){
		printf("%c : ", root->data);
		for(i = 0; i < len; i++){
			printf("%c", path[i]);
		}
		printf("\n");
	}
	path[len] = root->data;	len++;
	PrePath(root->LChid, path, len);
	PrePath(root->RChid, path, len);
	len--;
}

//二元组打印树的层次
void PrintLevel(BiTree *root, int h)
{
	if (root != NULL){
		printf("(%c,%d)", root->data, h);
		PrintLevel(root->LChid, h + 1);
		PrintLevel(root->RChid, h + 1);
	}
}

//求孩子兄弟表示法的叶子结点个数
void PrintLeaf(BiTree *root, int *count)
{
	if (!root)
		return;
	if (root->LChid == NULL)
		(*count)++;
	PrintLeaf(root->LChid, count);
	PrintLeaf(root->RChid, count);	
}

//求兄弟链表表示法中树的高度
void TreeDepth(BiTree *root, int h, int *depth)
{
	if (root != NULL){
		if (h > (*depth))
			(*depth) = h;
		TreeDepth(root->LChid, h + 1, depth);
		TreeDepth(root->RChid, h, depth);
	}
}

//打印二叉树
void PrintTree(BiTree *root, int h)
{
	int i;
	if (root == NULL)
		return;
	PrintTree(root->RChid, h + 1);
	for (i = 0; i < h; i++){
		printf("  ");
	}
	printf("%c\n", root->data);
	PrintTree(root->LChid, h+1);
}

int main(void)
{
	BiTree *root;
    char pre[256], in[256];
    int count = 0;
    scanf("%s", pre);
    scanf("%s", in);
    count = strlen(pre);
    root = PostCreat(pre, in, count - 1, 0, count);
//	char path[256];
//	int len = 0;
//	int count = 0;
//	int h = 1, depth = 0;
//	printf("请输入要创建树的先序序列:");
//	root = CreatTree();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
//	PrintLeaf(root, &count);
//	printf("\n叶子节点个数:%d\n", count);
//	TreeDepth(root, h, &depth);
//	printf("树的高度为：%d\n", depth);
//	PrePath(root, path, len);
//	PrintLevel(root, h);
//	printf("\n非递归先序遍历:");
//	Pre_Order(root);
//	printf("\n非递归中序遍历:");
//	In_Order(root);
//	printf("\n非递归后序遍历:");
//	Post_Order(root);
	printf("\n");
//	PrintTree(root, 1);
	
	return 0;
}
