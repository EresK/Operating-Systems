#include <stdio.h>
#include "myexecvpe.h"

int main(int argc, char* argv[], char* envp[])
{
    char* path = "ls";
    char* nargv[] = {"ls", (char*)0};
    char* nenvp[] = {"PARAM=value", (char*)0};

    if (myexecvpe(path, nargv, nenvp))
        fprintf(stderr, "Error: myexecvpe failed\n");

    return 0;
}
