#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "filter.h"


bool filter(char *match, const size_t v){
    char *delim = NULL;
    char *value = NULL;
    if(match){
        value = strtok_r(match, ",", &delim);
        while(value){
            if(strtol(value, NULL, 10) == v)
                return true;
            value = strtok_r(NULL, ",", &delim);
        }
    }
    return false;
}


bool filter_word(char *match, const char *content){
    char *delim = NULL;
    char *value = NULL;
    if(match){
        value = strtok_r(match, ",", &delim);
        while(value){
            if(strstr(content, value))
                return true;
            value = strtok_r(NULL, ",", &delim);
        }
    }
    return false;
}
