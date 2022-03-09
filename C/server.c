#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

struct file_info_t{
    ssize_t size;
    char name[128];
};

void *recieve_handler(void *ctx)
{
    char buffer[4096];
    int recieved;
    int newSocket = (int)(size_t)ctx;
    struct file_info_t info;
    size_t size;
    int fd;

    printf("strt new thread conn %d\n", newSocket);
    recieved = recv(newSocket, &info, sizeof(struct file_info_t), MSG_WAITALL);

    if (recieved != sizeof(struct file_info_t)){
        printf("recieved error %d\n", recieved);
    }
size = info.size;
fd = open(info.name, O_CREAT | O_WRONLY | O_SYNC | O_TRUNC, S_IRUSR | S_IWUSR);
if (!fd){
    printf("failed to open %s\n", info.name);
    close(newSocket);
    return;
}
printf("opened %s\n", info.name);
while (size){
    recieved = recv(newSocket, buffer,4096,0);
    if (recieved <=0){
        printf("recieved error %d\n", recieved);
        break;
    }
    printf("recieved data %d\n", recieved);
    size -= recieved;
    write(fd, buffer, recieved);
}
close(fd);
close(newSocket);

}

int main(int argc, char *argv[])
{
    int listenfd = -1, c;
    struct sockaddr_in serv_addr, client;
    listenfd = socket(AF_INET, SOCK_STREAM, 0 );
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);
    while (1) {
        int connfd;
        memset(&client, 0, sizeof(client));
        connfd = accept(listenfd, (struct sockaddr*)&client, (socklen_t*)&c);
        if (connfd == -1){
            printf("accept returned errorno %d\n" , errno);
            break;
        }
        printf("accept conn %d\n", connfd);

        pthread_t t;

        if (ptherad_create(&t, NULL, &recieve_handler, (void *)(size_t)connfd) < 0){
            printf("cannot create thread\n");
            close(connfd);
            break;
        }
    }
exit :
    close(listenfd);
}
