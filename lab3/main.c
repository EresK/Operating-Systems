#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (setuid(getuid()))
            perror("setuid failed\n");
        else
            printf("setuid succeed\n");
    }

    printf("uid: %d\neuid: %d\n", getuid(), geteuid());

    FILE* file;

    if ((file = fopen("text", "rw")) != NULL) {
        printf("File opened\n");
        fclose(file);
        printf("File closed\n");
    }
    else {
        perror("fopen failed\n");
        exit(1);
    }

    return 0;
}
