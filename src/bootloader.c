#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/bootloader.h"
void bootloader(){
    int bootloader_option;
    char input_buffer[20] = "";
    printf("Welcome To Larp OS LarpLoader (Bootloader)\n");

    printf("Boot Options\n");
    printf("1 : Larp OS\n");
    printf("Choose Boot Option\n $ ");
    fgets(input_buffer,sizeof(input_buffer),stdin);
    input_buffer[strcspn(input_buffer,"\n")] = '\0';
    bootloader_option = atoi(input_buffer);
    if (bootloader_option == 1){
        printf("Larp Is Loading...\n");
        printf("Loading Larp OS...\n");



    }
    else{
        printf("Boot Entry Doesnt Exist\n");
        exit(1);


    }


}
