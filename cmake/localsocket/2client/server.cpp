#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> 
#include <sys/time.h>
#define UNIX_DOMAIN "/tmp/UNIX.domain"

using std::cout;

typedef struct _sockMsg{
    uint16_t magic;
    uint16_t id;
    char data[8];
} sockMsg;

void on_data(char *buf, int len)
{
    printf("recv: %s\n", buf);
}

int main(void)
{
    socklen_t clt_addr_len;
    int listen_fd;
    int fd;
    int ret;
    static char recv_buf[1024]; 
    socklen_t len;
    struct sockaddr_un clt_addr;
    struct sockaddr_un srv_addr;
    struct timeval timeout;
    fd_set rfds, wfds;

    listen_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(listen_fd < 0)
    {
        perror("cannot create communication socket");
        return 1;
    }  
    
    srv_addr.sun_family = AF_UNIX;
    snprintf(srv_addr.sun_path, sizeof(srv_addr.sun_path), UNIX_DOMAIN);
    ret = bind(listen_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr));
    if(ret == -1)
    {
        perror("cannot bind server socket");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }

    ret = listen(listen_fd, 1);
    if(ret == -1)
    {
        perror("cannot listen the client connect request");
        close(listen_fd);
        unlink(UNIX_DOMAIN);
        return 1;
    }

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    while (1) {
        FD_SET(listen_fd, &rfds);
        gettimeofday(&timeout, NULL);
        timeout.tv_sec += 1;
        int32_t ret = select(listen_fd + 1, &rfds, NULL, NULL, &timeout);
        if (FD_ISSET(listen_fd, &rfds)) {
            len = sizeof(clt_addr);
            fd = accept(listen_fd, (struct sockaddr*)&clt_addr, &len);
            if(fd < 0){
                perror("cannot accept client connect request");
                close(listen_fd);
                unlink(UNIX_DOMAIN);
                return 1;
            }
            FD_SET(listen_fd, &rfds);
            //FD_SET(listen_fd, &wfds);
            FD_CLR(listen_fd, &rfds);
        }

        do {
            FD_ZERO(&rfds);
            FD_SET(fd, &rfds);
            gettimeofday(&timeout, NULL);
            timeout.tv_sec += 1;
            ret = select(fd + 1, &rfds, NULL, NULL, &timeout);
            if (FD_ISSET(fd, &rfds)) {
                memset(recv_buf,0,1024);
                ret = read(fd, recv_buf, sizeof(recv_buf));
                if (ret > 0) {
                    on_data(recv_buf, ret);
                } else if (!ret || ((ret < 0) && (errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK))) {
                    printf ("socket close\n");
                    close(fd);
                    fd = -1;
                } else {
                    printf ("socket error\n");
                    continue;
                }
            }
        }while (fd > 0);
    }
    close(fd);
    close(listen_fd);
    unlink(UNIX_DOMAIN);
    return 0;
}

