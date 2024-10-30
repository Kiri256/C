#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char **argv){
    int fd1,fd2;
    char buf[10];
    fd1=open(argv[1],O_RDONLY);
    fd2=open(argv[2],O_WRONLY);
    while (read(fd1,buf,10)>0)
        write(fd2,buf,10);
    close(fd1);
    close(fd2);
    return 0;
}