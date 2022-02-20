#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd;

    if ((fd = open("file", O_RDWR)) == -1) {
        perror("Can not open file");
        exit(1);
    }
    else {
        struct flock lock;

        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;

        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl failed");
            exit(2);
        }
        else {
            if (system("nano file") == -1) {
                perror("system() failed");
                exit(3);
            }
        }

        if (close(fd) == -1) { /* The lock will unlocked after closing*/
            perror("Can not close file");
            exit(4);
        }
    }

    return 0;
}