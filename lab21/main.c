#include <stdio.h>
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
        char tmp[20];
        int size = snprintf(tmp, 20, "%d\n", cnt);
        write(STDOUT_FILENO, tmp, size + 1);
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
