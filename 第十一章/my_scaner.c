/*******************************************************************************
 * Author	 : zhanggen
 * Email	 : zhanggen.jung@gmail.com
 * Last modified : 2015-08-05 10:49
 * Filename	 : my_scaner.c
 * Description	 : TCP端口扫描程序
 * *****************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

pthread_mutex_t mutex;

//定义端口区间信息
typedef struct _port_segment{
	struct in_addr dest_ip;			//IP地址
	unsigned short int min_port;	//最小端口号
	unsigned short int max_port;	//最大端口号
}port_segment;

//扫描一个端口,开放返回1,不开放返回0,出错返回-1
int do_scan(struct sockaddr_in serv_addr)
{
	int fd;
	int result;
	//创建socket
	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd < 0){
		perror("Socket Error");	return -1;
	}
	//向待扫描服务器发送连接请求
	if ((result =  connect(fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0)){
		if (errno == ECONNREFUSED){
	//		printf("未开放!\n");
			close(fd);
			return 0;
		}
		else{
	//		printf("出错\n");
			close(fd);
			return -1;
		}
	}
	else if (result == 0){
		printf("端口%d开放\n",ntohs(serv_addr.sin_port));
		close(fd);
		return 1;
	}

	return -1;
}

//执行扫描的线程,扫描某一个端口区间
void scaner(port_segment *arg)
{
	unsigned short int i;
	struct sockaddr_in serv_addr;
	port_segment portinfo;
	//复制端口区间结构
	pthread_mutex_lock(&mutex);
	memcpy(&portinfo,arg,sizeof(struct _port_segment));
	pthread_mutex_unlock(&mutex);
	//初始化服务器端地址结构
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = portinfo.dest_ip.s_addr;
	
	for (i = portinfo.min_port; i < portinfo.max_port; i++){
		serv_addr.sin_port = htons(i);
		do_scan(serv_addr);
		//	continue;
	//	}
	}
}

int main(int argc,char *argv[])
{
	pthread_t *pthread;
	int max_port;
	int thread_num;
	int seg_len;
	struct in_addr dest_ip;
	port_segment portinfo;
	int i;
	
	if (argc != 7){
		printf("参数有误!\n");
		return EXIT_FAILURE;
	}
	for (i = 1; i < argc; i++){
		if (strcmp("-m",argv[i]) == 0){
			max_port = atoi(argv[i + 1]);
			if (max_port > 65535 || max_port < 0){
				printf("最大端口号有误!\n");
				return EXIT_FAILURE;
			}
		}
		else if(strcmp("-a",argv[i]) == 0){
			if (inet_aton(argv[i + 1],&dest_ip) == 0){
				printf("IP有误!\n");
				return EXIT_FAILURE;
			}
		}
		else if (strcmp("-n",argv[i]) == 0){
			thread_num = atoi(argv[i + 1]);
			if (thread_num <= 0){
				printf("线程数有误!\n");
				return EXIT_FAILURE;
			}
		}
	}

	//如果输入的线程数大于要扫描的端口数则将线程数更改为要扫描的端口数
	if (max_port < thread_num){
		thread_num = max_port;
	}
	seg_len = max_port / thread_num;
	if (seg_len % thread_num != 0)
		thread_num++;
	pthread = (pthread_t *)malloc(sizeof(pthread_t) * thread_num);

	//创建线程执行扫描
	for (i = 0; i < thread_num; i++){

		pthread_mutex_lock(&mutex);
		portinfo.dest_ip = dest_ip;
		portinfo.min_port = i * seg_len + 1;
		if (i != thread_num - 1)
			portinfo.max_port = portinfo.min_port + seg_len;
		else
			portinfo.max_port = max_port;
		pthread_mutex_unlock(&mutex);

		if (pthread_create(&pthread[i],NULL,(void *)scaner,&portinfo) != 0){
			printf("第%d个线程创建失败\n",i);
			return EXIT_FAILURE;
		}
	}

	for (i = 0; i < thread_num; i++)
		pthread_join(pthread[i],NULL);
	printf("扫描完成!\n");

	return EXIT_SUCCESS;
}
