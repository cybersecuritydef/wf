#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wordlists.h"
#include "common.h"


static void add_wordlists(wordlists *word, const char *value){
    word->words = add_first(word->words, value);
    word->count++;
}

wordlists *read_wordlists(const char *filename){
    FILE *file = NULL;
    wordlists *word = NULL;
    char buf[LEN_BUF] = {'\0'};
    if((file = fopen(filename, "r")) != NULL){
        if((word = (wordlists*)malloc(sizeof(wordlists))) != NULL){
            word->count = 0;
            word->words = NULL;
            while(fgets(buf, sizeof(buf), file) != NULL){
                buf[strlen(buf) - 1] = '\0';
                add_wordlists(word, buf);
            }
            fclose(file);
            return word;
        }
        else{
            fclose(file);
            die("[-] Error allocation memory!");
        }
    }
    return NULL;
}


void free_wordlists(wordlists *word){
    free_list(&word->words);
    word->count = 0;
}
