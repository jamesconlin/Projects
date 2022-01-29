#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int main(int argc, char *argv[]){
    int fd, fd2;
    ssize_t returned;
    char buffer[4096];
    
    if (argc != 3) {
        printf("usage: filecopy <source> <target>");
        return -1;
    }
    fd = open(argv[1], O_RDONLY);

    if (!fd){
        printf("failed to open %s\n", argv[1]);
        return -1;
    }
    fd2 = open(argv[2], O_CREAT | O_WRONLY | O_SYNC | O_TRUNC | S_IRUSR | S_IWUSR);

    if (!fd2){
        printf("failed to open %s\n", argv[2]);
        close(fd);
        return -1;
    }
    while (1){
        ssize_t r;

        returned = read(fd, buffer, 4096);
        if (returned < 0){
            printf("failed to read %d\n", errno);
            break;
        }

        printf("read \n", returned);

        if (returned == 0){
            printf("successfully finsihed copy %s -> %s \n", argv[1],argv[2]);
            break;
        }

        r = write(fd2, buffer,returned);

        if(returned != r){
            printf("failed to write to %s. \n", argv[2]);
            break;
        }

        if (returned < 4096) {
            printf("successfully copied %s -> %s. \n", argv[1],argv[2]);
            break;
        }

    }
    close(fd);
    close(fd2);
}
