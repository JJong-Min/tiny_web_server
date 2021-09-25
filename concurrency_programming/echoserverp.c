#include "csapp.h"
void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio, connfd);
    while((n = rio_readlineb(&rio, buf, MAXLINE)) != 0) {
        printf("server received %d bytes\n", (int)n);
        rio_writen(connfd, buf, n);
    }
}

void sigchild_handler(int sig)
{
    while (waitpid(-1, 0, WNOHANG) > 0)
        ;
    return;
}

int main(int argc, char **argv) {
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = atoi(argv[1]);

    signal(SIGCHLD, sigchild_handler);
    listenfd = Open_listenfd(port);
    while (1) {
        connfd = Accept(listenfd, (SA *) &clientaddr, clientlen);
        if (Fork() == 0) {
            // close the listenfd of child
            Close(listenfd);
            // service to client of child
            echo(connfd);
            // close the connfd of child
            Close(connfd);
            // child exits
            exit(0);
        }
        //(important) close the connfd of parent
        Close(connfd);
    
    }
}