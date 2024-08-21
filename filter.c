#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "filter.h"


bool number_filter(char *match, const size_t num){
    char *delim = NULL;
    char *value = NULL;
    if(match != NULL){
        value = strtok_r(match, ",", &delim);
        while(value != NULL){
            if(strtol(value, NULL, 10) == num)
                return true;
            value = strtok_r(NULL, ",", &delim);
        }
    }
    return false;
}


bool string_filter(char *match, const char *content){
    char *delim = NULL;
    char *value = NULL;
    if(match != NULL){
        value = strtok_r(match, ",", &delim);
        while(value != NULL){
            if(strstr(content, value))
                return true;
            value = strtok_r(NULL, ",", &delim);
        }
    }
    return false;
}
