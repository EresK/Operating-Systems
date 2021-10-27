#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <unistd.h>

extern char* optarg;
extern int optind, opterr, optopt;

int main(int argc, char* argv[], char* envp[])
{
    char* options = "ispuU:cC:dvV:";
    int c, k;

    // U:
    long new_ulimit;

    // d
    char* buff;
    long pathsize = pathconf(".", _PC_PATH_MAX);

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
                fprintf(stderr, "Error: %s\n", strerror(errno));
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
                fprintf(stderr, "Error: incorrect new ulimit parameter\n");
            else
            {
                if(ulimit(UL_SETFSIZE, new_ulimit) == -1)
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                else
                    printf("Success set new ulimit\n");
            }
            break;

        case 'c':
            if(getrlimit(RLIMIT_CORE, &proc_rlim))
                fprintf(stderr, "Error: %s\n", strerror(errno));
            else
                printf("Size of core file %lu\n", proc_rlim.rlim_cur);
            break;

        case 'C':
            if(getrlimit(RLIMIT_CORE, &proc_rlim))
                fprintf(stderr, "Error: %s\n", strerror(errno));
            else
            {
                proc_rlim.rlim_cur = strtoul(optarg, &end, 10);
                if(setrlimit(RLIMIT_CORE, &proc_rlim))
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                else
                    printf("Success setrlimit\n");
            }
            break;

        case 'd':
            if((buff = malloc((size_t)pathsize)))
            {
                if((getcwd(buff, (size_t)pathsize)))
                    printf("%s\n", buff);
                else
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                break;
                free(buff);
            }
            else
                fprintf(stderr, "Error: %s\n", strerror(errno));

        case 'v':
            k = 0;
            while (envp[k] != 0)
            {
                printf("%s\n", envp[k]);
                k++;
            }
            break;

        case 'V':
            if(putenv(optarg))
                fprintf(stderr, "Error: %s\n", strerror(errno));
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
