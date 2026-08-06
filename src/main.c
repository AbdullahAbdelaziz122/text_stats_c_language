/*
 ============================================================================
 Name        : Text-Stats
 Author      : Abdullah Abdelaziz
 Version     :
 Copyright   : MIT License
 Description : Parse Text and give stats
 ============================================================================
 */


#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *input_file = NULL;
    char buffer[100];

    if(argc > 1){
        input_file = fopen(argv[1], "r");

        if(!input_file){
            perror("error opening file");
            return 1;
        }
    }

    int i = 0;
    while (fgets(buffer, 100, input_file)) {
        i++;
        printf("%d: %s", i, buffer);
    }





    return 0;
}



