#include <stdio.h>

int main()
{
    long val = 7321;
    long* ptr = &val;
    printf("%ld\n", ptr[0]);
    return 0;
}