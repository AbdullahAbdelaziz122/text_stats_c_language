#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *input = stdin;  // Default: read from stdin
    
    // If a filename is provided, open it
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
    }
    
    // Process the input
    Statistics stats = {0, 0, 0, 0};  // Initialize to zero
    char buffer[BUFFER_SIZE];
    
    while (fgets(buffer, sizeof(buffer), input) != NULL) {
        // Remove trailing newline for counting (but keep it for line count)
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Update statistics for this line
        update_stats(buffer, &stats);
    }
    
    // Print results
    print_stats(&stats);
    
    // Clean up
    if (input != stdin) {
        fclose(input);
    }
    
    return EXIT_SUCCESS;
}