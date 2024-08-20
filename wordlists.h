#ifndef __WORDLISTS_H__
#define __WORDLISTS_H__

#include "common.h"

typedef struct{
    struct list *words;
    size_t count;
}wordlists;


void add_wordlists(wordlists *word, const char *value);

wordlists *read_wordlists(const char *filename);

void free_wordlists(wordlists *word);

#endif
