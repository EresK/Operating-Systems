#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void question(int fd) {
    char ch;

    printf("10 < 100?\n");

    if (read(fd, &ch, 1) < 0) {
        perror("Can not read character");
        exit(6);
    }

    if (ch == 'y' || ch == 'Y')
        printf("true\n");
    else if (ch == 'n' || ch == 'N')
        printf("false\n");
    else
        printf("unknown symbol\n");
}

int main() {
    int fd;

    if ((fd = open("/dev/tty", O_RDONLY)) == -1) {
        perror("Can not open /dev/tty");
        exit(1);
    }
    else {
        struct termios tty, savedtty;

        if (!isatty(fileno(stdin)) || tcgetattr(fd, &tty)) {
            perror("isatty or tcgetattr failed");
            exit(2);
        }

        savedtty = tty;
        tty.c_lflag &= ~(ICANON | ECHO);
        tty.c_cc[VMIN] = 1;
        tty.c_cc[VTIME] = 0;

        if (tcsetattr(fd, TCSANOW, &tty)) {
            perror("Can not tcsetattr");
            exit(3);
        }

        question(fd);
        
        if(tcsetattr(fd, TCSAFLUSH, &savedtty)) {
            perror("Can not set previouse attribute");
            exit(4);
        }

        if (close(fd)) {
            perror("Can not close /dev/tty");
            exit(5);
        }
    }

    return 0;
}
