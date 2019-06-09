/*************************************************************************
*                    程序名称：c语言实现守护进程                         *
*                    开发工具：基于vim编辑器和gcc编译器实现              *
*                    程序描述：实现向文件中读取当地系统时间              *
*                        作者：略                                        *
*                    创作日期：2019年6月1日                              *
**************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>

#define  ERR_EXIT(m)\
do\
{\
perror(m);\
exit(EXIT_FAILURE);\
}\
while(0);\
void create_daemon(void);
int main(void){
  time_t t;
  int fd;
  create_daemon();   //该段代码之后，运行独立于控制台的子进程，向文件log.log每隔5秒钟写入当前系统时间。
  while(1){
    fd = open("log.log",O_WRONLY|O_CREAT|O_APPEND,0644);
    if(fd == -1){
      ERR_EXIT("open error");
      exit(0);
     }
    t = time(0);   //当前系统时间
    *buf = asctime(localtime(&t));
    write(fd,buf,strlen(buf));
    close(fd);
    sleep(5);
  }
  return 0;
}
void create_daemon(void){
  pid_t pid;
  pid = fork();//创建子进程
  if(pid == -1){  //判断是否出错，为真，则标准错误输出字符串“folk error”
    ERR_EXIT("folk error"); //
  } 
  else if(pid>0){//为真，则退出父进程
    exit(EXIT_SUCCESS);
  }
  if(setsid() == -1){//为刚创建的子进程建立会话，注意，确保当前进程不是进程组长，未建立会话
     ERR_EXIT("SETSID ERROR");
   }
  chdir("/");  //默认当前路径
  int i = 0;
  for(;i < 3;++i){//关闭部分文件
    close(i);
    open("/dev/null",O_RDWR);
    dup(0);   //不是很理解，请求解答
    dup(0); 
  }
  umask(0); //屏蔽文件权限
  return;
  }