#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void openFile(char* name)
{
        FILE* file = fopen(name, "rw");

        if (!file)
            perror("Error: can not open file\n");
        else
            printf("File \"%s\" opened\n", name);

        fclose(file);
}

int main(int argc, char* argv[])
{
    printf("Real ID: %u\nEffective ID: %u\n", getuid(), geteuid());

    if (argc >= 2)
        openFile(argv[1]);
    else
    {
        perror("Error: enter file name\n");
        exit(1);
    }

    if(setuid(getuid()))
        fprintf(stderr, "Error: failed setuid \"%s\"\n", strerror(errno));
    else
        printf("Success: setuid\n");

    printf("Real ID: %u\nEffective ID: %u\n", getuid(), geteuid());

    openFile(argv[1]);

    return 0;
}
