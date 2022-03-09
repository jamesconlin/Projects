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
int main (int argc, char *argv[])
{
    int sockfd = 0;
    char buff[4096];
    struct sockaddr_in serv_addr;
    int ret = 0;
    int fd;
    ssize_t returned;
    char buffer[4096];
    struct stat st;
    struct file_info_t info;
    ssize_t size;
if (argc !=3)
{
    printf("\n Usage %s <local file> <ipadd>", argv[0]);
    return 1;
}

fd = open(argv[1], O_RDONLY);
if (!fd) {
    printf("failed to open %s\n", argv[1, size]);
    return -1;
}
stat(argv[1], &st);
size = info.size = st.st_size;
strcpy(info.name, argv[1]);
printf("open %s size %ld\n", argv[1], size);
memset(buff, '0', sizeof(buff));
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
    printf("\n Error : Could not create socket \n");
    closed(fd);
    return 1;
}
memset(&serv_addr, '0', sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000);
if (inet_pton(AF_INET, argv[2], &serv_addr.sin_addr) <=0)
{
    printf("\n intet_pton error occured \n");
    goto exit;
}
if (connect(sockfd, ( struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
{
    printf("\n Error : Connect Failed \n");
    goto exit;
}
returned = write(sockfd, (char *)&info, sizeof(struct file_info_t));

if (returned != sizeof(struct file_info_t)){
    printf("Error : Send infofailed %d \n", returned);
    goto exit;
}

printf("send info %d \n", returned);
    while (size) {
        ssize_t r;
        returned = read(fd, buffer , 4096);
        if (returned < 0){
            printf("failed to read errno %d\n", errno);
            break;
        }
        size -= returned;

        write(sockfd, buffer, returned);

        if (size == 0) {
            printf("successfully finished read %s\n, argv[1]");
            break;
        }

    }
    exit:
        close(sockfd);
        close(fd);
        return 0;
}
