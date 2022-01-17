#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "myexecvpe.h"

int main(int argc, char* argv[], char* envp[])
{
    char* path = "./myprog";
    char* nargv[] = {"myprog", "arg1", "arg2", (char*)0};
    char* nenvp[] = {"PARAM1=valueOne", "PARAM2=valueTwo", "TZ=Asia/Novosibirsk", (char*)0};

    if (myexecvpe(path, nargv, nenvp))
        fprintf(stderr, "Error: myexecvpe failed\n");

    return 0;
}
