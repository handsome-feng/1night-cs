#ifndef __unp_h
#define __unp_h

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <signal.h>

#include <sys/errno.h>

#define SA struct sockaddr

#define MAXLINE     4096
#define BUFFSIZE    8192
#define LISTENQ     1024

#define SERV_PORT   9877

typedef void Sigfunc(int);    /* for signal handlers */

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);


/* prototypes for our Unix wrapper functions */
void  Close(int);
pid_t Fork(void);
void  Write(int, void *, size_t);

/* prototypes for our stdio wrapper functions */
void  Fclose(FILE *);
FILE *Fdopen(int, const char *);
char *Fgets(char *, int, FILE *);
FILE *Fopen(const char *, const char *);
void  Fputs(const char *, FILE *);


/* prototypes for our socket wrapper functions */
int   Accept(int, SA *, socklen_t *);
void  Bind(int, const SA *, socklen_t);
void  Connect(int, const SA *, socklen_t);
void  Listen(int, int);
ssize_t Readline(int, void *, size_t);
void  Writen(int, void *, size_t);
int  Socket(int, int, int);
Sigfunc *Signal(int, Sigfunc *);

/* prototypes for our own library wrapper functions */
void          Inet_pton(int, const char *, void *);
const char   *Inet_ntop(int, const void *, char *, size_t);
void          str_echo(int);
#endif /* __unp_h */
