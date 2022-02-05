#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define FLAG_INT 1
#define FLAG_QUIT 2

static int cnt;
static int flag;

void sigcatch(int sig) {
    if (sig == SIGINT) {
        cnt += 1;
        flag = FLAG_INT;
    }
    else {
        flag = FLAG_QUIT;
    }
}

int main() {
    sigset(SIGINT, sigcatch);
    signal(SIGQUIT, sigcatch);

    while(1) {
        pause();

        if (flag == FLAG_INT) {
            printf("\007\n");
        }
        else if (flag == FLAG_QUIT) {
            printf("%d\n", cnt);
            exit(0);
        }
    }
}
