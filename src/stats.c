#include "stats.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
int count_words(const char *line){
    int count = 0;
    bool is_word = false;

    for(int i = 0; line[i] != '\0'; i++){
        if(isalnum(line[i])){
            if(!is_word){
                count++;
                is_word = true;
            }
        }else{
            is_word = false;
        }
    }
    return count;
}

static int count_sentences(const char *line){
    int count = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        if(line[i]== '.' || line[i]== '!' || line[i] == '?'){
            count++;
        }
    }
    return count;
}



void update_stats(const char *line, Statistics *stats){
    stats->characters += strlen(line);
    stats->lines++;
    stats->words += count_words(line);
    stats->sentences += count_sentences(line);
}

void print_stats(const Statistics *stats) {
    printf("Characters: %d\n", stats->characters);
    printf("Words:      %d\n", stats->words);
    printf("Lines:      %d\n", stats->lines);
    printf("Sentences:  %d\n", stats->sentences);
}

