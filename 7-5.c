#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(void){
    int fd1;
    char buf[10];
    pid_t child;
    fd1=open("file3",O_RDONLY);
    child=fork();
    if(child!=0){
        buf[0]='p';buf[1]='a';buf[2]='r';buf[3]='n';buf[4]='e';buf[5]='t';buf[6]='\0';
        write(fd1,buf,10);
    }
    else{
        buf[0]='c';buf[1]='h';buf[2]='i';buf[3]='l';buf[4]='d';buf[5]='\0';
        write(fd1,buf,10);
    }
    printf("pid=%d\nppid=%d\n",getpid(),getppid());
    return 0;
}
