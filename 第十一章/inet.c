#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	char ip[32],*new_ip;
	struct in_addr addr;
	struct in_addr addr1;
	struct in_addr addr2;
	printf("请输入IP地址：");
	scanf("%s",ip);
	//将字符串IP转换为网络字节中的IP
	if (inet_aton(ip,&addr) == 0)
		perror("inet_aton error");
	else
		printf("inet_aton:%#x\n",addr);
	if ((addr.s_addr = inet_addr(ip)) == -1)
		perror("inet_addr error");
	else
		printf("inet_addr:%#x\n",addr.s_addr);
	//将字符串转换为主机存储字节顺序的地址
	if ((addr1.s_addr = inet_network(ip)) == -1)
		perror("inet_network error");
	else
		printf("inet_network:%#x\n",addr1.s_addr);
	//将网络字节顺序形式的ip转换为以'.'分割的字符串形式
	if ((new_ip = inet_ntoa(addr)) == NULL)
		perror("inet_ntoa error");
	else
		printf("inet_ntoa：%s\n,len = %d\n",new_ip,strlen(new_ip));
	//从网络字节顺序中提取出主机号
	addr1.s_addr = inet_lnaof(addr);
	printf("inet_lnaof：%#x\n",addr1.s_addr);
	//从网络字节顺序中提取出网络地址
	addr2.s_addr = inet_netof(addr);
	printf("inet_lnaof：%#x\n",addr2.s_addr);
	//将主机号和网络号连接起来
	addr2 = inet_makeaddr(addr2.s_addr,addr1.s_addr);
	printf("makeaddr：%#x\n",addr2);

	return EXIT_SUCCESS;
}
