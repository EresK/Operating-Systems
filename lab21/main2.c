#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int cnt = 0;
static char ch = '\007';

void sigcatch(int sig) {
    if (sig == SIGINT) {
        cnt += 1;
        write(STDOUT_FILENO, &ch, 1);
    }
    else {
        char buff[12]; // 2^32 = 10 symbols + 2 \n\0
        snprintf(buff, 12, "%d\n", cnt);
        write(STDOUT_FILENO, buff, strlen(buff));
        exit(0);
    }
}

int main() {
    sigset(SIGINT, sigcatch);
    signal(SIGQUIT, sigcatch);

    while(1) {
        pause();
    }
}
