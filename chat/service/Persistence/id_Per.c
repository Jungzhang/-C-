/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-07 14:48
 * Filename	 : id_Per.c
 * Description	 : 分配ID的相关文件操作
 * *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "../Server/id_sev.h"
#include "../Common/common.h"

static const char ID_FILE_TEMP[] = "idTemp.dat";
static const char ID_FILE[] = "id.dat";

//从文件中查找最大用户ID
int Per_find_userid(void)
{
	FILE *fp;
	char *path = get_pwd();
	ID data;
	if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			chdir(path);
			return 0;		
		}
	}
	if ((fp = fopen(ID_FILE,"rb")) == NULL){
		system("touch id.dat");
		chdir(path);
		return 0;
	}
	else{
		while(!feof(fp)){
			if (fread(&data, sizeof(ID), 1, fp)){
				if (strcmp(data.type,"userid") == 0){	
					fclose(fp);
					chdir(path);
					return data.id;
				}
			}
		}
	}
	chdir(path);

	return 0;
}

//更新ID到文件
int Per_add_userid(unsigned int new_id)
{
	FILE *fp,*fp1;
	char *path = get_pwd();
	ID data;
	int flag = 0;

	if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			chdir(path);
			return 0;		
		}
	}
	if (rename(ID_FILE, ID_FILE_TEMP) < 0){
		chdir(path);
		return 0;
	}
	if ((fp = fopen(ID_FILE,"wb")) == NULL){
		chdir(path);
		return 0;
	}
	if ((fp1 = fopen(ID_FILE_TEMP, "rb")) == NULL){
		chdir(path);
		return 0;
	}

	while(!feof(fp1)){
		fread(&data, sizeof(data), 1, fp1);
		if (strcmp(data.type,"userid") == 0){
			data.id = new_id;
			flag = 1;
		}
		fwrite(&data,sizeof(ID), 1, fp);
	}
	//还无此类型,添加此类型
	if (flag == 0)
	{
		strcpy(data.type, "userid");
		data.id = new_id;
		fwrite(&data,sizeof(ID), 1, fp);
	}
	remove(ID_FILE_TEMP);
	fclose(fp);
	fclose(fp1);
	chdir(path);

	return 1;
}

//从文件中查找最大群ID
int Per_find_groupid(void)
{
	FILE *fp;
	ID data;
	char *path = get_pwd();
	if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			chdir(path);
			return 0;		
		}
	}
	if ((fp = fopen(ID_FILE,"rb")) == NULL){
		system("touch id.dat");
		chdir(path);
		return 0;
	}
	else{
		while(!feof(fp)){
			if (fread(&data, sizeof(ID), 1, fp)){
				if (strcmp(data.type,"groupid") == 0){
					fclose(fp);
					chdir(path);
					return data.id;
				}
			}
		}
	}

	chdir(path);
	return 0;
}

//添加新ID到文件
int Per_add_groupid(unsigned int new_id)
{
	FILE *fp,*fp1;
	ID data;
	int flag = 0;
	char *path = get_pwd();
		if (chdir("./data") == -1){
		system("mkdir data");
		if (chdir("./data") == -1){
			chdir(path);
			return 0;		
		}
	}

	if (rename(ID_FILE, ID_FILE_TEMP) < 0){
		chdir(path);
		return 0;
	}
	if ((fp = fopen(ID_FILE,"wb")) == NULL){
		chdir(path);
		return 0;
	}
	if ((fp1 = fopen(ID_FILE_TEMP, "rb")) == NULL){
		chdir(path);
		return 0;
	}

	while(!feof(fp1)){
		fread(&data, sizeof(data), 1, fp1);
		if (strcmp(data.type,"groupid") == 0){
			data.id = new_id;
			flag = 1;
		}
		fwrite(&data,sizeof(ID), 1, fp);
	}
	//还无此类型,创建此类型
	if (flag == 0)
	{
		strcpy(data.type,"groupid");
		data.id = new_id;
		fwrite(&data,sizeof(ID), 1, fp);
	}
	remove(ID_FILE_TEMP);
	fclose(fp);
	fclose(fp1);
	chdir(path);

	return 1;
}
