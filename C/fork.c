#include <stdio.h> 
#include "unistd.h"

int main()
{
 /*folk one process*/
 fork();

 /*fork another*/
 fork();

 /*folk another*/
 fork();

 return 0;

}


