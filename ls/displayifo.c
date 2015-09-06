/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-06-10 10:55
 * Filename	 : displayifo.c
 * Description	 : 解析单个文件详细信息并显示
 * *****************************************************************************/
 
#include "head.h"

//解析文件类型
void analyze_type(struct stat *buf)
{
	if (S_ISLNK(buf->st_mode))
		printf("l");
	else if (S_ISREG(buf->st_mode))
		printf("-");
	else if (S_ISDIR(buf->st_mode))
		printf("d");
	else if (S_ISCHR(buf->st_mode))
		printf("c");
	else if (S_ISBLK(buf->st_mode))
		printf("b");
	else if (S_ISFIFO(buf->st_mode))
		printf("f");
	else if (S_ISSOCK(buf->st_mode))
		printf("s");
}

//解析所有者权限
void analyze_user(struct stat *buf)
{
	if (buf->st_mode & S_IRUSR)
		printf("r");
	else
		printf("-");
	if (buf->st_mode & S_IWUSR)
		printf("w");
	else
		printf("-");
	if (buf->st_mode & S_IXUSR)
		printf("x");
	else
		printf("-");
}

//解析所有组的权限
void analyze_group(struct stat *buf)
{
	if (buf->st_mode & S_IRGRP)
		printf("r");
	else
		printf("-");
	if (buf->st_mode & S_IWGRP)
		printf("w");
	else
		printf("-");
	if (buf->st_mode & S_IXGRP)
		printf("x");
	else
		printf("-");
}

//解析其他用户的权限
void analyze_other(struct stat *buf)
{
	if (buf->st_mode & S_IROTH)
		printf("r");
	else
		printf("-");
	if (buf->st_mode & S_IWOTH)
		printf("w");
	else
		printf("-");
	if (buf->st_mode & S_IXOTH)
		printf("x");
	else
		printf("-");
}

//对文件名进行着色处理,并输出文件名
void showifo(struct stat *pbuf,char *name)
{
	if (S_ISDIR(pbuf->st_mode))
		printf("\033[1;34;49m%s\t\033[0m",name);
	else if ((pbuf->st_mode & S_IXUSR) || (pbuf->st_mode & S_IXGRP) || (pbuf->st_mode & S_IXOTH))
		printf("\033[1;32;49m%s\t\033[0m",name);
	else
		printf("%s\t",name);
}
//按需求打印文件全部信息
void display_attribute(struct stat *buf,char *name,int type)
{
	char time[32];
	struct passwd *psd = getpwuid(buf->st_uid); //从st_uid指定的标识码中获取所有者信息
	struct group *pgroup = getgrgid(buf->st_gid); //从st_gid指定的标识码中获取组信息
	
	strcpy(time,ctime(&(buf->st_mtime)));
	time[strlen(time) - 1] = '\0';

	analyze_type(buf); //解析并打印类型
	analyze_user(buf);  //所有者权限信息
	analyze_group(buf); //所有者用户组权限信息
	analyze_other(buf);	//其他用户权限信息
	
	printf(" %4d ",(int)buf->st_nlink);  //连接到该文件的硬链接数目
	if (type == 0)
		printf(" %-8s ",psd->pw_name);  //打印所有者名
	printf(" %-8s ",pgroup->gr_name); //打印组名
	printf(" %6d ",(int)buf->st_size); //打印大小
	printf("  %s  ",time);
	showifo(buf,name);	printf("\n");
}
