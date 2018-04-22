#include "unp.h"

int
main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t chilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_add.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listendf, (SA *) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for ( ; ; ) {
        chilen = sizeof(cliaddr);
        connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);
        if ( (childpid = Fork()) == 0) {           /* child process */
            Close(listenfd);       /* close listening socket */
            str_echo(connfd);      /* process the request */
            exit(0);
        }
        Close(connfd);             /* parent closes connected socket */
    }
}
