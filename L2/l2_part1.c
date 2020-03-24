#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

void printProcessInfo(char *processType){
    printf("\n%s Process ID: %d\n", processType, getpid());
    printf("%s Process parent ID: %d\n", processType, getppid());
    printf("%s Process session ID: %d\n", processType, getsid(0));
    printf("%s Process GID: %d\n\n", processType, getgid());
}

int main(int argc, char const *argv[]){
    const pid_t childPid = fork();
    if (childPid == 0){
        sleep(1);
	printProcessInfo("child");        
        printf("child Exiting\n");
    }
    else if(childPid == -1){
        printf("parent Error while forking: %s\n", strerror(errno));
        return -1;
    }                
    else{
	printProcessInfo("parent");
        printf("parent Forked child ID: %d\n", childPid);
        printf("parent Waiting for child process\n");
        int status;
        if (wait(&status) == -1){
            printf("parent Error while waiting for child process: %s\n", strerror(errno));
            return -1;
        }
        if (WIFEXITED(status)) printf("parent Child process exited with status %d\n", WEXITSTATUS(status));
        else if(WIFSIGNALED(status)) psignal(WTERMSIG(status),"Exit signal\n");
    }
    return 0;
}
