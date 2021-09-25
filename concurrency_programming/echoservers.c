#include "csapp.h"

// connected descriptor(client)의 pool을 나타태는 구조체
typedef struct {
    int maxfd;                          // largest descriptor in read_set
    fd_set read_set;                    // set of all active descriptors
    fd_set ready_set;                   // subset of descriptors ready for reading
    int nready;                         // number of ready descriptors from select
    int maxi;                           // high water index into client array
    int clientfd[FD_SETSIZE];           // set of active decritors
    rio_t clientrio[FD_SETSIZE];        // set of active read buffers
} pool;

//  count total bytes recived by server
int byte_cnt = 0;

// init pool that is alive
void init_pool(int listenfd, pool *p)
{
    int i;
    p->maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
    {
        p->clientfd[i] = -1;
    }
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

// add new client in pool
void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    // find an available slot
    for (i = 0; i < FD_SETSIZE; i++) {
        if (p->clientfd[i] < 0) {
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);

            FD_SET(connfd, &p->read_set);

            if (connfd > p->maxfd) {
                p->maxfd = connfd;
            }
            if (i > p->maxi) {
                p->maxi = i;
            }
            break;
        }
    }
    if (i == FD_SETSIZE) {
        app_error("add_client error : Too many clients");
    }
}

// service to the ready client
void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if ((connfd >0) && (FD_ISSET(connfd, &p->ready_set))) {
            byte_cnt += n;
            printf("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
            Rio_writen(connfd, buf, n);
        }

        else {
            Close(connfd);
            FD_CLR(connfd, &p->read_set);
            p->clientfd[i] = -1;
        }
    }
}