#include <stdio.h>
#include <string.h>
#include "include/bootloader.h"
#include "include/version.h"
#include "include/split_string.h"


int main() {
    char user_input[50] = "";
    char argv[6][64];
    char larper_whoami[20] = "master larper";

    bootloader();
    printf("Welcome to %s\n", OS_NAME);
    
    while (1){
        memset(user_input, 0, sizeof(user_input));
        memset(argv, 0, 6 * 64);

        printf("larp-os@%s $ ", OS_HOSTNAME);
        if (fgets(user_input, sizeof(user_input), stdin) == NULL){
            break;
        }

        user_input[strcspn(user_input, "\n")] = '\0';
        int argc = split_string(user_input, ' ', 6, 64, argv);

        if (strcmp(argv[0], "exit") == 0){
            printf("Exiting Larp OS...\n");
            break;

        } else if (strcmp(argv[0], "whoami") == 0){
            printf("%s\n", larper_whoami);

        } else if (strcmp(argv[0], "version") == 0){
            printf("%s\n", OS_VERSION);

        } else if (strcmp(argv[0], "uname") == 0){
            if (strcmp(argv[1], "-n") == 0){
                printf("%s\n", OS_HOSTNAME);
            } else if (argc == 1) {
                printf("%s %s\n", OS_NAME, OS_VERSION);
            } else {
                printf("uname: Invalid argument\n");
            }

        } else if (strncmp(argv[0], "echo", 4) == 0) {
            for (int i = 1; i < argc; i++) {
                fputs(argv[i], stdout);

                if (i < argc - 1) putchar(' ');
            }
            putchar('\n');

        } else if (strlen(user_input) == 0){
            continue;
        } else {
            printf("Unknown command: %s\n", argv[0]);
        }
    }

    return 0;
}
