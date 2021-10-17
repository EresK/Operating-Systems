#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ulimit.h>
#include <unistd.h>

extern char* optarg;
extern int optind, opterr, optopt;

int main(int argc, char** argv)
{
    char* options = "ispuU:n";
    char* U_ptr;
    int c;
    long new_ulimit;
    
    printf("argc equals %d\n", argc); // is it really nead?
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
            
            /*case 'U':
                if(new_ulimit = atol(optarg))
                    perror("Error: can not atol argument\n");
                else
                {
                    if(ulimit(UL_SETFSIZE, new_ulimit) == -1)
                        fprintf("Error: %s\n", strerror(errno));
                    else
                        printf("success SETFSIZE ulimit\n");
                }
                break;*/
            case 'U':
                U_ptr = optarg;
                break;

            case '?':
                printf("incorrect option %c\n", optopt);
                break;
        }
    }

    return 0;
}