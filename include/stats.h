#ifndef STATS_H
#define STATS_H


typedef struct {
    int words;
    int lines;
    int characters;
    int sentences;
} Statistics;


void update_stats(const char *lines, Statistics *stats);
void print_stats(const Statistics *stats);

#endif