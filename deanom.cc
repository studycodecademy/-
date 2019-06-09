/*************************************************************************
*                    �������ƣ�c����ʵ���ػ�����                         *
*                    �������ߣ�����vim�༭����gcc������ʵ��              *
*                    ����������ʵ�����ļ��ж�ȡ����ϵͳʱ��              *
*                        ���ߣ���                                        *
*                    �������ڣ�2019��6��1��                              *
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
  create_daemon();   //�öδ���֮�����ж����ڿ���̨���ӽ��̣����ļ�log.logÿ��5����д�뵱ǰϵͳʱ�䡣
  while(1){
    fd = open("log.log",O_WRONLY|O_CREAT|O_APPEND,0644);
    if(fd == -1){
      ERR_EXIT("open error");
      exit(0);
     }
    t = time(0);   //��ǰϵͳʱ��
    *buf = asctime(localtime(&t));
    write(fd,buf,strlen(buf));
    close(fd);
    sleep(5);
  }
  return 0;
}
void create_daemon(void){
  pid_t pid;
  pid = fork();//�����ӽ���
  if(pid == -1){  //�ж��Ƿ����Ϊ�棬���׼��������ַ�����folk error��
    ERR_EXIT("folk error"); //
  } 
  else if(pid>0){//Ϊ�棬���˳�������
    exit(EXIT_SUCCESS);
  }
  if(setsid() == -1){//Ϊ�մ������ӽ��̽����Ự��ע�⣬ȷ����ǰ���̲��ǽ����鳤��δ�����Ự
     ERR_EXIT("SETSID ERROR");
   }
  chdir("/");  //Ĭ�ϵ�ǰ·��
  int i = 0;
  for(;i < 3;++i){//�رղ����ļ�
    close(i);
    open("/dev/null",O_RDWR);
    dup(0);   //���Ǻ���⣬������
    dup(0); 
  }
  umask(0); //�����ļ�Ȩ��
  return;
  }