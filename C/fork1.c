#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;


    pid = fork();
    pid = fork();
    pid = fork();

    printf("pid %d\n", getpid());
    if (pid < 0) {
        printf (stderr, "Fork Failed");
        return 1;
    }

    else if (pid ==0) {
        
        execlp("/bin/ls","ls", NULL);
        
    }
    else {
        wait(NULL);
        printf("Child Complete");
        
    }
    
    return 0;
}