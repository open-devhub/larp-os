#include <string.h>
#include "include/split_string.h"


int split_string(char *str, char (*argv_ptr)[6][64]){
    int argc = 0;
    char *token = strtok(str," \t\n");

    while (token != NULL && argc < 6) {
        strncpy((*argv_ptr)[argc],token, 64);
        (*argv_ptr)[argc][63] = '\0';
        argc++;
        token = strtok(NULL," \t\n");
    }

    return argc;
}