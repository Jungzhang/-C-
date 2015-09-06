/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-11 20:55
 * Filename	 : main.c
 * Description	 : ls命令部分功能的主程序文件
 * *****************************************************************************/
#include "head.h"

extern choise_display(DIRNAME *pHead,char *path,int type);
extern save_dir(DIRNAME *pHead,char *path);

//命令行参数的解析,若解析失败则返回-1
int analyze_param(char *param)
{
	char temp[3];
	temp[0] = param[1];	
	temp[1] = param[2];	
	temp[3] = '\0';
	if (strcmp(temp,"a") == 0)
		return A;
	else if ((strcmp(temp,"l")==0)||(strcmp(temp,"lc")==0)||(strcmp(temp,"cl")==0))
		return L;
	else if (strcmp(temp,"c") == 0)
		return C;
	else if ((strcmp(temp,"g")==0)||(strcmp(temp,"lg")==0)||(strcmp(temp,"gl")==0)||(strcmp(temp,"cg")==0)||(strcmp(temp,"gc")==0))
		return G;
	else if ((strcmp(temp,"U") == 0)||(strcmp(temp,"Uc")==0)||(strcmp(temp,"cU")==0))
		return CAPU;
	else if ((strcmp(temp,"la") == 0) || (strcmp(temp,"al") == 0))
		return LA;
	else if ((strcmp(temp,"ca")==0)||(strcmp(temp,"ac")==0))
		return AC;
	else if ((strcmp(temp,"Ua")==0)||(strcmp(temp,"aU")==0))
		return ACAPU;
	else if ((strcmp(temp,"lU")==0)||(strcmp(temp,"Ul")==0))
		return LCAPU;
	else if ((strcmp(temp,"gU")==0)||(strcmp(temp,"Ug")==0))
		return GCAPU;
	else if ((strcmp(temp,"ga")==0)||(strcmp(temp,"ag")==0))
		return GA;
	else if ((strcmp(temp,"r")) == 0)
		return R;
	else if ((strcmp(temp,"i")) == 0)
		return I;
	else if ((strcmp(temp,"R")) == 0)
		return CAPR;
	return -1;
}

int main(int argc,char *argv[])
{
	char path[PATH_MAX + 1];
	DIRNAME *pHead = (DIRNAME *)malloc(sizeof(DIRNAME));
	int type = 0;
	if (argc == 1)
	{
		strcpy(path,"./");
	}
	else if (argc == 2)
	{
		if ((strlen(argv[1]) == 1) || (argv[1][0] != '-'))
		{
			strcpy(path,argv[1]);
		}
		else
		{
			if ((type = analyze_param(argv[1])) == -1)
			{
				printf("参数有误,暂不支持该命令参数!\n");  exit(-1);
			}
			strcpy(path,"./");
		}
	}
	else if (argc == 3)
	{
		if ((strlen(argv[1]) == 1) || (argv[1][0] != '-')) //判断参数1是否为路径参数
		{
			if ((strlen(argv[2]) == 1) || (argv[2][0] != '-'))   //判断参数2是否为路径参数
			{
				printf("暂不支持多路径参数!\n");	exit(-1);
			}
			else if ((type = analyze_param(argv[2])) == -1)
			{
				printf("参数有误,暂不支持该命令参数!\n");  exit(-1);
			}
			strcpy(path,argv[1]);
		}
		else if ((strlen(argv[2]) == 1) || (argv[2][0] != '-'))		//判断参数2是否为路径参数
		{
			if ((type = analyze_param(argv[1])) == -1)
			{
				printf("参数有误,暂不支持该命令参数!\n");  exit(-1);
			}
			strcpy(path,argv[2]);
		}
		else
		{
			printf("暂只支持一个路径参数和一个命令参数!\n");	exit(-1);
		}
	}
	else
	{
		printf("暂只支持一个命令参数和一个路径参数!\n");
		exit(-1);
	}
	save_dir(pHead,path);
	choise_display(pHead,path,type);
	printf("\n");

	return 0;
}
