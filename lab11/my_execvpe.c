#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int my_execvpe(char* path, char* argv[], char* envp[])
{
    char* env_path;
    if ((env_path = getenv("PATH")) == NULL)
    {
        fprintf(stderr, "Error: can not getenv PATH");
    }
    else
    {
        char new_path[_PC_PATH_MAX];

        char* token = strtok(env_path, ":");
        while (token)
        {
            strcpy(new_path, token);
            size_t token_len = strlen(token);

            new_path[token_len] = '/';
            strcpy(new_path + token_len + 1, path);

            if (!access(new_path, F_OK))
            {
                if (execve(path, argv, envp))
                {
                    perror("Error: execve failed");
                    return -1;
                }
            }

            token = strtok(NULL, ":");
        }
    }

    fprintf(stderr, "Error: file %s did not find\n", path);
    return -1;
}
