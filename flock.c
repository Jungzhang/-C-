/*************************************************************************
	> File Name: flock.c
	> Author: Jung
	> Mail: jungzhang@xiyoulinux.org
	> Created Time: 2016年07月21日 星期四 23时24分33秒
	> Description:
 ************************************************************************/
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf[256];
    struct flock lock;

    fd = open("test2.txt", O_CREAT | O_RDWR, 0664);
    if (fd == -1) {
        perror("open error");
        return EXIT_FAILURE;
    }

    /* 只有对文件有相应的读写权限才能施加对应的文件锁 */
    memset(&lock, 0, sizeof(lock));
    //lock.l_type = F_WRLCK; // 排他锁,即不允许其他进程再对其加任何类型的锁，但读锁（共享锁）允许
    //lock.l_type = F_RDLCK; //共享锁
    lock.l_whence = SEEK_SET;
    lock.l_start = 0; //从文件开头开始锁定
    lock.l_len = 1; // 文件全部内容锁住

    // 若为F_SETLKW,这时如果锁已经被其他进程占用，则此进程会阻塞直到其他进程释放锁
    //if (fcntl(fd, F_SETLKW, &lock) == 0) {
    //if (fcntl(fd, F_SETLK, &lock) == 0) {
        /*for (int i = 0; i < 10; ++i) {
            if (write(fd, "Xiyou Linux Group1\n", 19) != 19) {
                perror("write");
            }
            sleep(1);
        }*/
        
        while (1) {
            if (read(fd, buf, 1) < 0) {
                perror("read");
            }
            sleep(2);
            printf("%d, %s\n",getpid(), buf);
        }
        
        printf("lock success\n");
        printf("press enter to unlock\n");
        getchar();
        lock.l_type = F_UNLCK;
        
        if (fcntl(fd, F_SETLK, &lock) == 0) {
            printf("unlock success\n");
        } else {
            perror("unlock fail");
            return EXIT_FAILURE;
        }
 //   } //else {
      //  perror("lock fail");
     //   return EXIT_FAILURE;
    //}

    return EXIT_SUCCESS; //进程退出会对所有文件解锁
} 
