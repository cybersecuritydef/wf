#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"


void push(struct stack **s, const char *value){
    struct stack *news = NULL;
    if((news = (struct stack*)calloc(1, sizeof(struct stack))) != NULL){
        news->data = strdup(value);
        news->next = (*s);
        (*s) = news;
    }
}

char *pop(struct stack **s){
    struct stack *cur = NULL;
    char *value = NULL;
    if(s != NULL && (*s) != NULL){
        cur = (*s);
        value = strdup(cur->data);
        (*s) = (*s)->next;

        free(cur->data);
        cur->data = NULL;

        free(cur);
        cur = NULL;
    }
    return value;
}

bool isempty(struct stack *s){
    if(s == NULL)
        return true;
    return false;
}
