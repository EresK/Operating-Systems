#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int cnt;

void sigcatch(int sig) {
    if (sig != SIGQUIT) {
        printf("\07\n");
        cnt += 1;    
    }
    else {
        printf("%d\n", cnt);
        exit(0);
    }
}

int main() {
    cnt = 0;

    sigset(SIGINT, sigcatch);
    signal(SIGQUIT, sigcatch);

    while(1) {
        pause();
    }
}
