#include<unistd.h>
#include<sys/types.h>
//#include<wait.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>

void show(int sig){
    printf("child get signal %d\npid=%d,ppid=%d\n",sig,getpid(),getppid());
    kill(getpid(),SIGKILL);
}
int main(void){
    pid_t pid;
    struct sigaction newact;
    newact.sa_handler=show;
    //sigemptyset(&newact.sa_mask);
    //newact.sa_flags=0;
    sigaction(SIGCHLD,&newact,NULL);
    if((pid=fork())<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){
        sleep(1);
    }
    else{
        printf("parent send signal\n");
        kill(pid,SIGCHLD);
    }
    return 0;
}