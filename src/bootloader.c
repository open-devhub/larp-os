#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/bootloader.h"


void bootloader(){
    int bootloader_option;
    
    printf("Welcome To Larp OS LarpLoader (Bootloader)\n");
    printf("Boot Options\n");
    printf("1 : Larp OS\n");
    printf("Choose Boot Option\n $ ");

    char c = getch();
    bootloader_option = c - '0';
    
    if (bootloader_option == 1){
        printf("\nLarp Is Loading...\n");
        printf("Loading Larp OS...\n");
    }
    else{
        printf("Boot Entry Doesnt Exist\n");
        exit(1);
    }
}
