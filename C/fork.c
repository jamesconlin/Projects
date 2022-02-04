#include <stdio.h> 
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
 /*folk one process*/


 /*fork another*/


 /*folk another*/


printf("Child pid ", getpid());



 return 0;

}
// 4 Total Processes
//printf("%ld%ld", (long)getpid(), (long)getppid());