#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ulimit.h>
#include <unistd.h>

extern char* optarg;
extern int optind, opterr, optopt;

int main(int argc, char* argv[], char* envp[])
{
    char* options = "ispuU:cdvV:";
    char* buff[PATH_MAX];
    int c, k;
    long new_ulimit;
    
    printf("argc equals %d\n", argc); 
    while ((c = getopt(argc, argv, options)) != -1)
    {
        switch (c)
        {
            case 'i':
                printf("real uid: %u, effective uid: %u\n", getuid(), geteuid());
                break;

            case 's':
                if(setpgid(getpid(), getpid()))
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                else
                    printf("success setpgid\n");
                break;

            case 'p':
                printf("process id: %u\nparent process id: %u\nprocess group id: %u\n", getpid(), getppid(), getpgrp());
                break;
            
            case 'u':
                printf("maximum file size: %ld\n", ulimit(UL_GETFSIZE));
                break;
            
            case 'U':
                if((new_ulimit = atol(optarg)) <= 0)
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                else
                {
                    if(ulimit(UL_SETFSIZE, new_ulimit) == -1)
                        fprintf(stderr, "Error: %s\n", strerror(errno));
                    else
                        printf("success SETFSIZE ulimit\n");
                }
                break;

            case 'c':

                break;

            case 'd':
                if(getcwd(buff, sizeof(buff)))
                    printf("%s\n", buff);
                else
                    fprintf(stderr, "Error: %s\n", strerror(errno));
                break;

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
                    printf("success putenv\n");
                break;

            case '?':
                printf("incorrect option %c\n", optopt);
                break;
        }
    }

    return 0;
}