#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;

    if ((pid = fork()) > 0) {
        int status;
        if (wait(&status) == -1) {
            perror("child process failed");
            exit(2);
        }
        printf("\nParent process, returned status: %d\n", status);
    }
    else if (pid == 0) {
        char* nargv[] = {"cat", "big_text", (char*)0};

        if (execvp("cat", nargv) == -1) {
            perror("execvp failed");
            exit(3);
        }
    }
    else {
        perror("Can not create child process\n");
        exit(1);
    }

    return 0;
}
