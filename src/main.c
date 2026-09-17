#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/vfs.h"
#include "include/bootloader.h"
#include "include/split_string.h"


#define OS_NAME         os_info[0]
#define OS_VERSION      os_info[1]
#define OS_HOSTNAME     os_info[2]

int main() {
    /*
        /etc/os-info format (each entry is separated by a semicolon)
        [os name];[os version];[hostname]
    */
    char *temp = calloc(1, 72);
    char os_info[3][24];

    VFSNode *config_node = vfs_open("/etc/os-info", VFS_MODE_READ);
    if (config_node == NULL) {
        free(temp);

        printf("Failed to open /etc/os-info\n");
        return -1;
    }

    int r = vfs_read(config_node, temp, 64);
    int os_info_split_count = split_string(temp, ';', 3, 24, os_info);
    
    printf("%d %s\n", r, temp);
    free(temp);
    if (os_info_split_count != 3) {
        printf("Error: failed to parse /etc/os-info: %d\n", os_info_split_count);
        return -1;
    }    

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
            }
            else {
                printf("uname: Invalid argument\n");
            }

        } else if (strncmp(argv[0], "echo", 4) == 0) {
            if (strcmp(argv[1],"--help") == 0){
                printf("usage: echo [text] \n");
            } else if (argc < 2) {
                printf("\n");
            } else{
                for (int i = 1; i < argc; i++) {
                    fputs(argv[i], stdout);

                    if (i < argc - 1) putchar(' ');
                }
                putchar('\n');
            }


        } else if (strlen(user_input) == 0){
            continue;
        } else {
            printf("Unknown command: %s\n", argv[0]);
        }
    }

    return 0;
}
