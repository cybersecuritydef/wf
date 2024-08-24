#ifndef __WORDLISTS_H__
#define __WORDLISTS_H__

#include "list.h"

#define LEN_BUF 512

typedef struct{
    struct list *words;
    size_t count;
}wordlists;


wordlists *read_wordlists(const char *filename);

void clear_wordlists(wordlists *word);

#endif
