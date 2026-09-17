#include <stdio.h>
#include <string.h>
#include "include/bootloader.h"
#include "include/version.h"
#include "include/hostname.h"
#include "include/os_name.h"
#include "include/split_string.h"
int main(){
    bootloader();
    char user_input[50] = "";
    char argv[6][64];
    char larper_whoami[20] = "master larper";
    printf("Welcome To Larp OS\n");
    while (1){
        memset(user_input,0,sizeof(user_input));
        for (int i = 0; i < 6; i++){
            memset(argv[i],0,64);
        }

        printf("larp-os@%s $ ",HOSTNAME);
       if (fgets(user_input,sizeof(user_input),stdin) == NULL){
           break;
       }
        user_input[strcspn(user_input,"\n")] = '\0';
        int argc = split_string(user_input,&argv);
        if (strcmp(argv[0],"exit") == 0){
            printf("Exiting Larp OS...\n");
            break;
        }
        else if (strcmp(argv[0],"whoami") == 0){
            printf("%s\n",larper_whoami);
        }
        else if (strcmp(argv[0],"version") == 0){
            printf("%s\n",VERSION);
        }
        else if (strcmp(argv[0],"uname") == 0){
            if (strcmp(argv[1],"-n") == 0){
                printf("%s\n",HOSTNAME);
            }
            else{
                printf("%s %s\n",NAME,VERSION);
            }

        }
        else if (strncmp(argv[0],"echo",4) == 0){
           char *echo_pointer = &user_input[5];
           printf("%s\n",echo_pointer);
       }
        else if (strlen(user_input) == 0){
            continue;
        }


    }
    return 0;
}
