#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    time_t now;

    time(&now);
    printf("%s", ctime(&now));

    if (putenv("TZ=America/Los_Angeles"))
    {
        perror("Error: putenv TZ failed\n");
        exit(1);
    }

    time(&now);
    printf("%s", ctime(&now));

    return 0;
}
