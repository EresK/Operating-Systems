#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe creating failed\n");
        exit(1);
    }

    pid_t pid;

    if ((pid = fork()) == 0) { /* First process */
        if ((pid = fork()) > 0) { /* Still first process*/
            close(1);
            dup(fd[1]);

            char message[BUFSIZ] = "Message text.";

            if (write(fd[1], message, BUFSIZ) == -1)
                perror("Writing failed\n");
        }
        else if (pid == 0) { /* Second process */
            close(0);
            dup(fd[0]);

            char buff[BUFSIZ];

            if (read(fd[0], buff, BUFSIZ) > 0) {
                for (int i = 0; (buff[i] != '\0') && (i < BUFSIZ); i++)
                    buff[i] = toupper((int)buff[i]);

                printf("Message: \"%s\"\n", buff);
            }
            else
                perror("Reading failed\n");
        }
        else {
            perror("Can not fork second process\n");
            exit(3);
        }
    }
    else if (pid < 0) {
        perror("Can not fork first process\n");
        exit(2);
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}
