#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    struct termios tty, savedtty;
    int fd;
    char ch;

    if ((fd = open("/dev/tty", O_RDONLY)) != -1) {
        if (!isatty(fileno(stdin))) {
            perror("stdin not terminal");
            exit(2);
        }

        if (tcgetattr(fd, &tty)) {
            perror("tcgetattr failed\n");
            exit(3);
        }

        savedtty = tty;
        tty.c_lflag &= ~(ICANON | ECHO);
        tty.c_cc[VMIN] = 1;
        tty.c_cc[VTIME] = 0;

        if (tcsetattr(fd, TCSANOW, &tty)) {
            perror("Can not tcsetattr\n");
            exit(4);
        }

        // Read symbol
        printf("10 < 100?\n");

        if (read(fd, &ch, 1) < 0) {
            perror("Can not read character\n");
            exit(5);
        }

        // Check symbol
        if (ch == 'y' || ch == 'Y')
            printf("true\n");
        else if (ch == 'n' || ch == 'N')
            printf("false\n");
        else
            printf("unknown symbol\n");

        if(tcsetattr(fd, TCSAFLUSH, &savedtty)) {
            perror("Can not set previouse attribute\n");
            exit(4);
        }

        if (close(fd)) {
            perror("Can not close /dev/tty\n");
            exit(6);
        }
    }
    else {
        perror("Can not open /dev/tty\n");
        exit(1);
    }

    return 0;
}
