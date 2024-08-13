#ifndef __WORDLISTS_H__
#define __WORDLISTS_H__

#include "common.h"

struct wordlists{
    struct list *words;
    size_t count;
};

struct dictlists{
    struct list *dicts;
    size_t count;
};


void add_dictlists(struct dictlists *dict, const char *value);

void add_wordlists(struct wordlists *word, const char *value);

struct wordlists *read_wordlists(const char *filename);

void free_dictlists(struct dictlists *dict);

void free_wordlists(struct wordlists *word);

#endif
