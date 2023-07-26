#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

long findMax(long* a, long n, long* i) {
    if (a == NULL || n <= 0) {
        if (i != NULL)
            *i = -1;

        return LONG_MIN;
    }

    long maxValue = LONG_MIN;
    long minIndex = 0;

    for (long k = 0; k < n; k++) {
        if (a[k] > maxValue) {
            maxValue = a[k];
            minIndex = k;
        }
    }

    if (i != NULL)
        *i = minIndex;

    __asm__("mov %0, %%eax\n"
        : /* No outputs. */
        : "rm" (maxValue)
    );
}

void printArray(long* numbers, long n) {
    if (numbers == NULL || n <= 0)
        return;
    
    for (long i = 0; i < n; i++) {
        if (i == (n-1))
            printf("%ld\n", numbers[i]);
        else
            printf("%ld, ", numbers[i]);
    }
}

void test() {
    long max = LONG_MIN;
    long i = -1;
    long numbers[10] = {200, 150, 100, 50, 0, 0, 200, -1, -10, -100};

    printArray(numbers, 10);
    printf("Test:\nbefore max: %ld, index: %ld\n", max, i);

    /* 1) assigning result */
    max = findMax(numbers, 10, &i);

    /* 2) extracting result from eax register
        Warning, check eax register size and long size!
    */
    // findMax(numbers, 10, &i);

    // __asm__("mov %%eax, %0"
    //     : "=m" (max)
    // );

    printf("after max: %ld, index: %ld\n", max, i); 
}

int main() {
    test();

    return 0;
}