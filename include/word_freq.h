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
void sort_word_frequency(WordFrequency *wf);
void print_top_words(const WordFrequency *wf, unsigned int top_n);
void free_word_frequency(WordFrequency *wf);

#endif