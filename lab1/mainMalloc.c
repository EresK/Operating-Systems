#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <unistd.h>

extern char* optarg;
extern int optind, opterr, optopt;
extern char** environ;

int main(int argc, char* argv[], char* envp[])
{
    char* options = "ispuU:cC:dvV:";
    int c, k;

    // U:
    long new_ulimit;

    // d
    char* buff;

    // cC:
    char* end;
    unsigned long new_csize;
    struct rlimit proc_rlim;

    while ((c = getopt(argc, argv, options)) != -1)
    {
        switch (c)
        {
        case 'i':
            printf("Real uid: %u, effective uid: %u\n", getuid(), geteuid());
            break;

        case 's':
            if(setpgid(getpgrp(), getpid()))
                perror("Error: can not setpgid\n");
            else
                printf("Success setpgid\n");
            break;

        case 'p':
                printf("pid: %u\nppid: %u\npgid: %u\n", getpid(), getppid(), getpgrp());
            break;

        case 'u':
            printf("Maximum file size: %ld\n", ulimit(UL_GETFSIZE));
            break;

        case 'U':
            if(!(new_ulimit = atol(optarg)))
                perror("Error: atol failed\n");
            else
            {
                if(ulimit(UL_SETFSIZE, new_ulimit) == -1)
                    perror("Error: can not set new SETFSIZE ulimit\n");
                else
                    printf("Success set new ulimit\n");
            }
            break;

        case 'c':
            if(getrlimit(RLIMIT_CORE, &proc_rlim))
                perror("Error: failed getrlimit\n");
            else
                printf("Size of core file %lu\n", proc_rlim.rlim_cur);
            break;

        case 'C':
            if(getrlimit(RLIMIT_CORE, &proc_rlim))
                perror("Error: failed getrlimit\n");
            else
            {
                proc_rlim.rlim_cur = strtoul(optarg, &end, 10);
                if(setrlimit(RLIMIT_CORE, &proc_rlim))
                    perror("Error: failed setrlimit\n");
                else
                    printf("Success setrlimit\n");
            }
            break;

        case 'd':
            if(!(buff = getcwd(NULL, 0)))
                perror("Error: can not allocate memory getcwd\n");
            else
            {
                printf("%s\n", buff);
                free(buff);
            }
            break;

        case 'v':
            k = 0;
            while (environ[k] != 0)
            {
                printf("%s\n", environ[k]);
                k++;
            }
            break;

        case 'V':
            if(putenv(optarg))
                perror("Error: failed putenv\n");
            else
                printf("Success putenv\n");
            break;

        case '?':
            fprintf(stderr, "Incorrect option %c\n", optopt);
            break;
        }
    }

    return 0;
}
