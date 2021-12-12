#include <stdio.h>
#include <stdlib.h> // getenv
#include <string.h> // strtok
#include <unistd.h> // execve
#include <limits.h> // path_max

int myexecvpe(char* filename, char* argv[], char* envp[])
{
    char* env_path;
    if ((env_path = getenv("PATH")) == NULL)
    {
        fprintf(stderr, "Error: there is no PATH in environ\n");
    }
    else
    {
        char path[PATH_MAX];

        char* token = strtok(env_path, ":");        

        long filename_len = strlen(filename);
        long token_len;

        while (token)
        {
            token_len = strlen(token);

            if (sizeof(path) <= token_len + filename_len + 1)
            {
                fprintf(stderr, "Warning: path to the file, %s, is too long\n", filename);
                break;
            }

            strcpy(path, token);
            path[token_len] = '/';

            strcpy(path + token_len + 1, filename);

            if (!access(path, F_OK))
            {
                if (execve(path, argv, envp))
                {
                    perror("Error: execve failed\n");
                    return -1;
                }
            }

            token = strtok(NULL, ":");
        }
    }

    fprintf(stderr, "Error: file, %s, not found\n", filename);
    return -1;
}
