/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-10 18:19
 * Filename	 : head.h
 * Description	 : 定义代表权限的宏和存放文件名的结构体变量以及程序所用到的
                   所有头文件
 * *****************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>

#define NONE     0     //不带任何参数,只输出文件名字(不含隐藏文件)并按字典顺序排序
#define A        1     //带-a参数,输出所有文件名字(含隐藏文件)并按字典顺序排序
#define L        2     //带-l参数,输出文件(不包含隐藏文件)的详细信息,并按字典顺序输出
#define C        3     //带-c参数,输出文件(不包含隐藏文件)的名字，按ctime排序
#define G        4     //带-g参数,输出文件(不包含隐藏文件)的除所有者信息外的详细信息
#define CAPU     5     //带-U参数,不排序输出文件(不包含隐藏文件)名字
#define LA	     6     //带-la参数,按拼音顺序输出全部文件(包含隐藏文件)的详细信息
#define AC       7     //带-ac参数,按ctime顺序输出文件名(不包含隐藏文件)
#define ACAPU    8     //带-aU参数,不排序输出全部文件名(包含隐藏文件)
#define LCAPU    9     //带-lU参数,不排序输出文件(不包含隐藏文件)的详细信息
#define GCAPU    10    //带-gU参数,不排序输出文件(不包含隐藏文件)除所有者外的所有信息
#define GA       11    //带-ga参数,按拼音排序输出所有文件(包含隐藏文件)除 所有者外的所有信息
#define CAPR	 12	   //带R参数,递归输出路径下的所有文件
#define R		 13	   //带r参数,按名字排序后逆置输出
#define I		 14	   //带i参数,输出文件的i-node节点

typedef struct dirname{
	
	char dir_name[NAME_MAX + 1];
	struct stat buf;
	struct dirname *pNext;

}DIRNAME;
