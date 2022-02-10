#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

    int fd;

    if ((fd = open("file", O_RDWR)) != -1) {
        struct flock lock;

        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;

        if (fcntl(fd, F_SETLK, &lock) != -1) {
            if (system("nano file") == -1) {
                perror("system() failed\n");
                exit(3);
            }
        }
        else {
            perror("fcntl failed\n");
            exit(2);
        }

        lock.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("Can not unlock file\n");
            exit(4);
        }

        if (close(fd) == -1) {
            perror("Can not close file\n");
            exit(5);
        }
    }
    else {
        perror("Can not open file\n");
        exit(1);
    }

    return 0;
}