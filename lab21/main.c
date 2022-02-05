#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int cnt;
static int flag;
static int flagch = 1;
static pid_t pid;

void sigcatch(int sig) {
    if (sig == SIGINT) {
        cnt += 1;

        printf("(parent pid: %d)\n", getpid());

        putc((int)'\n', stdout);
        for (int i = 0; i < 1000; i++) {
            if (i == 0)
                putc((cnt + 47), stdout);
            else
                putc((int)'h', stdout);
        }
        putc((int)'\n', stdout);
    }
    else {
        if (pid > 0 && flagch > 0) {
            flagch -= 1;
        }
        else {
            printf("\n%d\n", cnt);
            exit(0);
        }
    }
}

int main() {
    if ((pid = fork()) > 0) {
        sigset(SIGINT, SIG_IGN);
        signal(SIGQUIT, sigcatch);
        
        while (1) {
            putc((int)'-', stdout);
            sleep(1);
        }
        printf("child process can not out from while loop\n");
    }

    sigset(SIGINT, sigcatch);
    signal(SIGQUIT, sigcatch);

    while(1) {
        pause();
    }
}
