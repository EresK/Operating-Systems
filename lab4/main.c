#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* strlist[BUFSIZ];
    int count = 0;

    char line[BUFSIZ];
    size_t length;

    while (fgets(line, BUFSIZ, stdin) != NULL && (count < BUFSIZ)) {
        length = strlen(line);
        if (length > 0 && line[0] == '.') {
            break;
        }
        else if (length > 0) {
            char* pt;

            if ((pt = malloc(length + 1)) == NULL) {
                perror("Error: can not allocate memory");
                break;
            }
            strcpy(pt, line);
            strlist[count++] = pt;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%s", strlist[i]);
        free(strlist[i]);
    }

    return 0;
}
