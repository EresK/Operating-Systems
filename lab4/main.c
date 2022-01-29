#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    char* lines[BUFSIZ] = {0};
    int cnt = 0;

    char buff[BUFSIZ];
    size_t length;

    while (fgets(buff, BUFSIZ, stdin) != NULL && (cnt < BUFSIZ))
    {
        length = strlen(buff);

        if (length > 0 && buff[0] == '.') {
            break;
        }
        else if (length > 0) {
            char* ptr;

            if ((ptr = malloc((length + 1) * sizeof(char))) == NULL) {
                perror("Can not allocate memory");
                break;
            }
            strcpy(ptr, buff);

            lines[cnt++] = ptr;
        }
    }

    for (int i = 0; (lines[i] != NULL) && (i < BUFSIZ); i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    return 0;
}
