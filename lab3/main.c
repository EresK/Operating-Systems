#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    FILE* file;

    printf("uid: %u\neuid: %u\n", getuid(), geteuid());
    if ((file = fopen("data_file", "rw")) != NULL) {
        printf("File opened\n");
        fclose(file);
        printf("File closed\n");
    }
    else {
        perror("Error: fopen data_file failed\n");
        exit(1);
    }

    setuid(getuid());

    printf("uid: %u\neuid: %u\n", getuid(), geteuid());
    if ((file = fopen("data_file", "rw")) == NULL) {
        printf("Can not open data_file after setuid()\n");
    }
    else
        fclose(file);

    return 0;
}
