#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // execve
#include <libgen.h> // pathfind

int myexecvpe(char* filename, char* argv[], char* envp[])
{
    if (strchr(filename, (int)'/') != NULL && !access(filename, X_OK))
    {
        if (execve(filename, argv, envp))
            return -1;
    }
    else
    {
        char* env_path;
        if ((env_path = getenv("PATH")) != NULL)
        {
            char* path = pathfind(env_path, filename, "x");

            if (path != NULL)
            {
                if (execve(path, argv, envp))
                    return -1;
            }
        }
    }

    errno = ENOENT;
    return -1;
}
