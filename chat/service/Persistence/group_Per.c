/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-10 09:39
 * Filename	 : group_Per.c
 * Description	 : 群操作的相关文件操作
 * *****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../Common/common.h"
#include "../Server/group_sev.h"
#include "../Server/user_sev.h"
#include "group_Per.h"

static const char GROUP_FILE[] = "group.dat";
static const char GROUP_FILE_TEMP[] = "grouptemp.dat";

//获取群信息,成功1,错误-1,未找到0
int selectgroup_Per(unsigned int groupid, groupifo *group)
{
	char *path = get_pwd();
	FILE *fp;

	if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			return -1;
		}
	}
	if ((fp = fopen(GROUP_FILE, "rb")) == NULL){
		chdir(path);
		return -1;
	}
	while(!feof(fp)){
		if (fread(group, sizeof(groupifo), 1, fp)){
			if (group->groupid == groupid){
				fclose(fp);
				chdir(path);
				return 1;
			}
		}
	}

	fclose(fp);
	chdir(path);

	return 0;	
}

//保存新创建群进文件,并创建群列表文件
int save_groupifo_Per(groupifo *group)
{
	char *path = get_pwd();
	FILE *fp;
	char id[25];
	char cmd[25];

	if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			return 0;
		}
	}
	if ((fp = fopen(GROUP_FILE, "ab+")) == NULL){
		chdir(path);
		return 0;
	}
	if (fwrite(group, sizeof(groupifo), 1, fp) == 0){
		fclose(fp);
		chdir(path);
		return 0;
	}
	
	strcpy(cmd, "touch ");
	sprintf(id, "%d", group->groupid);
	strcat(id, "_list.dat");
	strcat(cmd, id);
	system(cmd);
	fclose(fp);
	chdir(path);

	return 1;
}

//解散群,成功返回1,不存在返回0,出错返回-1,不是群主返回2
int delgroup_Per(unsigned int groupid, unsigned int master)
{
	FILE *fp, *fp1;
	char *path = get_pwd();
	char name[25];
	groupifo group;
	userlist data;
	int result;
	
	result = selectgroup_Per(groupid, &group);
	//删除群列表文件中的群信息
	if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			return -1;
		}
	}

	if (result == 0){
		chdir(path);
		return 0;
	}
	if (result == -1){
		chdir(path);
		return -1;	
	}
	if (group.userid != master){
		chdir(path);
		return 2;
	}
	if (rename(GROUP_FILE, GROUP_FILE_TEMP) < 0){
		chdir(path);
		return -1;
	}
	if ((fp = fopen(GROUP_FILE, "wb")) == NULL){
		chdir(path);
		return -1;
	}
	if ((fp1 = fopen(GROUP_FILE_TEMP, "rb")) == NULL){
		fclose(fp);
		chdir(path);
		return -1;
	}
	while(!feof(fp1)){
		if (fread(&group, sizeof(groupifo), 1, fp1)){
			if (group.groupid == groupid){
				continue;
			}
			fwrite(&group, sizeof(groupifo), 1, fp);
		}
	}
	fclose(fp);
	fclose(fp1);
	//删除每个用户文件中的群信息
	sprintf(name, "%d", groupid);
	strcat(name, "_list.dat");
	if ((fp = fopen(name, "rb")) == NULL){
		chdir(path);
		return -1;
	}
	while(!feof(fp)){
		if (fread(&data, sizeof(userlist), 1, fp)){
			char a[100];
			strcpy(a,get_pwd());
			printf("1 = %s\n",a);
			if (chdir(path) == -1){
				return -1;
			}
			strcpy(a,get_pwd());
			del_friend_Per(data.id, groupid);
			del_friend_Per(groupid, data.id);
			if (chdir("./data") == -1){
				system("mkdir data");
				if (chdir("./data") == -1){
					return -1;
				}
			}
		}
	}
	fclose(fp);
	remove(name);
	remove(GROUP_FILE_TEMP);
	chdir(path);

	return 1;
}
