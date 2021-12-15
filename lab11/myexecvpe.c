#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // execve
#include <libgen.h> // pathfind

int myexecvpe(char* filename, char* argv[], char* envp[])
{
    char* env_path;
    if ((env_path = getenv("PATH")) != NULL)
    {
        char* path = pathfind(env_path, filename, "rx");

        if (path != NULL && !access(path, F_OK))
        {
            if (execve(path, argv, envp))
                return -1;
        }
    }

    errno = ENOENT;
    return -1;
}
