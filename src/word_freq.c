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