#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "wordlists.h"
#include "errors.h"



static void add_wordlists(wordlists *word, const char *value){
    word->words = add_first(word->words, value);
    word->count++;
}

wordlists *read_wordlists(const char *filename){
    FILE *file = NULL;
    wordlists *word = NULL;
    char buf[LEN_BUF] = {'\0'};
    if((file = fopen(filename, "r")) != NULL){
        if((word = (wordlists*)calloc(1, sizeof(wordlists))) != NULL){
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


void clear_wordlists(wordlists *word){
    if(word != NULL){
        free_list(&word->words);
        word->words = NULL;
        word->count = 0;
    }
}
