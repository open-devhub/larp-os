#include <stdio.h>
#include <string.h>
#include "include/bootloader.h"
#include "include/version.h"
int main(){
    bootloader();
    char user_input[50] = "";
    char larper_whoami[20] = "master larper";
    char hostname[20] = "larper";
    printf("Welcome To Larp OS\n");
    while (1){
        printf("larp-os@%s $ ",hostname);
        fgets(user_input,sizeof(user_input),stdin);
        user_input[strcspn(user_input,"\n")] = '\0';
        if (strcmp(user_input,"exit") == 0){
            printf("Exiting Larp OS...\n");
            break;
        }
        else if (strcmp(user_input,"whoami") == 0){
            printf("%s\n",larper_whoami);
        }
        else if (strcmp(user_input,"version") == 0){
            printf("%s\n",VERSION);
        }


    }
    return 0;
}
