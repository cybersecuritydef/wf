#ifndef __WORDLISTS_H__
#define __WORDLISTS_H__

#include "common.h"

typedef struct{
    struct list *words;
    size_t count;
}wordlists;

typedef struct{
    struct list *dicts;
    size_t count;
}dictlists;


void add_dictlists(dictlists *dict, const char *value);

void add_wordlists(wordlists *word, const char *value);

wordlists *read_wordlists(const char *filename);

void free_dictlists(dictlists *dict);

void free_wordlists(wordlists *word);

#endif
