/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 * Last modified : 2015-10-29 19:51
 * Filename	 : BiTree.c
 * Description	 : 二叉树相关操作
 * *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

//树的数据结构
typedef struct BiTree{
	
	char data;
	struct BiTree *LChid;
	struct BiTree *RChid;

}BiTree;

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

//树的先序遍历
void PreOrder(BiTree *root)
{
	if (root == NULL)
		return ;
	printf("%c", root->data);
	PreOrder(root->LChid);
	PreOrder(root->RChid);
}

//树的中序遍历
void InOrder(BiTree *root)
{
	if (root == NULL)
		return ;
	InOrder(root->LChid);
	printf("%c", root->data);
	InOrder(root->RChid);
}

//树的后序遍历
void PostOrder(BiTree *root)
{
	if (root == NULL)
		return ;
	PostOrder(root->LChid);
	PostOrder(root->RChid);
	printf("%c", root->data);
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

//求树高
void 

//打印二叉树

int main(void)
{
	BiTree *root;
	int count = 0;
	printf("请输入要创建树的先序序列:");
	root = CreatTree();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");
	LeafCount(root, &count);
	printf("\n叶子节点个数:%d\n", count);
	
	return 0;
}
