#include "word_freq.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void init_word_frequency(WordFrequency *wf){

	wf->capacity = 0;
	wf->count = 0;
	wf->entries = NULL;	
	
}


void add_word(WordFrequency *wf,const char *word){
	
	// check if word is already in wordFrequency
	for (unsigned int i = 0; i < wf->count; i++) {
		if (strcmp(wf->entries[i].word, word) == 0) {
			wf->entries[i].count++;
			return;
		}
	}
	
	// if not
	// check if there is capacity for more.
	if(wf->count >= wf->capacity){
		wf->capacity = (wf->capacity == 0) ? 4 : wf->capacity * 2;
		wf->entries = realloc(wf->entries, wf->capacity * sizeof(WordEntry));
		if (!wf->entries) {
		            // Handle allocation failure
		            fprintf(stderr, "Memory allocation failed\n");
		            return;
		        }
	}
	
	// add word
	char *copy = strdup(word);
	
	if(!copy){
		fprintf(stderr, "Memory allocation failed for word: %s\n", word);
		return;	
	}
	
	
	wf->entries[wf->count].word = copy;
	wf->entries[wf->count].count += 1;
	wf->count +=1;
	
	
}


static int compare_entries(const void* a, const void* b){
	const WordEntry *entry_a = (const WordEntry*)a;
	const WordEntry *entry_b = (const WordEntry*)b;
	
	// sort by count
	if(entry_b->count != entry_a->count){
		return entry_b->count - entry_a->count;
	}
	
	// if counts equal sort alphabetically
	return strcmp(entry_a->word, entry_b->word);
}



void sort_word_frequency(WordFrequency *wf){
	if(wf->count > 0){
		qsort(wf->entries, wf->count, sizeof(WordEntry), compare_entries);
	}
	
}


void print_top_words(const WordFrequency *wf, unsigned int top_n){
	
	if(wf->count == 0){
		printf("No Words found.\n");
		return;
	}
	
	
	printf("\nTop %d most frequent words:\n", top_n);
	    printf("-----------------------------\n");
	    
	    int limit = (top_n < wf->count) ? top_n : wf->count;
	    for (int i = 0; i < limit; i++) {
	        printf("%4d: %-15s %d\n", i + 1, wf->entries[i].word, wf->entries[i].count);
	    }
	
	
}


void free_word_frequency(WordFrequency *wf){
	for (unsigned int i = 0; i <wf->count; i++) {
		free(wf->entries[i].word);
	}
	free(wf->entries);
	wf->entries = NULL;
	wf->count = 0;
	wf->capacity =0;
	
}
