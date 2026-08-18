#ifndef WORD_FREQ_H
#define WORD_FREQ_H

typedef struct {
	char* word;
	unsigned int count;
} WordEntry;

typedef struct {
	WordEntry* entries;
	unsigned int count;
	unsigned int capacity;
}WordFrequency;


void init_word_frequency(WordFrequency *wf);
void add_word(WordFrequency *wf,const char *word);
#endif