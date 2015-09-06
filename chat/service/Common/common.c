#include <time.h>
#include "common.h"
#include <string.h>
#include <unistd.h>

//获取当前系统时间
void date_now(char now_time[])
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strcpy (now_time,asctime (timeinfo));
	now_time[24] = '\0';
}

//获取当前路径
inline char *get_pwd(void)
{
	return getcwd(NULL,0);
}
