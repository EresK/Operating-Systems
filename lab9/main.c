#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    if ((pid = fork()) > 0) {
        if (wait(&status) == -1) {
            perror("child process failed");
            exit(2);
        }
        printf("Parent process, returned status: %d\n", status);
    }
    else if (pid == 0) {
        FILE* fp;
        char line[BUFSIZ];

        if ((fp = popen("cat big_text", "r")) != NULL) {
            while (fgets(line, BUFSIZ, fp) != NULL)
                printf("%s", line);
            printf("\n");
        }
        else {
            perror("popen text failed\n");
            exit(3);
        }

        if (pclose(fp) == -1) {
            perror("pclose failed");
            exit(4);
        }
    }
    else {
        perror("Can not create child process\n");
        exit(1);
    }

    return 0;
}
