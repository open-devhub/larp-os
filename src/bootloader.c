#include <stdio.h>
#include <stdlib.h>
#include <bootloader.h>


void bootloader(){
    int bootloader_option;
    printf("------------------------\n");
    printf("  LarpLoad 1.6.7\n");
    printf("------------------------\n");
    printf("Boot Option's\n");
    printf("1 : [ Larp OS ]\n");
    printf("Choose Boot Option\n $ > ");

    char buff[3];
    fgets(buff, sizeof(buff), stdin);
    bootloader_option = buff[0] - '0';

    if (bootloader_option == 1){
        printf("\nLarp Is Loading...\n");
        printf("Loading Larp OS...\n");
    } else {
        printf("Boot Entry Doesnt Exist\n");
        exit(1);
    }
}
