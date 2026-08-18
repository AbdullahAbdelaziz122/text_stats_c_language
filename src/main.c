#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include <word_freq.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    FILE *input = stdin; 
    
    
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
    }
    
    
    Statistics stats = {0, 0, 0, 0};  
    char buffer[BUFFER_SIZE];
    
	WordFrequency wf;
	init_word_frequency(&wf);
	
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        // Remove trailing newline for counting (but keep it for line count)
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Update statistics for this line
        update_stats(buffer, &stats);
		
		// Tokenize and add words
		char *token = strtok(buffer, " .,!?;:\t\n");
		while(token != NULL){
			add_word(&wf, token);
			token = strtok(NULL, " .,!?;:\t\n");

		}
    }
    
    // Print results
    print_stats(&stats);
	// Sort and print word frequencies
    sort_word_frequency(&wf);
    print_top_words(&wf, 10);
	 
    // Clean up
    if (input != stdin) {
        fclose(input);
    }

    return EXIT_SUCCESS;
}



// Testing add word function 
//int main(){
//	
//	
//	WordFrequency wf;
//	
//	init_word_frequency(&wf);
//	
//	add_word(&wf, "hello");
//	add_word(&wf, "world");
//	add_word(&wf, "hello");
//
//	printf("Count: %d\n", wf.count);  // Should be 2 (hello, world)
//	printf("hello count: %d\n", wf.entries[0].count);  // Should be 2
//	printf("world count: %d\n", wf.entries[1].count);  // Should be 1
//	
//}