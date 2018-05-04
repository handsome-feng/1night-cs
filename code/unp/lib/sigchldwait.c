#include "unp.h"

// 错误的sig_chld
//void
//sig_chld(int signo)
//{
//    pid_t pid;
//    int stat;

//    pid = wait(&stat);
//    printf("child %d terminated\n", pid);
//    return;
//}

void
sig_chld(int signo)
{
    pid_t pid;
    int stat;
    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}
