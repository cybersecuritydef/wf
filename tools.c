#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tools.h"



char *strrep(const char *str, const char *oldstr, const char *newstr){
    char *nstr = NULL;
    char *tmp = NULL;
    size_t len = 0;
    if(str != NULL && oldstr != NULL && newstr != NULL){
        len = (strlen(str) - strlen(oldstr)) + strlen(newstr);
        if((tmp = strstr(str, oldstr)) != NULL){
            if((nstr = (char*)calloc(len + 1, sizeof(char))) != NULL){
                strncat(nstr, str, tmp - str);
                strcat(nstr, newstr);
                strcat(nstr, (tmp + strlen(oldstr)));
                return nstr;
            }
        }
    }
    return NULL;
}


char *strrepeat(const char *str, const size_t depth){
    char *repeats = NULL;
    size_t i = 0;
    if(str != NULL && depth > 0){
        if((repeats = (char*)calloc((strlen(str) * depth + 1), sizeof(char))) != NULL){
            for(i = 0; i < depth; i++)
                strcat(repeats, str);
            return repeats;
        }
    }
    return NULL;
}


char *strupper(const char *str){
    char *upper = NULL;
    int i = 0;
    if(str != NULL){
        if((upper = (char*)calloc(strlen(str) + 1, sizeof(char))) != NULL){
            for(i = 0; str[i] != '\0'; i++)
                upper[i] = toupper(str[i]);
            upper[i] = '\0';
            return upper;
        }
    }
    return NULL;
}

char *strlower(const char *str){
    char *lower = NULL;
    int i = 0;
    if(str != NULL){
        if((lower = (char*)calloc(strlen(str) + 1, sizeof(char))) != NULL){
            for(i = 0; str[i] != '\0'; i++)
                lower[i] = tolower(str[i]);
            lower[i] = '\0';
            return lower;
        }
    }
    return NULL;
}


char *strchrupper(const char *str, const int index){
    char *upper = NULL;
    int i = 0;
    if(str != NULL && index >= 0){
        if((upper = (char*)calloc(strlen(str) + 1, sizeof(char)))){
            for(i = 0; str[i] != '\0'; i++){
                if(i == index)
                    upper[i] = toupper(str[i]);
                else
                    upper[i] = str[i];
            }
            upper[i] = '\0';
            return upper;
        }
    }
    return NULL;
}

char *strchrlower(const char *str, const int index){
    char *lower = NULL;
    int i = 0;
    if(str != NULL && index >= 0){
        if((lower = (char*)calloc(strlen(str) + 1, sizeof(char))) != NULL){
            for(i = 0; str[i] != '\0'; i++){
                if(i == index)
                    lower[i] = tolower(str[i]);
                else
                    lower[i] = str[i];
            }
            lower[i] = '\0';
            return lower;
        }
    }
    return NULL;
}
