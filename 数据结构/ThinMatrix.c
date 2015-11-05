/*******************************************************************************
 Author	 : zhanggen
 Email	 : zhanggen.jung@gmail.com  or  jungzhang@xiyoulinux.org
 Last modified : 2015-10-26 20:03
 Filename	 : ThinMatrix.c
 Description	 : 稀疏矩阵的相关运算
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

//三元组数据定义
typedef struct {
	
	int row, col;
	int value;
	
}Triple;

//三元组结点定义
typedef struct {
	
	Triple data[MAXSIZE];
	int rows, cols, len;	//矩阵的行列和非零元素的个数

}TSMatrix;

//初始化三元组
TSMatrix *InitTriple(int rows, int cols, int len)
{
	if (rows <= 0 && cols <= 0 && len < 0){
		printf("初始化参数有误!\n");
		exit(-1);
	}
	TSMatrix *matrix = (TSMatrix *)malloc(sizeof(TSMatrix));
	matrix->rows = rows;
	matrix->cols = cols;	
	matrix->len = len;

	return matrix;
}

//输入三元组
int InputValue(TSMatrix *matrix)
{
	int row, col, i, val;

	for (i = 0; i < matrix->len; i++){
		printf("请输入行：");
		scanf("%d", &row);
		printf("请输入列：");
		scanf("%d", &col);
		if (row > matrix->rows || col > matrix->cols){
			printf("输入的行(或列)超过矩阵的最大行(或列)!\n");
			return 0;
		}
		if (i > 0 && row < matrix->data[i - 1].row){
			printf("输入的列值小于前一个列值!\n");
			return 0;
		}
		if (i > 0 && row == matrix->data[i - 1].row && col < matrix->data[i - 1].col){
			printf("输入的行值小于前一个行值!\n");
			return 0;
		}
		printf("请输入本坐标下的值:");
		scanf("%d", &val);
		matrix->data[i].row = row;	matrix->data[i].col = col;
		matrix->data[i].value = val;
	}

	return 1;
}

//将三元组矩阵按照普通矩阵的形式输出
void ShowMatrix(TSMatrix *matrix)
{
	int i, j, k = 0, count = 0;

	for (i = 0; i < matrix->rows; i++){
		for (j = 0; j < matrix->cols; j++){
			if (count < matrix->len && i+1 == matrix->data[k].row && j+1 == matrix->data[k].col){
				printf("%5d", matrix->data[k].value);
				k++;	count++;
			}
			else {
				printf("%5d", 0);
			}
		}
		printf("\n");
	}
}

//两个三元组矩阵的相加
TSMatrix *AddMatrix(TSMatrix *a, TSMatrix *b)
{
	int i, j, k = 0, m = 0, n = 0;
	TSMatrix *result;
	if (a->rows != b->rows || a->cols != b->cols){
		printf("两个矩阵不符合相加的条件!\n");
		return NULL;
	}
	result = InitTriple(a->rows, a->cols, 0);
	for (i = 1; i <= a->rows; i++){
		for (j = 1; j <= a->cols; j++){
			//如果该坐标在a和b中都存在,则将a,b相加
			if ((i == a->data[k].row && j == a->data[k].col) && (i == b->data[m].row && j == b->data[m].col)){
				result->data[n].row = a->data[k].row;
				result->data[n].col = a->data[k].col;
				result->data[n].value = a->data[k].value + b->data[m].value;
				m++;	n++;	k++;	result->len++;
			}	//如果a中存在,而b中不存在则a中此坐标的元素直接赋值给结果中
			else if (i == a->data[k].row && j == a->data[k].col){
				result->data[n].row = a->data[k].row;
				result->data[n].col = a->data[k].col;
				result->data[n].value = a->data[k].value;
				n++;	k++;	result->len++;
			}
			else if (i == b->data[m].row && j == b->data[m].col){
				result->data[n].row = b->data[m].row;
				result->data[n].col = b->data[m].col;
				result->data[n].value = b->data[k].value;
				n++;	m++;	result->len++;
			}
		}
	}

	return result;
}

//两个三元组矩阵的相减
TSMatrix *SubMatrix(TSMatrix *minuend, TSMatrix *sub)
{
	int i, j, k = 0, m = 0, n = 0;
	TSMatrix *result;
	if (sub->rows != minuend->rows || sub->cols != minuend->cols){
		printf("两个矩阵不符合相加的条件!\n");
		return NULL;
	}
	result = InitTriple(minuend->rows, minuend->cols, 0);
	for (i = 1; i <= minuend->rows; i++){
		for (j = 1; j <= minuend->cols; j++){
			//如果该坐标在a和b中都存在,则将minuend减去sub
			if ((i == minuend->data[k].row && j == minuend->data[k].col) && (i == sub->data[m].row && j == sub->data[m].col)){
				result->data[n].row = minuend->data[k].row;
				result->data[n].col = minuend->data[k].col;
				result->data[n].value = minuend->data[k].value - sub->data[m].value;
				m++;	n++;	k++;	result->len++;
			}	//如果a中存在,而b中不存在则a中此坐标的元素直接赋值给结果中
			else if (i == minuend->data[k].row && j == minuend->data[k].col){
				result->data[n].row = minuend->data[k].row;
				result->data[n].col = minuend->data[k].col;
				result->data[n].value = minuend->data[k].vaule;
				n++;	k++;	result->len++;
			}	//只存在于减数中,而被减数中不存在
			else if (i == sub->data[m].row && j == sub->data[m].col){
				result->data[n].row = sub->data[m].row;
				result->data[n].col = sub->data[m].col;
				result->data[n].value = 0 - sub->data[m].vaule;
				n++;	m++;	result->len++;
			}
		}
	}

	return result;
}

//两个三元组矩阵的相乘
TSMatrix *MultMatrix(TSMatrix *a, TSMatrix *b)
{
	if (a->rows != b->cols){
		printf("两个矩阵不符合相乘条件!\n");
		return NULL;
	}
}

//三元组矩阵的转置
TSMatrix *TranMatrix(TSMatrix matrix)
{
	
}

int main(void)
{
	TSMatrix *a1, *a2, *result1, *result2;
	a1 = InitTriple(3, 3, 3);
	a2 = InitTriple(3, 3, 3);
	
	InputValue(a1);
	InputValue(a2);
	
	ShowMatrix(a1);
	ShowMatrix(a2);

	if ((result1 = AddMatrix(a1, a2)) != NULL)
		ShowMatrix(result1);
	if ((result2 = SubMatrix(a1, a2)) != NULL)
		ShowMatrix(result2);
	
	return 0;
}
