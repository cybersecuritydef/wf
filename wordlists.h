#ifndef __WORDLISTS_H__
#define __WORDLISTS_H__

#include "common.h"

typedef struct{
    struct list *words;
    size_t count;
}wordlists;

typedef struct{
    struct list *ext;
    size_t count;
}extlists;

wordlists *read_wordlists(const char *filename);

void clear_wordlists(wordlists *word);

#endif
