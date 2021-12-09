#include <stdio.h>
#include <stdlib.h>
#include <my_execvpe.h>

int main(int argc, char* argv[], char* envp[])
{
    char* path = "newprog";
    char* nargv[] = {"newpgm", "parm1", "parm2", "parm3", (char*)0};
    char* nenvp[] = {"TZ=Asia/Novosibirsk", "USER=userRR", "parm=last", (char*)0};

    if (my_execvpe(path, nargv, nenvp))
    {
        fprintf(stderr, "Error: my_execvpe failed");
    }

    return 0;
}
