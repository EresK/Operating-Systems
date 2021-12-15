#include <stdio.h>

int main(int argc, char* argv[], char* envp[])
{
    printf("My test program\n");

    printf("My argv:\n");
    int k = 0;
    while (argv[k] != NULL)
    {
        printf("%s\n", argv[k]);
        k++;
    }

    printf("My envp:\n");
    k = 0;
    while (envp[k])
    {
        printf("%s\n", envp[k]);
        k++;
    }

    return 0;
}
