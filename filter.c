#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "filter.h"


static struct list *split(char *match){
    struct list *ls = NULL;
    char *v = NULL;
    if(match){
        if(strchr(match, ',')){
            while((v = strtok_r(match, ",", &match))){
                ls = add_last(ls, v);
            }
        }
        else
            ls = add_last(ls, match);
        return ls;
    }
    return NULL;
}


bool filter_code(char *codes, const long code){
    return false;
}


bool filter_size(char *sizes, const size_t len){
    return false;
}


bool filter_word(char *words, const char *content){
    return false;
}
