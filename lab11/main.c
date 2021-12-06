#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/fcntl.h>

// The program does not work

int main(int argc, char* argv[], char* envp[])
{
    char *nargv[ ] = {"newpgm", "parm1", "parm2", "parm3", (char *) 0};

    myexecvpe("myprog", nargv, nargv);

    return 0;
}

int myexecvpe(const char* path, char* const argv[], char* const envp[])
{
    char* env_path;
    if ((env_path = getenv("PATH")) == NULL)
    {
        fprintf(stderr, "Error: can not getenv PATH");
        return -1;
    }
    else
    {
        printf("%s\n", env_path);
        char new_path[_PC_PATH_MAX];

        char* token = strtok(env_path, ":");
        while (token)
        {
            strcpy(new_path, token);
            new_path[strlen(token)] = '/';
            strcpy((new_path + strlen(token) + 1), path);
            
            if (!access(new_path, F_OK))
            {
                if (execve(new_path, argv, envp))
                {
                    perror("Error: execve failed\n");
                    return -1;
                }
            }
            
            token = strtok(NULL, ":");
        }
    }

    fprintf(stderr, "Error string\n");

    exit(0);
}
